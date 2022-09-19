#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "Mesh.h"
#include "constants.h"
#include "utilities.h"

#define MATERIAL_LIBRARY_NAME_TOKEN "mtllib"
#define OBJECT_NAME_TOKEN "o"
#define VERTEX_COORDINATES_TOKEN "v"
#define VERTEX_NORMAL_COORDINATES_TOKEN "vn"
#define VERTEX_TEXTURE_COORDINATES_TOKEN "vt"
#define FACE_INDICES_TOKEN "f"

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
				f.v1 = (int)strtol(a, NULL, 10);
				f.uv1 = INDEX_UNDEFINED;
				f.n1 = (int)strtol(b, NULL, 10);
			} else {
				f.v1 = (int)strtol(a, NULL, 10);
				f.uv1 = (int)strtol(b, NULL, 10);
				f.n1 = (int)strtol(c, NULL, 10);
			}

			a = strtok(secondFaceStr, FORWARD_SLASH_DELIMITER); /* v2 */
			b = strtok(NULL, FORWARD_SLASH_DELIMITER);          /* uv2 or n2 */
			c = strtok(NULL, FORWARD_SLASH_DELIMITER);          /* n2 or NULL */

			if (!c) {
				f.v2 = (int)strtol(a, NULL, 10);
				f.uv2 = INDEX_UNDEFINED;
				f.n2 = (int)strtol(b, NULL, 10);
			} else {
				f.v2 = (int)strtol(a, NULL, 10);
				f.uv2 = (int)strtol(b, NULL, 10);
				f.n2 = (int)strtol(c, NULL, 10);
			}

			a = strtok(thirdFaceStr, FORWARD_SLASH_DELIMITER); /* v3 */
			b = strtok(NULL, FORWARD_SLASH_DELIMITER);         /* uv3 or n3 */
			c = strtok(NULL, FORWARD_SLASH_DELIMITER);         /* n3 or NULL */

			if (!c) {
				f.v3 = (int)strtol(a, NULL, 10);
				f.uv3 = INDEX_UNDEFINED;
				f.n3 = (int)strtol(b, NULL, 10);
			} else {
				f.v3 = (int)strtol(a, NULL, 10);
				f.uv3 = (int)strtol(b, NULL, 10);
				f.n3 = (int)strtol(c, NULL, 10);
			}

			/*printf("%d %d %d\n", f.v1, f.uv1, f.n1);
			printf("%d %d %d\n", f.v2, f.uv2, f.n2);
			printf("%d %d %d\n", f.v3, f.uv3, f.n3);*/

			writeMeshFace(m, f);
		} else {
			/*printf("Token \"%s\" is not supported\n", token);*/
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

#endif // OBJ_LOADER_H
