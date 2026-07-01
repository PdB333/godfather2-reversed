// FUNC_NAME: Player::~Player
void __thiscall Player::~Player(Player *this)
{
  ManagerA *pMgrA;
  ManagerB *pMgrB;
  void **ppItemArray;
  
  // Set vtable to derived class vtable (before base destruction)
  this->vtable = (void *)&PTR_LAB_00d6dbd0;

  // Release sub-objects via manager interfaces
  pMgrA = (ManagerA *)FUN_007ab130(); // Get the manager for type A
  (*(code **)(*pMgrA + 4))(this->m_pSubObjA); // Call release(this->m_pSubObjA)
  
  pMgrB = (ManagerB *)FUN_007ab150(); // Get the manager for type B
  (*(code **)(*pMgrB + 4))(this->m_pSubObjB); // Call release(this->m_pSubObjB)

  // Handle dynamic array of items at offset 0x62
  ppItemArray = &this->m_pItemArray;
  if (this->m_pItemArray != NULL) {
    if (this->m_pItemArray != (void **)0x48) { // Possibly sentinel value
      ItemHeader *pHeader = (ItemHeader *)((uint8_t *)this->m_pItemArray - 0x48); // Back to header
      // Release specific item from a hash/resource cache
      (*(code **)(*pHeader + 0x10))(0x369ac561, &stack0xfffffff4);
    }
    // Free the array memory
    FreeMemory(ppItemArray);
    this->m_pItemArray = NULL;
  }

  // Release several system resources (channels, streams?)
  ReleaseResource(0x37);
  ReleaseResource(0x38);
  ReleaseResource(0x39);
  ReleaseResource(0x0E);
  CleanupSubsystem();

  // Clear flag bit 9 (0x200) in the large sub-object at offset 0x16
  *(uint32_t *)(this->m_pLargeObject + 0x249C) &= ~0x200;

  // Adjust other flags based on a word at offset 0x24
  {
    uint8_t flags = *(uint8_t *)&this->m_flagsWord; // Low byte of the word
    if ((flags & 0x04) != 0) { // Bit 2
      *(uint32_t *)(this->m_pLargeObject + 0x24A0) |= 0x400000;
    } else if ((flags & 0x08) != 0) { // Bit 3
      *(uint32_t *)(this->m_pLargeObject + 0x24A0) |= 0x800000;
    }
  }

  // Free another pointer within the large sub-object (at +0x1C78)
  {
    void **ppSub = (void **)(this->m_pLargeObject + 0x1C78);
    if (*ppSub != NULL) {
      FreeMemory(ppSub);
      *ppSub = NULL;
    }
  }

  // Clear some flags and set a byte to 0xFF
  *(uint32_t *)(this->m_pLargeObject + 0x24A4) &= ~0x08;
  *(uint8_t *)(this->m_pLargeObject + 0x1EC4) = 0xFF;
  *(uint32_t *)(this->m_pLargeObject + 0x24A4) &= ~0x1000;

  // Free the array again? (duplicate check)
  if (this->m_pItemArray != NULL) {
    FreeMemory(ppItemArray);
    this->m_pItemArray = NULL;
  }

  // Cleanup other managers
  FinalizeSubsystem();

  // Release sub-object at offset 0x20
  if (this->m_pSubObject != NULL) {
    ReleaseSubObject(this->m_pSubObject);
  }

  // Transition vtable to base class vtable and call base destructor
  this->vtable = (void *)&PTR_LAB_00d6b95c;
  BaseClassDestructor();
}