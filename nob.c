#define NOB_IMPLEMENTATION
#include "nob.h"

int main(int argc, char** argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);
    Nob_Cmd str_build = {0};
    nob_cmd_append(&str_build, "gcc", "-ggdb", "-Werror", "-Wextra", "-Wall",
                   "-I", "./include/", "-c", "src/str.c", "src/arena.c",
                   "src/lcg.c", "src/maths.c");
    if (!nob_cmd_run_sync(str_build)) {
        nob_log(NOB_ERROR, "Failed to build src/str.c || src/arena.c || "
                           "src/lcg.c || src/maths.c");
        return 1;
    }

    Nob_Cmd static_lib_build = {0};
    nob_cmd_append(&static_lib_build, "ar", "rcs", "libccstd.a", "str.o",
                   "arena.o", "lcg.o", "maths.o");
    if (!nob_cmd_run_sync(static_lib_build)) {
        nob_log(NOB_ERROR, "Failed to archive libccstd.a");
        return 1;
    }

    Nob_Cmd build_example = {0};
    nob_cmd_append(&build_example, "gcc", "-I", "./include/", "tests.c", "-o",
                   "tests", "-ggdb", "-L", ".", "-l", "ccstd");

    if (!nob_cmd_run_sync(build_example)) {
        nob_log(NOB_ERROR, "Failed to build tests.c");
        return 1;
    }

    Nob_Cmd cleanup = {0};
    nob_cmd_append(&cleanup, "rm", "str.o", "arena.o", "lcg.o", "maths.o");
    nob_cmd_run_sync(cleanup);
}
