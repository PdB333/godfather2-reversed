// FUNC_NAME: BasicObject::constructor
// Reconstructed constructor at 0x0043df70 for a basic game object.
// Sets vtable, initializes name string to "unknown", clears some fields,
// and calls an initialization function with a parent object.

class BasicObject {
public:
    // Vtable pointer at +0x00
    void* vtable;
    // Name string at +0x04 (char*)
    char* name;
    // Unknown byte at +0x0C
    char field_0C;
    // Padding / alignment
    char pad_0D[3];
    // Some integer at +0x10 (not set here)
    // ...
    // Unknown integer at +0x1C (offset 7)
    int field_1C;
    // Unknown integer at +0x20 (offset 8)
    int field_20;
    // More fields...

    BasicObject(void* parentObject) {
        // Set vtable pointer (externally defined)
        vtable = (void*)&PTR_FUN_00da9810; // +0x00

        // Set initial name to "unknown"
        name = "unknown"; // +0x04

        // Clear some fields
        field_1C = 0;     // +0x1C
        field_20 = 0xF;   // +0x20

        // Zero a byte at offset 0x0C (this + 3 as int* -> cast to byte)
        field_0C = 0;     // +0x0C

        // Call initialization routine with parent, a zero flag, and -1
        // Likely initializes or clears a list/container.
        FUN_0043eeb0(parentObject, 0, -1); // Unknown function
    }
};