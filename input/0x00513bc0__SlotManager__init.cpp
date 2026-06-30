// FUNC_NAME: SlotManager::init

void __thiscall SlotManager::init(uint totalSize, int *pPoolBase, int someValue)
{
  uint uVar1;
  int iVar2;
  int offset;

  this->pPoolBase = pPoolBase;
  this->field_4 = someValue;
  this->totalSize = totalSize;

  uint count = totalSize / 0x2a0; // element size 0x2a0 bytes
  this->count = count;
  this->field_1C = count; // duplicate count
  this->field_18 = count; // another duplicate count
  this->elementSize = 0x2a0;
  this->field_20 = 0;

  uVar1 = 0;
  if (count != 1) {
    offset = 0;
    do {
      uVar1 = uVar1 + 1;
      iVar2 = FUN_00513720(); // returns pointer to pool base? (likely pPoolBase)
      *(int *)(iVar2 + offset) = uVar1; // assign sequential IDs to elements
      offset = offset + 0x2a0;
    } while (uVar1 < count - 1);
  }

  // Compute offset for last element using TLS
  int baseOffset = 0;
  if (this->pPoolBase != 0) {
    // Get pointer from TLS slot #2 (0x2c -> TLS array, +8 -> index 2)
    baseOffset = *(int *)(*(int **)(threadLocalStorage + 0x2c) + 8) + (int)this->pPoolBase;
  }

  // Mark last element as end-of-list (-1)
  *(int *)(baseOffset + (count - 1) * 0x2a0) = -1;

  this->freeListHead = 0;
  return;
}