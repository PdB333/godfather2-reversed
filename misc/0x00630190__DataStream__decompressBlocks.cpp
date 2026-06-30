// FUNC_NAME: DataStream::decompressBlocks
// Address: 0x00630190
// This function decompresses blocks from an input stream to an output stream.
// It appears to handle a run-length encoding or LZ-like compression with back references.
// Structure offsets: this+0x8 = output write pointer, this+0xC = input read pointer.

int DataStream::decompressBlocks() {
    int *readPtr = *(int **)(this + 0xC); // input read position pointer
    int *writePtr = *(int **)(this + 0x8); // output write position pointer

    // Validate that read pointer is valid and the block type is 5
    if (writePtr <= readPtr || readPtr == nullptr || *readPtr != 5) {
        FUN_00627ac0(PTR_s_table_00e2a8b0); // error handler
    }

    int blockCount = FUN_00628820(1); // get number of elements in this block
    readPtr = (int *)(*(int *)(this + 0xC) + 8); // advance read pointer past type and maybe size

    // If the block has no elements, just skip
    if (readPtr >= writePtr || readPtr == nullptr || *readPtr <= 0) {
        // No elements to process; possibly just set output
        // in_XMM0_Da is used only if condition fails, but here it's uninitialized?
        // Actually the original code uses a floating point register that may be leftover.
        // We'll treat it as zero if branch taken.
    } else {
        blockCount = *readPtr; // Actually the code uses the value at readPtr as count
    }

    if (blockCount <= 0) {
        return 0;
    }

    // Decrement count for first element
    int currentIndex = FUN_006286b0(blockCount - 1); // Possibly a seek or decrement

    // Read first 8-byte element from codec and copy to output
    int64_t *codecPtr = (int64_t *)FUN_00637f10(); // get next code entry
    int64_t *outputPos = *(int64_t **)(this + 0x8);
    *outputPos = *codecPtr; // copy 8 bytes
    *(int *)(this + 0x8) = (int)outputPos + 8; // advance write pointer

    int current = (int)in_XMM0_Da; // initial value from floating point register (may be 0 from failed branch)
    while (current < blockCount) {
        codecPtr = (int64_t *)FUN_00637f10(); // get next code entry
        outputPos = *(int64_t **)(this + 0x8);
        *outputPos = *codecPtr; // copy 8 bytes
        *(int *)(this + 0x8) = (int)outputPos + 8; // advance

        // Save the position of the last written element (before potential back-reference)
        int lastPos = *(int *)(this + 0x8);
        int type = *(int *)(*(int *)(this + 0xC) + 4); // probably field from input

        // Read another code entry (possibly token for back-reference)
        codecPtr = (int64_t *)FUN_00637f10();
        if (codecPtr == &DAT_00e2a93c) { // sentinel indicating a back-reference
            // Write a back-reference token: format { int type=3, float offset }
            struct BackRefToken {
                int tokenType; // 3
                float distance; // float version of index
            } token;
            token.tokenType = 3;
            token.distance = (float)current;
            codecPtr = (int64_t *)FUN_00637d60(this, type, &token);
        }
        // Write the back-reference data (8 bytes from the previously written element)
        *codecPtr = *(int64_t *)(lastPos - 8);
        // Undo the advance: restore write pointer
        *(int *)(this + 0x8) = lastPos - 8;

        current++;
    }

    // Write a zero terminator at the end
    *(int *)(*(int *)(this + 0x8)) = 0;
    *(int *)(this + 0x8) += 8;

    int type = *(int *)(*(int *)(this + 0xC) + 4);
    int endPos = *(int *)(this + 0x8);
    codecPtr = (int64_t *)FUN_00637f10();
    if (codecPtr == &DAT_00e2a93c) {
        struct EndToken {
            int tokenType; // 3
            float count; // float version of blockCount
        } endToken;
        endToken.tokenType = 3;
        endToken.count = (float)blockCount;
        codecPtr = (int64_t *)FUN_00637d60(this, type, &endToken);
    }
    // Write the 8 bytes that were just before endPos (probably to fix the back-reference)
    *codecPtr = *(int64_t *)(endPos - 8);
    *(int *)(this + 0x8) = endPos - 8;

    return 1;
}