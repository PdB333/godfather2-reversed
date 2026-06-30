// FUNC_NAME: EventSystem::registerDialogHandler
// Function address: 0x004BB390
// Role: Wrapper that registers a specific event handler (LAB_004BB340) by forwarding to the generic event registration function.
// Note: `this` pointer is not used; the method is __thiscall but acts as a static delegate.

#include <cstdint>

// Forward declaration of the generic event registration function.
// Takes four parameters plus a handler pointer; implementation at 0x004BB190.
extern void setEventHandler(int param1, int param2, int param3, int param4, void* handler);

// The handler this function registers.
static constexpr void* kDialogHandler = reinterpret_cast<void*>(0x004BB340);

// Registers the dialog handler for a given event context.
// param1: Event source or object ID
// param2: Event type or category
// param3: Additional data (e.g., user context)
// param4: Flags or time stamp
void __thiscall EventSystem::registerDialogHandler(void* this, int param1, int param2, int param3, int param4)
{
    // Delegate to the generic registration function with the specific handler address.
    setEventHandler(param1, param2, param3, param4, kDialogHandler);
}