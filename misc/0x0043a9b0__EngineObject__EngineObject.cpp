// FUNC_NAME: EngineObject::EngineObject
// Function: 0x0043a9b0 - Constructor for EngineObject (EARS engine base class)
// Calls a base initializer (FUN_0043b400) and conditionally invokes a virtual function
// if the flag's bit 0 is set, typically used for post-construction setup.

#include <cstdint>

// External base initializer (likely sets up core members)
extern void initializeBase(); // FUN_0043b400

// Global descriptor used to retrieve vtable pointer.
// The descriptor is a structure at address DAT_01223410.
// Offset +0x2d4 holds a pointer to the object's vtable pointer.
extern void* g_classDescriptor; // DAT_01223410

class EngineObject {
public:
    // Constructor: flag is a bitfield controlling additional initialization.
    EngineObject(uint8_t flags) {
        initializeBase();

        // If bit 0 is set, call virtual function at vtable index 1.
        if (flags & 1) {
            // Fetch vtable pointer from the class descriptor.
            // The descriptor at offset 0x2d4 contains a pointer to the vtable pointer.
            void** ppVtable = *reinterpret_cast<void***>(
                static_cast<uint8_t*>(g_classDescriptor) + 0x2d4
            );
            // vtable[1] (offset 4) is the function pointer.
            using InitFunc = void (__thiscall*)(EngineObject*, int);
            InitFunc initFunc = reinterpret_cast<InitFunc>(ppVtable[1]);
            // Call the initialization function with argument 0.
            initFunc(this, 0);
        }
    }
};