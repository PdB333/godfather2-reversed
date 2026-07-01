// FUNC_NAME: GodfatherGameManager::operator new(uint, byte)
undefined4 __thiscall GodfatherGameManager__operator_new(undefined4 param_1,byte param_2)

{
  // Call the memory allocation function (likely operator new or a custom allocator)
  FUN_007c2d80();
  
  // If the second parameter (likely a placement flag) has bit 0 set, 
  // call the constructor for the object at param_1
  if ((param_2 & 1) != 0) {
    FUN_00624da0(param_1);
  }
  
  return param_1;
}