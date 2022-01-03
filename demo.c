#include <stdio.h>
#include <string.h>

#include "mesh.h"
#include "obj_loader.h"

int main() {
    mesh bunny;
    if (!load_obj("./assets/bunny.obj", &bunny)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
