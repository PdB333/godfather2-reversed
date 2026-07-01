// FUNC_NAME: EARSObject::Constructor
// Function address: 0x008e91e0
// This is a constructor for an EARS object. It calls a base class initializer, sets up the vtable,
// writes debug sentinel values, clears several short fields, then clears the sentinels and additional fields.

// Forward declaration of callee (base constructor)
extern void FUN_0046c590(int param);

class EARSObject
{
public:
    // +0x00: vtable pointer
    void* vtable;
    
    // +0x3C: pointer to some runtime label/function
    void* ptr_field_0x3C;
    
    // +0x48: pointer to another runtime label/function
    void* ptr_field_0x48;
    
    // +0x50..0x5C: debug magic numbers
    uint32 magic1; // +0x50
    uint32 magic2; // +0x54
    uint32 magic3; // +0x58
    uint32 magic4; // +0x5C
    
    // +0x60: field cleared after magic
    uint32 field_0x60;
    
    // +0x64, +0x66: short fields
    uint16 field_0x64;
    uint16 field_0x66;
    
    // +0x68: field cleared after magic
    uint32 field_0x68;
    
    // +0x6C, +0x6E: short fields
    uint16 field_0x6C;
    uint16 field_0x6E;

    EARSObject(int param);
};

EARSObject::EARSObject(int param)
{
    // Call base class constructor with the given parameter
    FUN_0046c590(param);

    // Set vtable and additional function pointers
    this->vtable = &PTR_FUN_00d80b7c;
    this->ptr_field_0x3C = &PTR_LAB_00d80b6c;
    this->ptr_field_0x48 = &PTR_LAB_00d80b68;

    // Write debug magic values
    this->magic1 = 0xbadbadba;
    this->magic2 = 0xbeefbeef;
    this->magic3 = 0xeac15a55;
    this->magic4 = 0x91100911;

    // Clear the short fields
    this->field_0x64 = 0;
    this->field_0x66 = 0;
    this->field_0x6C = 0;
    this->field_0x6E = 0;

    // Clear the debug magic values (they are temporary markers)
    this->magic4 = 0;
    this->magic3 = 0;
    this->magic2 = 0;
    this->magic1 = 0;

    // Clear remaining fields
    this->field_0x60 = 0;
    this->field_0x68 = 0;
}