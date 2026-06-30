// FUNC_NAME: GodfatherGameManager::constructor
GodfatherGameManager * __thiscall GodfatherGameManager::constructor(GodfatherGameManager *this, byte allocateFlag)
{
  // +0x0: primary vtable pointer
  this->vtable = &g_GodfatherGameManagerVTable;
  // +0x8: pointer to internal descriptor/vtable (set to first label)
  this->m_pDescriptor = &g_DescriptorLabel1;
  
  // Initialize base subsystems
  this->initBase();
  
  // Call a virtual function on embedded sub-object at offset 0xC
  // param_1[3] is this->m_pEmbeddedObject; its first DWORD is a vtable
  void *embedded = this->m_pEmbeddedObject; // +0xC
  uint *embeddedVtable = *(uint **)embedded;
  ((void (*)(void))embeddedVtable[3])(); // offset 0xC (0xC/4 = 3)
  
  // Second initialization step
  this->initSubsystem();
  
  // Update the descriptor pointer
  this->m_pDescriptor = &g_DescriptorLabel2; // +0x8
  
  // Reset global initialization flag
  g_GodfatherGameManagerInitialized = 0;
  
  // Final initialization call (likely sets up static data)
  this->resetGlobals();
  
  // If allocation flag is set (bit 0), free the object (e.g., placement new failure path)
  if (allocateFlag & 1) {
    operator delete(this);
  }
  
  return this;
}