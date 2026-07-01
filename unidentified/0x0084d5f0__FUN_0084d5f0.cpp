// FUNC_NAME: SomeClass::operator= (copy assignment)
void __thiscall SomeClass::operator=(int this, int other)
{
  int *piVar1;
  int iVar2;
  
  if (this != other) {
    // Copy linked list node at offset +4 (prev pointer)
    piVar1 = (int *)(this + 4);
    if (piVar1 != (int *)(other + 4)) {
      iVar2 = *(int *)(other + 4);
      if (*piVar1 != iVar2) {
        if (*piVar1 != 0) {
          FUN_004daf90(piVar1);  // Release previous node
        }
        *piVar1 = iVar2;
        if (iVar2 != 0) {
          *(undefined4 *)(this + 8) = *(undefined4 *)(iVar2 + 4);
          *(int **)(iVar2 + 4) = piVar1;
        }
      }
    }
    // Copy linked list node at offset +0xC (next pointer)
    piVar1 = (int *)(this + 0xc);
    if (piVar1 != (int *)(other + 0xc)) {
      iVar2 = *(int *)(other + 0xc);
      if (*piVar1 != iVar2) {
        if (*piVar1 != 0) {
          FUN_004daf90(piVar1);  // Release previous node
        }
        *piVar1 = iVar2;
        if (iVar2 != 0) {
          *(undefined4 *)(this + 0x10) = *(undefined4 *)(iVar2 + 4);
          *(int **)(iVar2 + 4) = piVar1;
        }
      }
    }
    // Copy remaining data members (likely a struct with floats/ints)
    *(undefined8 *)(this + 0x14) = *(undefined8 *)(other + 0x14);  // 8 bytes (e.g., two floats)
    *(undefined4 *)(this + 0x1c) = *(undefined4 *)(other + 0x1c);  // 4 bytes
    *(undefined8 *)(this + 0x20) = *(undefined8 *)(other + 0x20);  // 8 bytes
    *(undefined4 *)(this + 0x28) = *(undefined4 *)(other + 0x28);  // 4 bytes
    *(undefined4 *)(this + 0x2c) = *(undefined4 *)(other + 0x2c);  // 4 bytes
    *(undefined4 *)(this + 0x30) = *(undefined4 *)(other + 0x30);  // 4 bytes
    *(undefined4 *)(this + 0x34) = *(undefined4 *)(other + 0x34);  // 4 bytes
    *(undefined4 *)(this + 0x38) = *(undefined4 *)(other + 0x38);  // 4 bytes
    *(undefined4 *)(this + 0x3c) = *(undefined4 *)(other + 0x3c);  // 4 bytes
    *(undefined4 *)(this + 0x40) = *(undefined4 *)(other + 0x40);  // 4 bytes
    *(undefined4 *)(this + 0x44) = *(undefined4 *)(other + 0x44);  // 4 bytes
  }
  return;
}