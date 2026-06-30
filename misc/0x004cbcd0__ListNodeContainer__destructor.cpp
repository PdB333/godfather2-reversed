// FUNC_NAME: ListNodeContainer::destructor
undefined4 * __thiscall ListNodeContainer::destructor(ListNodeContainer *this, byte param_2)
{
  undefined4 *current;
  undefined4 *next;
  
  this->vtable = &PTR_FUN_00e32808; // set vtable to base class
  current = (undefined4 *)this->head; // +0x04: linked list head pointer
  while (current != (undefined4 *)0x0) {
    next = (undefined4 *)current[1]; // +0x04: next node pointer
    current[1] = 0; // clear next pointer
    *current = 0;  // clear data
    current = next;
  }
  if ((param_2 & 1) != 0) {
    FUN_009c8eb0(this); // deallocation call (operator delete or custom free)
  }
  return this;
}