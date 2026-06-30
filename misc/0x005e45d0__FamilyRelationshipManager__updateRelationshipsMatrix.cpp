// FUNC_NAME: FamilyRelationshipManager::updateRelationshipsMatrix
void FamilyRelationshipManager::updateRelationshipsMatrix(int param_1)

{
  byte bVar1;
  byte bVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  undefined4 *puVar10;
  uint uVar11;
  uint uVar12;
  byte local_19;
  uint local_14;
  
  iVar6 = DAT_01223504; // Global family manager instance +0x1d = numFamilies
  bVar1 = *(byte *)(DAT_01223504 + 0x1d); // num families
  local_19 = 0;
  if (bVar1 != 0) {
    uVar9 = 0; // current family index
    do {
      uVar11 = 0;
      uVar7 = 0; // relationship entry index
      if (*(byte *)(iVar6 + 0x1c) != 0) { // max relationships per family
        do {
          uVar12 = uVar11;
          if ((*(char *)(iVar6 + 0x18 + uVar7) != '\0') && (uVar12 = uVar11 + 1, uVar9 == uVar11)) {
            if ((byte)uVar7 < 4) {
              local_14 = uVar7 & 0xff ^ 0xad103100; // XOR with magic constant for transform
            }
            puVar10 = (undefined4 *)(param_1 + uVar9 * 0x30); // each family entry is 0x30 bytes
            puVar10[10] = local_14; // +0x28: transform key
            uVar9 = local_14 ^ 0xad103100;
            if (uVar9 < *(byte *)(iVar6 + 0x1c)) {
              puVar10[0xb] = *(undefined4 *)(*(int *)(iVar6 + 4 + (uVar9 & 0xff) * 4) + 0x6c); // +0x2c: family data ptr +0x6c
            }
            bVar2 = *(byte *)(iVar6 + 0x1c);
            if ((((uVar9 < bVar2) && (bVar2 != 0)) && ((byte)local_14 < bVar2)) &&
               (iVar8 = *(int *)(iVar6 + 4 + (local_14 & 0xff) * 4), iVar8 != 0)) {
              uVar3 = *(undefined4 *)(iVar8 + 0x44);
              uVar4 = *(undefined4 *)(iVar8 + 0x48);
              uVar5 = *(undefined4 *)(iVar8 + 0x4c);
              *puVar10 = *(undefined4 *)(iVar8 + 0x40); // +0x00: relationship matrix [0][0]
              puVar10[1] = uVar3; // +0x04: [0][1]
              puVar10[2] = uVar4; // +0x08: [0][2]
              puVar10[3] = uVar5; // +0x0c: [0][3]
            }
            bVar2 = *(byte *)(iVar6 + 0x1c);
            if (((uVar9 < bVar2) && (bVar2 != 0)) &&
               (((byte)local_14 < bVar2 &&
                (iVar8 = *(int *)(iVar6 + 4 + (uVar9 & 0xff) * 4), iVar8 != 0)))) {
              uVar3 = *(undefined4 *)(iVar8 + 0x54);
              uVar4 = *(undefined4 *)(iVar8 + 0x58);
              uVar5 = *(undefined4 *)(iVar8 + 0x5c);
              puVar10[4] = *(undefined4 *)(iVar8 + 0x50); // +0x10: [1][0]
              puVar10[5] = uVar3; // +0x14: [1][1]
              puVar10[6] = uVar4; // +0x18: [1][2]
              puVar10[7] = uVar5; // +0x1c: [1][3]
            }
            iVar8 = 0;
            if ((puVar10 + 9 != (undefined4 *)0x0) && (uVar9 < *(byte *)(iVar6 + 0x1c))) {
              iVar8 = *(int *)(iVar6 + 4 + (uVar9 & 0xff) * 4);
              puVar10[9] = *(undefined4 *)(iVar8 + 0x60); // +0x24: [2][0]
            }
            puVar10[8] = iVar8; // +0x20: [1][4] (stub)
            break;
          }
          uVar7 = uVar7 + 1;
          uVar11 = uVar12;
        } while ((int)uVar7 < (int)(uint)*(byte *)(iVar6 + 0x1c));
      }
      local_19 = local_19 + 1;
      uVar9 = (uint)local_19;
    } while (uVar9 < bVar1);
  }
  return;
}