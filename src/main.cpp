#include "SDL3/SDL.h"
#include "fmt/base.h"
#include "jkr/cmd_options.hpp"
#include "jkr/compiler.hpp"
#include "jkr/hardware/cpu.hpp"
#include "sim_program.hpp"
#include <fmt/format.h>

int cmd(int argc, char* argv[]) {
  CMD_Options opts(argc, argv);

  if (!opts.success)
    return -1;

  if (opts.flags & CMD_Options::FLAG_COMPILE) {
    compile(opts.c_val, NULL);
  }
  return 0;
}

int main(int argc, char* argv[]) {
  fmt::println("YO");

  SimProgram program(800, 600);
  program.execute();

  return 0;
} 
