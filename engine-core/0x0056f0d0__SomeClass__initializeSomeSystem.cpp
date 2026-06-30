// FUNC_NAME: SomeClass::initializeSomeSystem
void SomeClass::initializeSomeSystem(undefined4 *param_1, undefined4 param_2)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  puVar1 = (undefined4 *)FUN_009c8e50(0x14); // Allocate 0x14 bytes (20 bytes) for a structure
  if (puVar1 != (undefined4 *)0x0) {
    puVar1[4] = param_2; // Store param2 at offset +0x10
    *puVar1 = param_1; // Store param1 at offset +0x0
    local_c = 2; // Some kind of command or type
    local_8 = 0x10; // Size or offset
    local_4 = 0; // Flags or additional parameter
    uVar2 = (**(code **)*param_1)(param_2,&local_c); // Call virtual function on param1 object
    puVar1[2] = uVar2; // Store result at offset +0x8
    puVar1[3] = uVar2; // Store same result at offset +0xC
    puVar1[1] = 0; // Initialize offset +0x4 to zero
    DAT_01205564 = puVar1; // Store pointer to global
    return;
  }
  DAT_01205564 = (undefined4 *)0x0;
  return;
}