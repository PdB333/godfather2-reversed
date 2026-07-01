// FUNC_NAME: EARSObject::EARSObject
// Function address: 0x008d01d0
// Role: Constructor for base EARS engine object. Sets vtable and two additional pointer fields.

typedef void* VTablePtr;
typedef void* DataPtr;

// Forward declaration of base initializer
void __thiscall FUN_0083f8e0(void* owner);

class EARSObject {
public:
    VTablePtr vtable;       // +0x00 (vtable pointer)
    // ... other members (not shown) ...
    DataPtr field_3C;       // +0x3C (index 0xf) – likely type info or behavior data
    DataPtr field_48;       // +0x48 (index 0x12) – secondary data pointer

    // Constructor
    __thiscall EARSObject* EARSObject(void* owner);
};

__thiscall EARSObject* EARSObject::EARSObject(void* owner) {
    // Call base class initializer (e.g., memory zeroing or reference counting)
    FUN_0083f8e0(owner);

    // Set up virtual function table
    this->vtable = (VTablePtr)0x00d7ce90;

    // Initialize runtime type information or behavior tables
    this->field_3C = (DataPtr)0x00d7ce80;  // +0x3C points to structure at address 0x00d7ce80
    this->field_48 = (DataPtr)0x00d7ce7c;  // +0x48 points to structure at address 0x00d7ce7c

    return this;
}