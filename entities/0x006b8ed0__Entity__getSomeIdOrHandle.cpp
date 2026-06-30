// FUNC_NAME: Entity::getSomeIdOrHandle
int __fastcall Entity::getSomeIdOrHandle(int this)
{
  int result;
  int *pData;
  int local_4;

  local_4 = this;
  if (*(int *)(this + 0x60) != 0) {
    result = FUN_006b0ee0(*(int *)(this + 0x60)); // likely Entity::getInternalId or similar
    return result;
  }
  pData = (int *)FUN_00446100(this + 100, 0); // likely some hash/string lookup function
  if (pData != (int *)0x0) {
    local_4 = 0;
    // vtable call with hash 0x6f1d0554 - likely a method lookup
    if ((**(code **)(*pData + 0x10))(0x6f1d0554) != '\0') {
      return *(int *)(local_4 + 0x60); // return value at offset +0x60
    }
  }
  return 0;
}