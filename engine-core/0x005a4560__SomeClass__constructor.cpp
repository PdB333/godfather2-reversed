// FUNC_NAME: SomeClass::constructor
void SomeClass::constructor(void)
{
  int iVar1;
  undefined4 uVar2;
  undefined2 *puVar3;
  undefined4 *this;
  
  this[1] = 0;
  *this = 0xffffffff;
  this[2] = 0;
  this[3] = 0;
  iVar1 = (*DAT_0119caf0)(4,0); // Allocate 4 bytes
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_005b1df0(); // Initialize allocated memory
  }
  this[7] = uVar2; // +0x1C
  this[6] = 0; // +0x18
  this[5] = this[5] & 0xf9000000 | 0x1000000; // +0x14, set some flags
  puVar3 = (undefined2 *)(*DAT_0119caf0)(0x48,0); // Allocate 0x48 bytes
  if (puVar3 != (undefined2 *)0x0) {
    *puVar3 = 4; // Initialize size field
    puVar3[1] = 0; // Initialize count field
    *(undefined2 **)(puVar3 + 2) = puVar3 + 4; // +0x04 points to data start
    _memset(puVar3 + 4,0,0x40); // Clear data area (0x40 bytes)
    this[3] = puVar3; // +0x0C
    this[8] = 0; // +0x20
    this[4] = 0xffffffff; // +0x10
    return;
  }
  this[3] = 0; // +0x0C
  this[8] = 0; // +0x20
  this[4] = 0xffffffff; // +0x10
  return;
}