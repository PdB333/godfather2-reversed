// FUNC_NAME: DebugManager::conditionalPrint

// Global debug manager singleton pointer (address 0x01223484)
static DebugManager* s_debugManager = reinterpret_cast<DebugManager*>(0x01223484);

// External debug print function (address 0x008b5cb0)
extern void debugPrint(const char* message, int level);

// Debug message string constant (address 0x00d79770)
extern const char* kDebugMessage;

void DebugManager::conditionalPrint() {
    // Check if the debug manager is initialized and has a valid context
    if (s_debugManager != nullptr && s_debugManager->m_context != 0) {
        debugPrint(kDebugMessage, 0xd);  // Print with level 13
    }
}