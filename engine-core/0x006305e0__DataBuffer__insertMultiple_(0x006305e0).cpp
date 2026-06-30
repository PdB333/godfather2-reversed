// FUNC_NAME: DataBuffer::insertMultiple (0x006305e0)
// Reconstructed from Ghidra decompilation of The Godfather 2 (EARS engine).

// This function appears to be a member of a custom container (DataBuffer) that stores pairs of integers.
// Offsets:
// +0x08: int* m_writePtr (current write position in buffer)
// +0x0C: int* m_basePtr   (base of allocated storage, used for indexing by integer offsets)
// The container likely holds a dynamic array of 8-byte entries (two ints each).

// Forward declarations of helper functions (addresses assumed)
int* __stdcall getDefaultValue();        // 0x00625430 – returns a default/null pointer
int* __thiscall handleSpecialCase(int);  // 0x00625950 – handles empty/first-insert case
void __stdcall finalizeInsert();         // 0x006362d0 – performs post-insert cleanup/validation

class DataBuffer {
public:
    int* m_writePtr;  // +0x08
    int* m_basePtr;   // +0x0C

    // __fastcall in original decompiled as __fastcall(this in ECX, param2=index1, param3=index2)
    // We use __thiscall for clarity.
    int __thiscall insertMultiple(int index1, int index2) {
        int* basePtr = m_basePtr;
        int* writePtr = m_writePtr;

        // Compute source for first element: basePtr+2 (offset 8 bytes from base)
        int* firstSrc = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(basePtr) + 8);

        // Special case: if the insertion would be at an already-empty position and buffer has room?
        if (firstSrc < writePtr && firstSrc != nullptr && *firstSrc == 0) {
            // Delegate to handleSpecialCase (likely starts a new segment or treats as special)
            return reinterpret_cast<int>(handleSpecialCase(index2));
        }

        // --- Insert first pair (from basePtr+8 and basePtr+12) ---
        // Copy two ints from basePtr[2] and basePtr[3] to current write position
        writePtr[0] = firstSrc[0];                       // value from basePtr[2]
        writePtr[1] = *(reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(basePtr) + 0xC)); // basePtr[3]
        m_writePtr = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(m_writePtr) + 8);
        writePtr = m_writePtr;

        // --- Insert second pair (from computed offset based on index1) ---
        int* secondSrc;
        if (index1 - 1 < 1) {
            // Index too low – use default value (null or placeholder)
            secondSrc = getDefaultValue();
        } else {
            // Access element at index (index1 - 2) from basePtr:
            // basePtr + (index1-2)*2 ints => basePtr - 8 + (index1-1)*8 bytes
            secondSrc = reinterpret_cast<int*>(
                reinterpret_cast<uintptr_t>(basePtr) - 8 + (index1 - 1) * 8
            );
        }
        writePtr[0] = secondSrc[0];
        writePtr[1] = secondSrc[1];
        m_writePtr = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(m_writePtr) + 8);
        writePtr = m_writePtr;

        // --- Insert third pair (from computed offset based on index2) ---
        int* thirdSrc;
        if (index2 - 2 < 1) {
            thirdSrc = getDefaultValue();
        } else {
            // Access element at index (index2 - 3) from basePtr:
            // basePtr - 8 + (index2-2)*8 bytes
            thirdSrc = reinterpret_cast<int*>(
                reinterpret_cast<uintptr_t>(basePtr) - 8 + (index2 - 2) * 8
            );
        }
        writePtr[0] = thirdSrc[0];
        writePtr[1] = thirdSrc[1];
        m_writePtr = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(m_writePtr) + 8);

        // Perform post-insert cleanup (e.g., reorder or validate chain)
        finalizeInsert();

        // Back up one element (last written pair) for validation
        int* lastPair = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(m_writePtr) - 8);
        if (lastPair != nullptr && *lastPair != 0) {
            // Check if it's a valid entry (not a special sentinel like (1,0))
            bool isValid = !(*lastPair == 1 && *(lastPair + 1) == 0);
            if (isValid) {
                m_writePtr = lastPair;  // Keep write pointer at this element? Actually revert? Pointer is already at next position?
                // The original does: *(this+8) = piVar2; which resets buffer to lastPair (i.e., don't advance)
                m_writePtr = lastPair;
                return 1;  // Success, element kept
            }
        }
        // Invalid pair – revert write pointer and return failure
        m_writePtr = lastPair;  // In both cases, write ptr is set to lastPair
        return 0;
    }
};