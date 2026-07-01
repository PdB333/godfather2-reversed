// FUNC_NAME: eastl::VectorImpl::insert

#include <cstdint>
#include <cstring>

// Forward declarations of internal allocator functions (from EASTL)
void* debugAllocate(size_t size, const char* name, int flags, int alignment, const char* file, int line);
void  debugFree(void* ptr);

// Vector internal structure: three pointers for begin, end, capacity_end (each pointing to 4-byte elements)
struct VectorImpl {
    int* mpBegin;        // +0x00
    int* mpEnd;          // +0x04
    int* mpCapacityEnd;  // +0x08
};

void __thiscall VectorImpl::insert(int* pos, uint count, const int& value) {
    // Ensure pos is within range (begin <= pos <= end)
    int* data = mpBegin;
    int* endPtr = mpEnd;
    int* capEnd = mpCapacityEnd;

    // Number of elements currently stored
    size_t size = endPtr - data;
    // Number of elements that can be stored without reallocation
    size_t capacity = capEnd - data;
    // Number of elements after insertion point
    size_t elementsAfterPos = endPtr - pos;

    // Check if reallocation is needed
    if (size + count > capacity) {
        // Calculate new capacity: at least double old capacity, but not less than needed
        size_t newCapacity;
        if (size == 0) {
            newCapacity = 1;
        } else {
            size_t doubleCap = size * 2;
            newCapacity = (doubleCap > size + count) ? doubleCap : (size + count);
        }

        // Allocate new storage
        int* newData = nullptr;
        if (newCapacity > 0) {
            // Allocator call: debugAllocate(size, name, flags, alignment, file, line)
            newData = (int*)debugAllocate(newCapacity * 4, "EASTL", 0, 0,
                                          "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h", 0xe9);
        }

        // Number of elements before insertion point
        size_t beforeCount = pos - data;
        // Copy elements before pos
        std::memmove(newData, data, beforeCount * 4);
        // Fill new elements with value
        int* insertStart = newData + beforeCount;
        for (size_t i = 0; i < count; ++i) {
            insertStart[i] = value;
        }
        // Copy elements after pos
        size_t afterCount = endPtr - pos;
        std::memmove(newData + beforeCount + count, pos, afterCount * 4);

        // Free old storage if any
        if (data != nullptr) {
            debugFree(data);
        }

        // Update vector pointers
        mpBegin = newData;
        mpEnd = newData + beforeCount + count + afterCount;
        mpCapacityEnd = newData + newCapacity;
    } else {
        // Sufficient capacity: shift elements to make room
        if (count != 0) {
            // Number of elements from pos to end
            size_t tailCount = elementsAfterPos;

            if (count <= tailCount) {
                // Case 1: count fits within the tail, shift tail right by count
                // Move elements from pos to end-count to pos+count .. end
                std::memmove(endPtr + count, endPtr - count, (endPtr - (endPtr - count))? Actually careful:
                // The offset calculation from the disassembly: shift the last 'tailCount - count' elements right by count
                // Then shift the 'count' elements from pos to pos+count? 
                // Simpler: shift the block starting at pos+count..end to pos+count..end? Actually we need to shift the entire tail right.
                // Standard method: move elements from (end - count) to end to the right, then fill the gap with value copies.
                // The decompiled code does this with two memmoves.
                // I'll implement the same pattern:
                // Shift the last 'count' elements of the tail to after end
                std::memmove(endPtr + count, endPtr - count, (uintptr_t)endPtr - (uintptr_t)(endPtr - count));
                // Shift the 'tailCount - count' elements that follow pos to the right by count
                // Actually: move the block from pos to (end - count) to pos+count
                // But the disassembly uses puVar8 = endPtr - count, then moves from param_2 (pos) to puVar8 - ((puVar8-pos)/4)?
                // Let's implement logically: The tail consists of two parts: the part immediately after pos of length 'afterPos' = pos...end
                // After shifting the last count elements beyond end, we have a gap from pos to end - count.
                // We then move the block from pos to end-count to pos+count.
                // I'll use two memmoves:
                std::memmove(endPtr + count, endPtr - count, count * 4);
                std::memmove(pos + count, pos, (endPtr - count - pos) * 4);
                // Fill the vacated 'count' slots with value
                for (size_t i = 0; i < count; ++i) {
                    pos[i] = value;
                }
                mpEnd = endPtr + count;
            } else {
                // Case 2: count > tailCount, need to extend tail
                size_t extra = count - tailCount;
                // Fill the new extra slots at end with value
                for (size_t i = 0; i < extra; ++i) {
                    endPtr[i] = value;
                }
                mpEnd = endPtr + extra;
                // Shift original tail (from pos to end) after the newly filled extra slots
                // newEnd = endPtr + extra; oldEnd = endPtr;
                // Move block from pos to oldEnd
                std::memmove(pos + count, pos, tailCount * 4);
                // Fill the newly created gap of size tailCount with value (the rest were already filled above)
                for (size_t i = 0; i < tailCount; ++i) {
                    pos[i] = value;
                }
                // Update end pointer already done
                mpEnd = endPtr + extra + tailCount;
            }
        }
    }
}