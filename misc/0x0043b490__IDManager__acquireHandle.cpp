// FUNC_NAME: IDManager::acquireHandle
// Address: 0x0043b490
// Allocates or returns an existing 12-bit handle ID for a managed object.
// The handle is stored in field +0x14: bit 28 indicates allocation status, lower 12 bits are the ID.
// Uses a global bitfield array to track used IDs.

class IDManager {
public:
    uint32_t acquireHandle(); // __thiscall (this in ecx)
    // ... other members ...
};

// Global constants/state
extern uint32_t g_lastAllocatedID;    // DAT_0110abd4
extern uint32_t g_idBitfield[];       // DAT_0120e718, array of 32-bit bitfield masks
extern uint32_t g_idShiftBits;        // DAT_0120e710, shift amount for index calculation

// External function: allocates a new free ID and returns it
extern uint32_t allocateNewID();      // FUN_0043bb00

uint32_t IDManager::acquireHandle()
{
    uint32_t handleFlags = *(uint32_t*)((uint8_t*)this + 0x14);
    
    // If bit 28 is already set, handle already allocated – return the lower 12 bits.
    if ((handleFlags >> 0x1C) & 1)
    {
        return handleFlags & 0xFFF;
    }
    
    // Allocate a new ID (12-bit)
    uint32_t newID = 0;
    newID = allocateNewID(); // FUN_0043bb00
    
    // Store the new ID in the handle field, preserving bits 12-27 and setting bit 28.
    // Bits 0-11 = newID, bit 28 = 1 (allocated), rest unchanged.
    *(uint32_t*)((uint8_t*)this + 0x14) = (handleFlags & 0xFFFFF000) | newID | 0x10000000;
    
    // Update global last allocated ID
    g_lastAllocatedID = newID;
    
    // Mark the ID as used in the global bitfield array.
    // Index = newID >> (g_idShiftBits & 0x1F)
    // Bit position = newID & 0x1F
    uint32_t shift = g_idShiftBits & 0x1F;
    uint32_t bitIndex = 1 << (newID & 0x1F);
    uint32_t arrayIndex = newID >> shift;
    g_idBitfield[arrayIndex] |= bitIndex;
    
    return newID;
}