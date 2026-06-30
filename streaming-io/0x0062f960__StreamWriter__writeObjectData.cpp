// FUNC_NAME: StreamWriter::writeObjectData
void __thiscall StreamWriter::writeObjectData(void)
{
    int iVar1;
    uint32_t uVar2;
    uint32_t *puVar3;
    int *piVar4;

    // Check if buffer has space for an entry (8 bytes)
    StreamBuffer* buf = *(StreamBuffer **)(this + 0x10);
    if (buf->mWritePos >= buf->mBufferSize) {
        handleBufferOverflow();
    }

    // Write TypeId (4 = integer) and a value from some member/data
    puVar3 = *(uint32_t **)(this + 8);
    *puVar3 = 4;                                          // TypeTag = integer
    uVar2 = getSomeTimestampOrId();                       // +0x10? return value
    puVar3[1] = uVar2;
    *(int *)(this + 8) += 8;                              // Advance write pointer

    // Write two fields directly (raw data, no tag) – possibly position/rotation
    puVar3 = *(uint32_t **)(this + 8);
    *puVar3 = *(uint32_t *)(this + 0x40);                // field1
    puVar3[1] = *(uint32_t *)(this + 0x44);              // field2
    *(int *)(this + 8) += 8;

    processSomeData(0);                                    // related to this data?

    // Write another integer tag + value
    if (buf->mWritePos >= buf->mBufferSize) {
        handleBufferOverflow();
    }
    puVar3 = *(uint32_t **)(this + 8);
    *puVar3 = 4;
    uVar2 = getSomeTimestampOrId();
    puVar3[1] = uVar2;
    *(int *)(this + 8) += 8;

    // Write tag 5 (float?) with value from another function
    if (buf->mWritePos >= buf->mBufferSize) {
        handleBufferOverflow();
    }
    puVar3 = *(uint32_t **)(this + 8);
    *puVar3 = 5;                                          // TypeTag = float (or similar)
    uVar2 = getFloatValue(0, 0);                          // e.g., a speed or orientation
    puVar3[1] = uVar2;
    *(int *)(this + 8) += 8;

    // Copy the previous entry (tag and data) again – for fixup purposes
    puVar3 = *(uint32_t **)(this + 8);
    puVar3[0] = puVar3[-2];
    puVar3[1] = puVar3[-1];
    *(int *)(this + 8) += 8;

    // Backpatch: if the tag at current-0x10 is 5 or 7, set a pointer at the data address +8
    iVar1 = *(int *)(this + 8);
    piVar4 = (int *)(iVar1 - 8);                          // points to the data part of the copied entry
    if (*piVar4 == 0) {
        piVar4 = (int *)(*(int *)(this + 0x10) + 0x34);  // fallback buffer?
    }
    if (*(int *)(iVar1 - 0x10) == 5) {
        *(int *)(*(int *)(iVar1 - 0xC) + 8) = piVar4[1]; // set field at +0x8
    } else if (*(int *)(iVar1 - 0x10) == 7) {
        *(int *)(*(int *)(iVar1 - 0xC) + 8) = piVar4[1];
    }
    *(int *)(this + 8) -= 8;                              // undo the copy (pop)

    // Write two more integer values
    if (buf->mWritePos >= buf->mBufferSize) {
        handleBufferOverflow();
    }
    puVar3 = *(uint32_t **)(this + 8);
    *puVar3 = 4;
    uVar2 = getSomeTimestampOrId();
    puVar3[1] = uVar2;
    *(int *)(this + 8) += 8;

    if (buf->mWritePos >= buf->mBufferSize) {
        handleBufferOverflow();
    }
    puVar3 = *(uint32_t **)(this + 8);
    *puVar3 = 4;
    uVar2 = getSomeTimestampOrId();
    puVar3[1] = uVar2;
    *(int *)(this + 8) += 8;

    // Adjust buffer by removing last two entries (16 bytes) – effectively discarding intermediate data
    iVar1 = *(int *)(this + 8);
    puVar3 = (uint32_t *)getBufferAllocator();            // returns a pointer to scratch area
    *puVar3 = *(uint32_t *)(iVar1 - 8);
    puVar3[1] = *(uint32_t *)(iVar1 - 4);
    *(int *)(this + 8) -= 0x10;                           // remove 16 bytes

    // Finalize the block (e.g., flush, compress, or mark)
    finalizeBlock();

    // Two more similar 16-byte reductions – presumably removing temporary frames
    iVar1 = *(int *)(this + 8);
    puVar3 = (uint32_t *)getBufferAllocator();
    *puVar3 = *(uint32_t *)(iVar1 - 8);
    puVar3[1] = *(uint32_t *)(iVar1 - 4);
    *(int *)(this + 8) -= 0x10;

    iVar1 = *(int *)(this + 8);
    puVar3 = (uint32_t *)getBufferAllocator();
    *puVar3 = *(uint32_t *)(iVar1 - 8);
    puVar3[1] = *(uint32_t *)(iVar1 - 4);
    *(int *)(this + 8) -= 0x10;

    return;
}