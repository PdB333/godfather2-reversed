// FUNC_NAME: GameManager::update
// Address: 0x005e3df0
// Role: Wrapper function that calls a virtual method at offset 0xcc on the global GameManager singleton.
// The global pointer DAT_01223510 points to the GameManager instance; if non-null, the virtual method is called with the provided parameter.
void GameManager::update(void* param) {
    if (g_GameManager != nullptr) {
        // Call virtual function at vtable offset 0xcc
        (*(void(__thiscall**)(void*, void*))(*reinterpret_cast<int*>(g_GameManager) + 0xcc))(g_GameManager, param);
    }
}