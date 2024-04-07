#include "fmt/base.h"
#include "jkr/cmd_options.hpp"

int cmd(int argc, char* argv[]) {
  CMD_Options opts(argc, argv);

  if (!opts.success)
    return -1;

  return 0;
}

int main(int argc, char* argv[]) {
  fmt::println("YO");

  return 0;
} 
