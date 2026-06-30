// FUNC_NAME: SomeManager::initializeSomeSystem
void FUN_0056fa90(undefined4 *param_1, undefined4 param_2)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  // Allocate 0x14 (20) bytes from some memory manager
  puVar1 = (undefined4 *)FUN_009c8e50(0x14);
  if (puVar1 != (undefined4 *)0x0) {
    // Store the second parameter at offset +0x10 (4th slot)
    puVar1[4] = param_2;
    // Store the first parameter at offset +0x00 (base)
    *puVar1 = param_1;
    
    // Setup local variables for a call: type=2, size=0x10, flags=0
    local_c = 2;
    local_8 = 0x10;
    local_4 = 0;
    
    // Call a virtual method on param_1 (likely a manager/interface) with param_2 and the local struct
    uVar2 = (**(code **)*param_1)(param_2, &local_c);
    
    // Store the result at offset +0x08 and +0x0C (duplicated)
    puVar1[2] = uVar2;
    puVar1[3] = uVar2;
    // Initialize offset +0x04 to 0
    puVar1[1] = 0;
    
    // Store the allocated structure in a global pointer
    DAT_01205568 = puVar1;
    return;
  }
  // Allocation failed, set global to null
  DAT_01205568 = (undefined4 *)0x0;
  return;
}