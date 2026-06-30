// FUNC_NAME: TeleportPlayerToPosition

#include <cstdint>

// Forward declaration or struct from EA EARS engine
struct GameManager {
    // ... many fields
    char m_bDebugEnabled; // +0x1744
};

// Global game manager instance at fixed address 0x0122350c
extern GameManager g_GameManager;

// Forward declaration: returns pointer to active player entity
struct Entity;
Entity* GetActivePlayer();   // FUN_005e2150

// Teleports the active player to the given position.
// Returns true on success, false if debug mode is disabled or player not available.
bool TeleportPlayerToPosition(const float* pPositionVec3)
{
    // Check debug mode flag
    if (g_GameManager.m_bDebugEnabled == 0)
        return false;

    Entity* pPlayer = GetActivePlayer();
    if (pPlayer == nullptr)
        return false;

    // Write position components at offsets 0x288, 0x28c, 0x290
    *(uint32_t*)((uint8_t*)pPlayer + 0x288) = *(uint32_t*)&pPositionVec3[0];
    *(uint32_t*)((uint8_t*)pPlayer + 0x28c) = *(uint32_t*)&pPositionVec3[1];
    *(uint32_t*)((uint8_t*)pPlayer + 0x290) = *(uint32_t*)&pPositionVec3[2];

    return true;
}