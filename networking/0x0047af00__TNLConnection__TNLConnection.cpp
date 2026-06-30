// FUNC_NAME: TNLConnection::TNLConnection

class TNLConnection {
public:
    // Vtable pointers (set here)
    void* vtable;                 // +0x00
    int field_0x3C;               // +0x3C: pointer to PTR_LAB_00e330dc
    int field_0x48;               // +0x48: pointer to PTR_LAB_00e330ec

    // Sub-object for packet window management
    struct PacketWindow {
        // Addresses +0x50 (0x14 * 4)
    } packetWindow;               // +0x50

    // Array of 32 packet slots (each 4 bytes)
    // Stored at offsets 0x5C .. 0xD8
    int packetSlots[32];          // +0x5C (actually starts at +0x5C)

    // Constructor
    void __fastcall constructor(void* param_1) {
        // Set vtable pointers
        this->vtable = &PTR_FUN_00e330c0;          // +0x00
        this->field_0x3C = &PTR_LAB_00e330dc;      // +0x3C
        this->field_0x48 = &PTR_LAB_00e330ec;      // +0x48

        // Initialize packet window sub-object at +0x50
        sub_4086d0(&this->packetWindow);           // FUN_004086d0
        sub_408310(&this->packetWindow);           // FUN_00408310

        // Initialize 32 packet slots (starting at +0x5C)
        int* slotPtr = &this->packetSlots[0];      // Actually starts at +0x5C
        for (int i = 0; i < 32; ++i) {
            sub_408310(slotPtr + i);               // FUN_00408310 on each slot
        }

        // Global initialization finalizer
        sub_46c640();                              // FUN_0046c640
    }
};