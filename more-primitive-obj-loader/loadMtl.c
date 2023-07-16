//
//  loadMtl.c
//  more-primitive-obj-loader
//
//  Created by Igor on 16/07/2023.
//

#include "loadMtl.h"

bool loadMtl(const char *fileName, Material *m) {
  initMaterial(m);

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

    /*printf("Token: %s\n", token);*/

    if (strcmp(token, MATERIAL_NAME_TOKEN) == 0) {
      token = strtok(NULL, SPACE_DELIMITER);
      STRIP_NEWLINE(token);
      writeMaterialName(m, token);
    } else if (strcmp(token, DIFFUSE_MAP_TOKEN) == 0) {
      token = strtok(NULL, SPACE_DELIMITER);
      STRIP_NEWLINE(token);
      writeMaterialDiffuseMapPath(m, token);
    } else if (strcmp(token, NORMAL_MAP_TOKEN) == 0) {
      char *path;

      strtok(NULL, SPACE_DELIMITER);
      strtok(NULL, SPACE_DELIMITER);
      path = strtok(NULL, SPACE_DELIMITER);
      STRIP_NEWLINE(path);

      writeMaterialNormalMapPath(m, path);
    } else {
      /*STRIP_NEWLINE(token);
      printf("Token \"%s\" is not supported\n", token);*/
    }

    lineCounter++;
  }

  if (!feof(pFile)) {
    printf("Error loading a file %s\n", fileName);
    fclose(pFile);
    freeMaterial(m);

    return false;
  } else {
    printf("MTL file %s is loaded successfully\n", fileName);
    printf("Total number of lines are read: %d\n", lineCounter);
  }

  fclose(pFile);
  return true;
}
