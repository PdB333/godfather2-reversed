// FUNC_NAME: Application::updateFrame

#include <cstdint>

// Global singleton pointers
extern void* g_pApp;                // DAT_01223510 - pointer to Application object
extern void* g_pAudioManager;       // DAT_012234bc - pointer to audio manager
extern void* g_pTimer;              // DAT_01223508 - pointer to timer/system clock

// Forward declarations of subroutines
extern void processInputEvents();                    // FUN_005e1ee0
extern void updateAudioManager(void* audioMgr);     // FUN_005e4d30
extern void updateScene();                          // FUN_005e43d0
extern uint32_t getTimerValue(void* timer);         // FUN_005dc2f0

// Virtual function offsets in Application vtable
const uint32_t kPreUpdateVFuncOffset  = 0xb8;   // called at start of frame
const uint32_t kPostUpdateVFuncOffset = 0xc4;   // called at end of frame

uint32_t updateFrame()
{
    // Call virtual pre-update (offset 0xb8)
    // Dereference global pointer to get vtable, then call function at offset
    (*(void (*)())(*(uint32_t*)g_pApp + kPreUpdateVFuncOffset))();

    // Call virtual post-update (offset 0xc4)
    (*(void (*)())(*(uint32_t*)g_pApp + kPostUpdateVFuncOffset))();

    // Update input processing
    processInputEvents();

    // Update audio system
    updateAudioManager(g_pAudioManager);

    // Update game scene / simulation
    updateScene();

    // Fetch timer value and mask out lower bits (keep only bit 0)
    uint32_t timerValue = getTimerValue(g_pTimer);
    return timerValue & 0xffffff01;
}