//
//  loadObj.c
//  more-primitive-obj-loader
//
//  Created by Igor on 16/07/2023.
//

#include "loadObj.h"

static int parseIndex(const char *str) {
  return ((int)strtol(str, NULL, 10) - 1);
}

bool loadObj(const char *fileName, Mesh *m) {
  initMesh(m);

  FILE *pFile = fopen(fileName, "r");
  if (!pFile) {
    printf("Error loading file: %s\n", fileName);
    return false;
  }

  char line[MAX_LINE_WIDTH];
  int lineCounter = 0;
  while (fgets(line, MAX_LINE_WIDTH, pFile) != NULL) {
    char *token;

    token = strtok(line, SPACE_DELIMITER);

    if (strcmp(token, MATERIAL_LIBRARY_NAME_TOKEN) == 0) {
      token = strtok(NULL, SPACE_DELIMITER);
      STRIP_NEWLINE(token);
      writeMeshMtl(m, token);
    } else if (strcmp(token, OBJECT_NAME_TOKEN) == 0) {
      token = strtok(NULL, SPACE_DELIMITER);
      STRIP_NEWLINE(token);
      writeMeshName(m, token);
    } else if (strcmp(token, VERTEX_COORDINATES_TOKEN) == 0) {
      char *xStr, *yStr, *zStr;

      xStr = strtok(NULL, SPACE_DELIMITER);
      yStr = strtok(NULL, SPACE_DELIMITER);
      zStr = strtok(NULL, SPACE_DELIMITER);

      Vec3 v;
      v.x = strtof(xStr, NULL);
      v.y = strtof(yStr, NULL);
      v.z = strtof(zStr, NULL);

      /*printf("Vec3: %f %f %f\n", v.x, v.y, v.z);*/

      writeMeshVertex(m, v);
    } else if (strcmp(token, VERTEX_NORMAL_COORDINATES_TOKEN) == 0) {
      char *xStr, *yStr, *zStr;

      xStr = strtok(NULL, SPACE_DELIMITER);
      yStr = strtok(NULL, SPACE_DELIMITER);
      zStr = strtok(NULL, SPACE_DELIMITER);

      Vec3 n;
      n.x = strtof(xStr, NULL);
      n.y = strtof(yStr, NULL);
      n.z = strtof(zStr, NULL);
      writeMeshNormal(m, n);
    } else if (strcmp(token, VERTEX_TEXTURE_COORDINATES_TOKEN) == 0) {
      char *uStr, *vStr;

      uStr = strtok(NULL, SPACE_DELIMITER);
      vStr = strtok(NULL, SPACE_DELIMITER);

      Tex2 t;
      t.u = strtof(uStr, NULL);
      t.v = strtof(vStr, NULL);
      writeMeshUv(m, t);
    } else if (strcmp(token, FACE_INDICES_TOKEN) == 0) {
      /* TODO: this branch should be DRYed */
      char firstFaceStr[64], secondFaceStr[64], thirdFaceStr[64];

      strcpy(firstFaceStr, strtok(NULL, SPACE_DELIMITER));
      strcpy(secondFaceStr, strtok(NULL, SPACE_DELIMITER));
      strcpy(thirdFaceStr, strtok(NULL, SPACE_DELIMITER));

      Face f;
      char *a, *b, *c;

      a = strtok(firstFaceStr, FORWARD_SLASH_DELIMITER); /* v1 */
      b = strtok(NULL, FORWARD_SLASH_DELIMITER);         /* uv1 or n1 */
      c = strtok(NULL, FORWARD_SLASH_DELIMITER);         /* n1 or NULL */

      if (!c) {
        f.v1 = parseIndex(a);
        f.uv1 = INDEX_UNDEFINED;
        f.n1 = parseIndex(b);
      } else {
        f.v1 = parseIndex(a);
        f.uv1 = parseIndex(b);
        f.n1 = parseIndex(c);
      }

      a = strtok(secondFaceStr, FORWARD_SLASH_DELIMITER); /* v2 */
      b = strtok(NULL, FORWARD_SLASH_DELIMITER);          /* uv2 or n2 */
      c = strtok(NULL, FORWARD_SLASH_DELIMITER);          /* n2 or NULL */

      if (!c) {
        f.v2 = parseIndex(a);
        f.uv2 = INDEX_UNDEFINED;
        f.n2 = parseIndex(b);
      } else {
        f.v2 = parseIndex(a);
        f.uv2 = parseIndex(b);
        f.n2 = parseIndex(c);
      }

      a = strtok(thirdFaceStr, FORWARD_SLASH_DELIMITER); /* v3 */
      b = strtok(NULL, FORWARD_SLASH_DELIMITER);         /* uv3 or n3 */
      c = strtok(NULL, FORWARD_SLASH_DELIMITER);         /* n3 or NULL */

      if (!c) {
        f.v3 = parseIndex(a);
        f.uv3 = INDEX_UNDEFINED;
        f.n3 = parseIndex(b);
      } else {
        f.v3 = parseIndex(a);
        f.uv3 = parseIndex(b);
        f.n3 = parseIndex(c);
      }

      writeMeshFace(m, f);
    } else {
      printf("Token \"%s\" is not supported\n", token);
    }

    lineCounter++;
  }

  if (!feof(pFile)) {
    perror("Error loading a file");
    fclose(pFile);
    freeMesh(m);

    return false;
  } else {
    printf("OBJ file %s loaded successfully\n", fileName);
    printf("Total number of lines are read: %d\n", lineCounter);
  }

  fclose(pFile);
  return true;
}
