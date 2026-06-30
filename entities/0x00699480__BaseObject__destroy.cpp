// FUNC_NAME: BaseObject::destroy
int __thiscall BaseObject::destroy(uint this, byte deleteMemory)
{
  // +0x20: pointer to first sub-object
  // +0x2c: destructor function pointer for first sub-object
  if (*(int *)(this + 0x20) != 0) {
    (**(code **)(this + 0x2c))(*(int *)(this + 0x20));
  }
  // +0x10: pointer to second sub-object
  // +0x1c: destructor function pointer for second sub-object
  if (*(int *)(this + 0x10) != 0) {
    (**(code **)(this + 0x1c))(*(int *)(this + 0x10));
  }
  // If deleteMemory flag (bit 0) is set, deallocate this object
  if ((deleteMemory & 1) != 0) {
    FUN_009c8eb0(this);  // deallocation function (likely operator delete)
  }
  return this;
}