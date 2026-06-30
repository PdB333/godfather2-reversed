// FUNC_NAME: InputManager::InputManager
#include <windows.h>

// Forward declarations for internal functions
bool __fastcall SomethingAlreadyInitialized(void* ptr); // FUN_00402080
void __fastcall InitStaticInstance(void* ptr);          // FUN_00408310
void __fastcall ConstructSubObject(void* ptr);         // FUN_004086d0
void __fastcall FinalizeGlobalInit(void);              // FUN_0046c640

// Vtable pointers (global constants)
extern void* PTR_FUN_00e3334c;  // Primary vtable for InputManager
extern void* PTR_LAB_00e33368;  // Secondary vtable (interface 1) at offset +0x3C
extern void* PTR_LAB_00e33378;  // Secondary vtable (interface 2) at offset +0x48

// Static instances (global memory)
extern void DAT_0120eb00;       // Some global singleton
extern void DAT_0120eaf8;       // Another global singleton
extern void DAT_0120e970;       // Sub-resource for controllers
extern void DAT_0120e960;       // Optional sub-resource

class InputManager
{
public:
    // Constructor: __fastcall with 'this' in ecx
    void __fastcall InputManager()
    {
        // Set primary vtable pointer (always at offset 0)
        *(void**)this = &PTR_FUN_00e3334c;

        // Set secondary vtable pointers for multiple inheritance
        // Offset 0x3C (0xF * 4) - likely first interface
        *(void**)((char*)this + 0x3C) = &PTR_LAB_00e33368;
        // Offset 0x48 (0x12 * 4) - second interface
        *(void**)((char*)this + 0x48) = &PTR_LAB_00e33378;

        // Initialize/reinitialize global singletons (EARS engine static managers)
        InitStaticInstance(&DAT_0120eb00);
        InitStaticInstance(&DAT_0120eaf8);

        // Construct a global sub-resource (e.g., controller list)
        ConstructSubObject(&DAT_0120e970);

        // Check if an optional resource is already active; if so, tear it down
        if (SomethingAlreadyInitialized(&DAT_0120e960))
        {
            ConstructSubObject(&DAT_0120e960); // Deconstruct/reinitialize?
        }

        // Initialize internal sub-objects at offsets +0x50 and +0x58
        // These appear as pairs of construct/destruct or reinit calls
        // First sub-object at +0x50 (0x14 * 4)
        ConstructSubObject((char*)this + 0x50);
        InitStaticInstance((char*)this + 0x50);   // Secondary init for same region

        // Second sub-object at +0x58 (0x16 * 4)
        ConstructSubObject((char*)this + 0x58);
        InitStaticInstance((char*)this + 0x58);

        // Final global engine initialization (e.g., start input thread)
        FinalizeGlobalInit();
    }
};