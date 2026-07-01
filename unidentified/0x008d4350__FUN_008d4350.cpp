// FUNC_NAME: SomeClass::Constructor
// Function address: 0x008d4350
// Allocates and initializes an object of size 0x88 (136 bytes)
// Takes an owner pointer (param_1) and a second parameter (param_2)
// Sets vtable pointer at +0x00 and another function table pointer at +0x13*4 = 0x4C

#include <cstdint>

// Forward declarations
void* __fastcall operator_new(size_t size); // Assuming FUN_009c8e50 is a custom operator new
void __fastcall BaseConstructor();           // FUN_008d3ec0 is likely a base class constructor

// Vtable symbols (extern references)
extern void* PTR_FUN_00d7d60c[];  // vtable for SomeClass
extern void* PTR_LAB_00d7d5fc[];  // secondary vtable or function table

class SomeBase {
public:
    // Base class methods...
};

class SomeClass : public SomeBase {
public:
    // Offset +0x00: vtable pointer (inherited from SomeBase or set here)
    // Offset +0x04 ... (other base members)
    // Offset +0x1C: param_2 stored at [7] (7*4 = 28 = 0x1C)
    // Offset +0x48: param_1 stored at [0x12] (18*4 = 72 = 0x48)
    // Offset +0x4C: secondary function table at [0x13] (19*4 = 76 = 0x4C)

    uint32_t field_0x1C;   // param_2
    uint32_t field_0x48;   // param_1 (owner pointer)
    void*    field_0x4C;   // secondary table pointer

    static SomeClass* Create(int owner, uint32_t param_2) {
        if (owner == 0) return nullptr;

        void* mem = operator_new(0x88);
        if (mem == nullptr) return nullptr;

        SomeClass* obj = static_cast<SomeClass*>(mem);
        
        // Call base class constructor
        BaseConstructor();

        // Initialize fields
        obj->field_0x1C = param_2;      // offset +0x1C
        obj->field_0x48 = owner;        // offset +0x48
        obj->field_0x00 = &PTR_FUN_00d7d60c;  // vtable
        obj->field_0x4C = &PTR_LAB_00d7d5fc;  // secondary table

        return obj;
    }
};