#include <iostream>

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/screen/string.hpp"

#include "llm.hpp"

int main(int argc, char** argv) {
  auto params = ex::parse_params(argc, argv);
  using namespace ftxui;

  std::string prompt;
  Component input_prompt = TextArea(&prompt, {}) | size(HEIGHT, EQUAL, 10);

  auto logical = Container::Vertical({
      input_prompt,
  });

  auto renderer = Renderer(logical, [&] {
    auto document =  //
        vbox({
            text("LLaMA tui") | center,
            hflow({text("seed: " + std::to_string(params.seed))}),
            window(text("Prompt"), input_prompt->Render()),
        });

    // Limit the size of the document to 80 char.
    document = document | size(WIDTH, LESS_THAN, 80);
    return document;
  });

  auto screen = ScreenInteractive::TerminalOutput();
  screen.Loop(renderer);

  return EXIT_SUCCESS;
}
