// FUNC_NAME: FontManager::renderTextWithOutline
void FontManager::renderTextWithOutline(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int local_8;
  
  iVar2 = *(int *)(param_1 + 0x2224); // +0x2224: outline vertex buffer
  iVar3 = *(int *)(param_1 + 0x2220); // +0x2220: fill vertex buffer
  iVar4 = *(int *)(param_1 + 0x2228); // +0x2228: character width array
  local_8 = 0;
  if (0 < *(short *)(param_1 + 0x221c)) { // +0x221c: number of text runs
    do {
      iVar11 = (int)*(short *)(*(int *)(param_1 + 0x2214) + local_8 * 2); // +0x2214: run start indices
      iVar14 = (int)*(short *)(*(int *)(param_1 + 0x2218) + local_8 * 2); // +0x2218: run end indices
      iVar15 = (iVar14 - iVar11) + 1;
      cVar1 = *(char *)(iVar11 + iVar4);
      iVar13 = iVar11;
      while (cVar1 == '\0') {
        iVar13 = iVar13 + 1;
        cVar1 = *(char *)(iVar13 + iVar4);
      }
      uVar9 = *(undefined4 *)(iVar3 + iVar13 * 4);
      uVar10 = *(undefined4 *)(iVar2 + iVar13 * 4);
      while (0 < iVar15) {
        iVar13 = iVar13 + 1;
        if (iVar14 < iVar13) {
          iVar13 = iVar11;
        }
        uVar5 = *(undefined4 *)(iVar3 + iVar13 * 4);
        uVar6 = *(undefined4 *)(iVar2 + iVar13 * 4);
        if (*(char *)(iVar13 + iVar4) == '\0') {
          iVar12 = iVar13 + 1;
          if (iVar14 < iVar13 + 1) {
            iVar12 = iVar11;
          }
          iVar13 = iVar12 + 1;
          if (iVar14 < iVar12 + 1) {
            iVar13 = iVar11;
          }
          uVar7 = *(undefined4 *)(iVar2 + iVar13 * 4);
          uVar8 = *(undefined4 *)(iVar3 + iVar13 * 4);
          FUN_00676e80(param_1,uVar9,uVar10,uVar5,uVar6,*(undefined4 *)(iVar3 + iVar12 * 4),
                       *(undefined4 *)(iVar2 + iVar12 * 4),uVar8,uVar7);
          iVar15 = iVar15 + -3;
          uVar9 = uVar8;
          uVar10 = uVar7;
        }
        else {
          FUN_006767c0(uVar9,uVar10,uVar5,uVar6);
          iVar15 = iVar15 + -1;
          uVar9 = uVar5;
          uVar10 = uVar6;
        }
      }
      local_8 = local_8 + 1;
    } while (local_8 < *(short *)(param_1 + 0x221c));
  }
  return;
}