// FUNC_NAME: removeFromArray
// Address: 0x004f1530
// Role: Removes an element at a given index from a global array of 8-byte entries, shifting remaining elements left.
// The array is stored at global pointer `g_arrayBase` and size at `g_arraySize`.
// Uses __fastcall: first parameter (ecx) is the index to remove.

#include <cstdint>

// Global array state (offsets based on Ghidra analysis)
static uint32_t* g_arrayBase = reinterpret_cast<uint32_t*>(0x01218f28); // array of two uint32 per element
static uint32_t g_arraySize = *reinterpret_cast<uint32_t*>(0x01218f2c); // number of elements

void __fastcall removeFromArray(uint32_t removeIndex)
{
    // Check if removal index is within valid range (strictly less than last element index)
    if (removeIndex < g_arraySize - 1U)
    {
        // Shift all elements after removeIndex left by one slot
        do
        {
            // Access element at removeIndex (each element is two 4-byte fields)
            uint32_t* element = g_arrayBase + removeIndex * 2; // each element is 8 bytes
            // Overwrite with next element's two fields
            element[0] = element[2];
            element[1] = element[3];
            removeIndex++;
        } while (removeIndex < g_arraySize - 1U);
    }
    // Decrement array size
    g_arraySize--;
}