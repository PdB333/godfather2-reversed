// FUNC_NAME: Player::updateCameraOrSomething
void __thiscall Player::updateCameraOrSomething(int *this, undefined4 param_2, undefined4 *param_3)
{
  int iVar1;
  undefined1 *puVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 unaff_EBX;
  uint uVar6;
  int *piVar7;
  int *piVar8;
  undefined4 uStack_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  
  // Call virtual function at offset 0x18 (likely getCameraTransform or similar)
  (**(code **)(*this + 0x18))(param_2, &local_20);
  
  // Get string from param_3, default to some global string if null
  puVar2 = (undefined1 *)*param_3;
  if (puVar2 == (undefined1 *)0x0) {
    puVar2 = &DAT_0120546e;
  }
  FUN_004ec1c0(puVar2); // Likely debug/log function
  
  iVar1 = this[6]; // +0x18 - some sub-object pointer
  *(undefined4 *)(iVar1 + 0x10) = unaff_EBX;
  *(undefined4 *)(iVar1 + 0x14) = uStack_24;
  *(undefined4 *)(iVar1 + 0x18) = local_20;
  *(undefined4 *)(iVar1 + 0x1c) = uStack_1c;
  FUN_004df830(this[6]); // Likely updateTransform or similar
  
  if (*(char *)((int)this + 0x171) == '\0') { // +0x171 - flag for something
    uVar3 = FUN_004ee450(this + 5); // +0x14 - some collection/array
    uVar6 = 0;
    if (uVar3 != 0) {
      while( true ) {
        iVar4 = FUN_004ee3a0(this + 5, uVar6); // Get element at index
        iVar1 = _DAT_00d5780c; // Global variable
        if ((iVar4 != 0) && (*(int *)(iVar4 + 0x24) != 0)) break; // +0x24 - some pointer
        uVar6 = uVar6 + 1;
        if (uVar3 <= uVar6) {
          return;
        }
      }
      piVar7 = *(int **)(iVar4 + 0x24); // Dereference pointer at +0x24
      piVar8 = this + 0x10; // +0x40 - destination buffer
      for (iVar5 = 0x26; iVar5 != 0; iVar5 = iVar5 + -1) { // Copy 0x26*4 = 0x98 bytes
        *piVar8 = *piVar7;
        piVar7 = piVar7 + 1;
        piVar8 = piVar8 + 1;
      }
      // Set various fields from globals
      this[0x22] = iVar1; // +0x88
      this[0x14] = DAT_00d5f208; // +0x50
      this[0x20] = _DAT_00d77da8; // +0x80
      iVar1 = DAT_00d77da4;
      this[0x11] = 0x2d2307a5; // +0x44 - some constant
      *(undefined2 *)(this + 0x1b) = 0x81; // +0x6c - set to 0x81
      this[0x19] = iVar1; // +0x64
      FUN_004ee5a0(this + 0x10); // +0x40 - process/update the copied data
      *(undefined1 *)((int)this + 0x171) = 1; // Set flag to 1
    }
  }
  return;
}