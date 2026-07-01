// FUNC_NAME: ObjectFactory::createInstance
// Function address: 0x007ec8e0
// This function initializes an object by storing a vtable/class pointer and calling a virtual initializer.
// It optionally creates an additional object via FUN_004265d0 and stores it at offset +4.

undefined4* __thiscall ObjectFactory::createInstance(undefined4* this, int* classPtr, int param3)
{
  undefined4 additionalObject;

  // Store the class pointer or vtable (offset 0)
  this[0] = (undefined4)classPtr;

  // Call virtual function at vtable offset 8 (likely initializer/constructor)
  (*(code**)(*classPtr + 8))();

  if (param3 != 0) {
    // Create additional object using param3 and the just-initialized this
    additionalObject = FUN_004265d0(param3, this[0]);
    this[1] = additionalObject;
    return this;
  }
  this[1] = 0;
  return this;
}