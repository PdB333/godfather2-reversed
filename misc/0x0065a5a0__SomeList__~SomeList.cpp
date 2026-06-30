// FUNC_NAME: SomeList::~SomeList
undefined4 * __thiscall SomeList::~SomeList(undefined4 *this, byte param_2)

{
  undefined4 *nextNode;
  undefined4 currentNode;
  
  *this = &PTR_LAB_00e42de4; // vtable setup
  currentNode = this[1]; // +0x04 head pointer
  while (currentNode != (undefined4 *)0x0) {
    nextNode = (undefined4 *)currentNode[2]; // +0x08 next pointer
    *currentNode = 0; // clear data
    currentNode[1] = 0; // clear data
    currentNode[2] = 0; // clear next
    currentNode = nextNode;
  }
  if ((param_2 & 1) != 0) {
    FUN_009c8eb0(this); // operator delete
  }
  return this;
}