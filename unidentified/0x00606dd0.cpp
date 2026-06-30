// FUN_00606dd0: allocateSlotWithType
// Uses global array at 0x011a0f28 of 0x38-byte slot descriptors (max 0x1000 slots).
// struct SlotDescriptor { uint8_t state; uint8_t type; ... } // +0x00: state, +0x01: type
// Returns handle (0xFFFFFFFF on failure), calls getDefaultSlotIndex (0x606b50) and allocateSlotInternal (0x606c80).

typedef unsigned char uint8_t;
typedef unsigned int uint;

struct SlotDescriptor {
    uint8_t state; // +0x00: 0=free, 1=used, 2+=invalid
    uint8_t type;  // +0x01: type identifier
    // ... remaining 0x36 bytes
};

extern SlotDescriptor g_slotDescriptors[0x1000]; // at 0x011a0f28

uint getDefaultSlotIndex(void); // FUN_00606b50
int allocateSlotInternal(int arg1, int arg2, int arg3, int arg4, uint slotType, uint slotIndex); // FUN_00606c80

int allocateSlotWithType(int arg1, int arg2, int arg3, int arg4,
                         uint slotType, uint resourceIndex, uint unused, uint slotIndex)
{
    // Validate resource index
    if (resourceIndex >= 0x1000) {
        return -1;
    }
    // Ensure resource descriptor exists (pointer check – always true for static array)
    if (&g_slotDescriptors[resourceIndex] == nullptr) {
        return -1;
    }
    // If no slot index provided, get a default one
    if (slotIndex == 0xFFFFFFFF) {
        slotIndex = getDefaultSlotIndex();
    }
    // Validate slot index
    if (slotIndex >= 0x1000) {
        return -1;
    }
    if (&g_slotDescriptors[slotIndex] == nullptr) {
        return -1;
    }
    // Check that the target slot is available (state < 2)
    if (g_slotDescriptors[slotIndex].state >= 2) {
        return -1;
    }
    // If no slot type provided, inherit from resource descriptor
    if (slotType == 0) {
        slotType = g_slotDescriptors[resourceIndex].type;
    }
    // Delegate to internal allocation
    return allocateSlotInternal(arg1, arg2, arg3, arg4, slotType, slotIndex);
}