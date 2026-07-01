// FUNC_NAME: SomeContainer::removeAt
void __thiscall SomeContainer::removeAt(int thisPtr, uint index)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined8 *puVar3;
  
  if (index < *(uint *)(thisPtr + 0xc0)) {
    if (index < *(uint *)(thisPtr + 0xc0) - 1) {
      puVar3 = (undefined8 *)(thisPtr + index * 0xc);
      do {
        // Shift elements left by one slot (each element is 0xC bytes)
        *puVar3 = *(undefined8 *)((int)puVar3 + 0xc);
        *(undefined4 *)(puVar3 + 1) = *(undefined4 *)((int)puVar3 + 0x14);
        index = index + 1;
        puVar3 = (undefined8 *)((int)puVar3 + 0xc);
      } while (index < *(int *)(thisPtr + 0xc0) - 1U);
    }
    // Decrement element count
    *(int *)(thisPtr + 0xc0) = *(int *)(thisPtr + 0xc0) + -1;
    // Clear the now-unused last slot
    puVar1 = (undefined4 *)(thisPtr + *(int *)(thisPtr + 0xc0) * 0xc);
    if (puVar1 != (undefined4 *)0x0) {
      puVar1[1] = 0;
      uVar2 = DAT_00d5ccf8;
      *puVar1 = 0;
      puVar1[2] = uVar2;
    }
  }
  return;
}