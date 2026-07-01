// FUNC_NAME: PriorityQueue::addWithPriority
void __thiscall PriorityQueue::addWithPriority(int this, undefined4 value, ushort priority)
{
  uint uVar1;
  uint uVar2;
  ushort *puVar3;
  undefined4 local_8;
  uint local_4;
  
  uVar1 = *(uint *)(this + 0x128);  // +0x128: current count of entries
  local_4 = (uint)priority;
  uVar2 = 0;
  local_8 = value;
  if (uVar1 != 0) {
    puVar3 = (ushort *)(this + 0x104);  // +0x104: array of priorities (each 2 bytes)
    do {
      if (*puVar3 < priority) {
        FUN_0083b820(&local_8, uVar2);  // Insert value at index uVar2 (shifting others down)
        return;
      }
      uVar2 = uVar2 + 1;
      puVar3 = puVar3 + 4;  // Skip 4 bytes per entry (2 bytes priority + 2 bytes padding?)
    } while (uVar2 < uVar1);
  }
  // If not inserted yet, append at end if space available
  if (uVar1 < 5) {  // Max 5 entries
    *(undefined4 *)(this + 0x100 + uVar1 * 8) = value;     // +0x100: array of values (4 bytes each)
    *(uint *)(this + 0x104 + uVar1 * 8) = local_4;         // +0x104: array of priorities (stored as 4 bytes)
    *(int *)(this + 0x128) = *(int *)(this + 0x128) + 1;   // Increment count
  }
  return;
}