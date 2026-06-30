// FUNC_NAME: EARSObject::init
bool __thiscall EARSObject::init(EARSObject *this, void *pContext, EARSObjectDef *pDef)
{
  int *piVar1;
  float *pfVar2;
  uint uFlags;
  int iNodeIdx;
  undefined4 uVar5;
  char cReturnFlag;
  undefined1 *pOrientationData;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  float fHeight;
  int local_58;
  undefined4 local_54;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  float local_24;
  undefined4 local_20;
  int local_1c;
  undefined4 local_18;
  undefined4 *local_14;

  FUN_00533cc0(); // base class constructor
  this->vtable = &PTR_LAB_00e37940; // set vtable
  if (*(char *)(pContext + 0xd) != '\0') {
    return true; // early exit if already initialized
  }
  this->pDef = pDef; // +0x24
  this->field_0x40 = 0; // +0x40
  this->field_0x44 = 0; // +0x44
  this->field_0x38 = 0; // +0x38
  this->field_0x3c = 0; // +0x3c
  this->field_0x34 = 0; // +0x34
  this->field_0x2c = 0; // +0x2c
  FUN_004ebb40(); // initialize something (3x)
  FUN_004ebb40();
  FUN_004ebb40();
  iVar10 = **(int **)(__readfsdword(0x2c) + 0x2c); // get global pointer (e.g., engine singleton)
  FUN_0056b8a0(pDef->posX * DAT_00e445c8, pDef->posY * DAT_00e445c8, pDef->posZ * DAT_00e445c8,
               *(int *)(iVar10 + 8) + 0x10 + this->nodeIndex); // set world position with scale
  uFlags = pDef->flags; // +0x54
  this->flags = uFlags; // +0x28
  if ((uFlags & 2) == 0) {
    iNodeIdx = *(int *)(iVar10 + 8);
    iVar9 = this->nodeIndex; // +0x10
    *(undefined4 *)(iNodeIdx + 0x40 + iVar9) = pDef->rotX; // +0x5c
    iVar9 = iNodeIdx + 0x40 + iVar9;
    *(undefined4 *)(iVar9 + 4) = pDef->rotY; // +0x60
    *(undefined4 *)(iVar9 + 8) = pDef->rotZ; // +0x64
  }
  else {
    pfVar2 = (float *)(*(int *)(iVar10 + 8) + 0x40 + this->nodeIndex);
    *pfVar2 = pDef->rotX + *pfVar2;
    pfVar2[1] = pDef->rotY + pfVar2[1];
    pfVar2[2] = pDef->rotZ + pfVar2[2];
  }
  FUN_00533fb0(); // update transform
  pfVar2 = (float *)(*(int *)(iVar10 + 8) + 0x80 + this->nodeIndex);
  fHeight = *pfVar2;
  if ((*(byte *)(this + 0x28) & 6) == 0) { // check flags
    fHeight = pDef->rotZ + pfVar2[2];
  }
  if ((pDef->orientationX != 0 || pDef->orientationY != 0) ||
     (pDef->orientationZ != 0 || pDef->orientationW != 0)) {
    pOrientationData = (undefined1 *)FUN_009c8e50(0x14); // allocation (size 20)
    if (pOrientationData == (undefined1 *)0x0) {
      pOrientationData = (undefined1 *)0x0;
    }
    else {
      *(undefined4 *)(pOrientationData + 8) = 0;
      *(undefined4 *)(pOrientationData + 0xc) = 0;
      *(undefined4 *)(pOrientationData + 0x10) = 0;
      *pOrientationData = 0;
      *(undefined4 *)(pOrientationData + 4) = 1;
    }
    this->pOrientationData = pOrientationData; // +0x34
    if (pOrientationData == (undefined1 *)0x0) goto LAB_004f7ffc;
    this->orientPosX = pDef->orientationX; // +0x38
    this->orientPosY = pDef->orientationY; // +0x3c
    uVar8 = pDef->orientationZ; // +0x18
    this->field_0x44 = this->field_0x04; // +0x44 = +0x4
    this->field_0x40 = uVar8; // +0x40
    cReturnFlag = FUN_004f85a0(DAT_01205510, this->pOrientationData); // register orientation?
    if (cReturnFlag == '\0') {
      *(char *)(pContext + 0xc) = 1;
      return true;
    }
  }
  uVar8 = FUN_004f7c10(); // get animation system handle
  iVar9 = this->field_0x04; // +0x4
  if (*(int *)(iVar9 + 0xc4) == 0) {
    local_58 = 0;
  }
  else {
    local_58 = *(int *)(iVar9 + 0xc4) + -0x48;
  }
  local_18 = 0xffffffff;
  local_14 = (undefined4 *)0x0;
  if ((this->flags & 8) == 0) {
    if ((this->flags & 0x10) != 0) {
      local_18 = *(undefined4 *)(iVar9 + 0xb8);
      local_30 = pDef->rotX; // +0x5c
      local_2c = pDef->rotY; // +0x60
      local_28 = pDef->rotZ; // +0x64
      local_24 = DAT_00e2b1a4;
      local_14 = &local_30;
      fHeight = DAT_00e2b1a4;
    }
  }
  else {
    local_58 = 0;
  }
  local_54 = 0;
  if ((*(uint *)(iVar9 + 0xc) & 0x400000) != 0) {
    local_54 = 4;
  }
  local_1c = local_58;
  local_20 = 2;
  iVar9 = FUN_004f79b0(uVar8, *(undefined4 *)(iVar9 + 0x84), local_54); // create animation controller
  piVar1 = &this->pAnimController; // +0x2c
  *piVar1 = iVar9;
  if (iVar9 != 0) {
    *(int **)(iVar9 + 8) = piVar1;
    FUN_00414aa0(); // initializer?
    *(undefined4 *)(*piVar1 + 0x84) = *(undefined4 *)(this->field_0x04 + 0x84);
    if ((this->pOrientationData == 0) || (*(int *)(this->pOrientationData + 0x10) == 0)) {
      FUN_004f7940(this->field_0x04 + 0x20); // set animation? 
    }
    else {
      FUN_004ebc00(this->field_0x04, 0); // reset animation? 
      uVar5 = *(undefined4 *)(this->pOrientationData + 0xc);
      iVar9 = *(int *)(this->pOrientationData + 8);
      uVar8 = pDef->field_0x50; // +0x50
      iVar10 = *(int *)(iVar10 + 8) + iVar9;
      *(float *)(iVar10 + 0x2c) = fHeight;
      *(undefined4 *)(iVar10 + 0x28) = uVar8;
      iVar10 = FUN_004e0750(0x40); // allocate something
      if ((iVar10 != 0) && (iVar10 = FUN_004f7850(), iVar10 != 0)) {
        *(int *)(iVar10 + 0x24) = iVar9;
        *(undefined4 *)(iVar10 + 0x28) = uVar5;
        FUN_004deb00(); // finalize
        this->field_0x30 = *(undefined4 *)(pDef + 0x58);
        return true;
      }
    }
    this->field_0x30 = *(undefined4 *)(pDef + 0x58);
    return true;
  }
LAB_004f7ffc:
  *(char *)(pContext + 0xc) = 1;
  return true;
}