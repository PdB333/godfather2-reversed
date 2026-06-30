// FUNC_NAME: Framework::update
void Framework::update(void)
{
    bool bVar1;
    char isMenuActive;
    char isApplicationActive;
    uint32_t frameTime;
    uint24_t timeHighBits;

    // Begin frame processing
    beginFrame();

    // Prepare input update context
    InputUpdateContext inputCtx;
    inputCtx.field0 = g_inputFlags;   // +0x00
    inputCtx.field4 = 0;              // +0x04
    inputCtx.field8 = 0;              // +0x08

    // Update input manager if available
    if (g_inputManager != (InputManager*)0x0) {
        g_inputManager->vtable->update(&inputCtx);  // offset +4 in vtable
    }

    endFrame();

    // Determine if we are in a state that allows sleeping
    if ((g_isGamePaused == 0) || (isMenuActive = isMenuActiveCheck(), isMenuActive == '\0')) {
        bVar1 = false;
    } else {
        bVar1 = true;
    }

    isMenuActive = isInactiveFrame();   // cVar2: 0 = active frame, non-zero = inactive
    isApplicationActive = isAppActive(); // cVar3

    if (isApplicationActive != '\0') {
        frameTime = getLastFrameTime();  // returns some timing value (32-bit)

        if ((char)frameTime != '\0') {
            // Active frame processing
            if (g_inactiveTimer != '\0') {
                resetInactiveTimer();
                g_inactiveTimer = '\0';
            }

            timeHighBits = (uint24_t)(frameTime >> 8);  // extract upper 24 bits

            if ((bVar1) && (isMenuActive == '\0')) {
                // Allow sleeping with a small extra time
                sleepMs( ( (uint32_t)timeHighBits << 8 ) | 1 );
                presentFrame();
                return;
            }

            sleepMs((uint32_t)timeHighBits << 8);
            presentFrame();
            return;
        }

        // Inactive frame: set timer if not already
        if (g_inactiveTimer == '\0') {
            g_inactiveTimer = getCurrentTimeRate();
        }

        if (g_rendererActive != 0) {
            processInactive();
            yieldToOS();
        }
    }
    return;
}