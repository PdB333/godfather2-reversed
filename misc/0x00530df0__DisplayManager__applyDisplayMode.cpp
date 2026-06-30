// FUNC_NAME: DisplayManager::applyDisplayMode
void DisplayManager::applyDisplayMode()
{
    // Store the current mode index (unaff_ESI is likely a global or register holding the mode index)
    s_currentModeIndex = g_modeIndex;

    // Check if the display manager singleton is initialized
    if (s_displayManagerSingleton == &s_displayManagerInstance)
    {
        // Compare current mode state against various known states
        if (s_currentModeState == s_stateNormal)
        {
            int modeParam = s_modeParamA;
            if (s_flagSomething != 0)
            {
                // Recalculate something (e.g., refresh rate or scaling)
                recalculateDisplaySettings();
                modeParam = s_modeParamA;
            }
        }
        else
        {
            if (s_currentModeState == s_stateWide)
            {
                setDisplayMode(s_currentModeState, s_wideParamA);
                return;
            }
            if (s_currentModeState == s_stateFullscreen)
            {
                setDisplayMode(s_currentModeState, s_fullscreenParamA);
                return;
            }
            if (s_currentModeState == s_stateWindowed)
            {
                setDisplayMode(s_currentModeState, s_windowedParamA);
                modeParam = s_modeParamB;
            }
            else
            {
                if (s_currentModeState == s_stateBorderless)
                {
                    setDisplayMode(s_currentModeState, s_borderlessParamA);
                    return;
                }
                if (s_currentModeState != s_stateCustom)
                {
                    return;
                }
                setDisplayMode(s_currentModeState, s_customParamA);
                modeParam = s_customParamB;
            }
        }

        if (modeParam != 0)
        {
            // Prepare scaling factors
            float scaleX = 0.0f;
            float scaleY = 0.0f;
            float aspectX = 0.0f;
            float aspectY = 0.0f;

            // Determine if we need to get current resolution from the mode table
            if ((s_currentModeState == s_stateNormal && s_modeParamA != 0) ||
                (s_currentModeState == s_stateWindowed && s_modeParamB != 0))
            {
                getResolutionFromMode(s_currentModeState, modeParam, &scaleX);
            }

            // Access the mode table (array of 0x38-byte entries, max 4096)
            uint8_t* modeEntry;
            if (g_modeIndex < 0x1000)
            {
                modeEntry = &s_modeTable[g_modeIndex * 0x38];
            }
            else
            {
                modeEntry = nullptr;
            }

            // Compute horizontal scale: baseWidth / modeEntry->width
            scaleX = s_baseWidth / (float)*(uint16_t*)(modeEntry + 2);
            // Compute vertical scale: baseWidth / modeEntry->height
            scaleY = s_baseWidth / (float)*(uint16_t*)(modeEntry + 4);

            // Apply aspect ratio correction
            aspectX = scaleX * s_aspectRatio;
            aspectY = scaleY * s_aspectRatio;

            // Apply the computed scaling to the current mode
            applyScaling(s_currentModeState, modeParam, &scaleX);
        }
    }
}