// FUNC_NAME: WeatherSystem::applyWeatherTransition
void WeatherSystem::applyWeatherTransition()
{
    // Check if any weather sets are active and time conditions are met for transitioning
    bool weatherAisActive = (g_weatherAWeight != 0.0f && g_currentTime <= g_weatherATargetTime);
    bool weatherBisActive = (g_weatherBWeight != 0.0f && g_currentTime <= g_weatherBTargetTime);
    bool weatherCisActive = (g_weatherCWeight != 0.0f && g_currentTime <= g_weatherCTargetTime);

    // Also check if the current weather zone index is valid and the zone type > 2
    if ((weatherAisActive || weatherBisActive || weatherCisActive) &&
        (g_currentZoneIndex < 0x1000 &&
         (g_weatherZones[g_currentZoneIndex].type > 2)))
    {
        // Initiate weather zone transition
        if (g_currentZoneIndex == g_targetZoneIndex && g_weatherTransitionFlag == 0)
        {
            // Transition to the same zone? start immediate effect
            startWeatherTransition(1);
        }
        else
        {
            // Change from current zone to target zone
            changeWeatherZone(g_currentZoneIndex, g_targetZoneIndex);
        }

        // Apply initial post-process adjustments (likely brightness/contrast)
        clampBrightnessAndContrast(0x16, 0x16);
        setEffectFlag(effectFlag1, 1);
        clampBrightnessAndContrast(7, 7);
        setEffectFlag(effectFlag2, 0);
        clampBrightnessAndContrast(0x19, 0x19);
        setEffectFlag(effectFlag3, 5);
        clampBrightnessAndContrast(0x18, 0x18);
        setEffectFlag(effectFlag4, 0);
        clampBrightnessAndContrast(0xf, 0xf);
        setEffectFlag(effectFlag5, 0);
        clampBrightnessAndContrast(0x1b, 0x1b);
        setEffectFlag(effectFlag6, 1);

        // Set color grading LUT (first LUT: indices 1,2,1)
        setColorGradingLUT(1, 2, 1);

        // Store old fog handles and reset related state
        g_fogColorHandle = g_currentFogColorHandle;
        g_fogParamsHandle = 0;
        g_fogDepthTextureHandle = g_currentFogHandle;

        // If the current fog handle matches a saved set, get shader constant handles
        if ((g_currentFogHandle == g_fogHandle1) ||
            (g_currentFogHandle == g_fogHandle2) ||
            (g_currentFogHandle == g_fogHandle3))
        {
            g_shaderFogColor = getShaderConstant(g_currentFogHandle, "fog_color");
            g_shaderFogParams = getShaderConstant(g_fogDepthTextureHandle, "fog_params");
            g_shaderDepthTexture = getShaderConstant(g_fogDepthTextureHandle, "depth_texture");
        }

        // If a specific effect pointer matches a known structure, release old shader constants
        if (g_someEffectPointer == &g_effectStructure)
        {
            releaseShaderConstant(g_fogDepthTextureHandle);
            releaseShaderConstant(g_fogColorHandle);
        }

        // Update weather set A interpolation
        updateWeatherAInterpolation();
        if (weatherAisActive && g_weatherAHold != g_weatherTargetHold)
        {
            float scaleFactor = g_targetDuration / g_weatherAWeight;
            g_weatherAParams.r = scaleFactor * g_weatherAParams.r;
            g_weatherAParams.g = scaleFactor * g_weatherAParams.g;
            g_weatherAParams.b = scaleFactor * g_weatherAParams.b;
            g_weatherAParams.time = scaleFactor * g_weatherAParams.time;
            g_weatherAParams.reserved1 = g_weatherAParams.reserved1 * scaleFactor;
            g_weatherAParams.reserved2 = g_weatherAParams.reserved2 * scaleFactor;
        }

        // Update weather set B interpolation
        updateWeatherBInterpolation();
        if (weatherBisActive && g_weatherBHold != g_weatherTargetHold)
        {
            float scaleFactor = g_targetDuration / g_weatherBWeight;
            g_weatherBParams.r = scaleFactor * g_weatherBParams.r;
            g_weatherBParams.g = scaleFactor * g_weatherBParams.g;
            g_weatherBParams.b = scaleFactor * g_weatherBParams.b;
            g_weatherBParams.time = scaleFactor * g_weatherBParams.time;
            g_weatherBParams.reserved1 = g_weatherBParams.reserved1 * scaleFactor;
            g_weatherBParams.reserved2 = g_weatherBParams.reserved2 * scaleFactor;
        }

        // Update remaining weather components
        updateWeatherCInterpolation();
        updateWeatherDInterpolation();
        updateFogAndEffects();

        // Allocate and fill shader parameter block
        float* shaderParams = (float*)allocateShaderParameters(5, 4, 0, 1, 0);
        float paramValue1 = g_constantParam1;
        float paramValue2 = g_constantParam2;
        float paramValue3 = g_targetDuration;
        if (shaderParams != nullptr)
        {
            shaderParams[0] = paramValue1;
            shaderParams[1] = paramValue2;
            shaderParams[2] = paramValue3;
            shaderParams[3] = paramValue1;
            shaderParams[4] = paramValue1;
            shaderParams[5] = paramValue3;
            shaderParams[6] = paramValue3;
            shaderParams[7] = paramValue3;
            submitShaderParameters();
        }

        // Update post-process state
        updatePostProcessState();

        // Apply second set of post-process adjustments (different LUT)
        clampBrightnessAndContrast(0x16, 0x16);
        setEffectFlag(effectFlag1, 1);
        clampBrightnessAndContrast(7, 7);
        setEffectFlag(effectFlag2, 1);
        clampBrightnessAndContrast(0x19, 0x19);
        setEffectFlag(effectFlag3, 7);
        clampBrightnessAndContrast(0x18, 0x18);
        setEffectFlag(effectFlag4, 0);
        clampBrightnessAndContrast(0xf, 0xf);
        setEffectFlag(effectFlag5, 0);
        clampBrightnessAndContrast(0x1b, 0x1b);
        setEffectFlag(effectFlag6, 0);

        // Switch color grading LUT to indices (1,5,6)
        setColorGradingLUT(1, 5, 6);

        // Zero out all weather parameter sets to end the transition
        g_weatherAParams.r = 0.0f;
        g_weatherAParams.g = 0.0f;
        g_weatherAParams.b = 0.0f;
        g_weatherAParams.time = 0.0f;
        g_weatherAParams.reserved1 = 0.0f;
        g_weatherAParams.reserved2 = 0.0f;

        g_weatherBParams.r = 0.0f;
        g_weatherBParams.g = 0.0f;
        g_weatherBParams.b = 0.0f;
        g_weatherBParams.time = 0.0f;
        g_weatherBParams.reserved1 = 0.0f;
        g_weatherBParams.reserved2 = 0.0f;

        // Set weights to zero to indicate no active weather
        g_weatherAWeight = 0.0f;
        g_weatherBWeight = 0.0f;
        g_weatherCWeight = 0.0f;
    }
}