// FUN_004ab9c0: EARSObject::release
undefined4 * __thiscall EARSObject::release(undefined4 *this, byte flags)
{
  // Check if we need to finalize the object
  // Conditions: object is not empty (has children or owner) and owner's flag is zero
  if ((((this[0x10] != 0) || (this[0xf] != 0)) && (this[7] != 0)) &&
     (*(char *)(this[7] + 0x44) == '\0')) {
    EARSObject::finalize();  // FUN_004abd20 - clean up children/owner
  }
  
  // Switch vtable to base class (after finalization)
  *this = &VTable_BaseEARSObject;  // PTR_LAB_00e414e0
  
  // Decrement reference count
  int refCountPtr = GetRefCountPointerFromHandle(this[2]);  // FUN_00621530
  *(short *)(refCountPtr + 0x12) -= 1;
  
  // If flags indicate deletion, call global memory manager delete
  if ((flags & 1) != 0) {
    // g_pMemManager[1][1] -> operator delete function
    (**(code **)(**(int **)(DAT_012234ac + 4) + 4))(this, 0);
  }
  
  return this;
}