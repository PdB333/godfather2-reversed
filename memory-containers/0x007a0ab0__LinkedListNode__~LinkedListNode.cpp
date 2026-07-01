// FUNC_NAME: LinkedListNode::~LinkedListNode
int __thiscall LinkedListNode::~LinkedListNode(int this, byte flags)
{
  // Set vtable pointer at offset +0x28
  *(void***)(this + 0x28) = &PTR_LAB_00e317cc;

  // Unlink this node from a doubly linked list with fields:
  // +0x18: prev node pointer
  // +0x1c: next node pointer
  // +0x20: some data pointer (possibly the node's value or a list head)
  int* prev = *(int**)(this + 0x18);
  if (prev != 0) {
    int* next = *(int**)(this + 0x1c);
    int* data = *(int**)(this + 0x20);
    if (next == 0) {
      // No next node: set prev's field at +4 to this node's data
      *(int*)(prev + 4) = (int)data;
    } else {
      // Has next node: set next's field at +8 to this node's data
      *(int*)(next + 8) = (int)data;
    }
    if (data != 0) {
      // Set data's field at +4 to this node's next
      *(int*)(data + 4) = (int)next;
    }
  }

  // Call base destructor or cleanup function
  FUN_0064d150();

  // If the low bit of flags is set, free memory (operator delete)
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }

  return this;
}