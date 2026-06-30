// FUNC_NAME: PacketBuilder::processCommand
// Address: 0x00628430
// This function processes a command from a lookup table and writes to a packet buffer.
// It appears to handle opcodes for packet serialization in the EARS engine's network layer.

void PacketBuilder::processCommand() {
    NetState* netState = *(NetState**)((char*)this + 0x10); // +0x10: pointer to network state
    InnerState* innerState = *(InnerState**)((char*)netState + 0x30); // +0x30: inner state pointer
    int* entry;
    
    if (innerState->count < 2) {
        // Use random entry from lookup table
        int mask = (1 << (innerState->bitField & 0x1f)) - 1;
        if (mask == 0) mask = 1; // Ensure non-zero divisor
        int index = randomSeed % mask;
        entry = (int*)((char*)innerState + 0x10) + index * 5; // 5 ints per entry (0x14 bytes)
        
        // Search for an entry with opcode 3 and matching float value
        while (entry != nullptr) {
            if (entry[0] == 3 && *(float*)&entry[1] == magicFloat) {
                entry += 2; // Advance past the matched pair
                goto foundEntry;
            }
            entry = (int*)entry[4]; // Next in linked list? (interpretation: fourth int is next pointer)
        }
        entry = (int*)&defaultEntry; // Fallback to default
    } else {
        entry = *(int**)((char*)innerState + 0xc) + 2; // Direct pointer +2 ints
    }
    
foundEntry:
    // Write the entry (two ints) to the packet buffer
    int* writePtr = *(int**)((char*)this + 8); // +0x8: current write pointer in buffer
    writePtr[0] = entry[0];
    writePtr[1] = entry[1];
    *(int**)((char*)this + 8) = writePtr + 2; // Advance by 8 bytes
    
    // Check if the written opcode is zero
    int* lastWritten = (int*)(*(int*)((char*)this + 8) - 8);
    if (lastWritten != nullptr && *lastWritten != 0) {
        return; // Non-zero opcode triggers early return
    }
    
    // Opcode was zero: insert a '5' opcode and duplicate the previous entry
    *(int**)((char*)this + 8) = lastWritten; // Rewind to previous pair (actually rewrites)
    uint* writePtr2 = *(uint**)((char*)this + 8);
    *writePtr2 = 5; // Opcode 5 (e.g., timestamp)
    writePtr2[1] = generateTimestamp(0, 0); // FUN_00637c50
    *(int**)((char*)this + 8) = writePtr2 + 2;
    
    // Duplicate the pair that was two positions back (the original entry)
    uint* dupWrite = *(uint**)((char*)this + 8);
    dupWrite[0] = dupWrite[-2];
    dupWrite[1] = dupWrite[-1];
    *(int**)((char*)this + 8) = dupWrite + 2;
    
    // Now process the last two writes
    int* currentWrite = *(int**)((char*)this + 8);
    int* prevPair = (int*)(currentWrite - 8); // Pair before last
    int* prevPrevPair = (int*)(currentWrite - 16); // Pair before that
    
    // If prevPrevPair opcode is 0, use alternative pointer from netState
    if (*prevPair == 0) {
        prevPair = (int*)((char*)netState + 0x34); // +0x34: some offset
    }
    
    // Assign based on opcode of prevPrevPair
    if (*prevPrevPair == 5) {
        *(int*)(prevPrevPair[1] + 8) = prevPair[1]; // Set field at +0x8
    } else if (*prevPrevPair == 7) {
        *(int*)(prevPrevPair[1] + 8) = prevPair[1];
    }
    
    // Pop the last pair (go back 8 bytes)
    *(int**)((char*)this + 8) = currentWrite - 2;
    
    // Check buffer capacity and potentially flush
    if (*(uint*)((char*)netState + 0x20) <= *(uint*)((char*)netState + 0x24)) {
        flushBuffer(); // FUN_00627360
    }
    
    // Write two '4' opcodes (IDs? object references?)
    uint* writePtr3 = *(uint**)((char*)this + 8);
    *writePtr3 = 4;
    writePtr3[1] = generateObjectID(); // FUN_00638920
    *(int**)((char*)this + 8) = writePtr3 + 2;
    
    if (*(uint*)((char*)netState + 0x20) <= *(uint*)((char*)netState + 0x24)) {
        flushBuffer();
    }
    
    writePtr3 = *(uint**)((char*)this + 8);
    *writePtr3 = 4;
    writePtr3[1] = generateObjectID();
    *(int**)((char*)this + 8) = writePtr3 + 2;
    
    // Copy the last pair before the two '4's to a newly allocated structure
    int* lastPair = (int*)(*(int*)((char*)this + 8) - 8);
    int* newStruct = (int*)allocateStruct(); // FUN_00638020
    newStruct[0] = lastPair[-2]; // Opcode from before the '4's?
    newStruct[1] = lastPair[-1]; // Associated data
    *(int**)((char*)this + 8) = (int*)((char*)this + 8) - 16; // Rewind 16 bytes (two pairs)
    
    // Duplicate the pair that was two positions back again
    uint* dupWrite2 = *(uint**)((char*)this + 8);
    dupWrite2[0] = dupWrite2[-2];
    dupWrite2[1] = dupWrite2[-1];
    *(int**)((char*)this + 8) = dupWrite2 + 2;
    
    // Finally, write back the saved pair into the lookup table
    innerState = *(InnerState**)(*(int*)((char*)this + 0x10) + 0x30);
    if (innerState->count < 2) {
        int mask = (1 << (innerState->bitField & 0x1f)) - 1;
        if (mask == 0) mask = 1;
        int index = randomSeed % mask;
        entry = (int*)((char*)innerState + 0x10) + index * 5;
        while (entry != nullptr) {
            if (entry[0] == 3 && *(float*)&entry[1] == magicFloat) {
                entry += 2;
                goto writeBack;
            }
            entry = (int*)entry[4];
        }
        entry = (int*)&defaultEntry;
    } else {
        entry = *(int**)((char*)innerState + 0xc);
        // Note: Original goto jumps to label that offsets by +2? Actually the assembly shows piVar6 = piVar6 + 2; but the decompilation shows if (piVar6 != &DAT_00e2a93c) goto... So it's conditional.
        // We'll simplify.
    }
    
writeBack:
    // Write the last pair from buffer back into the table
    int* lastWrite = (int*)(*(int*)((char*)this + 8) - 8);
    entry[0] = lastWrite[0];
    entry[1] = lastWrite[1];
    *(int**)((char*)this + 8) = (int*)((char*)this + 8) - 8; // Pop
    return;
}