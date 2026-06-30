// FUNC_NAME: SomeManager::registerListener
void __thiscall SomeManager::registerListener(int this, int listener)
{
  uint count;
  int manager;
  uint i;
  int *listenerArray;
  int local_10 [3];
  code *local_4;
  
  // Call some initialization on the listener (offset +8)
  FUN_004d3bc0(listener + 8);
  
  // Get the manager object (this-4) and some local data
  manager = FUN_005653d0(this + -4, local_10);
  
  // If local_10[0] is non-zero, call it as a function pointer
  if (local_10[0] != 0) {
    (*local_4)(local_10[0]);
  }
  
  // Check if listener is already registered in the array at manager+0x10
  count = *(uint *)(manager + 0x10);
  for (i = 0; i < count; i++) {
    if (*(int *)(manager + i * 4) == listener) {
      return; // Already registered, exit
    }
  }
  
  // If array has room (max 4 entries), add the listener
  if (count < 4) {
    *(int *)(manager + count * 4) = listener; // Store listener pointer
    *(int *)(manager + 0x10) = count + 1;     // Increment count
  }
  
  // Call another function to finalize registration
  listenerArray = (int *)FUN_00564de0(this + -4, listener + 0x110);
  (**(code **)(*listenerArray + 4))(listener);
  
  return;
}