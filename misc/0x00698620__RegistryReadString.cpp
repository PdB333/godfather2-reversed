// FUNC_NAME: RegistryReadString
bool RegistryReadString(int rootKeySelection, LPCWSTR subKey, LPCWSTR valueName, char* outBuffer, size_t bufferSize)
{
    LSTATUS result;
    HKEY hKey;
    DWORD type;
    DWORD cbData;
    BYTE szBuffer[1024];

    // Determine root key: rootKeySelection 0 -> HKEY_CURRENT_USER? Actually obfuscated logic:
    // if rootKeySelection == 0, we use HKLM; if == 1, HKCU; else HKLM.
    // This is likely a bug or reversed intention – typical usage: 0 = HKCU, 1 = HKLM.
    if ((rootKeySelection == 0) || (hKey = HKEY_CURRENT_USER, rootKeySelection != 1)) {
        hKey = HKEY_LOCAL_MACHINE;
    }

    // Open registry key with read/enumerate/query access (0x20019 = KEY_READ | KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE)
    result = RegOpenKeyExW(hKey, subKey, 0, 0x20019, &hKey);
    if (result == ERROR_SUCCESS) {
        cbData = sizeof(szBuffer);
        result = RegQueryValueExW(hKey, valueName, NULL, &type, szBuffer, &cbData);
        if ((result == ERROR_SUCCESS) && (type == REG_SZ) && (cbData > 0)) {
            // Convert wide string to ANSI
            __snprintf(outBuffer, bufferSize, "%ws", szBuffer);
            outBuffer[bufferSize - 1] = '\0';
            RegCloseKey(hKey);
            return true;
        }
        RegCloseKey(hKey);
    }
    return false;
}