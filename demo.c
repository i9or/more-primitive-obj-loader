#include <stdio.h>
#include <string.h>

#include "./src/mesh.h"
#include "./src/obj_loader.h"

int main() {
    mesh bunny;
    if (!load_obj("./assets/bunny.obj", &bunny)) {
        return EXIT_FAILURE;
    }

    printf("Material library: %s\n", bunny.mtl_lib);
    printf("Name of the object: %s\n", bunny.name);
    printf("Number of vertices: %d\n", bunny.vertices.count);
    printf("Number of normals: %d\n", bunny.normals.count);

    free_mesh(&bunny);
    return EXIT_SUCCESS;
}
