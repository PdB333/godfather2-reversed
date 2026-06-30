// FUNC_NAME: EARSObject::~EARSObject
// Address: 0x00728a10
// Destructor for an EARS engine object (size 0xA4 bytes).
// Sets vtable pointers for base classes at offsets 0x3C and 0x48,
// then destroys sub-objects if present, then optionally frees memory.

class EARSObject {
public:
    // Offset 0x00: vtable pointer (base vtable)
    // Offset 0x3C: vtable pointer (first base class at offset 0xF * 4)
    // Offset 0x48: vtable pointer (second base class at offset 0x12 * 4)
    // Offset 0x5E: byte flags (bit 0 indicates subobject at +0x50 is valid)
    // Offset 0x50: pointer to a separately allocated sub-object (void*)
    // Offset 0x9C: embedded sub-object (some class with its own destructor)

    // NOTE: The destructor receives a boolean parameter (from calling convention)
    // indicating whether to also free the object's memory (via operator delete).
    void __thiscall destroy(bool deleteMemory);
};

// External helper functions (from other translation units)
extern void FUN_00729980(void* ptr);   // releases sub-object at +0x50
extern void FUN_004daf90(void* obj);  // destructs embedded sub-object at +0x9C
extern void FUN_0046c640(void);        // static cleanup routine
extern void FUN_0043b960(void* ptr, unsigned int size); // operator delete

void EARSObject::destroy(bool deleteMemory) {
    // Set vtable pointers to base classes (destruction order)
    *(void**)this = &PTR_FUN_00d62498;                   // base vtable
    *(void**)((int*)this + 0xF) = &PTR_LAB_00d62488;     // +0x3C
    *(void**)((int*)this + 0x12) = &PTR_LAB_00d62484;    // +0x48

    // Release sub-object if flag indicates it exists
    if ((*(uint8_t*)((int)this + 0x5E) & 1) != 0) {
        FUN_00729980(((int*)this)[0x14]);                // pointer at +0x50
    }

    // Destroy embedded sub-object if it is non-null
    if (((int*)this)[0x27] != 0) {                       // offset 0x9C
        FUN_004daf90((int*)this + 0x27);                 // address of sub-object
    }

    // Perform class-common cleanup
    FUN_0046c640();

    // Optionally free the object's memory (if requested)
    if (deleteMemory) {
        FUN_0043b960(this, 0xA4);
    }
}