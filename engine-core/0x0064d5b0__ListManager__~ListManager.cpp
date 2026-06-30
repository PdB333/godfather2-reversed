// FUNC_NAME: ListManager::~ListManager
void __thiscall ListManager::~ListManager(undefined4 *this)
{
  int countOrPtr;
  undefined4 *node;
  undefined4 *nextNode;

  // Set vtable to first vtable (likely derived class)
  *this = &PTR_LAB_00e42e2c;

  // Loop while field at +0x1C (this[7]) is non-zero
  // This likely iterates over some list or decrements a reference count
  countOrPtr = this[7];
  while (countOrPtr != 0) {
    FUN_006501f0(); // Cleanup function (e.g., delete object, decrement count)
    countOrPtr = this[7];
  }

  // Remove first doubly-linked list head (this[5]) from its list
  // List structure: head at +0x14, prev at +0x0C, next at +0x10
  if (this[5] != 0) {
    if (this[3] == 0) {
      // If no previous, update head pointer (global or static)
      DAT_01205a28 = this[4];
    } else {
      // Otherwise, update previous node's next pointer
      *(undefined4 *)(this[3] + 0x10) = this[4];
    }
    if (this[4] != 0) {
      // Update next node's prev pointer
      *(undefined4 *)(this[4] + 0x0C) = this[3];
    }
  }

  // Remove second doubly-linked list head (this[8]) from its list
  // List structure: head at +0x20, prev at +0x24, next at +0x28
  if (this[8] != 0) {
    if (this[9] == 0) {
      // If no previous, update head pointer (at this[8]+4? Actually offset 4 from head)
      *(undefined4 *)(this[8] + 4) = this[10];
    } else {
      // Otherwise, update previous node's next pointer (at +0x08)
      *(undefined4 *)(this[9] + 8) = this[10];
    }
    if (this[10] != 0) {
      // Update next node's prev pointer (at +0x04)
      *(undefined4 *)(this[10] + 4) = this[9];
    }
  }

  // Set vtable to second vtable (likely base class)
  *this = &PTR_LAB_00e42de4;

  // Clear singly-linked list starting at this[1] (offset +0x04)
  // Each node has three fields: [0] = ?, [1] = ?, [2] = next pointer
  node = (undefined4 *)this[1];
  while (node != (undefined4 *)0x0) {
    nextNode = (undefined4 *)node[2];
    node[0] = 0;
    node[1] = 0;
    node[2] = 0;
    node = nextNode;
  }

  return;
}