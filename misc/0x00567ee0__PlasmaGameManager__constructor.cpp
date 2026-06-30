// FUNC_NAME: PlasmaGameManager::constructor
void __thiscall PlasmaGameManager::constructor(void *this)
{
  // +0x00: vtable pointer
  *(undefined4 *)this = &PTR_FUN_00e3a9e0;
  // +0x04: second vtable pointer
  *(undefined4 *)((int)this + 4) = &PTR_LAB_00e3aa7c;
  // +0x08: next vtable pointer
  *(undefined4 *)((int)this + 8) = &PTR_LAB_00e3aa78;
  // +0x0C: some pointer (initialized to 0)
  *(undefined4 *)((int)this + 0xc) = 0;
  // +0x10: another pointer (initialized to 0)
  *(undefined4 *)((int)this + 0x10) = 0;
  
  // Call string initialization function with "Plasma Game Manager Default ID"
  FUN_004d3bc0("Plasma Game Manager Default ID");
  
  // +0x20: some field (offset 8 words = 0x20)
  *(undefined4 *)((int)this + 0x20) = 0;
  // +0x28: some field (offset 10 words = 0x28)
  *(undefined4 *)((int)this + 0x28) = 0;
  // +0x2C: some field (offset 11 words = 0x2C)
  *(undefined4 *)((int)this + 0x2c) = 0;
  // +0x30: some field (offset 12 words = 0x30)
  *(undefined4 *)((int)this + 0x30) = 0;
  // +0x34: some field (offset 13 words = 0x34)
  *(undefined4 *)((int)this + 0x34) = 0;
  
  // Call some initialization function
  FUN_00b1a890();
  
  // +0x34C: vtable pointer (offset 0xD3 words = 0x34C)
  *(undefined4 *)((int)this + 0x34c) = &PTR_LAB_00e3a9d8;
  // +0x350: some field (offset 0xD4 words = 0x350)
  *(undefined4 *)((int)this + 0x350) = 0;
  // +0x354: some field (offset 0xD5 words = 0x354)
  *(undefined4 *)((int)this + 0x354) = 0;
  // +0x358: some field (offset 0xD6 words = 0x358)
  *(undefined4 *)((int)this + 0x358) = 0;
  // +0x35C: some field (offset 0xD7 words = 0x35C)
  *(undefined4 *)((int)this + 0x35c) = 0;
  
  return;
}