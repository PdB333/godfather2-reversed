// FUNC_NAME: SomeClass::tryPlaySound
undefined4 __fastcall SomeClass::tryPlaySound(int this)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  longlong lVar5;
  
  // Check if any of the four sound ID fields are non-zero and not equal to sentinel values
  // +0x8c, +0x90, +0x94, +0x98: sound IDs
  // Sentinel values: 0xBABDBABA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911
  if (((((*(int *)(this + 0x8c) != 0) || (*(int *)(this + 0x90) != 0)) ||
       (*(int *)(this + 0x94) != 0)) || (*(int *)(this + 0x98) != 0)) &&
     (((*(int *)(this + 0x8c) != -0x45245246 || (*(int *)(this + 0x90) != -0x41104111)) ||
      ((*(int *)(this + 0x94) != -0x153ea5ab || (*(int *)(this + 0x98) != -0x6eeff6ef)))))) {
    // Compute hash from sound parameters: 0x9c, 0xa0, 0xa4, 0xa8
    // Using multiplier 0x21 (33) - likely a hash function
    uVar1 = *(uint *)(this + 0xa4);
    lVar5 = __allmul((ulonglong)*(uint *)(this + 0x9c) * 0x21 +
                     (ulonglong)*(uint *)(this + 0xa0),0x21,0);
    iVar2 = __allmul(lVar5 + (ulonglong)uVar1,0x21,0);
    iVar2 = iVar2 + *(int *)(this + 0xa8);
    uVar3 = FUN_004059b0(iVar2);  // Get sound resource by hash
    iVar4 = FUN_004025a0(uVar3);  // Get sound state
    if (iVar4 == 0) {
      iVar4 = -1;
    }
    else {
      iVar4 = *(int *)(iVar4 + 0x24);  // +0x24: sound state enum
    }
    if (iVar4 != 3) {  // Not playing
      if ((iVar4 == 0) || (iVar4 == 1)) {  // Stopped or paused
        iVar2 = FUN_004059b0(iVar2);  // Get sound resource again
      }
      else {
        iVar2 = FUN_00404280();  // Get default sound
      }
      *(int *)(this + 0x128) = iVar2;  // +0x128: current sound handle
      if (iVar2 != 0) {
        FUN_004035c0();  // Play sound
        return 1;
      }
    }
  }
  return 0;
}