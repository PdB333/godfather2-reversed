// FUNC_NAME: AptValue::releaseReference
void __thiscall AptValue::releaseReference(uint *this) {
  uint *puVar1;
  int *piVar2;
  code *pcVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int unaff_FS_OFFSET;
  undefined1 *puStack_14;
  char *pcStack_10;
  undefined4 uStack_c;
  int iStack_8;
  undefined1 *puStack_4;

  if ((~(byte)(*this >> 0xf) & 1) != 0) {
    return; // return if reference count bit (bit 15) is already clear
  }

  // Function at 0x005aab30 - likely removes from global pool or similar
  FUN_005aab30(this);
  // Function at 0x005aaa20 - likely mutex unlock or similar
  FUN_005aaa20(this);

  iVar8 = 0;
  // Global static at DAT_0119a9cc, offset +0x1c08 holds count of items in a list
  if (0 < *(int *)(DAT_0119a9cc + 0x1c08)) {
    iVar7 = 0x1408;
    iVar4 = DAT_0119a9cc;
    do {
      puVar1 = *(uint **)(iVar7 + iVar4);
      if (puVar1 == this) {
        // Calls a virtual function via vtable at DAT_0103aee0
        // The vtable index is derived from the object's type (bits 0-14)
        (**(code **)(&DAT_0103aee0 + (*puVar1 & 0x7fff) * 4))(puVar1);
        iVar4 = DAT_0119a9cc;
        // Remove from list by swapping with last element
        *(undefined4 *)(iVar7 + DAT_0119a9cc) = 
             *(undefined4 *)(DAT_0119a9cc + 0x1404 + *(int *)(DAT_0119a9cc + 0x1c08) * 4);
        *(int *)(iVar4 + 0x1c08) = *(int *)(iVar4 + 0x1c08) + -1;
      }
      iVar8 = iVar8 + 1;
      iVar7 = iVar7 + 4;
    } while (iVar8 < *(int *)(iVar4 + 0x1c08));
  }

  // The lower 15 bits of the object's type/header word determine the action
  switch(*this & 0x7fff) {
  case 0xc: // Type 0xC - likely a specific AptValue subclass
    FUN_0059c3b0(); // Probably some manager/context function
    iVar8 = FUN_005a8340(); // Create a value object
    if (iVar8 != 0) {
      FUN_005a43a0(iVar8); // Initialize the value
      (*DAT_0119caf8)(iVar8, 0x10); // Free callback or destructor, size 0x10
      *(undefined1 *)(this + 0x19) = 0; // Clear some flag at offset +0x64
      this[0x16] = 0; // Clear value at offset +0x58
      return;
    }
    break;

  case 0xd: // Type 0xD - another specific subclass
    FUN_0059c3b0();
    iVar8 = FUN_005a3e80(); // Create different value object
    if (iVar8 != 0) {
      FUN_005a4600(); // Initialize
      (*DAT_0119caf8)(iVar8, 0x24); // Free callback, size 0x24
      *(undefined1 *)(this + 0x19) = 0;
      this[0x16] = 0;
      return;
    }
    break;

  case 0xf: // Type 0xF
    FUN_0059c3b0();
    iVar8 = FUN_0059c810(); // Create another value type
    if (iVar8 != 0) {
      FUN_005a8c90(); // Initialize
      (*DAT_0119caf8)(iVar8, 0x5c); // Free callback, size 0x5c
      *(undefined1 *)(this + 0x19) = 0;
      this[0x16] = 0;
      return;
    }
    break;

  case 0x12: // Type 0x12
    iVar8 = FUN_005a3f20();
    if (iVar8 != 0) {
      uVar5 = FUN_0059c3b0();
      FUN_005a61e0(uVar5); // Initialize with manager context
    }
    FUN_0059c3b0();
    iVar8 = FUN_0059c8b0(); // Create another value
    if (iVar8 != 0) {
      FUN_005ab220(); // Initialize
      *(undefined1 *)(this + 0x19) = 0;
      this[0x16] = 0;
      return;
    }
    break;

  case 0x13: // Type 0x13 - falls through to default cleanup
    break;

  default:
    // Assertion/error handling - prints debug info from AptValue.cpp line 0x3a0
    puStack_14 = &DAT_00e36da0;
    pcStack_10 = "..\\source\\Apt\\AptValue.cpp";
    uStack_c = 0x3a0;
    iStack_8 = 2;
    puStack_4 = &DAT_01128fc6;
    if (DAT_01128fc6 != '\0') {
      piVar2 = *(int **)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x30);
      uVar6 = 1;
      if (((piVar2 == (int *)0x0) ||
          (uVar6 = (**(code **)(*piVar2 + 8))(&puStack_14, &DAT_00e36da0),
          puStack_4 != (undefined1 *)0x0)) && ((uVar6 & 2) != 0)) {
        *puStack_4 = 0;
      }
      if (((piVar2 != (int *)0x0) || (iStack_8 != 4)) &&
         (((uVar6 & 1) != 0 || ((iStack_8 == 0 || (iStack_8 == 1)))))) {
        pcVar3 = (code *)swi(3); // This is likely a debug break/int3
        (*pcVar3)();
        return;
      }
    }
    break;
  }

  // Cleanup flags for unhandled types or fallthrough cases
  *(undefined1 *)(this + 0x19) = 0;
  this[0x16] = 0;
}