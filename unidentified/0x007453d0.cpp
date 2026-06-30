// FUN_NAME: Sentient::getControllingPlayerId
// Address: 0x007453d0
// Determines the controlling player ID (or handle) for this sentient entity.
// param_2: bForceCheck – when true, checks a special flag at offset 0x8ec to return a quick value.
// Otherwise uses the GameManager to get the player and checks local player status.

#include <cstdint>

// Forward declarations for game classes
class GodfatherGameManager;
class Player; // EARS::Modules::Player

// External functions from Ghidra callees
extern GodfatherGameManager* FUN_0043b870(uint32_t* globalPtr); // returns game manager singleton
extern bool FUN_009b24b0(); // checks if local player condition holds
extern uint32_t FUN_00744f60(Sentient* entity, Player* player, int param3, uint32_t playerID); // helper function

// Global pointer to game manager singleton (from .data)
extern uint32_t DAT_0113105c;

class Sentient {
public:
    // +0x8ec: Control flags. Bits: bit2 = quick return flag, bits 10-31 = some ID
    uint32_t m_controlFlags;
    // ... other members
};

uint32_t Sentient::getControllingPlayerId(bool bForceCheck) {
    uint32_t tempFlags;

    if (bForceCheck) {
        tempFlags = m_controlFlags >> 2;      // Shift to bring bit to position 0
        if (tempFlags & 1) {
            // Return 0x01000000 OR (bits 10-31 of m_controlFlags)
            return (1 << 24) | ((m_controlFlags >> 10) & 0x00FFFFFF);
        }
    }

    if (this != nullptr) {
        Player* player = reinterpret_cast<Player*>(FUN_0043b870(&DAT_0113105c)); // Get player from manager
        uint32_t result = reinterpret_cast<uint32_t>(player); // fallback value

        if (player != nullptr) {
            uint8_t flags = *(reinterpret_cast<uint8_t*>(player) + 0x78); // +0x78: some flags byte
            if ((flags >> 2) & 1) { // Check bit 2
                bool local = FUN_009b24b0();
                if (local) {
                    uint32_t playerId = *(reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(player) + 0x4c)); // +0x4c: player ID
                    result = FUN_00744f60(this, player, 0, playerId);
                }
            }
        }
        return result & 0xFFFFFF00; // Mask lower byte to produce handle/ID
    }

    // If this is null (should not happen), return fallback from first block
    return tempFlags & 0xFFFFFF00;
}