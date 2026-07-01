// FUNC_NAME: EARSObject::~EARSObject
// Address: 0x0076d2c0
// Role: Destructor for a base EARS object. Manages two subobjects at offsets +0x68 and +0x70.

#include <cstdint>

extern uint32_t _DAT_00d66208;         // Global reference count or handle
extern uint32_t PTR_LAB_00d6622c;      // Vtable for current class
extern uint32_t PTR_LAB_00d63090;      // Vtable for base class

void __thiscall FUN_007fb9b0(uint32_t, uint32_t);  // Decrements/releases global reference
void __thiscall FUN_007f7e40();                     // Intermediate cleanup
void __thiscall FUN_004daf90(uint32_t*);            // Deletes subobject (operator delete)
void __thiscall FUN_0080ea60();                     // Final cleanup

class EARSObject {
public:
    virtual ~EARSObject();
private:
    // Subobject pointers stored at these offsets:
    // +0x68: first subobject (slot 0x1a)
    // +0x70: second subobject (slot 0x1c)
};

void __thiscall EARSObject::~EARSObject()
{
    uint32_t globalValue = _DAT_00d66208;  // Get global reference count

    // Set vtable pointer to current class
    *(uint32_t*)this = (uint32_t)&PTR_LAB_00d6622c;

    // Release global reference
    FUN_007fb9b0(1, globalValue);   // 0x007fb9b0

    // Perform intermediate cleanup
    FUN_007f7e40();                 // 0x007f7e40

    // Delete subobject at offset +0x70
    if (*(uint32_t*)((uint8_t*)this + 0x70) != 0) {
        FUN_004daf90((uint32_t*)((uint8_t*)this + 0x70)); // 0x004daf90
    }

    // Switch vtable to base class
    *(uint32_t*)this = (uint32_t)&PTR_LAB_00d63090;

    // Delete subobject at offset +0x68
    if (*(uint32_t*)((uint8_t*)this + 0x68) != 0) {
        FUN_004daf90((uint32_t*)((uint8_t*)this + 0x68)); // 0x004daf90
    }

    // Final cleanup
    FUN_0080ea60();                 // 0x0080ea60
}