// FUNC_NAME: ScriptVM::processInstructions
// Address: 0x0063bad0 - Core instruction executor for the EARS script bytecode interpreter
// This function processes a buffer of opcodes, performing operations like branch, float, hash lookup, and scheduling.

class ScriptVM {
public:
    // Return 1 on success, 0 on failure or if nothing to process
    int processInstructions(int thisPtr, int userData);

private:
    // External functions (to be resolved from other modules)
    int resolveReference(int thisPtr, int userData); // FUN_00625ca0
    int* getGlobalFloatTrampoline(); // FUN_00637f10
    int* getGlobalDefaultTrampoline(); // FUN_00637ea0
    int checkNextOpcode(); // FUN_00625740 -> returns opcode tag (maybe internal state)
    int scheduleInstruction(int thisPtr, int* start, int count); // FUN_006362d0
    int cleanupStack(); // FUN_0063cbc0

    // Known opcodes
    static const int kOpCopy = 2;        // Duplicate an instruction from read buffer
    static const int kOpFloatOp = 3;     // Float comparison/operations
    static const int kOpHashLookup = 4;  // Hash-based value lookup
    static const int kOpGetValue = 5;    // Fetch value from context+8
    static const int kOpReturn = 6;      // Return control (triggers scheduling)
    static const int kOpSomething = 7;   // Another fetch similar to kOpGetValue
};

int ScriptVM::processInstructions(int thisPtr, int userData)
{
    // Structure offsets:
    // +0x08: mWritePtr (current write position in instruction buffer)
    // +0x0C: mReadPtr (current read position)
    // +0x10: mContext (pointer to a context block, e.g., behavior tree node)
    int* readPtr = *(int**)(thisPtr + 0x0C);
    int* writePtr = *(int**)(thisPtr + 0x08);

    // Check if there's data to process: read pointer < write pointer and not null
    if ((readPtr < writePtr) && (readPtr != nullptr)) {
        int opcode = *readPtr;
        if ((opcode == 7) || (opcode == 2)) {
            // Copy the instruction from read to write buffer
            *writePtr = opcode;
            writePtr[1] = readPtr[1];
            // Advance write pointer
            *(int**)(thisPtr + 0x08) = writePtr + 2;
            writePtr = *(int**)(thisPtr + 0x08);

            // Main processing loop
            while (true) {
                int* curWrite = *(int**)(thisPtr + 0x08);
                // Guard: check if we've wrapped around (decompiler artifact, but we keep)
                if ((curWrite - 2) == nullptr) break;

                int currOpcode = curWrite[-2];
                if (currOpcode == 5) {
                    currOpcode = *(int*)(curWrite[-1] + 8); // Value from context+8
                } else if (currOpcode != 7) {
                    break; // Unknown opcode, abort processing
                } else {
                    currOpcode = *(int*)(curWrite[-1] + 8); // Same for opcode 7
                }

                // Check if the resolved value is zero or matches a terminator from context
                int terminatorValue = *(int*)(*(int*)(thisPtr + 0x10) + 0x38);
                if ((currOpcode == 0) || (currOpcode == terminatorValue)) break;

                // Write a new instruction (opcode=5, value=resolved)
                *curWrite = 5;
                curWrite[1] = currOpcode;
                *(int**)(thisPtr + 0x08) = curWrite + 2;

                // Shift the buffer to compact after insertion
                int* shiftSrc = *(int**)(thisPtr + 0x08) - 2;
                if (shiftSrc < *(int**)(thisPtr + 0x08)) {
                    do {
                        shiftSrc[-2] = *shiftSrc;
                        shiftSrc[-1] = shiftSrc[1];
                        shiftSrc += 2;
                    } while (shiftSrc < *(int**)(thisPtr + 0x08));
                }
                // Adjust write pointer back by 8 bytes (one instruction removed)
                *(int**)(thisPtr + 0x08) = *(int**)(thisPtr + 0x08) - 2;

                // Call intermediate resolution step
                resolveReference(thisPtr, userData);

                // Read back the now-modified instruction at the current position
                int* instrPtr = *(int**)(thisPtr + 0x08);
                int modifiedOpcode = *(instrPtr - 2);
                int modifiedValue = *(instrPtr - 1);

                int* resultPtr;
                if (modifiedOpcode == 3) {
                    // Float op: check for NaN in the value (interpreted as float)
                    float fVal = *(float*)&modifiedValue;
                    if ((float)(int)fVal != fVal) {
                        goto LAB_0063bbfc;
                    }
                    resultPtr = getGlobalFloatTrampoline();
                } else if (modifiedOpcode == 4) {
                    // Hash lookup: use a bucket chain from a context table
                    int* hashBase = *(int**)(*(int*)(instrPtr - 3) + 0x10); // Context+0x10 -> table base
                    int shift = (*(byte*)(*(int*)(instrPtr - 3) + 7) & 0x1F);
                    int mask = (1 << shift) - 1;
                    int bucketIndex = mask & *(int*)(modifiedValue + 8);
                    resultPtr = (int*)(hashBase + bucketIndex * 5); // 0x14 bytes per bucket? (5 ints)

                    // Walk the linked list (4th field = next)
                    while (true) {
                        if ((*resultPtr == 4) && (resultPtr[1] == (int)modifiedValue)) {
                            resultPtr += 2;
                            goto LAB_0063bc01;
                        }
                        resultPtr = (int*)resultPtr[4];
                        if (resultPtr == nullptr) break;
                    }
                    // Fallback: global default
                    resultPtr = (int*)0x00e2a93c; // DAT_00e2a93c
                } else {
LAB_0063bbfc:
                    resultPtr = getGlobalDefaultTrampoline();
                }

LAB_0063bc01:
                // Write back the resolved operation to the instruction
                int* target = instrPtr - 2;
                *target = *resultPtr;
                target[1] = resultPtr[1];

                // Check the next state from the VM
                int nextState = checkNextOpcode(); // Returns a small integer (opcode tag)

                readPtr = *(int**)(thisPtr + 0x0C);
                if (nextState == 6) {
                    // Return instruction: copy two ints from read to write, then schedule
                    int* returnWrite = *(int**)(thisPtr + 0x08);
                    *returnWrite = *readPtr;
                    returnWrite[1] = readPtr[1];
                    *(int**)(thisPtr + 0x08) = returnWrite + 2;

                    // Also copy the following two ints (perhaps return address?)
                    int* readPtrBase = *(int**)(thisPtr + 0x0C);
                    returnWrite = *(int**)(thisPtr + 0x08);
                    *returnWrite = *(int*)(readPtrBase + 2);
                    returnWrite[1] = *(int*)(readPtrBase + 3);
                    *(int**)(thisPtr + 0x08) = returnWrite + 2;

                    // Schedule the instruction block starting at write-0x18 (3 instructions back)
                    scheduleInstruction(thisPtr, *(int**)(thisPtr + 0x08) - 6, 1);
                    return 1;
                }

                // If not returning, clear the remaining buffer to avoid stale data
                int* endMarker = *(int**)(thisPtr + 0x08);
                int* readLimit = *(int**)(thisPtr + 0x0C) + 6; // +0x18 bytes (6 ints)
                if (endMarker < readLimit) {
                    do {
                        *endMarker = 0;
                        endMarker++;
                    } while ((uint)endMarker < (uint)readLimit);
                }
                // Reset write pointer after the read pointer + 6 ints
                *(int**)(thisPtr + 0x08) = readLimit;
            }
        }
    }

    // No instructions processed or error – clean up and return failure
    cleanupStack();
    return 0;
}