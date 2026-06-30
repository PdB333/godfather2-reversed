// FUNC_NAME: getEARSGameManager

// 0x00459030 - Accessor for the global EARSGameManager singleton pointer
EARSGameManager* getEARSGameManager() {
    // The global variable at address 0x012053f4 stores the pointer to the singleton instance
    extern EARSGameManager* g_pEARSGameManager; // defined elsewhere, at 0x012053f4
    return g_pEARSGameManager;
}