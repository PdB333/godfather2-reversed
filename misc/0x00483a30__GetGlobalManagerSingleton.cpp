// FUNC_NAME: GetGlobalManagerSingleton
// Function at 0x00483a30 returns a pointer to the global manager instance (at 0x0120ec6c)
// This is a trivial accessor for a singleton-style object (likely a game state or manager)

struct GlobalManager; // Forward declaration, defined elsewhere in the engine

extern GlobalManager g_globalManager; // 0x0120ec6c

GlobalManager* GetGlobalManager() {
    return &g_globalManager;
}