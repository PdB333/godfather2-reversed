// FUNC_NAME: AnimationBlender::updateBlendTransforms
int __fastcall AnimationBlender::updateBlendTransforms(int this)
{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined1 *puVar5;
  uint uVar6;
  float fVar7;
  undefined8 uVar8;
  longlong lVar9;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;

  // Profile entry
  FUN_00612a60(); // likely profileBegin

  iVar2 = *(int *)(this + 0x10); // some global or skeleton index
  if ((iVar2 == DAT_01219908) && (DAT_01219928 != 0)) {
    local_20 = 0.0;
    local_1c = 0.0;
    local_18 = 0.0;
    local_14 = 0.0;
    iVar2 = FUN_0060add0(iVar2, DAT_01219928, &local_20); // add reference transform
  }

  iVar1 = *(int *)(this + 0x14); // current blend layer type
  if (iVar1 == *(int *)(this + 0x470)) { // Layer type 0
    // Blend from layer 0
    FUN_0060add0(iVar1, *(undefined4 *)(this + 0x254), this + 0xb0);
    FUN_0060add0(*(undefined4 *)(this + 0x14), *(undefined4 *)(this + 600), this + 0xc0);
    FUN_0060add0(*(undefined4 *)(this + 0x14), *(undefined4 *)(this + 0x25c), this + 0xd0);
    iVar2 = *(int *)(this + 0xa4);
    if (*(int *)(this + 0x260) != 0) {
      iVar2 = FUN_006063b0(); // some init
    }
    uVar6 = *(uint *)(this + 0x264);
    if (uVar6 == 0) {
      return iVar2;
    }
    uVar3 = *(uint *)(this + 0xa4); // bone index?
    if (uVar3 < 0x1000) {
      puVar5 = &DAT_011a0f28 + uVar3 * 0x38; // bone data table
    } else {
      puVar5 = (undefined1 *)0x0;
    }
    // Fall through to common weight calculation
    local_1c = 0.0;
    local_20 = 0.0;
    local_18 = DAT_00e2cd54 / (float)*(ushort *)(puVar5 + 2);
    fVar7 = DAT_00e2cd54;
    if (uVar3 < 0x1000) {
      lVar9 = CONCAT44(uVar6, &DAT_011a0f28 + uVar3 * 0x38);
    } else {
      lVar9 = (ulonglong)uVar6 << 0x20;
    }
  } else {
    if (iVar1 == *(int *)(this + 0x474)) { // Layer type 1
      // Blend from layer 1
      FUN_0060add0(iVar1, *(undefined4 *)(this + 0x26c), this + 0xb0);
      FUN_0060add0(*(undefined4 *)(this + 0x14), *(undefined4 *)(this + 0x270), this + 0xc0);
      FUN_0060add0(*(undefined4 *)(this + 0x14), *(undefined4 *)(this + 0x274), this + 0xd0);
      if (*(int *)(this + 0x278) != 0) {
        FUN_006063b0(); // init
      }
      if (*(int *)(this + 0x27c) != 0) {
        FUN_0060b2f0(*(undefined4 *)(this + 0x14), *(int *)(this + 0x27c),
                     *(undefined4 *)(this + 0xe0));
      }
      iVar2 = *(int *)(this + 0x280);
      if (iVar2 != 0) {
        iVar2 = FUN_0060add0(*(undefined4 *)(this + 0x14), iVar2, this + 0x140);
      }
      if (*(int *)(this + 0x284) != 0) {
        uVar6 = *(uint *)(this + 0xa4);
        local_20 = 0.0;
        local_1c = 0.0;
        if (uVar6 < 0x1000) {
          puVar5 = &DAT_011a0f28 + uVar6 * 0x38;
        } else {
          puVar5 = (undefined1 *)0x0;
        }
        local_18 = DAT_00e2cd54 / (float)*(ushort *)(puVar5 + 2);
        if (uVar6 < 0x1000) {
          puVar5 = &DAT_011a0f28 + uVar6 * 0x38;
        } else {
          puVar5 = (undefined1 *)0x0;
        }
        local_14 = DAT_00e2cd54 / (float)*(ushort *)(puVar5 + 4);
        iVar2 = FUN_0060add0(*(undefined4 *)(this + 0x14), *(int *)(this + 0x284), &local_20);
      }
      uVar6 = *(uint *)(this + 0x288);
      if (uVar6 == 0) {
        return iVar2;
      }
      uVar3 = *(uint *)(this + 0xe0);
      if (uVar3 < 0x1000) {
        puVar5 = &DAT_011a0f28 + uVar3 * 0x38;
      } else {
        puVar5 = (undefined1 *)0x0;
      }
      goto LAB_00538b69; // to common weight calculation
    } else {
      if (iVar1 == *(int *)(this + 0x478)) { // Layer type 2
        // Blend from layer 2
        FUN_0060add0(iVar1, *(undefined4 *)(this + 0x29c), this + 0xb0);
        FUN_0060add0(*(undefined4 *)(this + 0x14), *(undefined4 *)(this + 0x2a0), this + 0xc0);
        FUN_0060b2f0(*(undefined4 *)(this + 0x14), *(undefined4 *)(this + 0x28c),
                     *(undefined4 *)(this + 0xe4));
        FUN_0060b2f0(*(undefined4 *)(this + 0x14), *(undefined4 *)(this + 0x290),
                     *(undefined4 *)(this + 0xe8));
        FUN_0060add0(*(undefined4 *)(this + 0x14), *(undefined4 *)(this + 0x294), this + 0xf0);
        iVar2 = FUN_0060add0(*(undefined4 *)(this + 0x14), *(undefined4 *)(this + 0x298),
                             this + 0x100);
        if (*(int *)(this + 0x2a4) != 0) {
          local_20 = 0.0;
          local_1c = 0.0;
          fVar7 = DAT_00e2cd54;
          uVar8 = FUN_00606370(*(undefined4 *)(this + 0xe4));
          local_18 = fVar7 / (float)*(ushort *)((int)uVar8 + 2);
          local_14 = fVar7 / (float)*(ushort *)((int)uVar8 + 4);
          iVar2 = FUN_0060add0(*(undefined4 *)(this + 0x14), (int)((ulonglong)uVar8 >> 0x20),
                               &local_20);
        }
        if (*(int *)(this + 0x268) == 0) {
          return iVar2;
        }
        local_20 = 0.0;
        local_1c = 0.0;
        fVar7 = DAT_00e2cd54;
        lVar9 = FUN_00606370(*(undefined4 *)(this + 0xe8));
      } else {
        uVar6 = *(uint *)(this + 0x134); // flags
        if (uVar6 != 0) {
          if (iVar1 != *(int *)(this + 0x494)) { // Not special layer 9
            uVar4 = FUN_004e3a30(); // get current layer type from somewhere
            uVar8 = FUN_00606370(uVar4);
            fVar7 = DAT_00e2b04c;
            if (((uVar6 & 0x200) == 0) && (fVar7 = DAT_00e2b1a4, (uVar6 & 0x400) != 0)) {
              fVar7 = DAT_00e2d99c;
            }
            local_20 = fVar7 / (float)*(ushort *)((int)uVar8 + 2);
            local_1c = DAT_00e44564 - fVar7 / (float)*(ushort *)((int)uVar8 + 4);
            if ((uVar6 & 0x20) != 0) { // mirror horizontal
              local_20 = DAT_00e44564 - local_20;
              local_1c = DAT_00e44564 - local_1c;
            }
            iVar2 = *(int *)(this + 0x3b4 + *(int *)(this + 0x138) * 4); // indexed per bone
            if (iVar2 != 0) {
              FUN_0060ac80((int)((ulonglong)uVar8 >> 0x20), iVar2, &local_20); // set with weight
            }
            iVar2 = *(int *)(this + 0x2d4 + *(int *)(this + 0x138) * 4);
            if (iVar2 != 0) {
              FUN_0060add0(*(undefined4 *)(this + 0x14), iVar2, this + 0x110);
            }
            iVar2 = *(int *)(this + 0x30c + *(int *)(this + 0x138) * 4);
            if (iVar2 != 0) {
              FUN_0060b2f0(*(undefined4 *)(this + 0x14), iVar2, *(undefined4 *)(this + 0x120));
            }
            iVar2 = *(int *)(this + 0x344 + *(int *)(this + 0x138) * 4);
            if (iVar2 != 0) {
              FUN_0060b2f0(*(undefined4 *)(this + 0x14), iVar2, *(undefined4 *)(this + 0x124));
            }
            if (*(int *)(this + 0x3ec + *(int *)(this + 0x138) * 4) != 0) {
              iVar2 = FUN_00606370(*(undefined4 *)(this + 0x120));
              local_20 = DAT_00e2cd54 / (float)*(ushort *)(iVar2 + 2);
              local_1c = DAT_00e2cd54 / (float)*(ushort *)(iVar2 + 4);
              fVar7 = DAT_00e2cd54;
              uVar8 = FUN_00606370(*(undefined4 *)(this + 0x124));
              local_18 = fVar7 / (float)*(ushort *)((int)uVar8 + 2);
              local_14 = fVar7 / (float)*(ushort *)((int)uVar8 + 4);
              FUN_0060add0(*(undefined4 *)(this + 0x14), (int)((ulonglong)uVar8 >> 0x20), &local_20);
            }
            iVar2 = FUN_00539aa0(*(undefined4 *)(this + 0x130)); // finalize
            return iVar2;
          }
          // when iVar1 == *(this + 0x494) (special layer 9)
          FUN_0060b2f0(iVar1, *(undefined4 *)(this + 0x30c + *(int *)(this + 0x138) * 4),
                       *(undefined4 *)(this + 0x120));
          iVar2 = FUN_0060add0(*(undefined4 *)(this + 0x14),
                               *(undefined4 *)(this + 0x2d4 + *(int *)(this + 0x138) * 4),
                               this + 0x110);
          if (*(int *)(this + 0x3ec + *(int *)(this + 0x138) * 4) == 0) {
            return iVar2;
          }
          uVar8 = FUN_00606370(*(undefined4 *)(this + 0x120));
          uVar4 = (undefined4)((ulonglong)uVar8 >> 0x20);
          local_20 = DAT_00e2cd54 / (float)*(ushort *)((int)uVar8 + 2);
          local_1c = DAT_00e2cd54 / (float)*(ushort *)((int)uVar8 + 4);
          local_14 = 0.0;
          local_18 = 0.0;
          goto LAB_00539188;
        }
        // when uVar6 == 0 (flags zero)
        if (iVar1 == *(int *)(this + 0x47c)) { // Layer type 3
          FUN_0060add0(iVar1, *(undefined4 *)(this + 0x424), this + 0x150);
          FUN_0060add0(*(undefined4 *)(this + 0x14), *(undefined4 *)(this + 0x428),
                       this + 0x160);
          FUN_0060add0(*(undefined4 *)(this + 0x14), *(undefined4 *)(this + 0x42c),
                       this + 0x170);
          if (*(int *)(this + 0x438) != 0) {
            iVar2 = FUN_00606370(*(undefined4 *)(this + 0x180));
            local_20 = DAT_00e2cd54 / (float)*(ushort *)(iVar2 + 2);
            local_1c = DAT_00e2cd54 / (float)*(ushort *)(iVar2 + 4);
            fVar7 = DAT_00e2cd54;
            uVar8 = FUN_00606370(*(undefined4 *)(this + 0x184));
            local_18 = fVar7 / (float)*(ushort *)((int)uVar8 + 2);
            local_14 = fVar7 / (float)*(ushort *)((int)uVar8 + 4);
            FUN_0060add0(*(undefined4 *)(this + 0x14), (int)((ulonglong)uVar8 >> 0x20), &local_20);
          }
          FUN_0060b2f0(*(undefined4 *)(this + 0x14), *(undefined4 *)(this + 0x430),
                       *(undefined4 *)(this + 0x180));
          iVar2 = FUN_0060b2f0(*(undefined4 *)(this + 0x14), *(undefined4 *)(this + 0x434),
                               *(undefined4 *)(this + 0x184));
          return iVar2;
        }
        if (((iVar1 == *(int *)(this + 0x480)) || (iVar1 == *(int *)(this + 0x484))) ||
           (iVar1 == *(int *)(this + 0x488))) {
          // Layer types 4,5,6
          FUN_0060add0(iVar1, *(undefined4 *)(this + 0x43c), this + 400);
          FUN_0060ab00(*(undefined4 *)(this + 0x14), *(undefined4 *)(this + 0x440),
                       this + 0x1a0, 8);
          iVar2 = FUN_0060b2f0(*(undefined4 *)(this + 0x14), *(undefined4 *)(this + 0x444),
                               *(undefined4 *)(this + 0x1c0));
          return iVar2;
        }
        if (iVar1 == *(int *)(this + 0x48c)) { // Layer type 7
          FUN_0060ab00(iVar1, *(undefined4 *)(this + 0x448), this + 0x1d0, 8);
          FUN_0060ab00(*(undefined4 *)(this + 0x14), *(undefined4 *)(this + 0x44c),
                       this + 0x1f0, 8);
          FUN_0060ab00(*(undefined4 *)(this + 0x14), *(undefined4 *)(this + 0x450),
                       this + 0x210, 8);
          iVar2 = FUN_0060b2f0(*(undefined4 *)(this + 0x14), *(undefined4 *)(this + 0x454),
                               *(undefined4 *)(this + 0x230));
          if (*(int *)(this + 0x458) == 0) {
            return iVar2;
          }
          uVar4 = *(undefined4 *)(this + 0x230);
        } else {
          if (iVar1 != *(int *)(this + 0x490)) {
            return iVar2;
          }
          // Layer type 8
          FUN_0060add0(iVar1, *(undefined4 *)(this + 0x45c), this + 0x240);
          iVar2 = FUN_0060b2f0(*(undefined4 *)(this + 0x14), *(undefined4 *)(this + 0x460),
                               *(undefined4 *)(this + 0x250));
          if (*(int *)(this + 0x464) == 0) {
            return iVar2;
          }
          uVar4 = *(undefined4 *)(this + 0x250);
        }
        // Common weight calculation for layer 7/8 with extra transform
        local_1c = 0.0;
        local_20 = 0.0;
        lVar9 = FUN_00606370(uVar4);
        fVar7 = DAT_00e2cd54;
      }
      local_18 = fVar7 / (float)*(ushort *)((int)lVar9 + 2);
    }
  }
  uVar4 = (undefined4)((ulonglong)lVar9 >> 0x20);
  local_14 = fVar7 / (float)*(ushort *)((int)lVar9 + 4);
LAB_00539188:
  iVar2 = FUN_0060add0(*(undefined4 *)(this + 0x14), uVar4, &local_20);
  return iVar2;
}