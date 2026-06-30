// FUNC_NAME: Entity::createFromTemplate
undefined Entity::createFromTemplate(undefined4 this, undefined4 param_2)
{
  undefined uVar1;
  undefined4 *local_18; // pointer to an object
  void (*local_c)(undefined4); // function pointer
  
  // Call base class constructor/initializer
  FUN_004d3bc0(this);
  
  // Call a factory function using a global singleton (DAT_01223508) and the parameter
  uVar1 = FUN_005dc3d0(DAT_01223508, param_2);
  
  // If the local object pointer is non-null, call the function pointer on it
  if (local_18 != 0) {
    (*local_c)(local_18);
  }
  
  return uVar1;
}