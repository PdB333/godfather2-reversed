// FUNC_NAME: GetEntityManagerPointer
int __cdecl GetEntityManagerPointer(int fallbackPointer)
{
    // Attempt to get the global SimManager singleton
    int simManager = GetSimManagerInstance(); // calls FUN_0071e270
    if (simManager != 0) {
        // Return the address of the EntityManager pointer field within SimManager (offset +0xF4)
        return simManager + 0xF4; // offset to m_pEntityManager
    }
    // Fallback: return the provided pointer (e.g., a local EntityManager pointer field)
    return fallbackPointer;
}