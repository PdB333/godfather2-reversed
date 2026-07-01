// FUNC_NAME: CSomeManager::CSomeManager
// Constructor for an unknown EA EARS engine manager class.
// Sets up vtable, two function pointers at offsets 0x10 and 0x4C, 
// clears a global flag, and calls a base initializer.

class CSomeManager {
public:
    // Virtual function table pointer (offset 0x00)
    void *vfptr;

    // Unknown data members at offsets 0x04-0x0C (not used here)
    // Member at offset 0x10 (param_1[4])
    void *pfnUnknown1;

    // Member at offset 0x4C (param_1[0x13])
    void *pfnUnknown2; // Note: Ghidra shows two assignments to this offset; the second overwrites the first.
    // First assignment: &PTR_LAB_00d8d954, then overwritten by &PTR_LAB_00d8d950.
    // This might indicate a union, or a bug in the decompilation.

    // Constructor
    void __fastcall CSomeManager(CSomeManager *this);
};

// Static global variable (addr 0x01130898)
static int g_someFlag = 0;

// External function called (addr 0x005c16e0, likely base class constructor or init)
extern void __fastcall SomeBaseInit(void *this);

// Constructor implementation
void __fastcall CSomeManager::CSomeManager(CSomeManager *this) {
    // Set vtable pointer
    this->vfptr = (void*)&PTR_FUN_00d8d980;  // Vtable for CSomeManager

    // Set function pointer at offset 0x10
    this->pfnUnknown1 = (void*)&PTR_LAB_00d8d958;   // Possibly an event handler or dispatch table

    // Set function pointer at offset 0x4C (overwritten later, see note)
    this->pfnUnknown2 = (void*)&PTR_LAB_00d8d954;   // First assignment (overwritten)
    this->pfnUnknown2 = (void*)&PTR_LAB_00d8d950;   // Overwrites previous, final value

    // Clear global flag
    g_someFlag = 0;

    // Call base initializer
    SomeBaseInit(this);
}