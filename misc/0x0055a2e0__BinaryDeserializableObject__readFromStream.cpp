// FUNC_NAME: BinaryDeserializableObject::readFromStream
void __thiscall BinaryDeserializableObject::readFromStream(int thisPtr, undefined4 dataStream)
{
  undefined4 *puVar1;
  undefined4 **ppuVar2;
  uint uVar3;
  bool bVar4;
  char isBitmapMode; // local_64 - 0: linked list mode, 1: bitmap mode
  int bitmapBase; // local_60 - base address of bitmap for sparse mode
  undefined4 *currentDataItem; // local_5c - pointer to current data item in bitmap mode
  uint currentIndex; // local_58 - current index in iteration
  uint totalCount; // local_54 - total number of items (for bitmap mode) or not used?
  undefined4 *currentItem; // local_50 - pointer to current item being processed
  undefined4 itemHeader; // local_48 - first 4 bytes of current item? Actually used as temp.
  uint fieldIndex; // derived from puVar1 after decoding

  // Initialize stream parsing (decoder setup, magic constant 0xdf0a26e8)
  // This likely sets up local variables including isBitmapMode, currentIndex, etc.
  FUN_0043aff0(dataStream, 0xdf0a26e8);  // known decoder initialization

  uVar3 = currentIndex;  // initial index (probably 0)
  while (true) {
    // Determine termination condition based on mode
    if (isBitmapMode == '\0') {
      // Linked list mode: stop when current pointer is null
      bVar4 = *local_8 == (undefined4 *)0x0;  // local_8 is current linked list node pointer
    }
    else {
      // Bitmap mode: stop when index reaches total count
      bVar4 = uVar3 == totalCount;
    }
    if (bVar4) break;  // exit loop

    // Determine pointer to the item descriptor (contains field ID and value)
    ppuVar2 = &currentItem;  // default in bitmap mode
    if (isBitmapMode == '\0') {
      ppuVar2 = local_8;  // in linked list mode, the node itself provides the descriptor
    }

    // Extract field ID from the descriptor
    // Descriptor format: short at offset 0x6 may be a tag for special encoding?
    if (*(short *)((int)ppuVar2 + 6) == 0x25e3) {
      // If tag matches 0x25e3, field ID is taken from offset 0x2 (ushort)
      puVar1 = (undefined4 *)(uint)*(ushort *)(ppuVar2 + 1);  // ppuVar2+1 is offset 4? Actually ppuVar2 is pointer to uint*; ppuVar2+1 is offset 4 bytes, then cast to uint then pointer.
    }
    else {
      // Otherwise field ID is the second uint (at offset 4) of the descriptor
      puVar1 = ppuVar2[1];  // ppuVar2[1] is the second uint (offset 4)
    }

    // Switch based on field ID (0 through 0xA) to assign to this object's fields
    switch (puVar1) {
    case (undefined4 *)0x0:  // field 0: byte at this+0x24
      ppuVar2 = &currentItem;
      if (isBitmapMode == '\0') {
        ppuVar2 = local_8;
      }
      *(uint *)(thisPtr + 0x24) = (uint)*(byte *)(ppuVar2 + 2);  // ppuVar2+2 is offset 8, byte value
      break;
    case (undefined4 *)0x1:  // field 1: pointer at this+0x8
      ppuVar2 = &currentItem;
      if (isBitmapMode == '\0') {
        ppuVar2 = local_8;
      }
      *(undefined4 **)(thisPtr + 8) = ppuVar2[2];  // ppuVar2[2] is offset 8, pointer
      break;
    case (undefined4 *)0x2:  // field 2: pointer at this+0xc
      ppuVar2 = &currentItem;
      if (isBitmapMode == '\0') {
        ppuVar2 = local_8;
      }
      *(undefined4 **)(thisPtr + 0xc) = ppuVar2[2];
      break;
    case (undefined4 *)0x3:  // field 3: byte at this+0x2c
      ppuVar2 = &currentItem;
      if (isBitmapMode == '\0') {
        ppuVar2 = local_8;
      }
      *(uint *)(thisPtr + 0x2c) = (uint)*(byte *)(ppuVar2 + 2);
      break;
    case (undefined4 *)0x4:  // field 4: pointer at this+0x1c
      ppuVar2 = &currentItem;
      if (isBitmapMode == '\0') {
        ppuVar2 = local_8;
      }
      *(undefined4 **)(thisPtr + 0x1c) = ppuVar2[2];
      break;
    case (undefined4 *)0x5:  // field 5: byte at this+0x30
      ppuVar2 = &currentItem;
      if (isBitmapMode == '\0') {
        ppuVar2 = local_8;
      }
      *(uint *)(thisPtr + 0x30) = (uint)*(byte *)(ppuVar2 + 2);
      break;
    case (undefined4 *)0x6:  // field 6: pointer at this+0x20
      ppuVar2 = &currentItem;
      if (isBitmapMode == '\0') {
        ppuVar2 = local_8;
      }
      *(undefined4 **)(thisPtr + 0x20) = ppuVar2[2];
      break;
    case (undefined4 *)0x7:  // field 7: byte at this+0x28
      ppuVar2 = &currentItem;
      if (isBitmapMode == '\0') {
        ppuVar2 = local_8;
      }
      *(uint *)(thisPtr + 0x28) = (uint)*(byte *)(ppuVar2 + 2);
      break;
    case (undefined4 *)0x8:  // field 8: pointer at this+0x10
      ppuVar2 = &currentItem;
      if (isBitmapMode == '\0') {
        ppuVar2 = local_8;
      }
      *(undefined4 **)(thisPtr + 0x10) = ppuVar2[2];
      break;
    case (undefined4 *)0x9:  // field 9: pointer at this+0x14
      ppuVar2 = &currentItem;
      if (isBitmapMode == '\0') {
        ppuVar2 = local_8;
      }
      *(undefined4 **)(thisPtr + 0x14) = ppuVar2[2];
      break;
    case (undefined4 *)0xa:  // field 10: pointer at this+0x18
      ppuVar2 = &currentItem;
      if (isBitmapMode == '\0') {
        ppuVar2 = local_8;
      }
      *(undefined4 **)(thisPtr + 0x18) = ppuVar2[2];
    }

    // Advance to next item based on mode
    if (isBitmapMode == '\0') {
      // Linked list mode: advance by reading offset to next node from current node's first uint
      if ((int)uVar3 < 0) {
        // Special case: negative index? Probably not hit in normal operation
        local_8 = (undefined4 **)((int)local_8 + (int)*local_8);
        FUN_0043b140();  // unknown advance function
        uVar3 = currentIndex;
      }
      else if ((int)uVar3 < (int)(totalCount - 1)) {
        // Normal case: advance to next node
        local_8 = (undefined4 **)((int)local_8 + (int)*local_8);
        currentIndex = uVar3 + 1;
        uVar3 = currentIndex;
      }
      else {
        // End of list: set pointer to known sentinel address (0x01163cf8)
        local_8 = (undefined4 **)0x01163cf8;  // likely end marker
        local_8 = (undefined4 **)0x01163cf8;  // redundant assignment
      }
    }
    else {
      // Bitmap mode: simply increment index
      currentIndex = uVar3 + 1;
      uVar3 = currentIndex;
      if (currentIndex != totalCount) {
        // Load next item only if not at end
        // local_4c is a short copy of index (used for alignment but not needed)
        // Check bitmap: if bit at position (currentIndex) is set, then item exists
        if ((*(byte *)((currentIndex >> 3) + bitmapBase) & (byte)(1 << ((byte)currentIndex & 7))) == 0) {
          // Bit not set: item is null
          currentItem = currentDataItem;  // but it's the same? Actually it seems buggy? original: local_50 = local_5c; then local_48 = *local_5c; then local_5c++
          // Wait, the original code does: local_50 = local_5c; local_48 = *local_5c; local_5c = local_5c + 1;
          // That seems like it's reading a 4-byte value from the data stream? But here it's overwriting currentItem with the data pointer? 
          // Probably intended: if bit set, then currentItem = next data pointer, else null.
          // However the original code has the same pattern for both branches. Possibly a decompilation artifact.
          // We'll replicate as per original logic but note it's ambiguous.
          currentItem = currentDataItem;  // base pointer to data block
          itemHeader = *currentDataItem;  // read first 4 bytes of block (maybe size or type)
          currentDataItem = currentDataItem + 1;  // advance by 4 bytes
        } else {
          currentItem = (undefined4 *)0x0;
          itemHeader = 0;
        }
      }
    }
  }
  return;
}