// FUNC_NAME: Handle::Handle
// Function address: 0x00816e10
// Role: Constructor for a 32-byte handle structure. Initializes the handle value from the argument and zeroes remaining fields.
// The class likely wraps a resource/object handle with 7 additional fields (counters, flags, etc.)

class Handle {
public:
    uint32_t handleValue;  // +0x00
    uint32_t field_04;     // +0x04
    uint32_t field_08;     // +0x08
    uint32_t field_0C;     // +0x0C
    uint32_t field_10;     // +0x10
    uint32_t field_14;     // +0x14
    uint32_t field_18;     // +0x18
    uint32_t field_1C;     // +0x1C

    // Constructor: sets handle to the given value, zeroes all other fields
    __thiscall Handle(uint32_t initialHandle) {
        this->handleValue = initialHandle;
        this->field_04 = 0;
        this->field_08 = 0;
        this->field_0C = 0;
        this->field_10 = 0;
        this->field_14 = 0;
        this->field_18 = 0;
        this->field_1C = 0;
    }
};