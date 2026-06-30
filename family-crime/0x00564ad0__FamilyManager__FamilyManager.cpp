// FUNC_NAME: FamilyManager::FamilyManager
// Address: 0x00564ad0
// Role: Constructor for FamilyManager, initializes singleton pointer, vtable, and family data for 5 families.

class FamilyManager {
public:
    // Vtable pointers (multiple inheritance or interface)
    void* vtable0; // +0x00
    void* vtable4; // +0x04

    // Other member variables
    int field_0x1C;   // +0x1C
    int field_0x20;   // +0x20
    int field_0x124;  // +0x124
    int field_0x128;  // +0x128
    int field_0x22C;  // +0x22C
    int field_0x230;  // +0x230
    int field_0x234;  // +0x234
    uint8_t byte_0x238; // +0x238
    uint8_t byte_0x23C; // +0x23C

    // Array of 5 family entries, each 0x84 bytes
    struct FamilyEntry {
        int someInt;      // +0x00 (relative to entry)
        uint8_t someByte; // +0x04
        uint8_t pad[0x7F]; // padding to 0x84 bytes
    } families[5]; // starts at +0x2BC

    // Constructor
    FamilyManager() {
        // Store singleton pointer
        DAT_012233c0 = this;

        // Set vtable pointers
        this->vtable0 = &PTR_FUN_00e3a574;
        this->vtable4 = &PTR_FUN_00e3a58c;

        // Zero out various fields
        this->field_0x1C = 0;
        this->field_0x20 = 0;
        this->field_0x124 = 0;
        this->field_0x128 = 0;
        this->field_0x22C = 0;
        this->field_0x230 = 0;
        this->field_0x234 = 0;
        this->byte_0x238 = 0;
        this->byte_0x23C = 0;

        // Initialize family entries
        for (int i = 0; i < 5; i++) {
            families[i].someInt = 0xf; // Default value (e.g., reputation or ID)
            if (i < 4) {
                families[i].someByte = 0; // Only first 4 entries have byte set here
            }
        }
        // Note: The 5th family entry's byte is not initialized in this constructor.
    }
};