// FUNC_NAME: UnknownManager::constructor
// Function address: 0x0066cf70
// Reconstructed from Ghidra decompilation. This appears to be a constructor/initializer for a manager class.
// Sets vtable pointers, stores a parent/owner pointer, registers with a global singleton, and calls an initialization callback.

// Assumed class definition (offsets based on index * 4)
class UnknownManager {
public:
    // +0x00: vtable pointer (first)
    // +0x04: some flag
    // +0x08: second vtable pointer (overwritten)
    // +0x0C: pointer to owner/configuration object
    // +0x10: some field set to 0
};

// Global singleton pointer
extern UnknownManager* g_pManager;

// External function: registers this object with some system
void RegisterObject(int* dataObject, int param);

void __thiscall UnknownManager::constructor(UnknownManager* this, int* ownerObject) {
    // Initialize fields
    this->field_0x04 = 0;                                   // +0x04 = 0
    this->secondaryVtable = &PTR_LAB_00e4449c;              // +0x08: first assignment (overwritten later)
    this->vtable = &PTR_FUN_00e4448c;                       // +0x00: main vtable
    this->secondaryVtable = &PTR_LAB_00e44498;              // +0x08: final secondary vtable
    this->pOwner = ownerObject;                             // +0x0C: store owner
    g_pManager = this;                                      // Set global singleton

    // Call a virtual function on the owner object (offset 8 in its vtable)
    // This is likely an initialization notification
    (*(void (**)(void))(*ownerObject + 8))();

    this->field_0x10 = 0;                                   // +0x10 = 0

    // Register this object (or some data) with a system
    RegisterObject(&DAT_00e44488, 1);
}