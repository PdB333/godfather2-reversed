// FUNC_NAME: EARSObject::constructor
int __thiscall EARSObject::constructor(int thisObj, byte flag)
{
  // +0x8 points to some allocated resource or sub-object
  if (*(int *)(thisObj + 8) != 0) {
    FUN_004daf90(thisObj + 8);  // likely destroySubObject or release
  }
  // If flag & 1, deallocate the whole object (operator delete)
  if ((flag & 1) != 0) {
    FUN_009c8eb0(thisObj);  // operator delete?
  }
  return thisObj;
}