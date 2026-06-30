// FUNC_NAME: getConfigValue
// Function queries a named configuration value, handling built-in keys "platform", "b480w", "b720"
// Returns 1 on success, sets outType and outValue accordingly.
// For unknown keys, it uses a generic settings manager (global pointer + 0x2c) to resolve the value.
int __cdecl getConfigValue(char* key, int* outType, uint* outValue)
{
    int cmpResult;
    int type;
    void* vtablePtr;

    // Check for built-in keys
    cmpResult = __stricmp(key, "platform");
    if (cmpResult == 0) {
        // Returns pointer to platform string constant
        *outValue = (uint)&PTR_LAB_00e3e5d8;  // Platform identifier string
        *outType = 1;                        // Type: pointer
        return 1;
    }

    cmpResult = __stricmp(key, "b480w");
    if (cmpResult == 0) {
        // Returns whether HD mode is exactly 1 (i.e., 480p widescreen)
        *outValue = (uint)(g_HDEnabled == 1);  // DAT_01205698 -> g_HDEnabled
        *outType = 3;                          // Type: boolean/int
        return 1;
    }

    cmpResult = __stricmp(key, "b720");
    if (cmpResult == 0) {
        // Returns whether HD mode is non-zero (i.e., 720p)
        *outValue = (uint)(g_HDEnabled != 0);
        *outType = 3;
        return 1;
    }

    // Generic key resolution via settings manager
    // Global singleton at offset 0x2c holds pointer to a settings object with a virtual function table.
    vtablePtr = *(void**)(g_pSettingsManager + 0x2c);  // DAT_012234f0 + 0x2c -> g_pSettingsManager
    int keyId = convertStringToKeyId(key);               // FUN_004dafd0: converts string to ID
    type = (*(int (__cdecl *)(int))vtablePtr)(keyId);    // Call virtual function (first entry) to get type

    *outType = type;

    // Write a 1 into the key buffer (used as fallback value buffer)
    key[0] = 1;
    key[1] = 0;
    key[2] = 0;
    key[3] = 0;

    if (*outType == 0) {
        // If type is 0 (unknown/error), set type to pointer of the buffer (containing 1)
        *outType = (int)key;
    }

    return 1;
}