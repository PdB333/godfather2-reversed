// FUNC_NAME: StreamManager::loadAndWait
void __thiscall StreamManager::loadAndWait(int thisPtr, int resourceId) {
    char isComplete;
    int result;
    int loadedData;
    undefined1* resourcePath;

    // Initialize the resource loading
    FUN_00833760(resourceId);
    FUN_0043aff0(resourceId, 0xb5c5b5bb); // Register resource with type hash

    // Wait loop until resource is fully loaded
    isComplete = FUN_0043b120(); // Check if loading is done
    while (isComplete == '\0') {
        FUN_0043b210(); // Process events / yield
        result = FUN_0043ab70(); // Check if resource is ready
        if (result == 0) {
            FUN_0043b210(); // Another yield after success
            loadedData = FUN_0043ab90(); // Get loaded data pointer
            FUN_004d3d90(loadedData); // Process/play loaded data (e.g., sound)

            // Get the resource path from this+0xe8, default if NULL
            resourcePath = *(undefined1**)(thisPtr + 0xE8); // +0xE8 : resource path string
            if (resourcePath == (undefined1*)0x0) {
                resourcePath = &DAT_0120546e; // Default resource path
            }
            *(int*)(thisPtr + 0xE4) = FUN_004dafd0(resourcePath); // +0xE4 : loaded resource handle
        }
        FUN_0043b1a0(); // Yield or update loop state
        isComplete = FUN_0043b120(); // Re-check completion
    }
    return;
}