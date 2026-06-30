// FUNC_NAME: ObjectFactory::createAndLinkObject
void __thiscall ObjectFactory::createAndLinkObject(int *this, int param2)
{
  int *obj;
  undefined4 retVal;
  
  obj = this;
  // Call vtable method at offset 0x8 (likely constructor)
  (**(code **)(*this + 8))(this);
  
  if (param2 == 0) {
    retVal = 0;
  }
  else {
    // Call function to create/manage reference (likely reference counting or linking)
    retVal = FUN_004265d0(param2, obj);
  }
  
  // Call method to register/link the object (at this + offset)
  FUN_004cf4e0(obj, retVal);
  
  // Store back pointer to this object
  *(int **)(in_EAX + 8) = this;
  
  // Call vtable method at offset 0x8 again (post-init)
  (**(code **)(*this + 8))();
  
  if (param2 != 0) {
    retVal = FUN_004265d0(param2, *(undefined4 *)(in_EAX + 8));
    // Store reference at this + 0xC
    *(undefined4 *)(in_EAX + 0xc) = retVal;
    
    // Call vtable method at offset 0x4 (likely setParent or linkTo)
    (**(code **)(*this + 4))(param2, 0);
    
    // Call vtable method at offset 0xC (finalize)
    (**(code **)(*this + 0xc))();
    return;
  }
  
  // No parent - store null reference
  *(undefined4 *)(in_EAX + 0xc) = 0;
  
  // Call vtable method at offset 0xC (finalize)
  (**(code **)(*this + 0xc))();
  return;
}