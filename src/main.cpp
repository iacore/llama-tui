#include <iostream>

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/screen/string.hpp"

int main(void) {
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
