// FUNC_NAME: PacketBuffer::~PacketBuffer
void __thiscall PacketBuffer::~PacketBuffer()
{
  // Set vtable to the immediate base class destructor vtable
  this->vtable = (void **)&PTR_FUN_00e3663c;

  // If the flag at offset +0x18 is set, destroy sub-objects
  if (*(char *)(this + 0x18) != '\0') {
    FUN_004cb550();  // sub-object destructor
  }

  // Switch vtable to a further base class vtable to prevent virtual calls during member cleanup
  this->vtable = (void **)&PTR_FUN_00e32808;

  // Clear the doubly linked list starting at offset +0x04
  // Each node has two pointers: first at offset 0 (presumed prev or data) and second at offset 4 (next)
  ListNode *node = *(ListNode **)((char *)this + 4);
  while (node != (ListNode *)0x0) {
    ListNode *nextNode = *(ListNode **)((char *)node + 4);  // save next before clearing
    *(void **)((char *)node + 4) = (void *)0x0;             // clear next
    *(void **)node = (void *)0x0;                            // clear prev/data
    node = nextNode;
  }
  // Note: Node memory is not freed here; handled by sub-object destructor or externally.
}