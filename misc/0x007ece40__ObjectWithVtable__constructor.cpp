// FUNC_NAME: ObjectWithVtable::constructor
undefined4 * __thiscall ObjectWithVtable::constructor(undefined4 *this, int *vtablePtr, int sourceObj)
{
  undefined4 uVar1;
  
  // Set vtable pointer (first member)
  *this = vtablePtr;
  
  // Call base constructor (vtable entry at offset 8)
  (**(code **)(*vtablePtr + 8))();
  
  if (sourceObj != 0) {
    // Copy construct a member from sourceObj (likely a pointer or handle)
    uVar1 = FUN_004265d0(sourceObj, *this);  // Returns a handle/pointer stored at this[1]
    this[1] = uVar1;
    
    // Call copy assignment or initialization for a member (vtable entry at offset 4)
    (**(code **)(*vtablePtr + 4))(sourceObj, 0);
    
    // Call post-construction hook (vtable entry at offset 12)
    (**(code **)(*vtablePtr + 0xc))();
    return this;
  }
  
  // No source: initialize member to null
  this[1] = 0;
  
  // Call post-construction hook (vtable entry at offset 12)
  (**(code **)(*vtablePtr + 0xc))();
  return this;
}