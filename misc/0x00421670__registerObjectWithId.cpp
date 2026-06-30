// FUNC_NAME: registerObjectWithId
// Address: 0x00421670
// Role: Registers an object (param_2) with a unique ID (param_1) in a fixed-size global table.
//       Then calls the third virtual method (vtable offset +8) on the object.
//       The table holds up to 16 entries (id+ptr pairs). Duplicate IDs are ignored.

// Global state (from Ghidra data)
static const int MAX_REGISTRATIONS = 16;
static int g_registeredCount = 0;                               // DAT_01206ba0
static int g_registeredIds[MAX_REGISTRATIONS];                  // DAT_01206b20 (each id at offset i*8)
static void* g_registeredObjects[MAX_REGISTRATIONS];            // DAT_01206b24 (each ptr at offset i*8+4)

// Internal structure of the expected object (must have a vtable)
struct RegisterableObject {
    virtual void function0();  // vtable slot 0
    virtual void function1();  // vtable slot 1
    virtual void function2();  // vtable slot 2 -> called here (offset +8)
};

void __cdecl registerObjectWithId(int objectId, RegisterableObject* obj) {
    uint index = 0;
    if (g_registeredCount != 0) {
        do {
            // Check if this ID is already registered
            if (g_registeredIds[index] == objectId) {
                return; // Already registered, do nothing
            }
            index++;
        } while (index < g_registeredCount);
    }

    if (g_registeredCount < MAX_REGISTRATIONS) {
        // Store ID and pointer in the next available slot
        g_registeredIds[g_registeredCount] = objectId;
        g_registeredObjects[g_registeredCount] = obj;
        g_registeredCount++;
    }

    // Call the third virtual method on the object (vtable offset +8)
    // Equivalent: obj->function2();
    // In assembly: (**(code**)(*obj + 8))();
    obj->function2();
}