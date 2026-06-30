// FUNC_NAME: CObjectNode::~CObjectNode
void __fastcall CObjectNode::~CObjectNode(CObjectNode *this)
{
  int *pGlobalListHead; // pointer to global linked list head + 0x14

  // Step 1: Set vtable pointer to intermediate class vtable
  this->vfptr = (void **)&PTR_FUN_00e37fd4;

  // Remove m_pSomePointer from a global singly-linked list (if non-null)
  if (this->m_pSomePointer != 0) {
    pGlobalListHead = (int *)(DAT_012068e8 + 0x14);
    *pGlobalListHead = (int)&PTR_LAB_01124ba8; // sentinel or head update
    pGlobalListHead = (int *)*pGlobalListHead + 4;
    *pGlobalListHead = this->m_pSomePointer;
    pGlobalListHead = (int *)*pGlobalListHead + 4;
    this->m_pSomePointer = 0;
  }

  // Step 2: Set vtable pointer to another intermediate class vtable
  this->vfptr = (void **)&PTR_FUN_00e37f48;

  // Remove from doubly linked list using m_pPrev (offset +0x10) and m_pNext (offset +0x14)
  if (this->m_pPrev != 0) {
    *(int *)(this->m_pNext + 0x10) = this->m_pPrev;
    *(int *)(this->m_pPrev + 0x14) = this->m_pNext;
    this->m_pPrev = 0;
  }

  // Step 3: Set vtable pointer to base class vtable
  this->vfptr = (void **)&PTR_LAB_00e37304;
  return;
}