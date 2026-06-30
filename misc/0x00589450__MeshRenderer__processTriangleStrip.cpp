// FUNC_NAME: MeshRenderer::processTriangleStrip
void MeshRenderer::processTriangleStrip(int param_1, int param_2, int param_3)
{
  uint uVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  
  iVar2 = *(int *)(this + 0x1c); // currentIndex
  while (iVar2 < param_2) {
    iVar2 = *(int *)(this + 0x1c);
    uVar1 = __aullshr(); // random number generation
    if ((uVar1 & 3) - 1 < 3) {
      *(int *)(this + 0x10) = *(int *)(this + 0x10) + 2; // vertexDataOffset
    }
    else {
      *(int *)(this + 0x10) = *(int *)(this + 0x10) + 6;
    }
    *(int *)(this + 0x14) = *(int *)(this + 0x14) + 6; // normalDataOffset
    iVar2 = iVar2 + 1;
    *(int *)(this + 0x1c) = iVar2;
  }
  iVar2 = *(int *)(this + 0x1c);
  do {
    if (param_3 <= iVar2) {
      return;
    }
    uVar1 = __aullshr();
    uVar1 = uVar1 & 3;
    if (uVar1 == 1) {
      fVar3 = DAT_00e44564 - (float)**(ushort **)(this + 0x10) * DAT_00e44820;
      fVar4 = DAT_00e44564 - (float)*(ushort *)(*(int *)(this + 0x14) + 4) * DAT_00e44820;
LAB_005895f7:
      FUN_0056d040(fVar4,fVar3,param_1); // processVertex
      *(int *)(this + 0x10) = *(int *)(this + 0x10) + 2;
    }
    else {
      if (uVar1 == 2) {
        fVar3 = DAT_00e44564 - (float)**(ushort **)(this + 0x14) * DAT_00e44820;
        fVar4 = DAT_00e44564 - (float)**(ushort **)(this + 0x10) * DAT_00e44820;
        goto LAB_005895f7;
      }
      if (uVar1 == 3) {
        fVar3 = DAT_00e44564 - (float)**(ushort **)(this + 0x14) * DAT_00e44820;
        fVar4 = DAT_00e44564 - (float)(*(ushort **)(this + 0x14))[2] * DAT_00e44820;
        goto LAB_005895f7;
      }
      FUN_0056d040(DAT_00e44564 - (float)(*(ushort **)(this + 0x10))[2] * DAT_00e44820,
                   DAT_00e44564 - (float)**(ushort **)(this + 0x10) * DAT_00e44820,param_1);
      *(int *)(this + 0x10) = *(int *)(this + 0x10) + 6;
    }
    *(int *)(this + 0x14) = *(int *)(this + 0x14) + 6;
    *(int *)(this + 0x1c) = *(int *)(this + 0x1c) + 1;
    param_1 = param_1 + 0x10;
    iVar2 = *(int *)(this + 0x1c);
  } while( true );
}