#include <iostream>

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/screen/string.hpp"

#include "llm.hpp"

int main(int argc, char** argv) {
  auto params = ex::parse_params(argc, argv);

  auto ctx = ex::load_model(params);
  if (ctx == NULL) {
    fprintf(stderr, "%s: error: failed to load model '%s'\n", __func__,
            params.model.c_str());
    return 1;
  }

  auto _i0 = params.model.find_last_of('/');
  auto model_name = params.model.substr(_i0 + 1);

  using namespace ftxui;

  std::string transcript;
  Component txt_transcript = TextArea(&transcript, {});

  std::string prompt;

  Component input_prompt = TextArea(&prompt, {}) | size(HEIGHT, EQUAL, 10);
  Component btn_submit = Button("Submit", [&] {
    if (prompt.empty())
      return;
    transcript += prompt;
    transcript += "\n";
    // todo onclick
  });

  auto logical = Container::Vertical({
      txt_transcript,
      input_prompt,
      Container::Horizontal({
          btn_submit,
      }),
  });

  auto renderer = Renderer(logical, [&] {
    auto document =  //
        vbox({
            window(text("Transcript"), txt_transcript->Render()) | flex,

            text(model_name) | center,
            window(text("Prompt"), input_prompt->Render()),
            hflow({
                btn_submit->Render(),
            }),
            hflow({
                text("seed: " + std::to_string(params.seed)),
            }),
        });

    // Limit the size of the document to 80 char.
    document = document | size(WIDTH, LESS_THAN, 80);
    return document;
  });

  auto screen = ScreenInteractive::TerminalOutput();
  screen.Loop(renderer);

  return EXIT_SUCCESS;
}
