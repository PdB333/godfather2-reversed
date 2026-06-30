// FUNC_NAME: InputManager::initializeControllerSlots
undefined4 * __thiscall InputManager::initializeControllerSlots(undefined4 *this, undefined4 param_2)

{
  undefined4 *puVar1;
  int iVar2;
  
  // Set initial state: active = 1, some flag = 0
  this[1] = 1;
  this[2] = 0;
  // Set vtable pointer for controller slot management
  this[3] = &PTR_LAB_00d5c67c;
  // Store global singleton pointer
  DAT_011298e0 = this;
  // Store the input device manager reference
  this[4] = param_2;
  // Set base vtable
  *this = &PTR_FUN_00d5c684;
  this[3] = &PTR_LAB_00d5c680;
  
  // Initialize 18 controller slots (0x11 + 1 = 18)
  puVar1 = this + 5;
  iVar2 = 0x11;
  do {
    // Clear each slot: 9 dwords = 36 bytes per slot (0x24)
    *puVar1 = 0;
    puVar1[5] = 0;
    puVar1[6] = 0;
    puVar1[7] = 0;
    *(undefined1 *)(puVar1 + 8) = 0;
    puVar1 = puVar1 + 9;
    iVar2 = iVar2 + -1;
  } while (-1 < iVar2);
  
  // Initialize 48 additional slots (0x2f + 1 = 48)
  puVar1 = this + 0xa7;
  iVar2 = 0x2f;
  do {
    *puVar1 = 0;
    puVar1[5] = 0;
    puVar1[6] = 0;
    puVar1[7] = 0;
    *(undefined1 *)(puVar1 + 8) = 0;
    puVar1 = puVar1 + 9;
    iVar2 = iVar2 + -1;
  } while (-1 < iVar2);
  
  // Initialize 93 more slots (0x5c + 1 = 93)
  puVar1 = this + 599;
  iVar2 = 0x5c;
  do {
    *puVar1 = 0;
    puVar1[5] = 0;
    puVar1[6] = 0;
    puVar1[7] = 0;
    *(undefined1 *)(puVar1 + 8) = 0;
    puVar1 = puVar1 + 9;
    iVar2 = iVar2 + -1;
  } while (-1 < iVar2);
  
  // If input device manager exists, call its initialization
  if ((int *)this[4] != (int *)0x0) {
    (**(code **)(*(int *)this[4] + 8))();
  }
  
  // If global audio data manager exists, register this controller
  if (DAT_012069c4 != 0) {
    FUN_00408900(this,&DAT_012069c4,0x8000);
  }
  
  return this;
}