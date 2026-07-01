// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
void __thiscall GodfatherGameManager::destructor(GodfatherGameManager *this)
{
  // Set vtable to base class pointers (likely for cleanup chain)
  this->vtable0 = &PTR_FUN_00d8159c;   // +0x00
  this->vtable1 = &PTR_LAB_00d81598;   // +0x04
  this->vtable2 = &PTR_LAB_00d81588;   // +0x08

  // Cleanup static globals
  FUN_004086d0(&DAT_012069b4);          // Unknown cleanup function
  FUN_00408310(&DAT_0112fed4);          // Release/destroy static object
  FUN_00408310(&DAT_0112feb8);
  FUN_00408310(&DAT_0112fec4);
  FUN_00408310(&DAT_0112fecc);
  FUN_00408310(&DAT_0112fedc);

  // Debug print (hash 0x4aba815 likely corresponds to a shutdown message)
  FUN_004639e0(0x4aba815);

  // Destroy object at +0x30 via a function pointer stored at +0x3C
  if (this->m_pObjectToDestroy != NULL) {               // +0x30
    (*(code *)this->m_pDestroyFunc)(this->m_pObjectToDestroy); // +0x3C
  }

  // Clear pointer at +0x2C, also zero out a field inside that object
  if (this->m_pSomePtr != NULL) {                       // +0x2C
    *(int *)(this->m_pSomePtr + 8) = 0;                 // Zero a field in that object
    this->m_pSomePtr = NULL;                             // +0x2C
  }

  // Destroy object at +0x20
  if (this->m_pAnotherObj != NULL) {                    // +0x20
    FUN_009c8f10(this->m_pAnotherObj);                  // Destructor call
  }

  // Final cleanup
  FUN_004083d0();

  // Restore vtable to base class and clear global flags
  this->vtable1 = &PTR_LAB_00d814f0;                    // +0x04
  DAT_011299c4 = 0;                                     // Global shutdown flag
  this->vtable0 = &PTR_LAB_00e30fe0;                    // +0x00
}