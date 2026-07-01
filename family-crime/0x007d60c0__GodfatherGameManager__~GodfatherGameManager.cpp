// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
void __thiscall GodfatherGameManager::~GodfatherGameManager(GodfatherGameManager *this)
{
  int pGlobalManager;
  
  // Set vtable to derived class vtable (constructor step)
  this->vtable = (void **)&PTR_LAB_00d6f128;
  
  // Check if a child object exists at offset 0x58 (this->childObject)
  if (this->childObject != 0) {
    // Release resources with message IDs (likely audio or input)
    FUN_007f6420(0xd); // e.g., releaseAudioChannel(13)
    FUN_007f6420(0xc); // releaseAudioChannel(12)
    
    pGlobalManager = FUN_007a49d0(); // get global game manager singleton
    if ((pGlobalManager != 0) &&
       (pGlobalManager = FUN_007a49d0(), // second call may be redundant, but keep as-is
        (*(uint *)(pGlobalManager + 0xc88) & 0xfffdffff) != *(uint *)(pGlobalManager + 0xc88)))
    {
      // Call a virtual method via offset 0x28 on an object at pGlobalManager+0x58
      // This appears to be a flag clear action (bit 0x20000 = 0xfffdffff mask)
      (**(code **)(*(int *)(pGlobalManager + 0x58) + 0x28))(0x10);
      // Clear bit 0x20000 in the flag field
      *(uint *)(pGlobalManager + 0xc88) = *(uint *)(pGlobalManager + 0xc88) & 0xfffdffff;
    }
    // Shut down a subsystem
    FUN_0079d780(0);
    // Release another resource
    FUN_007f6420(0x31);
  }
  
  // Switch vtable to base class before calling base destructor
  this->vtable = (void **)&PTR_LAB_00d6b95c;
  // Call base class destructor
  FUN_0080ea60();
}