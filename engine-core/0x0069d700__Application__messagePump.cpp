// FUNC_NAME: Application::messagePump
uint8_t Application::messagePump()
{
    tagMSG msg;
    uint8_t bQuit = 1; // Assume continue

    // Peek and dispatch Windows messages
    while (PeekMessageW(&msg, nullptr, 0, 0, 3) != 0)
    {
        if (msg.message == WM_QUIT)
        {
            bQuit = 0;
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

    // Perform game frame update (tick)
    performFrameTick();

    // Determine if application should be considered active (for audio)
    bool bActive = true;
    if (g_bUseFocusForAudio == 0 || IsIconic(g_hMainWindow) != 0)
    {
        // Mute condition: either the flag forces mute, or window is minimized
        bActive = false;
    }
    else
    {
        bActive = true;
    }

    // Update audio volume based on active state
    if (bActive != g_bPrevActiveState)
    {
        float volume = bActive ? 1.0f : 0.0f;
        setAudioVolume(volume);
        g_bPrevActiveState = bActive;
    }

    return bQuit;
}