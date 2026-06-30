// FUNC_NAME: SomeClass::getFloatOrDefault
float10 __thiscall SomeClass::getFloatOrDefault(void* this, float defaultValue) {
    float cachedValue;
    struct CallbackData {
        int arg;
        int padding; // possibly unused
        void* callback; // function pointer - used via indirect call
    } callbackData;

    // Try to get a cached float value from internal storage.
    if (FUN_006999f0(this, &cachedValue) != 0) {
        return (float10)cachedValue;
    }

    // Check if a global index is valid (within an array of some sort).
    if ((g_currentIndex > -1) && (g_currentIndex < ((g_endArray - g_startArray) >> 2))) {
        // Prepare some state
        FUN_004d3bc0(this);
        // Fill callback data with the default value and set up a callback
        FUN_0069b510(&callbackData, defaultValue);
        // If the callback data's argument is non-zero, invoke the callback
        if (callbackData.arg != 0) {
            ((void (*)(int))callbackData.callback)(callbackData.arg);
        }
    }

    return (float10)defaultValue;
}