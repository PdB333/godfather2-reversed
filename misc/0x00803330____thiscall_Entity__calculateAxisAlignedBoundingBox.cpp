// FUNC_NAME: __thiscall Entity::calculateAxisAlignedBoundingBox
void __thiscall Entity::calculateAxisAlignedBoundingBox(int *this, float *outMin, float *outSize)
{
  float fVar1;
  char cVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  float10 fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  int *piStack_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float fStack_8;
  float fStack_4;
  
  fVar7 = (float10)FUN_0054eb00(); // getTimeDelta or some physics timestep
  local_28 = (float)fVar7;
  local_24 = DAT_00d5f6f0; // very large positive float (e.g. FLT_MAX)
  local_20 = DAT_00d5f6f0;
  local_1c = DAT_00d5f6f0;
  piVar6 = this + 0x793; // pointer to attachment array or children list (offset 0x1E4C)
  local_18 = DAT_00e44758; // very large negative float (e.g. -FLT_MAX)
  local_14 = DAT_00e44758;
  local_10 = DAT_00e44758;
  piVar5 = (int *)0x5;
  piVar3 = piVar6;
  do {
    (**(code **)(*this + 0xa4))(&local_c, piVar3); // virtual function: get world-space corner point
    fStack_8 = fStack_8 + local_28;
    if (local_c < local_24) {
      local_24 = local_c; // min X
    }
    if (local_18 < local_c) {
      local_18 = local_c; // max X
    }
    if (fStack_8 < local_20) {
      local_20 = fStack_8; // min Y
    }
    if (local_14 < fStack_8) {
      local_14 = fStack_8; // max Y
    }
    if (fStack_4 < local_1c) {
      local_1c = fStack_4; // min Z
    }
    if (local_10 < fStack_4) {
      local_10 = fStack_4; // max Z
    }
    piVar3 = piVar3 + 1;
    piVar5 = (int *)((int)piVar5 + -1);
  } while (piVar5 != (int *)0x0);
  // Check if this has a parent entity that should also contribute
  if (((((((char)this[0x40a] != '\0') && (this[0x3ff] != 0)) && (this[0x3ff] != 0x48)) &&
       (((this[0x3ff] != 0 && (piVar3 = (int *)(this[0x3ff] + -0x48), piVar3 != (int *)0x0))
        && ((piStack_2c = piVar5, cVar2 = (**(code **)(*piVar3 + 0x10))(0x55859efa,&piStack_2c),
            piVar3 = piStack_2c, cVar2 != '\0' &&
            ((piStack_2c != (int *)0x0 && ((char)piStack_2c[0x40a] != '\0')))))))) &&
      (piStack_2c[0x3ff] != 0)) &&
     ((piStack_2c[0x3ff] != 0x48 && (*(char *)((int)piStack_2c + 0x1029) != '\0')))) {
    iVar4 = 5;
    do {
      (**(code **)(*piVar3 + 0xa4))(&local_c, piVar6);
      fStack_8 = fStack_8 + local_28;
      if (local_c < local_24) {
        local_24 = local_c;
      }
      if (local_18 < local_c) {
        local_18 = local_c;
      }
      if (fStack_8 < local_20) {
        local_20 = fStack_8;
      }
      if (local_14 < fStack_8) {
        local_14 = fStack_8;
      }
      if (fStack_4 < local_1c) {
        local_1c = fStack_4;
      }
      if (local_10 < fStack_4) {
        local_10 = fStack_4;
      }
      piVar6 = piVar6 + 1;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  fVar9 = (local_18 - local_24) * _DAT_00d5c458; // scale factor for size (0.5 for half extents?)
  fVar10 = (local_14 - local_20) * _DAT_00d5c458;
  fVar8 = (local_10 - local_1c) * _DAT_00d5c458;
  *outSize = fVar9; // size X
  outSize[1] = fVar10; // size Y
  outSize[2] = fVar8; // size Z
  fVar1 = DAT_00d58cbc; // minimum allowed size (e.g. 0.1)
  if (((fVar9 <= 0.0) || (fVar10 <= 0.0)) || (fVar8 <= 0.0)) {
    if (fVar9 <= DAT_00d58cbc) {
      fVar9 = DAT_00d58cbc;
    }
    *outSize = fVar9;
    if (fVar10 <= fVar1) {
      fVar10 = fVar1;
    }
    outSize[1] = fVar10;
    if (fVar8 <= fVar1) {
      fVar8 = fVar1;
    }
    outSize[2] = fVar8;
  }
  if ((((uint)this[0x23b] >> 7 & 1) == 0) || // check flag for "use cached bounding box"
     (((int *)this[0x17d] != (int *)0x0 && // check if we have a valid parent
      (cVar2 = (**(code **)(*(int *)this[0x17d] + 0x38))(), cVar2 != '\0')))) {
    *outMin = *outSize + local_24; // min = size + min corner
    outMin[1] = local_20 + outSize[1];
    outMin[2] = outSize[2] + local_1c;
    *(undefined8 *)(this + 0x7c8) = *(undefined8 *)outSize; // cache the size
    this[0x7ca] = (int)outSize[2];
  }
  else {
    *outMin = (float)this[0x7c8] + local_24; // use cached size
    outMin[1] = (float)this[0x7c9] + local_20;
    outMin[2] = (float)this[0x7ca] + local_1c;
    *(undefined8 *)outSize = *(undefined8 *)(this + 0x7c8);
    outSize[2] = (float)this[0x7ca];
  }
  fVar1 = DAT_00e445a4; // some scale factor (e.g. 1.0)
  *outSize = *outSize * DAT_00e445a4;
  outSize[1] = outSize[1] * fVar1;
  outSize[2] = outSize[2] * fVar1;
  return;
}