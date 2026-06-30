// FUNC_NAME: BaseObject::~BaseObject
// Function at 0x007143b0 - Destructor for a base object with two sub-objects at +0x04 and +0x0C
// Called with a flag in param_2 (bit 0: whether to operator delete this)
// The vtable pointer is set to &PTR_LAB_00e2f0c0 (base class vtable)
// Sub-objects are deallocated via FUN_004daf90

undefined4 * __thiscall BaseObject::~BaseObject(undefined4 *this, byte deleteFlag)
{
  if (*(int *)(this + 3) != 0) {
    FUN_004daf90(this + 3); // deallocate sub-object at +0x0C
  }
  if (*(int *)(this + 1) != 0) {
    FUN_004daf90(this + 1); // deallocate sub-object at +0x04
  }
  *this = &PTR_LAB_00e2f0c0; // restore base vtable
  if ((deleteFlag & 1) != 0) {
    FUN_009c8eb0(this); // operator delete
  }
  return this;
}