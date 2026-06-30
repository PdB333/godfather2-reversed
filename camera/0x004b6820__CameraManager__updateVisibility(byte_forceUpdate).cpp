// FUNC_NAME: CameraManager::updateVisibility(byte forceUpdate)
void __thiscall CameraManager::updateVisibility(int this, byte forceUpdate)
{
  bool bVar3;
  int iVar2;
  int iVar4;
  char *pcVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  float fVar9;
  float cameraX;
  float cameraY;
  float cameraZ;
  float cameraDist;
  char cObjectType;
  int objectIndex;
  char acMatrix[48]; // 4x3? or 3x4 matrix
  float fStack_b0;
  float fStack_ac;
  float fStack_a8;
  float fStack_a4;
  float fStack_c0;
  float fStack_bc;
  float fStack_b8;
  float fStack_b4;
  float fStack_54;
  char acTemp[76];
  char acResult[2]; // from FUN_00aa1b20
  char acTemp2[1];

  // globals
  float lodDistance = DAT_00e44648; // initial LOD distance
  cameraX = 0.0f;
  cameraY = 0.0f;
  cameraZ = 0.0f;
  bVar3 = false;
  cameraDist = DAT_00e2b1a4; // some distance constant (maybe far plane?)

  if (DAT_00e44598 < DAT_012067e8) {
    lodDistance = DAT_00e2b1a4 / DAT_012067e8;
  }

  // unused read from global? probably some rendering state
  int renderState = *(int *)(DAT_01223480 + 0x24);

  objectIndex = 0;
  if (*(int *)(this + 0x1c) != 0) { // count of objects
    int offset = 0;
    do {
      // get object pointer from internal list (stride 0x70)
      int pNode = *(int *)(this + 0x18);
      iVar2 = *(int *)(offset + 0x40 + pNode); // pointer to game object
      cObjectType = *(char *)(iVar2 + 0xd8);

      if (cObjectType == 0x06) {
        // special type: update FOV or LOD scale
        setLodScale(lodDistance); // FUN_005570a0
      }
      else if (((forceUpdate != 0) && (cObjectType != 0)) || (cObjectType == 0x07)) {
        if (!bVar3) {
          // get camera or view object
          int cameraObj = (**(code **)(**(int **)(*(int *)(this + 8) + 8) + 4))();
          // store camera position/rotation
          float cameraRotZ = *(float *)(cameraObj + 0x38);
          float cameraRotY = *(float *)(cameraObj + 0x34);
          float cameraRotX = *(float *)(cameraObj + 0x30);
          fStack_54 = DAT_00e2b1a4;
          getViewMatrix(cameraObj, acMatrix); // FUN_004b59d0
          bVar3 = true;
        }

        if (*(int *)(iVar2 + 8) != 0) { // object enabled flag
          // transform world point to view space/perform projections
          transformPoint(acMatrix, *(int *)(this + 0x18) + offset, ? ); // FUN_00aa1cf0 - parameters unclear

          // compute screen coordinates? (FUN_00aa1b20)
          pcVar5 = projectPoint(&acResult, iVar2 + 0xe0, DAT_00e2e210); // returns char*
          if (*pcVar5 == '\0') { // projection succeeded
            if (cObjectType == 0x07) {
              // special type 7 handling
              somePreprocess(iVar2); // FUN_009e71f0
            }
            resetMatrix(acTemp); // FUN_009f4cd0
            if (*(char *)(iVar2 + 0xd8) != 0x07) {
              pushMatrix(); // FUN_009f2000
              (**(code **)(*(int *)(iVar2 + 0xd0) + 0x40))(&cameraX); // get position into cameraX etc.
              popMatrix(); // FUN_009f2000
              pushMatrix(); 
              (**(code **)(*(int *)(iVar2 + 0xd0) + 0x44))(acResult); // get orientation? into acResult
              popMatrix();
            }
            if (cObjectType == 0x07) {
              setObjectFlag(iVar2, 1); // FUN_009e6ff0
            }
          }
          else { // projection failed - check if difference is too large
            // compute differences relative to reference camera position (cameraX,cameraY,cameraZ,cameraDist)
            fStack_ac = *(float *)(iVar2 + 0x1a4) - cameraY;
            fStack_a8 = *(float *)(iVar2 + 0x1a8) - cameraZ;
            fStack_a4 = *(float *)(iVar2 + 0x1ac) - cameraDist;
            fVar9 = fabs(*(float *)(iVar2 + 0x1a0) - cameraX); // FUN_0040f220
            fStack_b0 = fVar9;
            fVar9 = fabs(fStack_ac);
            fStack_ac = fVar9;
            fVar9 = fabs(fStack_a8);
            fStack_a8 = fVar9;
            fVar9 = fabs(fStack_a4);
            fStack_a4 = fVar9;

            // check thresholds
            bVar8 = (fStack_b0 > DAT_00e2e210) ? 0 : 8;
            bVar7 = (fStack_ac > DAT_00e2e210) ? 0 : 4;
            bVar6 = (fStack_a8 > DAT_00e2e210) ? 0 : 2;

            if ((byte)(bVar6 | bVar7 | bVar8) != 0xe) {
              pushMatrix();
              (**(code **)(*(int *)(iVar2 + 0xd0) + 0x40))(&cameraX); // update position
            }

            fStack_bc = *(float *)(iVar2 + 0x1b4) - cameraY;
            fStack_b8 = *(float *)(iVar2 + 0x1b8) - cameraZ;
            fStack_b4 = *(float *)(iVar2 + 0x1bc) - cameraDist;
            fVar9 = fabs(*(float *)(iVar2 + 0x1b0) - cameraX);
            fStack_c0 = fVar9;
            fVar9 = fabs(fStack_bc);
            fStack_bc = fVar9;
            fVar9 = fabs(fStack_b8);
            fStack_b8 = fVar9;
            fVar9 = fabs(fStack_b4);
            fStack_b4 = fVar9;

            bVar8 = (fStack_c0 > DAT_00e2e210) ? 0 : 8;
            bVar7 = (fStack_bc > DAT_00e2e210) ? 0 : 4;
            bVar6 = (fStack_b8 > DAT_00e2e210) ? 0 : 2;

            if ((byte)(bVar6 | bVar7 | bVar8) != 0xe) {
              pushMatrix();
              (**(code **)(*(int *)(iVar2 + 0xd0) + 0x44))(&cameraX); // update orientation
            }
          }
        }
      }
      objectIndex++;
      offset += 0x70;
    } while (objectIndex < *(uint *)(this + 0x1c));
  }
}