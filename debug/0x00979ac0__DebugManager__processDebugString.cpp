// FUNC_NAME: DebugManager::processDebugString

// Global debug manager instance (singleton)
extern DebugManager* g_debugManager; // DAT_0112af70

// Fills a buffer with debug string from source at offset +0x110
void DebugManager::getDebugString(void* source, char* buffer); // FUN_00977090

// Outputs the debug string (e.g., to console or log file)
void DebugManager::outputDebugString(const char* buffer); // FUN_004df720

// Checks if debug output is enabled (offset +0x104) and processes pending debug strings
int DebugManager::processDebugString()
{
    char buffer[76]; // local_50

    if (g_debugManager != nullptr && *(int*)((uint8_t*)g_debugManager + 0x104) != 0)
    {
        // Retrieve debug string from internal source at offset +0x110
        DebugManager::getDebugString((void*)((uint8_t*)g_debugManager + 0x110), buffer);
        // Output the debug string
        DebugManager::outputDebugString(buffer);
    }
    return 0;
}