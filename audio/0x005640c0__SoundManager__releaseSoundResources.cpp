// FUNC_NAME: SoundManager::releaseSoundResources
void __fastcall SoundManager::releaseSoundResources(SoundManager *this)

{
  uint uVar1;
  int iVar2;
  
  // Release sound instance handles (slot 0xe holds reference to sound pool/instance)
  uVar1 = this->soundInstanceHandle; // +0x38 (offset 0xe * 4)
  if (-1 < (int)uVar1) {
    TlsGetValue(DAT_01139810);
    FUN_00aa26e0(this->soundPoolPointer, uVar1 & 0x3fffffff, 0x17); // +0x30 (offset 0xc * 4)
  }
  
  // Release second sound resource handle (slot 0xb)
  iVar2 = this->soundResourceHandle2; // +0x2c (offset 0xb * 4)
  if (-1 < iVar2) {
    TlsGetValue(DAT_01139810);
    FUN_00aa26e0(this->soundResourcePointer2, iVar2 << 4, 0x17); // +0x24 (offset 0x9 * 4)
  }
  
  // Release third sound resource handle (slot 8)
  iVar2 = this->soundResourceHandle3; // +0x20 (offset 0x8 * 4)
  if (-1 < iVar2) {
    TlsGetValue(DAT_01139810);
    FUN_00aa26e0(this->soundResourcePointer3, iVar2 << 4, 0x17); // +0x18 (offset 0x6 * 4)
  }
  
  // Reset vtable pointers for sound manager instance
  if (this != (SoundManager *)0x0) {
    this->vtable1 = (void *)&PTR_LAB_00d987cc; // +0x10 (offset 0x4 * 4)
    this->vtable0 = (void *)&PTR_LAB_00d96914; // +0x0
    return;
  }
  ppuRam00000000 = &PTR_LAB_00d96914;
  return;
}