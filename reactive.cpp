#include <iostream>
#include <sstream>
#include <string>
#include "board.hpp"
#include "reactive.hpp"

int main(int argc, char **argv) {
  if (reactive_start(argv[1]) == 1) {
    reactive_end();
    return 1;
  }
  Board board;
  for (;;) {
    board.output();
    reactive_write(board.to_json().c_str());
    std::istringstream is(reactive_read());
    int detach, attach;
    is >> detach >> attach;
    if (!board.play(detach, attach)) break;
  }
  board.output();
  reactive_write(board.to_json().c_str());
  reactive_end();
  std::cout << "Score: " << board.final_score() << std::endl;
  return 0;
}
