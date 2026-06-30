// FUNC_NAME: SomeLinkedList::~SomeLinkedList
undefined4 * __thiscall SomeLinkedList::~SomeLinkedList(undefined4 *this, byte param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  *this = &PTR_FUN_00e32808; // vtable setup
  puVar2 = (undefined4 *)this[1]; // head of linked list (offset +0x04)
  while (puVar2 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)puVar2[1]; // next node pointer (offset +0x04 in node)
    puVar2[1] = 0; // clear next pointer
    *puVar2 = 0; // clear node data
    puVar2 = puVar1;
  }
  if ((param_2 & 1) != 0) {
    FUN_009c8eb0(this); // operator delete
  }
  return this;
}