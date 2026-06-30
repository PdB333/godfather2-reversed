// FUNC_NAME: SomeLinkedList::destructor (or a custom list destructor)
undefined4 * __thiscall SomeLinkedListDtor(undefined4 *this, byte flags)
{
  undefined4 *current;
  undefined4 *next;
  
  *this = &PTR_FUN_00e32808; // vtable setup, likely base class destructor
  current = (undefined4 *)this[1]; // +0x04: head pointer
  while (current != (undefined4 *)0x0) {
    next = (undefined4 *)current[1]; // +0x04: next pointer in node
    current[1] = 0; // clear next
    *current = 0;   // clear node data (or vtable)
    current = next;
  }
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // operator delete or memory deallocation
  }
  return this;
}