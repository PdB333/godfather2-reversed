// FUNC_NAME: InputHelper::getKeyNameString
char* InputHelper::getKeyNameString(char* outBuffer, BYTE vKeyCode)
{
    // Zero out the output buffer (16 bytes: 4 DWORDs)
    *(DWORD*)(outBuffer + 0x0) = 0;
    *(DWORD*)(outBuffer + 0x4) = 0;
    *(DWORD*)(outBuffer + 0x8) = 0;
    *(DWORD*)(outBuffer + 0xC) = 0;

    WCHAR keyName[256];
    // GetKeyNameTextW expects an lParam containing scan code and extended flag.
    // Here the virtual key code is shifted left 16 bits to place it into the OEM scan code field.
    // This assumes vKeyCode is already a scan code, not a VK_ constant.
    int len = GetKeyNameTextW((DWORD)vKeyCode << 16, keyName, 256);
    if (len != 0)
    {
        // Convert wide key name to multibyte string (likely ASCII) into outBuffer
        // FUN_004ddaf0 - unknown helper function (string conversion/copy?)
        wideToMultiByte(keyName, outBuffer); // Replaces FUN_004ddaf0
    }
    return outBuffer;
}