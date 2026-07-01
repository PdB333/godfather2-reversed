// FUNC_NAME: isGameInitialized

// Globals checking the initialization state of the game core manager
extern uint32_t g_gameReadyFlag;      // DAT_0112982c - non-zero when the game is initializing/ready
extern uint8_t* g_pGameObject;        // DAT_0112981c - pointer to a singleton game object (e.g., GameManager)

uint8_t isGameInitialized(void)
{
    // Returns true only when all conditions are met:
    // 1. The global flag is set (g_gameReadyFlag != 0)
    // 2. The game object pointer is non-null
    // 3. The byte at offset +0x48 inside the object is non-zero (active/initialized flag)
    if ((g_gameReadyFlag != 0) && (g_pGameObject != (uint8_t*)0x0)) {
        // +0x48 : m_isActive (bool byte)
        if (*(uint8_t*)(g_pGameObject + 0x48) != 0) {
            return 1;
        }
    }
    return 0;
}