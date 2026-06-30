// FUNC_NAME: InputManager::applyControllerStateChanges
void __thiscall InputManager::applyControllerStateChanges(int this, int controllerState)
{
  uint uVar1;
  
  uVar1 = *(uint *)(this + 0x88); // +0x88: flags to clear
  if ((uVar1 & 1) != 0) {
    FUN_006b5ac0(); // clearButtonState(0)
  }
  if ((uVar1 & 4) != 0) {
    FUN_006b2600(0); // clearAxisState(0)
  }
  if ((uVar1 & 0x10) != 0) {
    *(uint *)(controllerState + 0x34) = *(uint *)(controllerState + 0x34) & 0xffffffef; // clear bit 4
  }
  if ((uVar1 & 0x20) != 0) {
    *(uint *)(controllerState + 0x34) = *(uint *)(controllerState + 0x34) & 0xffffffdf; // clear bit 5
  }
  if ((uVar1 & 0x40) != 0) {
    *(uint *)(controllerState + 0x34) = *(uint *)(controllerState + 0x34) & 0xffffffbf; // clear bit 6
  }
  if ((char)uVar1 < '\0') {
    *(uint *)(controllerState + 0x34) = *(uint *)(controllerState + 0x34) & 0xffffff7f; // clear bit 7
  }
  if ((uVar1 & 0x100) != 0) {
    *(uint *)(controllerState + 0x34) = *(uint *)(controllerState + 0x34) & 0xfffffeff; // clear bit 8
  }
  if ((uVar1 & 0x200) != 0) {
    *(uint *)(controllerState + 0x34) = *(uint *)(controllerState + 0x34) & 0xfffffdff; // clear bit 9
  }
  if ((uVar1 & 0x400) != 0) {
    *(uint *)(controllerState + 0x34) = *(uint *)(controllerState + 0x34) & 0xfffffbff; // clear bit 10
  }
  if ((uVar1 & 0x800) != 0) {
    *(uint *)(controllerState + 0x34) = *(uint *)(controllerState + 0x34) & 0xfffff7ff; // clear bit 11
  }
  if ((uVar1 & 8) != 0) {
    *(uint *)(controllerState + 0x34) = *(uint *)(controllerState + 0x34) & 0xfffffff7; // clear bit 3
  }
  uVar1 = *(uint *)(this + 0x8c); // +0x8c: flags to set
  if ((uVar1 & 1) != 0) {
    FUN_006b5b10(); // setButtonState(0)
  }
  if ((uVar1 & 4) != 0) {
    FUN_006b2600(1); // setAxisState(1)
  }
  if ((uVar1 & 0x10) != 0) {
    *(uint *)(controllerState + 0x34) = *(uint *)(controllerState + 0x34) | 0x10; // set bit 4
  }
  if ((uVar1 & 0x20) != 0) {
    *(uint *)(controllerState + 0x34) = *(uint *)(controllerState + 0x34) | 0x20; // set bit 5
  }
  if ((uVar1 & 0x40) != 0) {
    *(uint *)(controllerState + 0x34) = *(uint *)(controllerState + 0x34) | 0x40; // set bit 6
  }
  if ((char)uVar1 < '\0') {
    *(uint *)(controllerState + 0x34) = *(uint *)(controllerState + 0x34) | 0x80; // set bit 7
  }
  if ((uVar1 & 0x100) != 0) {
    *(uint *)(controllerState + 0x34) = *(uint *)(controllerState + 0x34) | 0x100; // set bit 8
  }
  if ((uVar1 & 0x200) != 0) {
    *(uint *)(controllerState + 0x34) = *(uint *)(controllerState + 0x34) | 0x200; // set bit 9
  }
  if ((uVar1 & 0x400) != 0) {
    *(uint *)(controllerState + 0x34) = *(uint *)(controllerState + 0x34) | 0x400; // set bit 10
  }
  if ((uVar1 & 0x800) != 0) {
    *(uint *)(controllerState + 0x34) = *(uint *)(controllerState + 0x34) | 0x800; // set bit 11
  }
  if ((uVar1 & 8) != 0) {
    *(uint *)(controllerState + 0x34) = *(uint *)(controllerState + 0x34) | 8; // set bit 3
  }
  return;
}