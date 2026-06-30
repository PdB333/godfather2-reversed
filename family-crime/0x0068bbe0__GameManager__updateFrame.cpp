// FUNC_NAME: GameManager::updateFrame
#include <cstdint>

// Global state
extern uint32_t g_windowHandle;                 // DAT_012069c4
extern void* g_pWindowProc;                     // DAT_012233b4
extern bool g_bGamePaused;                      // DAT_01129948
extern bool g_bIdleTimerActive;                 // DAT_01129a90
extern bool g_bAudioEnabled;                    // DAT_01223380

// Forward declarations (callees)
void beginFrame();                              // FUN_0040cfc0
void endFrame();                                // FUN_0040ebb0
bool isDialogActive();                          // FUN_00842870
bool isApplicationFocused();                    // FUN_009caa70
bool shouldProcessFrame();                      // FUN_0067e230
uint32_t getFrameState();                       // FUN_006082c0
void resetIdleTimer();                          // FUN_0069dd40
void beginRenderScene(uint32_t renderFlags);    // FUN_0040e1f0
void presentScene();                            // FUN_009cb430
uint32_t getIdleTimerDuration();                // FUN_0069dce0
void updateAudioDrivers();                      // FUN_00486b10
void updateAudioStreams();                      // FUN_00486b50

void GameManager::updateFrame() {
    beginFrame();

    // Build a window message and dispatch to the window procedure
    struct WindowMessage {
        uint32_t hWnd;      // +0x00
        uint32_t msg;       // +0x04
        uint32_t wParam;    // +0x08
    } msg = { g_windowHandle, 0, 0 };

    if (g_pWindowProc != nullptr) {
        // Call window procedure vtable entry at offset 4 (likely WindowProc)
        (*(void(__thiscall*)(WindowMessage*))(*(uint32_t*)g_pWindowProc + 4))(&msg);
    }

    endFrame();

    // Determine if game is paused and dialog is active simultaneously
    bool bPausedAndDialog = false;
    bool bDialogActive = false;
    if (g_bGamePaused) {
        bDialogActive = isDialogActive(); // use result to set bPausedAndDialog
        if (bDialogActive) {
            bPausedAndDialog = true;
        }
    }
    // bPausedAndDialog = (g_bGamePaused != 0) && isDialogActive();

    // Check if the application window is in focus
    bool bWindowActive = isApplicationFocused(); // cVar2 originally

    // Check if we should process this frame at all
    if (!shouldProcessFrame()) {
        return;
    }

    uint32_t frameState = getFrameState();
    if (frameState & 0xFF) { // low byte non-zero indicates a render frame
        if (g_bIdleTimerActive) {
            resetIdleTimer();
            g_bIdleTimerActive = false;
        }

        // Extract upper 24 bits as render flags
        uint32_t renderFlags = (frameState >> 8) & 0xFFFFFF;

        if (bPausedAndDialog && !bWindowActive) {
            // Force render with low byte = 1 (e.g., forced present)
            beginRenderScene((renderFlags << 8) | 0x01);
        } else {
            // Normal render with low byte = 0
            beginRenderScene(renderFlags << 8);
        }
        presentScene();
        return;
    }
    else {
        // No render frame this tick – possibly idle
        if (!g_bIdleTimerActive) {
            g_bIdleTimerActive = getIdleTimerDuration();
        }
        if (g_bAudioEnabled) {
            updateAudioDrivers();
            updateAudioStreams();
        }
    }
}