// FUNC_NAME: SomeClass::~SomeClass
undefined4 * __thiscall SomeClass::dtor(SomeClass *this, byte deleteFlag)
{
  // Set vtable to current class vtable (likely this class's vtable)
  *(void ***)this = &SomeClass::vtable1; // PTR_FUN_00d58188

  // Release member at offset 0x4 if non-null
  if (this->m_somePointer != 0) {
    SomeObject::release(this->m_somePointer); // FUN_009c8f10
  }

  // Switch vtable to base class vtable (likely parent's vtable)
  *(void ***)this = &SomeBaseClass::vtable; // PTR_LAB_00d580d4

  // Clear a global flag
  g_someFlag = 0;

  // If deleteFlag indicates dynamic allocation, call operator delete
  if (deleteFlag & 1) {
    operatorDelete(this); // FUN_009c8eb0
  }

  return this;
}