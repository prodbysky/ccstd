#define NOB_IMPLEMENTATION
#include "nob.h"

int main(int argc, char** argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);
    Nob_Cmd str_build = {0};
    nob_cmd_append(&str_build, "gcc", "-ggdb", "-c", "src/string.c",
                   "src/arena.c", "src/lcg.c");
    if (!nob_cmd_run_sync(str_build)) {
        nob_log(NOB_ERROR,
                "Failed to build src/string.c || src/arena.c || src/lcg.c");
        return 1;
    }

    Nob_Cmd static_lib_build = {0};
    nob_cmd_append(&static_lib_build, "ar", "rcs", "libccstd.a", "string.o",
                   "arena.o", "lcg.o");
    if (!nob_cmd_run_sync(static_lib_build)) {
        nob_log(NOB_ERROR, "Failed to archive libccstd.a");
        return 1;
    }

    Nob_Cmd build_example = {0};
    nob_cmd_append(&build_example, "gcc", "tests.c", "-o", "tests", "-ggdb",
                   "-L", ".", "-l", "ccstd");

    if (!nob_cmd_run_sync(build_example)) {
        nob_log(NOB_ERROR, "Failed to build tests.c");
        return 1;
    }

    Nob_Cmd cleanup = {0};
    nob_cmd_append(&cleanup, "rm", "string.o", "arena.o", "lcg.o");
    nob_cmd_run_sync(cleanup);
}
