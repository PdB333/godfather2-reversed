// FUNC_NAME: CBaseNode::~CBaseNode

void __thiscall CBaseNode::~CBaseNode(CBaseNode *this)
{
  int *childPtrA;
  int childPtrB;
  CBaseNode *currentNode;
  CBaseNode *nextNode;

  childPtrA = (int *)&this->field_0x4C;
  this->vtable = (void *)&PTR_FUN_00d78684;
  this->field_0x0C = (void *)&PTR_LAB_00d78620;
  this->field_0x1C = (void *)&PTR_LAB_00d78618;
  if (*childPtrA != 0) {
    releaseChild(*childPtrA); // FUN_004df600
  }
  if (this->field_0x50 != 0) {
    releaseChild(this->field_0x50); // FUN_004df600
  }
  globalCleanupStep1(); // FUN_00481570
  unregisterFromManager(&DAT_012069c4); // FUN_004086d0
  childPtrB = this->field_0x50;
  if (childPtrB != 0) {
    *(int *)(childPtrB + 8) = 0;
    this->field_0x50 = 0;
  }
  if (*childPtrA != 0) {
    *(int *)(*childPtrA + 8) = 0;
    *childPtrA = 0;
  }
  this->field_0x1C = (void *)&PTR_FUN_00e32808;
  currentNode = (CBaseNode *)this->childListHead;
  while (currentNode != (CBaseNode *)0x0) {
    nextNode = (CBaseNode *)currentNode->next;
    currentNode->next = 0;
    currentNode->data = 0;
    currentNode = nextNode;
  }
  globalCleanupStep2(); // FUN_00481520
  globalCleanupStep3(); // FUN_004083d0
  return;
}