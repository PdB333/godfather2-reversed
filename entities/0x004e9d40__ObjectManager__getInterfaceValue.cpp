// FUNC_NAME: ObjectManager::getInterfaceValue
// 0x004e9d40: Retrieves a value from an object by index using two virtual method calls.
// Uses global table at 0x012233a0 (ObjectTable) and sentinel/default value at 0x010c265c.

struct ObjectTable {
    uint32_t unknown0;    // +0x00: Possibly flags or pointer
    void** objects;       // +0x04: Pointer to array of object pointers
    uint32_t count;       // +0x0C: Number of entries in the array
};

// Global pointer to the object table
static ObjectTable* gObjectTable = (ObjectTable*)0x012233a0; // Assigned elsewhere
// Global sentinel/default result (initially -1 indicates "no current object")
static int gDefaultResult = *(int*)0x010c265c; // Initialized elsewhere

int ObjectManager::getInterfaceValue(int index) {
    int result = gDefaultResult;

    // Check if the sentinel is set, index is valid, and object exists
    if (gDefaultResult == -1 && index >= 0 && index < (int)gObjectTable->count) {
        void* obj = gObjectTable->objects[index];
        if (obj != nullptr) {
            // Call virtual method at vtable offset 0x0C (method index 3)
            // This method returns a pointer to an interface/sub-object.
            void* iface = (*(void* (__thiscall**)(void*))((*(uint32_t**)obj)[3]))(obj);
            if (iface != nullptr) {
                // Call virtual method at vtable offset 0x58 (method index 22)
                // This method returns the final integer value.
                result = (*(int (__thiscall**)(void*))((*(uint32_t**)iface)[22]))(iface);
            }
        }
    }
    return result;
}