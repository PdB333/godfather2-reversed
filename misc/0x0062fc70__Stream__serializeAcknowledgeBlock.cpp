// FUNC_NAME: Stream::serializeAcknowledgeBlock
undefined4 __thiscall Stream::serializeAcknowledgeBlock(Stream *this)

{
  int count;
  int *readCursor;
  int readOffset;
  int itemIndex;
  int *writeCursor;
  int *tmpPtr;
  undefined8 timestamp;

  // Validate that read cursor points to tag 5 (start of acknowledge block)
  readCursor = *(int **)(this + 0xc);
  if (((*(int **)(this + 8) <= readCursor) || (readCursor == (int *)0x0)) || (*readCursor != 5)) {
    FUN_00627ac0(PTR_s_table_00e2a8b0);  // assert("table expected")
  }

  // Read item count (tag 5 consumed? then read count via FUN_00628820)
  count = FUN_00628820(1);  // reads next integer (probably bitstream read)
  timestamp = CONCAT44(8, count);  // pack size and count
  readOffset = (int)(timestamp >> 32);  // 8 (size of each item)
  readCursor = (int *)(*(int *)(this + 0xc) + 8);  // advance read cursor past count

  // Validate next tag is 6 (acknowledge block data start)
  if (((*(int **)(this + 8) <= readCursor) || (readCursor == (int *)0x0)) || (*readCursor != 6)) {
    timestamp = FUN_00627ac0(PTR_s_function_00e2a8b4);  // assert("function expected")
  }

  // Extract count from packed value (lower 32 bits)
  if ((int)timestamp < 1) {
    return 0;
  }

  itemIndex = 1;
  while( true ) {
    // Copy 8 bytes from read buffer to write buffer
    readOffset = *(int *)(this + 0xc);
    writeCursor = *(int **)(this + 8);
    *writeCursor = *(int *)(readOffset + 8);       // first 4 bytes
    writeCursor[1] = *(int *)(readOffset + 8 + 4); // next 4 bytes
    *(int *)(this + 8) = *(int *)(this + 8) + 8;   // advance write cursor

    // Write tag 3 (acknowledge item) followed by float index
    writeCursor = *(int **)(this + 8);
    *writeCursor = 3;
    writeCursor[1] = (float)itemIndex;
    *(int *)(this + 8) = *(int *)(this + 8) + 8;

    // Write 8-byte timestamp from FUN_00637f10 (e.g., current frame time)
    writeCursor = *(int **)(this + 8);
    tmpPtr = (int *)FUN_00637f10();
    *writeCursor = *tmpPtr;
    writeCursor[1] = tmpPtr[1];
    *(int *)(this + 8) = *(int *)(this + 8) + 8;

    // Compute and write checksum for the 24-byte block written (8+8+8)
    FUN_006362d0(this, *(int *)(this + 8) + -0x18, 1);

    // Check for interrupt (e.g., yield if too much time spent)
    if (FUN_00625740() != 0) {
      return 1;
    }

    // Undo the last 8-byte advance? (probably to retry or adjust)
    *(int *)(this + 8) = *(int *)(this + 8) + -8;

    itemIndex++;
    if (count < itemIndex) break;

    // Reset read size per item (always 8)
    readOffset = 8;
  }

  return 0;
}