// FUNC_NAME: copyObjectBlocks
// Function at 0x698d60: Copies blocks of a fixed size (0x504 bytes / 321 dwords) from a source array to a destination array.
// Used to replicate or grow arrays of game objects (e.g., objects of size 0x504 bytes).
// Parameters:
//   outDestEnd - output pointer set to the final destination position (after last copied block)
//   srcStart   - start of source array
//   srcEnd     - end of source array (exclusive)
//   destStart  - start of destination array (can be null, in which case copy is skipped but pointers still advance)
// Returns: void (updated destination end via outDestEnd)

#include <cstdint>
#include <cstring>

static constexpr int OBJECT_DWORD_COUNT = 0x141;  // 321 dwords per block
static constexpr int OBJECT_BYTE_SIZE = OBJECT_DWORD_COUNT * 4; // 0x504

void __stdcall copyObjectBlocks(uint32_t** outDestEnd, uint32_t* srcStart, uint32_t* srcEnd, uint32_t* destStart)
{
    uint32_t* dest = destStart;
    *outDestEnd = dest;  // initial destination end

    while (srcStart != srcEnd)
    {
        if (dest != nullptr)
        {
            // Copy one block of OBJECT_BYTE_SIZE bytes
            // This likely copies a game object's data (e.g., entity, NPC, etc.)
            for (int i = 0; i < OBJECT_DWORD_COUNT; ++i)
            {
                dest[i] = srcStart[i];
            }
        }

        srcStart += OBJECT_DWORD_COUNT;
        dest += OBJECT_DWORD_COUNT;
    }

    *outDestEnd = dest;  // final destination end after all copies
}