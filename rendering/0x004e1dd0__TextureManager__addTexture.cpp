// FUNC_NAME: TextureManager::addTexture
int TextureManager::addTexture(int width, int height)
{
  short sVar1;
  char cVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  uint extraout_ECX;
  uint uVar8;
  uint uVar9;
  undefined1 *puVar10;
  int iVar11;
  float fVar12;
  float fVar13;
  uint local_1c;
  uint local_18;
  uint local_14;
  short *local_10;
  int local_c;
  short *local_8;
  uint local_4;
  
  cVar2 = FUN_004e1d80(&local_c, width);
  iVar6 = DAT_012054d8; // texture count
  if (cVar2 == '\0') {
    local_c = DAT_012054d8;
    local_8 = &DAT_01194558 + DAT_012054d8 * 0x56; // texture entry base
    fVar13 = DAT_00e2b1a4 / (float)(int)(short)width; // 1.0f / width
    fVar12 = DAT_00e2b1a4 / (float)(int)(short)height; // 1.0f / height
    DAT_012054d8 = DAT_012054d8 + 1; // increment texture count
    *local_8 = (short)width; // +0x00: width
    (&DAT_0119455a)[iVar6 * 0x56] = (short)height; // +0x02: height
    (&DAT_0119455c)[iVar6 * 0x2b] = fVar13; // +0x04: invWidth
    (&DAT_01194560)[iVar6 * 0x2b] = fVar12; // +0x08: invHeight
    puVar3 = &DAT_01194564 + iVar6 * 0x2b; // +0x0C: mipmap data array
    iVar6 = 0x14; // 20 mip levels
    do {
      *puVar3 = 0;
      puVar3 = puVar3 + 2;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    local_10 = &DAT_00e2ddc2; // texture format table
    do {
      local_4 = (uint)*(byte *)(local_10 + -1); // format index
      local_14 = 4; // default mip count
      iVar6 = width;
      iVar11 = height;
      if ((*(byte *)(local_10 + 3) & 3) != 0) { // check if mipmapped
        iVar6 = 1;
        if (0 < width) {
          do {
            iVar6 = iVar6 * 2;
          } while (iVar6 <= width);
        }
        iVar6 = iVar6 >> 1;
        iVar11 = 1;
        if (0 < height) {
          do {
            iVar11 = iVar11 * 2;
          } while (iVar11 <= height);
        }
        iVar11 = iVar11 >> 1;
        iVar4 = iVar6;
        if (iVar11 <= iVar6) {
          iVar4 = iVar11;
        }
        local_14 = 0;
        for (; 0x20 < iVar4; iVar4 = iVar4 >> 1) {
          local_14 = local_14 + 1;
        }
      }
      sVar1 = *local_10; // block width
      local_18 = (uint)sVar1;
      uVar8 = local_18;
      if (sVar1 < 0) {
        uVar8 = -(iVar6 / (int)local_18);
      }
      if ((int)uVar8 < 1) {
        local_18 = 1;
      }
      else if (sVar1 < 0) {
        local_18 = -(iVar6 / (int)local_18);
      }
      sVar1 = local_10[1]; // block height
      local_1c = (uint)sVar1;
      uVar8 = local_1c;
      if (sVar1 < 0) {
        uVar8 = -(iVar11 / (int)local_1c);
      }
      if ((int)uVar8 < 1) {
        local_1c = 1;
      }
      else if (sVar1 < 0) {
        local_1c = -(iVar11 / (int)local_1c);
      }
      switch((char)local_10[2]) { // format type
      case '\0': // DXT1
        uVar7 = FUN_004e3a30();
        iVar6 = FUN_00606370(uVar7);
        iVar6 = *(int *)(iVar6 + 8);
        break;
      case '\x01': // DXT3/DXT5
        uVar7 = FUN_004e3a50();
        iVar6 = FUN_00606370(uVar7);
        iVar6 = *(int *)(iVar6 + 8);
        break;
      default:
        iVar6 = 3; // unknown format
        break;
      case '\x03': // A8R8G8B8
        iVar6 = 0x1d;
        break;
      case '\x04': // A4R4G4B4
        iVar6 = 0x15;
      }
      uVar8 = (iVar6 != 0x15) - 1 & 0x10000;
      uVar9 = uVar8 | 0x40200098; // D3DFORMAT flags
      if ((*(byte *)(local_10 + 3) & 2) == 0) {
        local_14 = 1;
      }
      else if (1 < (int)local_14) {
        uVar9 = uVar8 | 0x40200099;
      }
      if (*(char *)((int)local_10 + 5) == -1) {
LAB_004e2095:
        uVar5 = 0xffffffff;
LAB_004e20a2:
        uVar7 = FUN_00606c80(iVar6, uVar9, local_18, local_1c, local_14, uVar5);
      }
      else {
        uVar8 = *(uint *)(local_8 + *(char *)((int)local_10 + 5) * 4 + 6);
        if (uVar8 < 0x1000) {
          puVar10 = &DAT_011a0f28 + uVar8 * 0x38; // texture handle table
        }
        else {
          puVar10 = (undefined1 *)0x0;
        }
        if ((*(ushort *)(puVar10 + 2) < local_18) || (*(ushort *)(puVar10 + 4) < local_1c))
        goto LAB_004e2095;
        if ((uVar8 < 0x1000) && (uVar8 * 0x38 != -0x11a0f28)) {
          uVar5 = FUN_00606b50(); // allocate texture slot
          if ((0xfff < uVar5) || (&DAT_011a0f28 + uVar5 * 0x38 == (byte *)0x0)) {
            uVar7 = 0xffffffff;
            goto LAB_004e20ae;
          }
          if (1 < (byte)(&DAT_011a0f28)[uVar5 * 0x38]) {
            uVar7 = 0xffffffff;
            goto LAB_004e20ae;
          }
          if (local_14 == 0) {
            local_14 = (uint)(byte)(&DAT_011a0f29)[uVar8 * 0x38];
          }
          goto LAB_004e20a2;
        }
        uVar7 = 0xffffffff;
      }
LAB_004e20ae:
      *(undefined4 *)(local_8 + local_4 * 4 + 6) = uVar7; // store texture handle
      if (((((iVar6 == 0x18) || (iVar6 == 0x19)) || (iVar6 == 0x1a)) ||
          (((iVar6 == 0x1b || (iVar6 == 0x1c)) || (iVar6 == 0x1d)))) &&
         (cVar2 = FUN_00608210(), cVar2 == '\0')) {
        if (extraout_ECX < 0x1000) {
          puVar10 = &DAT_011a0f28 + extraout_ECX * 0x38;
        }
        else {
          puVar10 = (undefined1 *)0x0;
        }
        if (*(int *)(puVar10 + 0x1c) == 0) {
          uVar7 = FUN_00606c80(0x15, *(undefined4 *)(puVar10 + 0xc), *(undefined2 *)(puVar10 + 2),
                               *(undefined2 *)(puVar10 + 4), puVar10[1], 0xffffffff);
          *(undefined4 *)(puVar10 + 0x1c) = uVar7;
        }
      }
      local_10 = local_10 + 8;
    } while ((int)local_10 < 0xe2df02);
  }
  return local_c;
}