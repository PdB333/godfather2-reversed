// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
void __thiscall GodfatherGameManager::destructor(GodfatherGameManager *this)
{
  ListNode *pNext; // eax
  ListNode *pCur; // eax
  int iVar2; // esi
  ListNode *pIter; // eax

  // Set initial vtable
  this->vtable = (void **)&PTR_FUN_00d61b00;
  // Set sub-manager vtable
  this->m_subManager->vtable = (void **)&PTR_FUN_00d61aec;

  // Free sub-manager if allocated
  if (this->m_subManager->m_data != 0) {
    FUN_007eea00(); // likely frees internal data
  }

  // Notify all objects in linked list about destruction
  for (pIter = (ListNode *)this->m_objectList; pIter != (ListNode *)0x0;
      pIter = (ListNode *)pIter->next) {
    (**(code **)(*(int *)pIter->vtable + 8))(this); // virtual call on each object
  }

  // Cleanup sub-manager (this + 0xc3)
  FUN_007ee320(this->m_subManager);
  // Cleanup another sub-object (offset 0xc3)
  FUN_007ee320(this + 0xc3);

  // Cleanup another subsystem
  FUN_0071d610();

  // Free all objects in linked list
  pCur = (ListNode *)this->m_objectList;
  while (pCur != (ListNode *)0x0) {
    iVar2 = pCur->next;
    (**(code **)(*(int *)this->m_allocator->vtable + 4))(pCur, 0); // delete object via allocator
    pCur = (ListNode *)iVar2;
  }

  // Free single object if present
  if (this->m_someObject != (ListNode *)0x0) {
    (**(code **)(*(int *)this->m_allocator->vtable + 4))(this->m_someObject, 0);
  }

  // Final cleanup on allocator
  (**(code **)(*(int *)this->m_allocator->vtable + 12))(); // probably freePool

  // Free two pointers
  if (this->m_ptr1 != 0) {
    FUN_004daf90(this + 0xce); // offset 0xce = m_ptr1
  }
  if (this->m_ptr2 != 0) {
    FUN_004daf90(this + 0xcc); // offset 0xcc = m_ptr2
  }

  // Update sub-manager vtable again
  this->m_subManager->vtable = (void **)&PTR_FUN_00d61adc;
  if (this->m_ptr3 != 0) {
    FUN_004daf90(this + 199); // offset 199 = m_ptr3
  }

  // Mark sub-manager with final vtable
  this->m_subManager->vtable = (void **)&PTR_LAB_00d61acc;

  // Call subsystem destructors
  FUN_00713650();   // likely subsystemA::~subsystemA
  FUN_00712390();   // likely subsystemB::~subsystemB
  FUN_0071e450();   // likely subsystemC::~subsystemC
  FUN_0071d6a0();   // likely subsystemD::~subsystemD
  thunk_FUN_00722190(); // likely subsystemE::~subsystemE
  FUN_0071b220();   // likely subsystemF::~subsystemF

  // Final vtable marker
  this->vtable = (void **)&PTR_LAB_00d61acc;
  return;
}