// FUNC_NAME: SomeClass::processSomething
void __fastcall SomeClass::processSomething(int this)
{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  
  // Check if some condition is met: +0x50 is zero and +0x48 is non-zero
  if ((*(int *)(this + 0x50) == 0) && (*(char *)(this + 0x48) != '\0')) {
    uVar1 = *(uint *)(this + 0x58);
    // Check if either uVar1 is zero and +0x54 > 2, or uVar1 < 5
    if (((uVar1 != 0) || (2 < *(uint *)(this + 0x54))) &&
       ((uVar1 < 5 &&
        // Access a lookup table at PTR_DAT_00e564f8, indexed by uVar1*2
        // Then compute offset: +0x54 * 100 + (+0x5c + 1) * 0x30
        iVar3 = *(int *)((&PTR_DAT_00e564f8)[uVar1 * 2] +
                         *(int *)(this + 0x54) * 100 + (*(int *)(this + 0x5c) + 1) * 0x30),
        iVar3 != -1)))) {
      // Call helper functions
      uVar2 = FUN_00923790(iVar3);
      FUN_004c3d60(uVar2,iVar3);
      FUN_00924360();
      FUN_00923590();
      // Set flag at +0x7c to 1
      *(undefined1 *)(this + 0x7c) = 1;
    }
  }
  return;
}