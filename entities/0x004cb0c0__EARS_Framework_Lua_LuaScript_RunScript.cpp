// Xbox PDB: EARS::Framework::Lua::LuaScript::RunScript
// FUNC_NAME: EARSObject::release
void EARSObject::release(void (*callback)(void))
{
  // this is in EAX (implicit)
  if (this == nullptr) {
    return;
  }

  // Check if this is the last reference or if object can be destroyed
  if (FUN_00629280() != 0) {
    // Not last reference, skip deletion
    FUN_006255e0();
    return;
  }

  // Prepare memory block descriptor for deallocation
  int blockDescriptor[3];
  blockDescriptor[0] = *(int *)(this + 0x8) - 8;  // +0x8: pointer to allocation header? Subtract 8 to get base
  blockDescriptor[1] = 0xFFFFFFFF;                // Flag: invalid or free
  int size = blockDescriptor[0] - *(int *)(this + 0x1c); // +0x1c: offset to size or end marker

  // Attempt to deallocate the object's memory
  if (FUN_00636570(&g_Allocator, blockDescriptor, size) == 0) {
    // Deallocation succeeded, call the destructor callback if provided
    if (callback != nullptr) {
      callback();
    }
  }

  // Final cleanup (e.g., decrement global reference count)
  FUN_006255e0();
}