// FUNC_NAME: EARSObject::constructor
// Function address: 0x0047ed30
// Role: Constructor for an EARS engine object. Calls a base constructor (FUN_0047ed60) and optionally performs additional initialization based on a flag byte.

class EARSObject {
public:
    // Constructor with allocation/initialization flag (bit 0 triggers extra setup)
    void __thiscall constructor(byte initFlags);
};

// Global pointer used for vtable or configuration data (offset 0x2d4 points to a vtable pointer)
extern void* g_GlobalData;

void EARSObject::constructor(byte initFlags) {
    // Call base class constructor (at 0x0047ed60)
    // This likely initializes base members and sets up the vtable
    FUN_0047ed60(); // Placeholder for base constructor

    // If the low bit is set, perform extra initialization (e.g., setting virtual method or allocation)
    if (initFlags & 1) {
        // Retrieve vtable pointer from global structure
        void** vtable = *(void***)((char*)g_GlobalData + 0x2d4); // global offset +0x2d4
        // Call virtual function at index 1 (offset 4) with 'this' and a zero argument
        void (*extraInit)(EARSObject*, int) = (void (*)(EARSObject*, int))vtable[1];
        extraInit(this, 0);
    }
    // Note: The original assembly returns this (param_1), but as a constructor, no return value is expected.
}