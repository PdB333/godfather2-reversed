// FUNC_NAME: NetworkManager::shutdown
void __fastcall NetworkManager::shutdown(undefined4 *this)
{
  int iVar1;
  char cVar2;
  undefined4 *puVar3;
  
  iVar1 = this[0x16]; // +0x58 - pointer to base address
  *this = &PTR_LAB_00d6fa60; // set vtable to base destructor
  FUN_007ab4d0(0x17); // shutdown network layer 23
  FUN_007ab4d0(0x18); // shutdown network layer 24
  FUN_007ab4d0(0x19); // shutdown network layer 25
  cVar2 = FUN_00481620(); // check if online services are active
  if (cVar2 != '\0') {
    FUN_0093b080(); // shutdown online services
  }
  FUN_007f6420(9); // release resource 9
  FUN_007f6420(0x42); // release resource 66
  puVar3 = (undefined4 *)(iVar1 + 0x1c78); // +0x1C78 - some pointer
  if (*(int *)(iVar1 + 0x1c78) != 0) {
    FUN_004daf90(puVar3); // free memory
    *puVar3 = 0;
  }
  FUN_004df600(); // clear network queue
  FUN_004df600(); // clear network queue (second time)
  if (this[0x9b] != 0) { // +0x26C - some pointer
    FUN_004daf90(this + 0x9b); // free memory
  }
  iVar1 = this[0x9a]; // +0x268 - pointer to object
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 8) = 0; // clear pointer at offset +8
    this[0x9a] = 0;
  }
  iVar1 = this[0x99]; // +0x264 - pointer to another object
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 8) = 0; // clear pointer at offset +8
    this[0x99] = 0;
  }
  FUN_007affe0(); // shutdown connection manager
  FUN_007affe0(); // shutdown connection manager (second time)
  *this = &PTR_LAB_00d6b95c; // set vtable to base class
  FUN_0080ea60(); // base class cleanup
  return;
}