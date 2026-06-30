// FUNC_NAME: EARS::Framework::Engine::frameUpdate
void Engine::frameUpdate(void)
{
    LARGE_INTEGER perfCounter1, perfCounter2;
    float frameTime = 0.0f;
    int i;

    // Phase 1: Begin profiling and execute first subsystem update (e.g., animation/physics)
    QueryPerformanceCounter(&perfCounter1);
    FUN_0060c2e0(); // Likely subsystem update (e.g., physics or animation)
    QueryPerformanceCounter(&perfCounter2);
    frameTime = 1.0f - (float)((__int64)((perfCounter2.QuadPart - perfCounter1.QuadPart) & 0x7FFFFFFFFFFFFFFFLL) * _DAT_01163ecc);

    // Phase 2: Second subsystem update (e.g., input or AI)
    QueryPerformanceCounter(&perfCounter1);
    FUN_0060b8b0(); // Likely input or AI update
    QueryPerformanceCounter(&perfCounter2);
    frameTime -= (float)((__int64)((perfCounter2.QuadPart - perfCounter1.QuadPart) & 0x7FFFFFFFFFFFFFFFLL) * _DAT_01163ecc);

    // Phase 3: Third subsystem update (e.g., audio or networking)
    QueryPerformanceCounter(&perfCounter1);
    FUN_0060bbd0(); // Likely audio or networking update
    QueryPerformanceCounter(&perfCounter2);
    frameTime -= (float)((__int64)((perfCounter2.QuadPart - perfCounter1.QuadPart) & 0x7FFFFFFFFFFFFFFFLL) * _DAT_01163ecc);

    // Phase 4: Fourth subsystem update (e.g., rendering or UI)
    FUN_0060c5e0(); // Likely rendering or UI update

    // Main engine update (virtual call at vtable+0xa4)
    g_pEngineManager->update(); // vtable[41]

    // Reset frame timer
    frameTime = 0.0f;

    // Signal that frame is active
    g_bEngineFrameActive = 1; // DAT_01205758

    // Pre-controller update and reset
    g_pEngineManager->preControllerUpdate(); // vtable[108] (+0x1b0)
    g_pEngineManager->processControllerResets(); // vtable[107] (+0x1ac)

    // Handle pending destruction (if any)
    if (g_pPendingDestroy) {
        g_pPendingDestroy->destruct(); // vtable[2] (+8)
    }

    // Pre- and post-frame hooks
    g_pEngineManager->preFrame(); // vtable[93] (+0x174)
    g_pEngineManager->postFrame(); // vtable[92] (+0x170)

    // Delete engine manager if marked? (seems odd for update; may be shutdown)
    // Actually, this delete might happen in cleanup, not here.

    // Process all 16 controller slots (loop 1)
    for (i = 0; i < 16; i++) {
        IController* pController = nullptr;
        g_pEngineManager->getController(i, &pController); // vtable[64] (+0x100)
        g_pEngineManager->releaseController(i);         // vtable[65] (+0x104)
        if (pController) {
            pController->destruct(); // vtable[2]
        }
    }

    // Clear input device state
    g_pEngineManager->clearInputDeviceState(&pInputClear); // vtable[105] (+0x1a4)
    g_pEngineManager->enableControllerInput(0);            // vtable[104] (+0x1a0)

    // Process all 16 controller slots (loop 2) – alternative method
    for (i = 0; i < 16; i++) {
        IController* pControllerA = nullptr;
        IController* pControllerB = nullptr;
        IController* pControllerC = nullptr;
        g_pEngineManager->getControllerState(i, &pControllerC, &pControllerA, &pControllerB); // vtable[101] (+0x194)
        g_pEngineManager->setControllerState(i, 0, 0, 0); // vtable[100] (+0x190)
        if (pControllerC) {
            pControllerC->destruct(); // vtable[2]
        }
    }

    // Clear various global memory buffers
    memset(&g_inputPadStates, -1, 0xF0);    // DAT_011f7450
    g_iLastInputTime = 0;                   // DAT_01205830
    g_iLastInputTime2 = 0;                  // DAT_01205834
    g_iLastInputTime3 = 0;                  // DAT_01205838
    g_iLastInputTime4 = 0;                  // DAT_0120583c
    memset(&g_audioBuffer, -1, 0x100);      // DAT_011da7f0
    memset(&g_audioBuffer2, -1, 0x1000);    // DAT_011d97f0
    memset(&g_audioBuffer3, -1, 0x1000);    // DAT_011ea8f0

    // Final subsystem update
    FUN_0060dcb0(); // e.g., network flush or frame end
}