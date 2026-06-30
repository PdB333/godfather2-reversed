// FUNC_NAME: SimManager::~SimManager
void __fastcall SimManager::~SimManager(undefined4 *this)
{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  *this = &PTR_FUN_00d5e76c; // vtable pointer
  this[0xf] = &PTR_LAB_00d5e75c; // +0x3C
  this[0x12] = &PTR_LAB_00d5e758; // +0x48
  this[0x20] = &PTR_LAB_00d5e73c; // +0x80
  if (((uint)this[0x21] >> 0x1d & 1) != 0) { // +0x84, check flag bit 29
    FUN_0083c9b0(this + 0x20); // free/delete at +0x80
  }
  FUN_006bbb40(); // SimManager::shutdown
  FUN_004086d0(&DAT_012069c4); // release global resource
  puVar3 = this + 0x2f; // +0xBC
  iVar2 = 10;
  do {
    FUN_004086d0(puVar3); // release each slot
    FUN_00408310(puVar3); // clear/zero
    puVar3 = puVar3 + 3; // each slot is 12 bytes (3 dwords)
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  if (this[0x27] != 0) { // +0x9C
    FUN_006b5790(); // cleanup related object
  }
  if (this[0x2b] != 0) { // +0xAC
    FUN_009c8f10(this[0x2b]); // delete
  }
  iVar2 = this[0x29] + -1; // +0xA4, count
  if (-1 < iVar2) {
    iVar1 = iVar2 * 0x18; // each entry is 24 bytes
    do {
      if (*(int *)(this[0x28] + iVar1) != 0) { // +0xA0, array pointer
        FUN_004daf90(this[0x28] + iVar1); // cleanup entry
      }
      iVar2 = iVar2 + -1;
      iVar1 = iVar1 + -0x18;
    } while (-1 < iVar2);
  }
  if (this[0x28] != 0) { // +0xA0
    FUN_009c8f10(this[0x28]); // delete array
  }
  FUN_006bcd70(); // final cleanup
  return;
}