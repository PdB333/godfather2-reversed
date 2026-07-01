// FUNC_NAME: MultiplayerScenarioManager::constructor
undefined4 __thiscall MultiplayerScenarioManager::constructor(undefined4 this, byte flags)

{
  // Call the base class constructor at 0x8dcea0 (likely EARSObject or similar)
  EARSObject::constructor();
  
  // If the low bit of flags is set, call the allocator/deleter at 0x43b960
  // This is the standard EA EARS pattern: if (flags & 1) allocate memory
  // The size 0x1e0 = 480 bytes is the sizeof(MultiplayerScenarioManager)
  if ((flags & 1) != 0) {
    EARSObject::operator new(this, 0x1e0);
  }
  
  return this;
}