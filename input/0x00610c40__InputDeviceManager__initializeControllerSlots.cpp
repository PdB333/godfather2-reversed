// FUNC_NAME: InputDeviceManager::initializeControllerSlots
void InputDeviceManager::initializeControllerSlots(void)
{
  // Stack-based array for initialization parameters (3 dwords)
  undefined4 initParams[3];
  void *slotMemory;
  
  initParams[0] = 0;
  initParams[1] = 0;
  initParams[2] = 0;
  
  // DAT_01205868 likely a vtable/allocator, allocate 0x44000 bytes for all controller slots
  // (16 slots * 0x44 bytes each = 0x440, not 0x44000. Possibly 256 slots or larger struct)
  // Note: 0x44000 / 0x44 = 0x1000 = 4096 slots? Unlikely. Maybe allocation size includes padding)
  DAT_012058e4 = (**(code **)*DAT_01205868)(0x44000, &initParams);
  
  // Allocate slot state array: 0x4024 bytes (16 * 0x4024? No. 0x4024 fits no clear multiple)
  slotMemory = (void *)FUN_009c8e50(0x4024);
  if (slotMemory != (void *)0x0) {
    // Clear each slot header at offset 0x4000 (slot 0?)
    *(undefined4 *)((int)slotMemory + 0x4000) = 0;
    // Zero out first 0x4000 bytes
    _memset(slotMemory, 0, 0x4000);
    
    // Initialize controller slot structures
    // DAT_012058e4: allocated block (0x44000 bytes)
    // Parameters: block, size=0x44000, elementSize=0x44, alignment=4
    FUN_004abe90(DAT_012058e4, 0x44000, 0x44, 4);
    
    // Store slot array pointer
    DAT_012058e0 = slotMemory;
    return;
  }
  
  DAT_012058e0 = (void *)0x0;
  return;
}