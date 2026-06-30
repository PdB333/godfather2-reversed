// FUNC_NAME: Entity::construct
// Address: 0x006e05d0
// Role: Constructor for an Entity subclass (likely from EA EARS engine).
// Initializes vtable, function pointer tables, zeroes some fields, and calls internal init.

#include <cstdint>

// Forward declaration of base class init (assumed from call at 0x00473840)
void initializeBase(uint32_t arg);

// Forward declaration of internal init (assumed from call at 0x006e01d0)
void internalInit();

// Structure offsets (in bytes from this):
// +0x00: vtable pointer
// +0x3C: function pointer table 1 (offset 0x0f * 4)
// +0x48: function pointer table 2 (offset 0x12 * 4)
// +0x50: function pointer table 3 (offset 0x14 * 4)
// +0x58 - 0x64: zeroed fields (offsets 0x16-0x19 * 4)
class Entity {
public:
    void** vtable;               // +0x00
    // unknown padding or members between +0x04 and +0x38
    void** funcTable1;           // +0x3C
    void** funcTable2;           // +0x48
    void** funcTable3;           // +0x50
    int32_t field_58;            // +0x58
    int32_t field_5C;            // +0x5C
    int32_t field_60;            // +0x60
    int32_t field_64;            // +0x64

    // Constructor
    __thiscall Entity* construct(uint32_t baseArg) {
        // Initialize base class / base portion
        initializeBase(baseArg);

        // Set vtable and internal function tables
        this->vtable = (void**)0x00d5f758;          // PTR_FUN_00d5f758
        this->funcTable1 = (void**)0x00d5f748;      // PTR_LAB_00d5f748
        this->funcTable2 = (void**)0x00d5f744;      // PTR_LAB_00d5f744
        this->funcTable3 = (void**)0x00d5f740;      // PTR_LAB_00d5f740

        // Zero out additional fields
        this->field_58 = 0;
        this->field_5C = 0;
        this->field_60 = 0;
        this->field_64 = 0;

        // Internal initialization (may set other members)
        internalInit();

        return this;
    }
};