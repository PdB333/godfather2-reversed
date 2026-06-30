// FUN_00478520: GameEngine::shutdown
void __thiscall GameEngine::shutdown(int* thisPtr)
{
  // Set vtable pointers for various subsystems (destruction phase)
  thisPtr[0] = (int)&PTR_FUN_00e32f9c;       // +0x00 main vtable
  thisPtr[1] = (int)&PTR_LAB_00e32fa0;       // +0x04 secondary vtable
  thisPtr[0x10] = (int)&PTR_LAB_00e32fbc;    // +0x40 vtable for child manager
  thisPtr[0x13] = (int)&PTR_LAB_00e32fcc;    // +0x4C vtable for resource list
  thisPtr[0x15] = (int)&PTR_LAB_00e32fd0;    // +0x54 vtable for shutdown step

  // Release global resources (mutexes, file handles, etc.)
  releaseResource((int*)&DAT_012069c4);      // FUN_004086d0
  releaseResource((int*)&DAT_01206980);      // FUN_004086d0

  // Destroy all child objects stored in the array
  int childCount = thisPtr[0x17];            // +0x5C number of children
  if (childCount > 0) {
    int* childArray = (int*)thisPtr[0x18];   // +0x60 pointer to array of object pointers
    for (int i = 0; i < childCount; i++) {
      int* obj = (int*)childArray[i];
      if (obj != 0) {
        // Virtual destroy call with argument 1 (delete memory flag)
        (*(void(__thiscall**)(int*, int))(*obj))(obj, 1);
      }
    }
  }

  // Free the child array using memory manager
  MemoryManager* memMgr = (MemoryManager*)getMemoryManager(); // FUN_009c89b0
  memMgr->vtable->free(memMgr, thisPtr[0x18], 0); // +0x04 index for free method

  // Adjust reference count of global singleton (e.g., InputManager)
  int* refCount = (int*)(DAT_01206880 + 0x14);
  *refCount += 4;  // Increment by 4 (counter or offset)

  // Set vtable for final deinitialization step
  thisPtr[0x15] = (int)&PTR_LAB_00e32854;   // +0x54

  // Perform engine‑wide shutdown routines (e.g., audio, rendering)
  shutdownEngineSystems();                   // FUN_0046c640

  // Set vtable to zombie/neutral state after shutdown
  thisPtr[0] = (int)&PTR_LAB_00e32fd4;      // +0x00

  // Clear global shutdown flag
  DAT_012233ac = 0;
}