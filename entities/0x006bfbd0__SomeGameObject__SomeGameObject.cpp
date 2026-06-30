// FUNC_NAME: SomeGameObject::SomeGameObject
// Address: 0x006bfbd0
// Role: Constructor for a game object (likely Sentient or Player base)
// Initializes vtable pointers, zeroes fields, and optionally performs additional setup
// based on global game state.

class SomeGameObject {
public:
    // Vtable pointers (offsets 0x00, 0x08)
    void* vtable1;      // +0x00
    int unknown0x04;    // padding? +0x04
    void* vtable2;      // +0x08

    // Fields at offsets 0x9c, 0x9d, 0x9e (int sized)
    int field_0x9c;     // +0x9c - possible object handle or index
    int field_0x9d;     // +0x9d
    int field_0x9e;     // +0x9e

    // Constructor
    SomeGameObject(int arg0) {
        // Call base class constructor (FUN_006d7020)
        baseConstructor(arg0);  // Possibly Entity::Entity or similar

        // Set vtable pointers
        this->vtable1 = &PTR_FUN_00d5ee24;
        this->vtable2 = &PTR_LAB_00d5ee1c;

        // Initialize fields
        this->field_0x9c = 0;
        this->field_0x9d = 0;
        this->field_0x9e = 0;

        // Check global game state pointer (DAT_012233a0)
        int* globalPtr = *(int**)(DAT_012233a0 + 4);
        if (globalPtr != 0 && globalPtr != 0x1f30) {
            uint32_t flags = *(uint32_t*)(globalPtr - 0x1648);
            if ((flags >> 0x1c & 1) != 0 && globalPtr != -0x814) {
                // Create some sub-object
                uint32_t subObj = FUN_007e0d20();  // e.g., create component
                FUN_006bfa20(subObj);              // attach it

                // Process field_0x9c as an offset into a pool
                if (this->field_0x9c != 0 && this->field_0x9c != 0x48) {
                    int basePtr = this->field_0x9c - 0x48;  // Subtract struct size
                    // Read double at basePtr + 0x1a8, split into two floats
                    double doubleVal = *(double*)(basePtr + 0x1a8);
                    float lowFloat = (float)doubleVal;
                    float highFloat = (float)((unsigned long long)doubleVal >> 32);
                    // Compute difference from global constant
                    float diff = DAT_00e44564 - *(float*)(basePtr + 0x1b0);
                    // Recombine into a 64-bit value (likely a double)
                    uint64_t combined = ((uint64_t)(uint32_t)diff << 32) | (uint64_t)(uint32_t)lowFloat;
                    // Call math utility
                    FUN_006d72a0(&combined);  // Possibly normalize or store
                }
            }
        }
    }
};