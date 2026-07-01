// FUNC_NAME: GodfatherGameManager::initializeSubsystem

void __fastcall GodfatherGameManager::initializeSubsystem(GodfatherGameManager* thisObj)
{
  // Set vtable pointer to global vtable at 0xd67c48
  thisObj->vtablePtr = &PTR_LAB_00d67c48;

  // Initialize subsystem with ID 0x11 (likely a heap or stream index)
  MemoryManager::setActiveHeap(0x11);

  // Sub-object at offset +0x58
  SubObject* subObj = reinterpret_cast<SubObject*>(reinterpret_cast<char*>(thisObj) + 0x58);

  // Clear bit 16 (0x10000) in flags at +0x1f58
  subObj->flagsAt1f58 &= ~0x10000;

  // Clear bits 0x200A (bits 1,3,9,13) in flags at +0x1b94  
  // Mask 0xffffdff5 keeps all bits except those cleared
  subObj->flagsAt1b94 &= ~0x200A;

  // Check global initialization state
  if (!GlobalManager::isReady()) {
    // Release resources if pointers are non-zero
    if (subObj->pointerAt1e70 != 0) {
      ResourceManager::release(subObj->pointerAt1e70);
    }
    if (subObj->pointerAt1e84 != 0) {
      ResourceManager::release(subObj->pointerAt1e84);
    }
  }

  // Additional post-init steps
  GodfatherGameManager::postInitialize();
  GodfatherGameManager::finalizeInitialization();
}