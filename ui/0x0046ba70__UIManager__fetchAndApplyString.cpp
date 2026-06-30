// FUNC_NAME: UIManager::fetchAndApplyString
bool UIManager::fetchAndApplyString(void* destWindow) {
    // Get the object with ID 1 (e.g., a singleton game object or global text holder)
    void* object = getObjectByID(1);
    if (object == nullptr) {
        return false;
    }
    
    // Access fields at offsets +0x20 and +0x24 (likely a pointer to string data and its size/type)
    void* stringData = *(void**)((char*)object + 0x20);
    int stringInfo = *(int*)((char*)object + 0x24);
    if (stringData == nullptr) {
        return false;
    }
    
    // Buffer to hold the constructed string (39 bytes, likely wide chars or a struct)
    char buffer[39];
    
    // Build the string from the object's data (e.g., format with additional info or just copy)
    buildString(buffer, stringData, stringInfo); // FUN_004d9080
    
    // Apply the string to the destination window (e.g., set text or update UI element)
    applyStringToWindow(destWindow, buffer); // FUN_00625ca0
    return true;
}