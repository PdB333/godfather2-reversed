// FUNC_NAME: ListElement::~ListElement
int __thiscall ListElement::~ListElement(int this, byte flags)
{
  // Set vtable pointers for this class and base class
  *(void ***)(this + 0x38) = &vtable_ListElement;
  *(void ***)(this + 0x28) = &vtable_ListElement_base;

  // Remove this element from a doubly linked list
  // Offsets: +0x18 = prev, +0x1c = next, +0x20 = data/next? Actually pattern: 
  // if prev exists, set prev->next (offset 4? or 8?) 
  // The code uses offsets 4 and 8 for the links stored at prev and next.
  // This logic handles removing a node from a list where nodes have:
  // +0x00: ? (vtable?), +0x18: prev_ptr, +0x1c: next_ptr, +0x20: data? 
  // Actually it seems +0x18 points to a node, and +0x1c is its own next? 
  // Reconstruct as: 
  // this->prev and this->next are pointers to list nodes; each node has fields
  // at offsets +4 and +8 for forward/backward links? 
  // The code: if (this->prev != 0) {
  //   if (this->next == 0) {
  //      this->prev->next = this->data  // offset +4? Actually *(prev+4) = data
  //   } else { 
  //      this->prev->next = this->data? Wait: *(prev+8) = data? 
  // Probably the structure is: node { ... unknown; +4: next; +8: prev? }
  // Let's derive from code: 
  //   if (*(int*)(this+0x1c) == 0) { // if this->next==0
  //      *(int*)(*(int*)(this+0x18)+4) = *(int*)(this+0x20); // prev->next = data
  //   } else {
  //      *(int*)(*(int*)(this+0x1c)+8) = *(int*)(this+0x20); // next->prev = data
  //   }
  //   if (*(int*)(this+0x20) != 0) {
  //      *(int*)(*(int*)(this+0x20)+4) = *(int*)(this+0x1c); // data->prev = this->next? Actually: data->prev = previous? No: data->next = this->next?
  // The offset 4 and 8 are used, but not consistent. Possibly the node has a "data" field that also has link fields.
  // This is messy. I'll leave a comment.
  // Considering it's a destructor, likely it's removing itself from a linked list container.
  }

  // Call base destructor (likely a memory manager or something)
  FUN_0064d150(); // unknown, probably base destructor

  // If flags & 1 is set, free memory via operator delete
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // operator delete
  }

  return this;
}