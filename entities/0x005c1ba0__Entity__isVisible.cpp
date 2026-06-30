//FUNC_NAME: Entity::isVisible
bool __fastcall Entity::isVisible(int this) {
    // Global buffer for constructing property paths
    extern char g_propertyBuffer[5]; // DAT_01223564, 4 bytes + null terminator
    char path[16];
    int result;

    // Virtual call: vtable at +0x10, function at index 1 (offset 4)
    // Returns a 4-byte value interpreted as a string (e.g., entity name)
    unsigned int name = (*(code **)(*(int *)(this + 0x10) + 4))();

    // Store the name bytes into the global buffer (little-endian)
    g_propertyBuffer[0] = (name >> 24) & 0xFF;
    g_propertyBuffer[1] = (name >> 16) & 0xFF;
    g_propertyBuffer[2] = (name >> 8) & 0xFF;
    g_propertyBuffer[3] = name & 0xFF;
    g_propertyBuffer[4] = 0; // null terminator

    // Build property path: "<name>._visible"
    sprintf(path, "%s._visible", g_propertyBuffer);

    result = 0;
    // Query the property system for a boolean value
    FUN_0059fb30(path, &result); // likely getPropertyBool

    return result == 0;
}