// FUNC_NAME: GodfatherGameManager::shutdown
void __fastcall GodfatherGameManager::shutdown(undefined4 *this)
{
  char cVar1;
  int *piVar2;
  
  *this = &PTR_LAB_00d6fdd8; // set vtable pointer
  FUN_007f6420(0x10); // probably memory free or resource release
  *(uint *)(this[0x16] + 0x1b94) = *(uint *)(this[0x16] + 0x1b94) & 0xffffffef; // clear bit 4
  *(uint *)(this[0x16] + 0x1b94) = *(uint *)(this[0x16] + 0x1b94) & 0xfffffffb; // clear bit 2
  piVar2 = (int *)FUN_007ab150(); // get some manager/service
  (**(code **)(*piVar2 + 4))(this[0x1e]); // call vfunc at offset 4 (probably release)
  piVar2 = (int *)FUN_007ab130(); // get another manager/service
  (**(code **)(*piVar2 + 4))(this[0x1d]); // call vfunc at offset 4
  FUN_007faca0(); // some shutdown routine
  cVar1 = FUN_008a4380(); // check if something
  if (cVar1 == '\0') {
    if (*(int *)(this[0x16] + 0x1e70) != 0) { // some pointer check
      FUN_004df600(); // release/free
    }
    if (*(int *)(this[0x16] + 0x1e84) != 0) { // another pointer check
      FUN_004df600(); // release/free
    }
  }
  *this = &PTR_LAB_00d6b95c; // restore base vtable maybe
  FUN_0080ea60(); // final cleanup
  return;
}