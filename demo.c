#include <stdio.h>
#include <string.h>

#include "vec3.h"
#include "vec3_array.h"

int main() {
  Vec3 v1 = {1.23f, 4.56f, 7.89f};
  Vec3 v2 = {2.34f, 5.67f, 8.90f};

  Vec3Array vertices;
  initVec3Array(&vertices);
  writeVec3Array(&vertices, v1);
  writeVec3Array(&vertices, v2);

  printf("v1: (%f %f %f)\n", vertices.data[0].x, vertices.data[0].y,
         vertices.data[0].z);
  printf("v2: (%f %f %f)\n", vertices.data[1].x, vertices.data[1].y,
         vertices.data[1].z);

  freeVec3Array(&vertices);
  return 0;
}
