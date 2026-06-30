// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 *param_2, undefined4 *param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6)
{
  undefined8 *puVar1;
  
  // +0x04: store param_6
  this[1] = param_6;
  // +0x08: zero out byte
  *(undefined1 *)(this + 2) = 0;
  // +0x0C: pointer to linked list node
  puVar1 = (undefined8 *)(this + 3);
  *puVar1 = 0;
  // +0x14: zero out 8 bytes
  *(undefined8 *)(this + 5) = 0;
  // +0x14: also zero (overlap?)
  this[5] = 0;
  // +0x18: zero out byte
  *(undefined1 *)(this + 6) = 0;
  // +0x1C: zero out
  this[7] = 0;
  // Initialize linked list: node->next = node->prev = node
  *(undefined8 **)puVar1 = puVar1;
  // +0x10: store puVar1 (list head)
  this[4] = puVar1;
  // +0x24: store param_4
  this[9] = param_4;
  // +0x00: vtable pointer
  *this = &PTR_FUN_00d5cec4;
  // +0x28: store param_5
  this[10] = param_5;
  // Call some function on param_3 (likely a string or object)
  FUN_004dba00(*param_3, param_3[1]);
  // Call some function on param_2 (likely a string or object)
  FUN_004dba00(*param_2, param_2[1]);
  return this;
}