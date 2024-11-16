#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "nob.h"

int main(int argc, char **argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);
    Cmd cmd = {0};
    cmd_append(&cmd, "cc", "-Wall", "-Wextra", "-ggdb", "-o", "randomart", "randomart.c", "-lm");

    if (!cmd_run_async(cmd)) return 1;

    return 0;
}
