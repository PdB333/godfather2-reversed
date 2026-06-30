// FUNC_NAME: UnknownClass::constructor (at 0x006b84b0)
// Constructor for an unknown class with size 0x68. Initializes multiple vtable pointers and a subobject at offset 0x14.
// The vtable pointers are set at offsets 0x00, 0x3C, and 0x48.
// param_2 flags: bit 0 indicates if the object was heap-allocated; if set, a failure will call delete.

extern const void* PTR_FUN_00d5e5b8;  // primary vtable
extern const void* PTR_LAB_00d5e5a8; // secondary vtable (+0x3C)
extern const void* PTR_LAB_00d5e5a4; // third vtable (+0x48)

// Forward declarations for internal initializers
void __thiscall initSubObjectA(unknownType* subObj);
void __thiscall initSubObjectB(unknownType* subObj);
void globalEngineInit(); // FUN_0046c640
void __cdecl operatorDelete(void* ptr, unsigned int size); // FUN_0043b960, with size parameter

// Return type is pointer to this (probably the constructed object)
undefined4* __thiscall unknownClassConstructor(undefined4* this, byte flags)
{
    // Set primary vtable at offset 0
    *this = &PTR_FUN_00d5e5b8;
    
    // Set secondary vtable at offset 0x0F * 4 = 0x3C
    this[0x0F] = &PTR_LAB_00d5e5a8;
    
    // Set third vtable at offset 0x12 * 4 = 0x48
    this[0x12] = &PTR_LAB_00d5e5a4;

    // Initialize subobject at offset 0x14 (size unknown, likely another class instance)
    // FUN_004086d0 and FUN_00408310 are probably constructors/initializers for that subobject
    initSubObjectA((unknownType*)((char*)this + 0x14));
    initSubObjectB((unknownType*)((char*)this + 0x14));

    // Perform global engine initialization (likely increments reference count, etc.)
    globalEngineInit();

    // If the object was dynamically allocated (flags bit 0 set), and construction fails here,
    // immediately delete the object with the known size (0x68).
    // This pattern is typical in EA allocators: the constructor takes a flag indicating whether
    // to self-destruct on failure.
    if (flags & 1)
    {
        operatorDelete(this, 0x68);
    }

    return this;
}