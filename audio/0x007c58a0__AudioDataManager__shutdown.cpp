// FUNC_NAME: AudioDataManager::shutdown
void __fastcall AudioDataManager::shutdown(undefined4 *this)
{
  int *pVtable;
  
  // Set initial vtable (likely during cleanup)
  *this = &PTR_LAB_00d6e7c4;
  
  // Release audio stream or resource pointer at offset 0x94
  pVtable = (int *)FUN_007ab130(); // Likely getInstance() of some manager
  (**(code **)(*pVtable + 4))(this[0x25]); // Call release via vtable (offset 4)
  
  // Release at offset 0x98
  pVtable = (int *)FUN_007ab140();
  (**(code **)(*pVtable + 4))(this[0x26]);
  
  // Release at offset 0x9C
  pVtable = (int *)FUN_007ab150();
  (**(code **)(*pVtable + 4))(this[0x27]);
  
  // Release manager reference (no parameter)
  FUN_007ab120();
  
  // Release object at offset 0xA0 (likely a stream reference)
  FUN_00896e10(this[0x28]); // Possibly release a contained object
  
  // Free sound resources by IDs
  FUN_007f6420(0x31); // Release sound bank or effect ID 0x31
  FUN_007f6420(0x5d); // Release sound bank or effect ID 0x5d
  
  // Free memory pool (size 0x100)
  FUN_00897830(0x100);
  
  // Switch to final vtable (base class or null)
  *this = &PTR_LAB_00d6b95c;
  
  // Call final cleanup
  FUN_0080ea60(); // Likely deinitializes module
}