// FUNC_NAME: InputManager::allocateControllerSlot
undefined4 * InputManager::allocateControllerSlot(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *_Dst;
  
  iVar2 = DAT_012058e0; // InputManager singleton pointer
  _Dst = *(undefined4 **)(DAT_012058e0 + 0x400c); // freeListHead +0x400c
  if (_Dst == (undefined4 *)0x0) {
    if (*(int **)(DAT_012058e0 + 0x4020) == (int *)0x0) { // allocFunc +0x4020
      return (undefined4 *)0x0;
    }
    // Call allocation function to create new controller slot
    _Dst = (undefined4 *)
           (**(code **)(**(int **)(DAT_012058e0 + 0x4020) + 4))
                     (*(undefined4 *)(DAT_012058e0 + 0x4010),*(undefined4 *)(DAT_012058e0 + 0x4014));
  }
  else {
    uVar1 = *_Dst; // next free slot
    *(int *)(DAT_012058e0 + 0x4018) = *(int *)(DAT_012058e0 + 0x4018) + -1; // freeCount +0x4018
    *(undefined4 *)(iVar2 + 0x400c) = uVar1; // update freeListHead
    if (*(uint *)(iVar2 + 0x4018) < *(uint *)(iVar2 + 0x401c)) { // lowWaterMark +0x401c
      *(uint *)(iVar2 + 0x401c) = *(uint *)(iVar2 + 0x4018); // update lowWaterMark
    }
  }
  if (_Dst != (undefined4 *)0x0) {
    _memset(_Dst,0,0x44); // Clear 0x44 bytes (controller slot size)
  }
  return _Dst;
}