// FUNC_NAME: initializeGlobalSingleton

// Address: 0x00491fd0
// Role: Initializes a global singleton object and returns a pointer to it.
// Calls FUN_00491c40 (presumed to be the constructor) then sets the vtable pointer
// in the global structure and returns its address.

#include <stdint.h>

// Forward declaration of the singleton structure.
struct GlobalSingleton;

// Extern globals - likely defined elsewhere.
extern uint32_t *PTR_LAB_00e34790; // +0x0: vtable pointer or similar
extern GlobalSingleton *g_pGlobalInstance; // Actually DAT_01216ce0, but we make it a pointer

// Function prototype for the constructor/initializer called first.
void __cdecl globalSingletonConstructor(void); // FUN_00491c40

// The global singleton instance structure.
// Its first member is a pointer to the vtable (or some function table).
struct GlobalSingleton {
    void **vtable; // +0x0: pointer to virtual method table
    // ... other members follow
};

// Global instance storage (the actual global object, not a pointer).
// In assembly, DAT_01216ce0 is the address of the object itself.
extern GlobalSingleton g_globalSingleton; // Actually DAT_01216ce0

// The exported function.
GlobalSingleton * initializeGlobalSingleton(void)
{
    // Call the low-level constructor which sets up non-vtable members.
    globalSingletonConstructor();

    // Set the vtable pointer to the predefined table.
    g_globalSingleton.vtable = (void **)PTR_LAB_00e34790;

    // Return the address of the global singleton.
    return &g_globalSingleton;
}