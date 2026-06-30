// FUNC_NAME: SomeClass::constructor
void __thiscall SomeClass::constructor(void *this, undefined4 param_2)
{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)operator_new(0x24); // Allocate 36 bytes
  if (puVar1 != (undefined4 *)0x0) {
    puVar1[1] = 0;   // +0x04: some field initialized to 0
    puVar1[2] = 0;   // +0x08: some field initialized to 0
    puVar1[4] = 0;   // +0x10: some field initialized to 0
    puVar1[3] = 1;   // +0x0C: some field initialized to 1
    *puVar1 = &PTR_LAB_00e42fc0;  // +0x00: vtable pointer
    puVar1[6] = &PTR_LAB_00e42fec; // +0x18: some pointer
    puVar1[7] = &LAB_00652760;     // +0x1C: function pointer
    puVar1[5] = puVar1 + 6;        // +0x14: pointer to +0x18
    puVar1[8] = param_2;           // +0x20: store parameter
    FUN_0064ef60(puVar1);          // Call some initialization function
    return;
  }
  uRam00000020 = param_2;  // Fallback: store parameter to global
  FUN_0064ef60(0);         // Call with null
  return;
}