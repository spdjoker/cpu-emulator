#ifndef JKR_CMD_OPTIONS_HPP
#define JKR_CMD_OPTIONS_HPP

#include "fmt/base.h"

struct CMD_Options {
  enum FLAGS {
    FLAG_COMPILE    = 1,
    FLAG_EXECUTE    = 2,
    FLAG_OUTPUT     = 4,
    FLAG_MODES      = FLAG_COMPILE | FLAG_EXECUTE
  };

  unsigned char flags = 0;
  bool success = false;
  char* c_val;
  char* x_val;
  char* o_val;

  CMD_Options(int argc, char* argv[]) {
    if (argc == 1) {
      fmt::println("Usage: {} (-c <filename> | -x <filename> | -cx <filename>) [-o <filename>]", argv[0]);
      return;
    }

    for (int i = 1; i < argc; i++) {
      if (argv[i][0] != '-' || argv[i][1] == '\0') {
        fmt::println("Usage: {} (-c <filename> | -x <filename> | -cx <filename>) [-o <filename>]", argv[0]);
        return;
      }

      switch (argv[i][1]) {
        case 'c':
          if (flags & FLAG_COMPILE) {
            fmt::println(stderr, "Error: '-c' was defined multiple times");
            return;
          }
          if (flags & FLAG_EXECUTE) {
            fmt::println(stderr, "Error: '-c' and '-x' can only be used together as '-cx <filename>'");
            return;
          }
          if (argv[1][2] == 'x') {
            flags |= FLAG_EXECUTE;
          }
          if (i + 1 == argc) {
            fmt::println(stderr, "Error: correct option usage is '-{} <filename>'", flags & FLAG_EXECUTE ? "cx" : "c");
            return;
          }
          flags |= FLAG_COMPILE;
          c_val = argv[i + 1];
          i++;
          break;
        case 'x':
          if (flags & FLAG_EXECUTE) {
            fmt::println(stderr, "Error: '-x' was defined multiple times");
            return;
          }
          if (flags & FLAG_COMPILE) {
            fmt::println(stderr, "Error: '-c' and '-x' can only be used together as '-cx <filename>'");
            return;
          }
          if (i + 1 == argc) {
            fmt::println(stderr, "Error: correct option usage is '-x <filename>'");
            return;
          }
          flags |= FLAG_EXECUTE;
          x_val = argv[i + 1];
          i++;
          break;
        case 'o':
          if (flags & FLAG_OUTPUT) {
            fmt::println(stderr, "Error: '-o' was defined multiple times");
            return;
          }
          if (i + 1 == argc) {
            fmt::println(stderr, "Error: correct option usage is '-o <filename>'");
            return;
          }
          flags |= FLAG_OUTPUT;
          o_val = argv[i + 1];
          i++;
          break;
        default:
          return;
      }
    }

    success = flags & FLAG_MODES;
  }
};

#endif
