// FUNC_NAME: SomeClass::createInstance
undefined4 FUN_007d0090(undefined4 param_1, undefined4 param_2)
{
  int allocResult;
  undefined4 instance;
  undefined4 args[3]; // local_c, local_8, local_4
  
  args[0] = 2;   // arg0 = 2 (possibly size or type)
  args[1] = 0x10; // arg1 = 16 (alignment or flags)
  args[2] = 0;    // arg2 = 0 (additional parameter)
  
  // Allocate memory: 0xe0 bytes, with args as allocation parameters
  allocResult = FUN_009c8ed0(0xe0, &args);
  if (allocResult != 0) {
    // Call constructor/initializer on the allocated memory
    instance = FUN_007cfc90(param_1, param_2);
    return instance;
  }
  return 0; // Allocation failed
}