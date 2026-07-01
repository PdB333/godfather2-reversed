// FUNC_NAME: AnimTree::driveBoneWithOffset
undefined4 __thiscall FUN_0080e770(int this, int animCmdType, float *basePos, float weight, char useGlobalSpace, undefined4 blendFlags)
{
  uint in_EAX; // likely some EAX register pass-through
  float *pfVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  float *pfVar5;
  bool bVar6;
  float fVar7;
  undefined8 local_5c; // resulting XY position
  float local_54;      // resulting Z position
  float local_50[4];   // identity quaternion or maybe matrix row? (16 floats)
  float local_40;
  float local_3c;
  float local_38;

  uVar4 = in_EAX & 0xffffff00; // mask off low byte, possibly preserve high bits for flags
  bVar6 = false;
  if (animCmdType != 0) {
    pfVar1 = (float *)FUN_00471610(); // likely getIdentityTransform() or getIdentityMatrix()
    fVar7 = DAT_01206800 * weight + DAT_00d5f520; // scale weight with global anim blend constants
    pfVar5 = local_50;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar5 = *pfVar1; // copy 16 floats (4x4 matrix?)
      pfVar1 = pfVar1 + 1;
      pfVar5 = pfVar5 + 1;
    }
    switch(animCmdType) {
    case 2: // ANIM_BONE_TRANSLATE_LOCAL
      fVar7 = fVar7 * DAT_00d5ccf8;
    case 1: // ANIM_BONE_TRANSLATE (fallthrough)
      local_5c = CONCAT44(local_3c * fVar7 + basePos[1], local_40 * fVar7 + *basePos); // blend: identity * fVar7 + base offset
      local_54 = local_38 * fVar7 + basePos[2];
      break;
    case 3: // ANIM_BONE_ROTATE_LOCAL
      fVar7 = fVar7 * DAT_00d5ccf8;
    case 4: // ANIM_BONE_ROTATE (fallthrough)
      local_5c = CONCAT44(local_50[1] * fVar7 + basePos[1], local_50[0] * fVar7 + *basePos);
      local_54 = local_50[2] * fVar7 + basePos[2];
      break;
    default:
      local_54 = basePos[2];
      local_5c = *(undefined8 *)basePos; // keep original position
    }
    // Fetch some flags from object at +0x50 then +0x830 (likely animation state flags)
    uVar4 = *(uint *)(*(int *)(this + 0x50) + 0x830);
    if (useGlobalSpace != '\0') {
      uVar4 = uVar4 & 0xfbffffff; // clear bit 26 maybe "use local space" ?
    }
    // Send blend command to animation system
    uVar2 = FUN_0054ebf0(basePos, &local_5c, 0x60336, uVar4, 0, 0, blendFlags, 0, 0);
    bVar6 = (char)uVar2 != '\0';
    uVar4 = CONCAT31((int3)((uint)uVar2 >> 8), bVar6);
  }
  return CONCAT31((int3)(uVar4 >> 8), !bVar6); // return status: low byte = success/fail
}