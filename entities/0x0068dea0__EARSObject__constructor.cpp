// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *thisObj, byte allocFlag)
{
  // Set vtable pointer (base class table)
  *thisObj = &PTR_FUN_00d5c684;
  // Initialize secondary data pointer (likely interface/type table)
  thisObj[3] = &PTR_LAB_00d5c680;
  // Call engine initialization routine (e.g., increment reference count or lock)
  FUN_004086d0(&DAT_012069c4);
  // If there is a parent/delegate object at offset 0x10 (thisObj[4]), call its third virtual method
  if ((int *)thisObj[4] != (int *)0x0) {
    (**(code **)(*(int *)thisObj[4] + 0xc))();
  }
  // Update secondary data pointer to a different table (derived class or state change)
  thisObj[3] = &PTR_LAB_00d5c67c;
  // Reset global status flag
  DAT_011298e0 = 0;
  // Call another initialization routine (e.g., finalize construction)
  FUN_004083d0();
  // If the allocation flag indicates dynamic memory, call custom deallocation (possibly error handling)
  if ((allocFlag & 1) != 0) {
    FUN_009c8eb0(thisObj);
  }
  return thisObj;
}