// FUNC_NAME: readRegistryWideString
// Function at 0x00698620: Reads a wide string value from the Windows registry and converts it to a narrow string.
// param_1: 0 = HKEY_CURRENT_USER, 1 = HKEY_LOCAL_MACHINE, other = HKEY_LOCAL_MACHINE (fallback)
// param_2: Registry key path (wide string)
// param_3: Value name (wide string)
// param_4: Output buffer for converted narrow string
// param_5: Size of output buffer
// Returns: 1 on success, 0 on failure

int readRegistryWideString(int baseKeyFlag, LPCWSTR keyPath, LPCWSTR valueName, char* outBuffer, size_t bufferSize)
{
    HKEY hKey;
    DWORD valueType;
    DWORD dataSize;
    BYTE buffer[1024];
    int result = 0;

    // Determine root key based on flag
    if (baseKeyFlag == 0 || baseKeyFlag == 1) {
        hKey = (baseKeyFlag == 0) ? HKEY_CURRENT_USER : HKEY_LOCAL_MACHINE;
    } else {
        hKey = HKEY_LOCAL_MACHINE;
    }

    // Open the registry key with read access (KEY_QUERY_VALUE = 0x20019)
    if (RegOpenKeyExW(hKey, keyPath, 0, 0x20019, &hKey) == ERROR_SUCCESS) {
        dataSize = 0x400; // 1024 bytes
        if (RegQueryValueExW(hKey, valueName, NULL, &valueType, buffer, &dataSize) == ERROR_SUCCESS) {
            // Verify type is REG_SZ (1) and data is non-empty
            if (valueType == 1 && dataSize != 0) {
                // Convert wide string to narrow string and null-terminate
                __snprintf(outBuffer, bufferSize, "%ws", buffer);
                outBuffer[bufferSize - 1] = '\0';
                result = 1;
            }
        }
        RegCloseKey(hKey);
    }
    return result;
}