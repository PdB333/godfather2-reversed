// FUNC_NAME: ResourceManager::registerResource
undefined4 * __thiscall ResourceManager::registerResource(undefined4 *this, char *name, undefined4 param3, undefined4 param4, undefined4 param5)
{
  FUN_0064cc90(); // base constructor / initialization
  *this = &PTR_LAB_00d79c38; // vtable pointer (ResourceManager)
  
  _strncpy((char *)(this + 8), name, 0x3f); // copy name (63 char max)
  this[1] = param3; // +0x04: resource type or data pointer
  this[3] = param4; // +0x0C: resource size or handle
  this[2] = param5; // +0x08: additional flags/parameters
  
  this[4] = 0; // +0x10: reference count
  this[5] = 0; // +0x14: linked list next
  this[6] = 0; // +0x18: linked list prev
  this[7] = 0; // +0x1C: hash chain next
  
  this[0x1c] = DAT_012059ec; // +0x70: link into global resource list
  DAT_012059ec = this; // update global resource list head
  
  return this;
}