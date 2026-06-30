// FUNC_NAME: ExecuteComponentActionCallback
// Function at 0x005bb580: checks if game is active, gets an object, and calls a global callback with a component pointer and an argument.
// Offsets: +0x50 = pointer to component object, +0x54 = argument (likely index or ID)
// Globals: DAT_0119cbbc (return value), DAT_0119cb4c (callback function pointer)

#include <cstdint>

typedef void (*ActionCallback)(void* component, uint32_t arg);

// Forward declarations of callees (likely in same translation unit)
extern bool IsGameActive();                // FUN_005a8030
extern int32_t GetCurrentObjectInstance(); // FUN_005a78b0

extern int32_t DAT_0119cbbc;   // Return value global
extern ActionCallback DAT_0119cb4c; // Function pointer global

int32_t ExecuteComponentActionCallback(void)
{
    bool active = IsGameActive();
    if (active)
    {
        int32_t obj = GetCurrentObjectInstance();
        // Check if component pointer at obj+0x50 is non-null
        void* component = *(void**)(obj + 0x50);
        if (component != nullptr)
        {
            uint32_t arg = *(uint32_t*)(obj + 0x54);
            DAT_0119cb4c(component, arg);
        }
    }
    return DAT_0119cbbc;
}