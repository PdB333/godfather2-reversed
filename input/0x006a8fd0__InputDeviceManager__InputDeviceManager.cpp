// FUNC_NAME: InputDeviceManager::InputDeviceManager
class InputDeviceManager {
public:
    // Vtable pointer stored at +0x00
    void** vtable;
    // Offset +0x04: some bool/int, initialized to 1
    int field_04;
    // Offset +0x08: some bool/int, initialized to 0
    int field_08;
    // Offset +0x0C: pointer to some static data (PTR_LAB_00d5d900)
    void* field_0C;
    // Offset +0x10: global instance pointer (DAT_01129950)
    // (stored globally)
    // Offset +0x40 (0x10*4): field_40, initialized to 0
    int field_40;
    // Offset +0x44 (0x11*4): field_44, initialized to 0
    int field_44;
    // Offset +0x48 (0x12*4): allocated buffer (size 0x14 = 20 bytes)
    void* buffer;
    // Offset +0x4C (0x13*4): count, initialized to 5
    int count;
    // Offset +0x50 (0x14*4): some int, initialized to 0
    int field_50;
    // Offset +0x54 (0x15*4): some int, initialized to 0
    int field_54;

    InputDeviceManager() {
        // Initialization
        this->field_04 = 1;
        this->field_08 = 0;
        this->field_0C = &PTR_LAB_00d5d900;  // some static VTable?
        // Store global pointer to self
        DAT_01129950 = this;
        // Set primary VTable
        this->vtable = &PTR_FUN_00d5d914;
        // Re-assign field_0C to another VTable? (maybe multiple inheritance)
        this->field_0C = &PTR_LAB_00d5d910;
        // Unknown initialization (maybe memory manager)
        FUN_00ab5fb0(0, 1);
        this->field_40 = 0;
        this->field_44 = 0;
        // Allocate small buffer (20 bytes)
        this->buffer = FUN_009c8e80(0x14);
        this->count = 5;
        this->field_50 = 0;
        this->field_54 = 0;
        // Register a callback for update (likely frame update)
        FUN_005e6620(FUN_006a8f10);
        // If there's a pre-allocated memory block, copy it into our buffer
        if (DAT_01206940 != 0) {
            FUN_00408900(this, &DAT_01206940, 0x8000);
        }
    }
};

// Global instance pointer
InputDeviceManager* DAT_01129950;