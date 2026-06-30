// FUNC_NAME: InputManager::updateStickScaling

void InputManager::updateStickScaling(int param_1, float param_2, int param_3) {
    // Global state variables (addresses from Ghidra)
    // g_stickConfigTable: array of 0x38-byte entries at 0x011a0f28 (max 0x1000 entries)
    // g_currentStickIndex: index into config table (0x01125b80)
    // g_controllerId: active controller ID (0x01125ab4)
    // g_compareId: comparison controller ID (0x01125b44)
    // g_defaultSensitivity: float constant at 0x00e2b1a4
    // g_stickValueA: first additional parameter (0x01125b58)
    // g_stickValueB: second additional parameter (0x01125b64)
    // g_stickScaleX, g_stickScaleY: output scale factors (0x01125b70, 0x01125b74)
    // g_stickScaleParam1, g_stickScaleParam3: output parameters (0x01125b78, 0x01125b7c)

    int additionalParam;
    float scaleX, scaleY;

    if (g_controllerId == g_compareId) {
        // Use default sensitivity for this controller type
        param_3 = 0;  // Override parameter (likely intended to be an output)

        // Compute scale from default constant divided by raw stick max values
        // Each config entry has ushort at offset 0x02 (stick X max) and 0x04 (stick Y max)
        ushort* config = (ushort*)((char*)g_stickConfigTable + g_currentStickIndex * 0x38);
        scaleX = g_defaultSensitivity / (float)config[1];  // +0x02
        scaleY = g_defaultSensitivity / (float)config[2];  // +0x04

        additionalParam = g_stickValueA;
    } else {
        // Use caller-provided sensitivity
        ushort* config = (ushort*)((char*)g_stickConfigTable + g_currentStickIndex * 0x38);
        scaleX = param_2 / (float)config[1];
        scaleY = param_2 / (float)config[2];

        additionalParam = g_stickValueB;
    }

    // Store computed scaling and parameters
    g_stickScaleX = scaleX;
    g_stickScaleY = scaleY;
    g_stickScaleParam1 = param_1;
    g_stickScaleParam3 = param_3;

    // Apply scaling via engine setter (function at 0x0060add0)
    // Signature: void setStickScale(int controllerId, int param, float* scalePair)
    setStickScale(g_controllerId, additionalParam, &g_stickScaleX);
}