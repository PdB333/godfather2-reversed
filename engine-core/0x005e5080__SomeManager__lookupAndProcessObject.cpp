// FUNC_NAME: SomeManager::lookupAndProcessObject
// 0x005e5080 - Finds an object by ID in an internal array and optionally processes it.
// The class has an object array at offset +0x6014 and count at +0x6018.
// Each object's first field is compared against the given ID.

typedef unsigned char byte;

// Global objects referenced
extern void* g_globalObject;  // DAT_01223510 (pointer to an object with vtable)
extern void* g_globalConfig;  // DAT_01223514 (passed to condition check)

// External functions
extern bool FUN_005f03c0(void* config);   // Returns true if processing is allowed
extern void FUN_005e6d20();               // Some cleanup / update
extern void FUN_009c8eb0(void* object);   // Finalize object

byte __thiscall SomeManager::lookupAndProcessObject(int objectId) {
    byte result = 0;
    uint32_t count = *(uint32_t*)((char*)this + 0x6018);
    
    if (count != 0) {
        void** objectArray = *(void***)((char*)this + 0x6014);
        uint32_t index = 0;
        
        while (true) {
            void* currentObject = objectArray[index];
            // Check if null or the first field matches objectId
            if (currentObject != nullptr && *(int*)currentObject == objectId) {
                break;
            }
            index++;
            if (index >= count) {
                return 0; // Not found
            }
        }
        
        // Found object at currentObject
        bool allowed = FUN_005f03c0(g_globalConfig);
        if (allowed) {
            // Virtual call on the global object's vtable at offset 0x14
            // This call takes the found object as argument and returns a byte
            byte (__thiscall* method)(void*) = (byte (__thiscall*)(void*))(*(int*)(*(int*)g_globalObject + 0x14));
            result = method(currentObject);
            FUN_005e6d20();
            FUN_009c8eb0(currentObject);
        }
    }
    return result;
}