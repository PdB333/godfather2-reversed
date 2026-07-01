// FUNC_NAME: UnknownClass::reinit
void __thiscall UnknownClass::reinit(void* thisPtr)
{
  // Set vtable pointer and other function pointers
  *(uint32_t**)thisPtr = &PTR_FUN_00d8b694;                    // +0x00: vtable
  thisPtr[6] = &PTR_LAB_00d8b690;                              // +0x18: some static data pointer
  thisPtr[7] = &PTR_LAB_00d8b680;                              // +0x1c: another static data pointer

  // Decrement reference counts or clean up global objects
  FUN_004086d0(&DAT_012069b4);                                 // likely atomic decrement on global ref count
  FUN_004086d0(&DAT_011301a8);                                 // another global ref count

  // If private data at offset 0x18*4 = 0x60 exists, release it
  if (thisPtr[0x18] != 0) {                                    // +0x60: pointer to sub-object
    FUN_009c8f10(thisPtr[0x18]);                               // destructor or release
  }

  // Set another vtable-like pointer
  thisPtr[10] = &PTR_FUN_00d8b674;                             // +0x28: member function pointer

  // Engine/manager initialization calls
  FUN_004de130();                                              // likely resets some manager state
  FUN_004083d0();                                              // increments a global ref count or lock

  // Update vtable pointer again (maybe to derived class)
  thisPtr[6] = &PTR_LAB_00d8b67c;                              // +0x18: changed static data pointer

  // Clear global flag
  DAT_0112a680 = 0;                                            // global "isActive" or "isInitialized" flag

  // Final initialization
  FUN_005c0190();                                              // likely completes setup
}