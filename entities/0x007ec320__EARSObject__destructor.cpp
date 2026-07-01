// FUNC_NAME: EARSObject::destructor
void __fastcall EARSObject::~EARSObject(undefined4 *this)
{
  short refCount;
  
  refCount = *(short *)((int)this + 0x12); // +0x12: reference count
  *this = &PTR_FUN_00d6ffac; // vtable pointer
  while (refCount != 0) {
    FUN_00408090(); // likely release/decrement reference
    refCount = *(short *)((int)this + 0x12);
  }
  if (((undefined4 *)this[2] != (undefined4 *)0x0) && ((*(byte *)(this + 6) & 1) == 0)) {
    // +0x08: parent object pointer, +0x18: flags (bit 0 = owned)
    (*(code *)**(undefined4 **)this[2])(1); // call parent's vtable destructor
  }
  return;
}