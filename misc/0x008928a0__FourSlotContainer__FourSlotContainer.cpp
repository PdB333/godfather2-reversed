// FUNC_NAME: FourSlotContainer::FourSlotContainer
// Function address: 0x008928a0
// Role: Constructor for a container with 4 slots, initializes header fields to zero and calls an external init routine for each slot.

class FourSlotContainer
{
public:
    // Offsets: +0x00, +0x04, +0x08, +0x0C, +0x10  (5 int32 header fields)
    int32_t field_0x00;
    int32_t field_0x04;
    int32_t field_0x08;
    int32_t field_0x0C;
    int32_t field_0x10;
    // +0x14 onward: 4 sub-structures (size TBD)

    // Constructor
    __thiscall FourSlotContainer()
    {
        // Zero out the 5 header fields (20 bytes)
        field_0x00 = 0;
        field_0x04 = 0;
        field_0x08 = 0;
        field_0x0C = 0;
        field_0x10 = 0;

        // Initialize each of the 4 slots via a global helper (FUN_008922a0)
        // Note: The helper is called with no arguments; likely operates on global state or static data.
        initGlobalSlot(); // Slot 0
        initGlobalSlot(); // Slot 1
        initGlobalSlot(); // Slot 2
        initGlobalSlot(); // Slot 3
    }
};

// External helper function used by the constructor
extern void __cdecl initGlobalSlot(void); // Address 0x008922a0