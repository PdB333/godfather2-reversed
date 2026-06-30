// FUNC_NAME: debugPrintInt
// Function at 0x0056a4e0: Converts an integer to a string and calls a global callback (e.g., debug output).
void __cdecl debugPrintInt(void* outputInterface, int value) {
    char buffer[16]; // +0x0: scratch buffer for integer string (size 0x10)
    __snprintf(buffer, sizeof(buffer), "%d", value);
    buffer[15] = 0; // local_1 = 0; explicit null terminator after snprintf

    // Global vtable/function table at DAT_012234e0 (likely DebugManager singleton)
    // Calls a function pointer at offset 0x14 (e.g., DebugManager::printStyled?).
    (*(void (__cdecl **)(void*, int, const char*))(*DAT_012234e0 + 0x14))(outputInterface, value, buffer);
}