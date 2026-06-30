// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(void *this)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)(*DAT_012059dc)(0,0x58); // Allocate 0x58 bytes
  if (puVar1 != (undefined4 *)0x0) {
    *(undefined1 *)(puVar1 + 1) = 8; // +0x04: field = 8
    *(undefined1 *)((int)puVar1 + 5) = 0; // +0x05: field = 0
    puVar1[0x13] = 0; // +0x4C: field = 0
    *puVar1 = 0; // +0x00: field = 0
    puVar1[7] = 0; // +0x1C: field = 0
    puVar1[8] = 0; // +0x20: field = 0
    puVar1[0x14] = 0; // +0x50: field = 0
    puVar1[0xf] = 0; // +0x3C: field = 0
    *(undefined1 *)((int)puVar1 + 0x32) = 0; // +0x32: field = 0
    *(undefined1 *)(puVar1 + 0xc) = 0; // +0x30: field = 0
    puVar1[0xd] = 0; // +0x34: field = 0
    *(undefined1 *)((int)puVar1 + 0x31) = 1; // +0x31: field = 1
    puVar1[0xe] = 0; // +0x38: field = 0
    puVar1[0x12] = 0; // +0x48: field = 0
    *(undefined2 *)(puVar1 + 0xb) = 0; // +0x2C: field = 0
    *(undefined2 *)((int)puVar1 + 0x2e) = 0; // +0x2E: field = 0
    puVar1[5] = 0; // +0x14: field = 0
    puVar1[10] = 0; // +0x28: field = 0
    puVar1[0x15] = 0; // +0x54: field = 0
    puVar1[0x10] = 0; // +0x40: field = 0
    puVar1[4] = 0; // +0x10: field = 0
    iVar2 = FUN_00635ab0(puVar1,&DAT_00627560,0); // Call some initialization function
    if (iVar2 == 0) {
      return puVar1;
    }
    FUN_006276b0(); // Cleanup on failure
  }
  return (undefined4 *)0x0;
}