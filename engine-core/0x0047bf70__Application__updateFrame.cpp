// FUNC_NAME: Application::updateFrame
// Address: 0x0047bf70
// Role: Main per-frame update for the game application.
// Calls into a global singleton (DAT_012069d4) for some subsystem processing,
// then invokes two virtual methods on the main application object (DAT_01223510).

#include <cstdint>

// These are external global instances, likely defined elsewhere.
extern SomeSubsystem g_subsystem; // DAT_012069d4
extern Application* g_app; // *DAT_01223510 (pointer stored at that address)

// Forward declarations of external helper functions.
bool IsSubsystemActive(SomeSubsystem*); // FUN_00402080
void ProcessSubsystem(SomeSubsystem*);  // FUN_004086d0

uint32_t Application::updateFrame()
{
    // If the subsystem is active, process it.
    char isActive = IsSubsystemActive(&g_subsystem);
    if (isActive != 0) {
        ProcessSubsystem(&g_subsystem);
    }

    // Call virtual methods through the application object's vtable.
    // +0xb8 likely corresponds to 'preUpdate' or 'updateGameLogic'
    // +0xc4 likely corresponds to 'postUpdate' or 'render'
    (*(void (**)())(*(uint32_t*)g_app + 0xb8))();
    (*(void (**)())(*(uint32_t*)g_app + 0xc4))();

    return 1; // Indicate frame completed successfully.
}