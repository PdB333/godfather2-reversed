// FUNC_NAME: QueueNode::destructor
undefined4 * __thiscall QueueNode_destructor(undefined4 *this,byte flags)

{
  undefined4 *current;
  undefined4 *next;
  
  *this = &PTR_FUN_00e32808;
  current = (undefined4 *)this[1];
  while (current != (undefined4 *)0x0) {
    next = (undefined4 *)current[1];
    current[1] = 0;
    *current = 0;
    current = next;
  }
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  return this;
}