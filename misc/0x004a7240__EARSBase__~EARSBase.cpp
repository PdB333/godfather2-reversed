// FUNC_NAME: EARSBase::~EARSBase
void __thiscall EARSBase::~EARSBase(EARSBase *this, byte deletionFlag)
{
  int *allocator;

  this->vtable = &EARSBase_vtable_0x00e35468;
  if (this->field_0x90 != 0) {
    FUN_00610100(&this->field_0x04);
  }
  this->vtable = &EARSBase_vtable_0x00e2f638;
  if ((deletionFlag & 1) != 0) {
    allocator = (int *)FUN_009c8f80();
    (*(code **)(*allocator + 4))(this, 0xa0); // size 0xa0 = 160 bytes
  }
  return;
}