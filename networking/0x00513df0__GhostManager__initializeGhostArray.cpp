// FUNC_NAME: GhostManager::initializeGhostArray
// Function at 0x00513df0 – Initializes an array of ghost entities from a pool.
// Takes a pointer to a 2-uint32 output handle (ghost pool pointer + count)
// The array elements are at offset 0xA0 in the pool's base allocation.
// Each element is 0xA8 bytes; fields are cleared at offsets -0x14, 0x00, +0x14, +0x28, +0x3C, +0x50, +0x64, +0x78.

struct GhostArrayHandle {
    void* poolPtr;    // +0x00
    uint32 count;     // +0x04
};

// Assumed size of each ghost entry
#define GHOST_ENTRY_SIZE 0xA8

// Offset to the start of the array within the pool
#define GHOST_ARRAY_OFFSET 0xA0

// Field offsets relative to the start of a ghost entry
#define GHOST_FIELD_0   (-0x14)  // 4 bytes cleared
#define GHOST_FIELD_1   0x00     // 4 bytes cleared
#define GHOST_FIELD_2   0x14     // 4 bytes cleared
#define GHOST_FIELD_3   0x28     // 4 bytes cleared
#define GHOST_FIELD_4   0x3C     // 4 bytes cleared
#define GHOST_FIELD_5   0x50     // 4 bytes cleared
#define GHOST_FIELD_6   0x64     // 4 bytes cleared
#define GHOST_FIELD_7   0x78     // 4 bytes cleared

GhostArrayHandle* __fastcall GhostManager::initializeGhostArray(GhostArrayHandle* outHandle)
{
    uint32 poolId = 0;               // local_4
    uint32 numEntries = 0;           // unaff_EDI – actually passed in EDI (non‑standard)

    // Count should be set by the caller (via EDI register in the original x86)
    numEntries = this->someCount;    // simplified; see note below

    if (numEntries != 0) {
        poolId = FUN_00485650(&poolId);   // Allocate/resolve pool, returns a handle
        if (poolId != 0 && numEntries != 0) {
            // Base pointer to the array inside the pool
            uint32* arrayStart = (uint32*)(poolId + GHOST_ARRAY_OFFSET);   // puVar2

            for (uint32 i = 0; i < numEntries; i++) {
                uint32* entry = arrayStart + (i * (GHOST_ENTRY_SIZE / sizeof(uint32)));

                // Only clear if the base pointer is valid (non‑null)
                if (entry != (uint32*)0) {
                    entry[-5]  = 0;   // offset -0x14 (4 bytes)
                    entry[0]   = 0;   // offset +0x00
                    entry[5]   = 0;   // offset +0x14 (5*4=20)
                    entry[10]  = 0;   // offset +0x28
                    entry[15]  = 0;   // offset +0x3C
                    entry[20]  = 0;   // offset +0x50
                    entry[25]  = 0;   // offset +0x64
                    entry[30]  = 0;   // offset +0x78
                }
            }
        }
        outHandle->poolPtr = (void*)poolId;
        outHandle->count   = numEntries;
        return outHandle;
    }
    outHandle->poolPtr = 0;
    outHandle->count   = 0;
    return outHandle;
}

// Note: The original code uses an uninitialised parameter unaff_EDI, likely passed in the EDI register
// from the calling function.  For clarity, we assume it is stored in a member variable (this->someCount)
// or that the function itself is a static helper that reads a global.  The reconstruction above treats
// it as an explicit input for understanding.