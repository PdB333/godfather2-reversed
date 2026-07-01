// FUNC_NAME: VFXManager::loadVFXFromConfig
undefined4 * __thiscall VFXManager::loadVFXFromConfig(undefined4 *this, int configData, undefined4 param_3)
{
  uint *puVar1;
  float fVar2;
  bool bVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  uint uVar6;
  int *piVar7;
  uint uVar8;
  int iVar9;
  char local_31;
  longlong local_30;
  uint local_28 [10];
  
  FUN_004a7560(configData, param_3);
  *this = &PTR_FUN_00d7cd90; // vtable
  this[4] = 0; // +0x10 - VFX handle 0
  this[5] = 0; // +0x14 - VFX handle 1
  this[6] = 0; // +0x18 - VFX handle 2
  this[7] = 0; // +0x1c - VFX handle 3
  this[8] = 0; // +0x20 - VFX handle 4
  this[9] = 0; // +0x24 - VFX handle 5
  uVar4 = FUN_0042b400(); // some hash function
  this[10] = uVar4; // +0x28 - hash1
  uVar4 = FUN_0042b400(); // another hash
  this[0xb] = uVar4; // +0x2c - hash2
  *(undefined1 *)(this + 0xc) = 0; // +0x30 - some byte
  *(undefined1 *)((int)this + 0x31) = 1; // +0x31 - flags byte, bit0=1
  iVar9 = 0;
  *(undefined1 *)((int)this + 0x32) = 0; // +0x32 - another byte
  uVar8 = 0;
  local_28[0] = 0;
  local_28[1] = 0;
  local_28[2] = 0;
  local_28[3] = 0;
  local_28[4] = 0;
  local_28[5] = 0;
  local_28[6] = 0;
  local_28[7] = 0;
  local_28[8] = 0;
  local_28[9] = 0;
  local_31 = '\0';
  bVar3 = false;
  if (*(short *)(configData + 0x20) == 0) { // no elements in config
LAB_008cf775:
    puVar5 = (undefined4 *)FUN_004a3790(0x136decc4); // lookup some global
    if ((puVar5 == (undefined4 *)0x0) || (puVar5[5] != 2)) goto LAB_008cf79c;
    uVar4 = thunk_FUN_0042a990(*puVar5); // get hash from global
  }
  else {
    do {
      puVar1 = *(uint **)(*(int *)(configData + 0x1c) + uVar8 * 4); // iterate config elements
      uVar6 = puVar1[4]; // element type hash
      if (uVar6 < 0x5fdd2832) {
        if (uVar6 == 0x5fdd2831) { // "Vfx1" hash
          local_28[0] = *puVar1; // value for Vfx1
          iVar9 = iVar9 + *puVar1;
        }
        else if (uVar6 == 0x2a9ee1e3) { // some flag hash
          local_31 = (char)*puVar1;
        }
      }
      else if (uVar6 < 0x6b133109) {
        if (uVar6 == 0x6b133108) { // some boolean flag
          if ((char)*puVar1 != '\0') {
            *(byte *)((int)this + 0x31) = *(byte *)((int)this + 0x31) | 2; // set bit1
          }
        }
        else {
          switch(uVar6) {
          case 0x5fdd2832: // "Vfx2"
            local_28[1] = *puVar1;
            iVar9 = iVar9 + *puVar1;
            break;
          case 0x5fdd2833: // "Vfx3"
            local_28[2] = *puVar1;
            iVar9 = iVar9 + *puVar1;
            break;
          case 0x5fdd2834: // "Vfx4"
            local_28[3] = *puVar1;
            iVar9 = iVar9 + *puVar1;
            break;
          case 0x5fdd2835: // "Vfx5"
            local_28[4] = *puVar1;
            iVar9 = iVar9 + *puVar1;
            break;
          case 0x5fdd2836: // "Vfx6"
            local_28[5] = *puVar1;
            iVar9 = iVar9 + *puVar1;
            break;
          case 0x5fdd2837: // "Vfx7"
            local_28[6] = *puVar1;
            iVar9 = iVar9 + *puVar1;
            break;
          case 0x5fdd2838: // "Vfx8"
            local_28[7] = *puVar1;
            iVar9 = iVar9 + *puVar1;
            break;
          case 0x5fdd2839: // "Vfx9"
            local_28[8] = *puVar1;
            iVar9 = iVar9 + *puVar1;
          }
        }
      }
      else if (uVar6 == 0x6f4556d6) { // hash for "override" or similar
        uVar6 = *puVar1;
        this[10] = uVar6;
        this[0xb] = uVar6;
        bVar3 = true;
      }
      else if (uVar6 == 0x886ea447) { // some byte flag
        *(char *)(this + 0xc) = (char)*puVar1;
      }
      else if (uVar6 == 0xbf9de43f) { // "Vfx10"
        local_28[9] = *puVar1;
        iVar9 = iVar9 + *puVar1;
      }
      uVar8 = uVar8 + 1;
    } while (uVar8 < *(ushort *)(configData + 0x20));
    if (bVar3) goto LAB_008cf79c;
    if (local_31 == '\0') goto LAB_008cf775;
    uVar4 = thunk_FUN_0042a9a0(local_31);
  }
  this[0xb] = uVar4;
  this[10] = uVar4;
LAB_008cf79c:
  uVar8 = DAT_010c2678 & DAT_012054b4; // some global state
  DAT_012054b4 = DAT_012054b4 + 1;
  fVar2 = (float)iVar9;
  if (iVar9 < 0) {
    fVar2 = fVar2 + DAT_00e44578; // rounding adjustment
  }
  uVar6 = 0;
  local_30._0_4_ = (uint)(longlong)ROUND(fVar2 * *(float *)(&DAT_010c2680 + uVar8 * 4));
  do {
    puVar1 = local_28 + uVar6;
    uVar6 = uVar6 + 1;
    if ((uint)local_30 < *puVar1) {
      local_30 = (longlong)ROUND(fVar2 * *(float *)(&DAT_010c2680 + uVar8 * 4));
      _sprintf((char *)&local_30,"Vfx%i",uVar6);
      uVar4 = FUN_004dafd0(&local_30); // string to hash
      piVar7 = (int *)FUN_004a3790(uVar4); // lookup by hash
      if (piVar7 == (int *)0x0) {
        this[4] = 0;
        this[5] = 0;
        this[6] = 0;
        this[7] = 0;
        return this;
      }
      iVar9 = *piVar7;
      this[4] = *(undefined4 *)(iVar9 + 0xc); // copy VFX data
      this[5] = *(undefined4 *)(iVar9 + 0x10);
      this[6] = *(undefined4 *)(iVar9 + 0x14);
      this[7] = *(undefined4 *)(iVar9 + 0x18);
      return this;
    }
    local_30._0_4_ = (uint)local_30 - *puVar1;
  } while (uVar6 < 10);
  return this;
}