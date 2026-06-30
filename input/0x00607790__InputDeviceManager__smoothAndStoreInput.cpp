// FUNC_NAME: InputDeviceManager::smoothAndStoreInput
void InputDeviceManager::smoothAndStoreInput(int* outDeltaX, int* outDeltaY, int* outDeltaZ, char isAbsolute, int extra) 
{
    char success;
    int i;
    uint* src;
    uint* dst;

    // Read raw input into the three delta outputs (calls raw device read)
    success = readRawInput(outDeltaX, outDeltaY, outDeltaZ, isAbsolute, extra); // FUN_006073e0

    if (success) {
        // If using relative delta and smoothing divisor > 1, average the movement
        if ((isAbsolute == 0) && (g_smoothingDivisor > 1)) {
            *outDeltaX /= g_smoothingDivisor;
            *outDeltaY /= g_smoothingDivisor;
        }

        // Copy 14 history entries from the local block (starting at outDeltaX) to global history buffer
        src = (uint*)outDeltaX;  // treat the three delta outputs as start of a 14-element block
        dst = g_inputHistory;    // DAT_011d9188
        for (i = 0; i < 14; i++) {
            dst[i] = src[i];
        }

        // Apply/forward the processed input (call another handler)
        applySmoothedInput(outDeltaZ, isAbsolute, extra); // FUN_00607730
    }
}