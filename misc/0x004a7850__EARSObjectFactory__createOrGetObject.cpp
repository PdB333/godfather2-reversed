// FUNC_NAME: EARSObjectFactory::createOrGetObject
// Address: 0x004a7850
// Role: Creates a new object of a given type, or returns a singleton instance if type is null.
// The factory object has a vtable pointer at offset 0x08.
// Uses helper functions: getSingletonObject (0x00442e90), registerObject (0x004a63a0), getAllocator (0x004a72e0), allocateObject (0x004a7340).

// Helper function declarations (stubs with sensible names)
int getSingletonObject(void* factory);          // 0x00442e90 – returns a default singleton object if this factory has one
void registerObject(void* object);              // 0x004a63a0 – registers the object (refcount bump?)
void* getAllocator();                           // 0x004a72e0 – returns a global allocator
void* allocateObject(void* allocator, int typeId, void* typeObject); // 0x004a7340 – allocates memory for the object, returns pointer

int __thiscall EARSObjectFactory::createOrGetObject(void* thisPtr, void* typeObject) {
    int result = 0;

    // If this factory is valid, attempt to get a pre‑existing singleton object
    if (thisPtr != 0) {
        result = getSingletonObject(thisPtr);
        if (result != 0) {
            if (typeObject == 0) {
                // No type specified: return the singleton
                registerObject(result);
            } else {
                // Type specified: allocate a new object of that type
                void* allocator = getAllocator();
                if (allocator != 0) {
                    // vtable of typeObject at +0, second virtual function (offset 4) returns a type identifier
                    int typeId = (*(int (__thiscall **)(void*))(*(int**)typeObject + 4))(typeObject);
                    int newObj = allocateObject(allocator, typeId, typeObject); // allocateObject returns 0 on failure
                    if (newObj != 0) {
                        registerObject(newObj);
                        result = newObj;
                    }
                }
            }
        }
    }
    return result;
}