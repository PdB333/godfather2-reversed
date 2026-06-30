// FUNC_NAME: Entity::shutdown
void __thiscall Entity::shutdown(void)
{
  // Call base class or internal method with flag 1 (likely 'shutdown' or 'disable')
  internalShutdown((int)this, 1);

  // Check if there's an attached child object at offset +0x1b0
  int* childObject = *(int**)((char*)this + 0x1b0);
  if (childObject != NULL)
  {
    // Call a method on the child passing values at offsets +0x98 and +0x90, with a flag 1
    // +0x98 and +0x90 are probably position or rotation data
    callChildMethod(childObject, *(int*)((char*)this + 0x98), *(int*)((char*)this + 0x90), 1);

    // Log or debug message: type 3 with child object pointer
    logMessage(3, (int)childObject);
  }

  // Update global state (possibly end-of-frame tasks)
  updateGlobalState();

  // Another global housekeeping call
  globalHousekeeping();
}