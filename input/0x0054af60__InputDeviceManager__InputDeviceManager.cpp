// FUNC_NAME: InputDeviceManager::InputDeviceManager
void __thiscall InputDeviceManager::InputDeviceManager(InputDeviceManager *this)
{
  int slotIndex;

  // vtable pointer at offset 0x00
  this->vtable = &PTR_FUN_00e39c48;
  // +0x10: pointer to itself + 8 (possible list head)
  this->someListHead = (undefined4 *)((int)(this + 8));
  // +0x18: flags (0x80000008)
  this->flags = 0x80000008;

  // Global manager pointer (likely Singleton)
  int globalManager = DAT_00e2b1a4;

  // Initialize 8 controller slots (each 0x60 bytes)
  for (slotIndex = 0; slotIndex < 8; slotIndex++)
  {
    // Each slot layout:
    // +0x00: pointer to global manager (or parent)
    this->slots[slotIndex].parent = (undefined4 *)globalManager;
    // +0x04: handle (invalid = -1)
    this->slots[slotIndex].handle1 = 0xffffffff;
    // +0x10: handle2 (invalid = -1)
    this->slots[slotIndex].handle2 = 0xffffffff;
    // +0x30: counter or timestamp (zero)
    this->slots[slotIndex].field30 = 0;
    // +0x40: another counter or timestamp (zero)
    this->slots[slotIndex].field40 = 0;
  }

  // Additional initialization outside slots:
  // +0x04: another pointer to global manager
  this->somePointer = (undefined4 *)globalManager;
  // +0x14: flag or counter (zero)
  this->field14 = 0;
}