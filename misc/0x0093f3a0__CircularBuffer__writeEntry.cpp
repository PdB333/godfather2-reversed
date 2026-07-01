// FUNC_NAME: CircularBuffer::writeEntry
void __thiscall CircularBuffer::writeEntry(int *this, undefined4 *entry)
{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = this[2] + this[3];  // +0x08 writeIndex + +0x0C count
  this[3] = this[3] + 1;      // +0x0C count++
  if (this[1] <= iVar1) {      // +0x04 capacity, wrap around
    iVar1 = iVar1 - this[1];
  }
  puVar2 = (undefined4 *)(iVar1 * 0x34 + *this);  // +0x00 buffer, each entry 0x34 bytes
  *puVar2 = *entry;          // Copy first dword (likely a type/id)
  FUN_004d3e20(entry + 1);    // Deep copy entry[1..4] (16 bytes)
  puVar2[5] = entry[5];      // Copy 6th field
  FUN_004d3e20(entry + 6);    // Deep copy entry[6..9] (16 bytes)
  puVar2[10] = entry[10];    // Copy 11th field
  puVar2[0xb] = entry[0xb];  // Copy 12th field
  puVar2[0xc] = entry[0xc];  // Copy 13th field
  return;
}