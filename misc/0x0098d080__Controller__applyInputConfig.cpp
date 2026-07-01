// FUNC_NAME: Controller::applyInputConfig
void __thiscall Controller::applyInputConfig(int thisPtr, char *configPath)
{
    char isValid;
    char *lastSlash;
    char buffer[192]; // local_c0

    isValid = isValidPath(configPath);
    if (isValid == '\0') {
        if (*configPath == '\0') {
            resetToDefault(1); // FUN_0098ce00(1)
        } else {
            _strncpy(buffer, configPath, 0xc0);
            lastSlash = _strrchr(buffer, 0x2f); // '/'
            if (lastSlash != (char *)0x0) {
                _strncpy(lastSlash, "/input", (int)&stack0x00000000 - (int)lastSlash);
            }
            loadConfigFile(buffer); // FUN_0098cf00
            if (*(int *)(thisPtr + 0x5c) != 0) {
                // Interpolate axis values with smoothing factor
                float smoothedX = (*(float *)(thisPtr + 0x138) - *(float *)(thisPtr + 0x130)) * g_inputSmoothingFactor + *(float *)(thisPtr + 0x130);
                float smoothedY = (*(float *)(thisPtr + 0x13c) - *(float *)(thisPtr + 0x134)) * g_inputSmoothingFactor + *(float *)(thisPtr + 0x134);
                setSmoothedAxis(smoothedX, smoothedY); // FUN_0098ab10
                applyDeadzone(*(undefined4 *)(*(int *)(thisPtr + 0x5c) + 0x28)); // FUN_0098a480
                return;
            }
        }
    }
    return;
}