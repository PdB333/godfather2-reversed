// FUNC_NAME: SomeGameObject::constructor
void __thiscall SomeGameObject::constructor(SomeGameObject* this)
{
  // Set vtable pointers (multiple inheritance or virtual base)
  this->vtable = &PTR_FUN_00d77a54;                      // +0x00: primary vtable
  this->field_0x3c = (void*)&PTR_LAB_00d77a44;           // +0x3C (offset 0xF*4)
  this->field_0x48 = (void*)&PTR_LAB_00d77a40;           // +0x48 (offset 0x12*4)

  // Construct sub-object at offset 0x5C (23*4)
  sub_4086d0(&this->subObjectA);                          // +0x5C: first sub-object constructor
  sub_408310(&this->subObjectA);                          // +0x5C: second stage init (likely same sub-object)

  // Construct sub-objects at offsets 0x64 and 0x6C (25*4 and 27*4)
  sub_408310(&this->subObjectB);                          // +0x64: second sub-object init
  sub_408310(&this->subObjectC);                          // +0x6C: third sub-object init

  // Call a static initialization routine (possibly global singleton or manager)
  fun_0046c640();

  return;
}