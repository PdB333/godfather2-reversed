// FUNC_NAME: LinkedListNode::~LinkedListNode
// Address: 0x0079ff40
// Role: Deleting destructor for a linked list node. Unlinks the node from a doubly-linked list and deallocates memory if required.

int __thiscall LinkedListNode::~LinkedListNode(void* this, uint8_t deleteFlag)
{
  // Set vtable to base class destructor vtable
  *(void***)((uint8_t*)this + 0x28) = &PTR_LAB_00e317cc;

  // Unlink this node from the list
  // Offsets: +0x18 = prev, +0x1c = next, +0x20 = data (or auxiliary pointer)
  void* prev = *(void**)((uint8_t*)this + 0x18);
  void* next = *(void**)((uint8_t*)this + 0x1c);
  void* data = *(void**)((uint8_t*)this + 0x20);

  if (next != nullptr)
  {
    if (prev == nullptr)
    {
      // This node is the head; set next node's "prev" to data
      *(void**)((uint8_t*)next + 0x04) = data;
    }
    else
    {
      // Set prev node's "next" to data
      *(void**)((uint8_t*)prev + 0x08) = data;
    }
  }

  if (data != nullptr)
  {
    // Set data's "prev" to prev
    *(void**)((uint8_t*)data + 0x04) = prev;
  }

  // Call base class destructor
  FUN_0064d150();

  // Delete memory if flag indicates scalar deletion
  if (deleteFlag & 1)
  {
    FUN_009c8eb0(this); // operator delete
  }

  return (int)this;
}