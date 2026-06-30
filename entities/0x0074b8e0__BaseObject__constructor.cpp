// FUNC_NAME: BaseObject::constructor
undefined4 * __thiscall BaseObject::constructor(BaseObject *this, byte allocFlag) {
  // Set vtable pointer at offset 0
  *this = (undefined4 *)&PTR_LAB_00d63090;

  // If subobject at offset 0x68 exists, release it
  if (this->subObject != 0) { // +0x68
    releaseSubObject((BaseObject *)((char *)this + 0x68)); // FUN_004daf90
  }

  // Global initialization routine
  initializeGlobalState(); // FUN_0080ea60

  // If heap-allocated, delete self after construction (placement delete pattern)
  if ((allocFlag & 1) != 0) {
    operatorDelete(this); // FUN_00624da0
  }

  return this;
}