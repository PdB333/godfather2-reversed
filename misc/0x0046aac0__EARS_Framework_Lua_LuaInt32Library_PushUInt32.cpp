// Xbox PDB: EARS::Framework::Lua::LuaInt32Library::PushUInt32
// FUNC_NAME: BitStreamWriter::writeUInt32
// Address: 0x0046aac0
// Reconstructed from Ghidra decompile. This function writes a UInt32 value into the bitstream/packet buffer.
// It allocates a new block for the value, writes a packet header (type 7), and handles buffer management.

bool BitStreamWriter::writeUInt32(uint32_t value)
{
    // Check write bounds: ensure current size (this+0x10->+0x20) does not exceed max size (this+0x10->+0x24)
    // +0x10: pointer to stream control structure
    // StreamControl offset 0x20: current write size (uint)
    // StreamControl offset 0x24: maximum allowed size (uint)
    if (*(uint32_t*)(*(int32_t*)(this + 0x10) + 0x20) > *(uint32_t*)(*(int32_t*)(this + 0x10) + 0x24))
    {
        // Overflow: trigger fatal error / assertion
        FUN_00627360(); // assertion failure
    }

    // Allocate a new block of 4 bytes (for the uint32 value? Actually it returns pointer to allocated block)
    int32_t* pNewBlock = (int32_t*)FUN_00638a40(4); // AllocateChunk(4) - returns pointer to new block of size 4? Might be bigger internally.

    // Write packet header into buffer at current write pointer (this+0x8)
    // Buffer entry layout: [type (4 bytes), pointer_to_block (4 bytes)]
    uint32_t* pWritePtr = *(uint32_t**)(this + 0x8);
    pWritePtr[1] = (uint32_t)pNewBlock; // Store block pointer
    pWritePtr[0] = 7;                    // Type tag: 7 = UInt32

    // Advance write pointer by 8 bytes (header size)
    *(int32_t*)(this + 0x8) += 8;

    // Check if the allocated block has space for the value at offset 0x10
    if ((int32_t*)((uint8_t*)pNewBlock + 0x10) != (int32_t*)0x0)
    {
        // Write the value into the block at offset 0x10
        *(uint32_t*)(pNewBlock + 0x10/4) = value; // pNewBlock[4]? Actually offset 0x10 = 16 bytes, so pNewBlock[4] if 4-byte ints.

        // Finalize or validate the current write (might update sizes or checksums)
        if (FUN_00627c90(this) != 0) // Função to finalize bitstream chunk? Returns error if non-zero?
        {
            // Debug output on error
            FUN_004aeb70(&PTR_s___tostring_00e32518); // Could be _DebugPrint or error handler
        }

        // Retrieve current write pointer (already advanced)
        int32_t currentPtr = *(int32_t*)(this + 0x8);

        // Look back at the previous packet header (8 bytes before current pointer)
        int32_t previousHeaderPtr = currentPtr - 8;
        int32_t previousType = *(int32_t*)(currentPtr - 16); // 0x10 bytes back: type of previous packet
        int32_t previousBlockPtr = *(int32_t*)(currentPtr - 12); // 0xC bytes back: block pointer of previous packet

        // If previous type was 5 (could be a special case like "UInt32" continuation?)
        if (previousType == 5)
        {
            // ??? Here it writes a value from somewhere (offset 0x34 relative to stream control) into the previous block's field at offset 8.
            // This looks like a relinking or update of a previous packet's data pointer.
            *(uint32_t*)(previousBlockPtr + 8) = *(uint32_t*)(*(int32_t*)(this + 0x10) + 0x34);
        }
        // If previous type is 7 (same as current? Possibly a concatenation?)
        else if (previousType == 7)
        {
            // For type 7, write value from current block's data offset 4? Actually iVar4+4 = (ptr to new block) + 4? 
            // The decompiled code: *(undefined4 *)(*(int *)(iVar2 + -0xc) + 8) = *(undefined4 *)(iVar4 + 4);
            // iVar2 = current buffer pointer, iVar2-0xc = address of previous block pointer? Let's reinterpret:
            // iVar2 = current write pointer (after advance)
            // iVar2 - 0xc = address of the block pointer field in previous header? Actually previous header is at iVar2-8 (type at -0x10? Wait offset calculations:
            // previous header: type at (current-16), block ptr at (current-12). So previousBlockPtr = *(int*)(current-12).
            // That is the block pointer from previous packet.
            // Then it writes to that block at offset 8: *(previousBlockPtr+8) = something.
            // The something is *(iVar4+4). iVar4 is the new block pointer. So it writes the new block's offset+4 into the old block's offset+8.
            // This could be linking the blocks into a list.
            *(uint32_t*)(previousBlockPtr + 8) = *(uint32_t*)((uint8_t*)pNewBlock + 4);
        }

        // Undo the write pointer advance (since the buffer might be used for chaining? This seems like a rollback)
        *(int32_t*)(this + 0x8) -= 8;
        return true;
    }

    // Allocation failed or null pointer
    FUN_00627bd0("Failed to create %s object.\n", "UInt32");
    // Trigger debug break
    int (*func)() = (int (*)())swi(3);
    return (uint32_t)func(); // unreachable, but returns whatever
}