// FUNC_NAME: Entity::applyDataBlock
undefined4 __thiscall Entity::applyDataBlock(Entity *this, void *dataBlock, int **outDataPtr, uint version)
{
  // Store the data block pointer
  *outDataPtr = (int *)dataBlock;

  // Call initialization functions with data from the block
  FUN_006b68c0(*(undefined4 *)((int)dataBlock + 8), 0, dataBlock, 0);
  FUN_006b4e30(*(undefined4 *)(*(int *)*outDataPtr + 0x10), 1);

  // Copy field at dataBlock+0x14 to this+0x170
  *(undefined4 *)(this + 0x170) = *(undefined4 *)(*(int *)*outDataPtr + 0x14);

  // Update flags at this+0x34: clear specific bits, then OR with dataBlock+4
  *(uint *)(this + 0x34) = *(uint *)(this + 0x34) & 0xe825e802;
  *(uint *)(this + 0x34) = *(uint *)(this + 0x34) | *(uint *)(*(int *)*outDataPtr + 4);

  // If version < 7, apply conditional bitmask operations on flags
  if (version < 7) {
    // First bitmask pair (DAT_00e50cf4 and PTR_IMAGE_DOS_HEADER_00e50cf8 are likely bitmask constants)
    if ((*(uint *)(this + 0x34) & DAT_00e50cf4) == 0) {
      *(uint *)(this + 0x34) = *(uint *)(this + 0x34) & ~(uint)PTR_IMAGE_DOS_HEADER_00e50cf8;
    } else {
      *(uint *)(this + 0x34) = *(uint *)(this + 0x34) | (uint)PTR_IMAGE_DOS_HEADER_00e50cf8;
    }
    *(uint *)(this + 0x34) = *(uint *)(this + 0x34) & ~DAT_00e50cf4;

    // Second bitmask pair
    if ((*(uint *)(this + 0x34) & DAT_00e50cfc) == 0) {
      *(uint *)(this + 0x34) = *(uint *)(this + 0x34) & ~(uint)PTR_FUN_00e50d00;
    } else {
      *(uint *)(this + 0x34) = *(uint *)(this + 0x34) | (uint)PTR_FUN_00e50d00;
    }
    *(uint *)(this + 0x34) = *(uint *)(this + 0x34) & ~DAT_00e50cfc;
  }

  // Copy fields from data block to this object
  *(undefined4 *)(this + 0x7c) = *(undefined4 *)(*(int *)*outDataPtr + 0x30);
  *(undefined4 *)(this + 0x80) = *(undefined4 *)(*(int *)*outDataPtr + 0x34);
  *(undefined4 *)(this + 200) = *(undefined4 *)(*(int *)*outDataPtr + 0x44);  // +0xC8
  *(undefined4 *)(this + 0x174) = *(undefined4 *)(*(int *)*outDataPtr + 0x4c);

  // If version > 5, copy additional field; otherwise set to 0
  if (5 < version) {
    *(undefined4 *)(this + 0x178) = *(undefined4 *)(*(int *)*outDataPtr + 0x50);
  } else {
    *(undefined4 *)(this + 0x178) = 0;
  }

  return 0x60;  // Return size constant (likely sizeof data block or similar)
}