// FUNC_NAME: Sentient::isPlayerControlled
// Address: 0x006b34a0
// Returns 1 if this entity is controlled by the current player, else calls a setup function.

#include <cstdint>

// Global pointer to the game's player manager singleton (offset +4 holds pointer to current player structure)
extern uint32_t g_pPlayerManager; // 0x012233a0

// Forward declaration of function called when control needs to be transferred
uint8_t __fastcall setupPlayerControl(Sentient* entity, uint32_t someGlobal, uint32_t unknownFlag);

class Sentient {
public:
    // +0x38: ID of the entity currently controlling this sentient (0 if none)
    int32_t m_controllerID;

    // +0xD4: Flag indicating if this entity can be controlled by a player (non-zero = true)
    int32_t m_playerControlCapable;

    // Check if this entity is currently under player control.
    // Returns 1 if controlled, otherwise 0 or result of setup function.
    uint8_t __fastcall isPlayerControlled() {
        // Dereference global player manager to get a pointer to the current player's sentient structure.
        int32_t* pCurrentPlayer = **(int32_t***)(reinterpret_cast<uint8_t*>(g_pPlayerManager) + 4);
        uint8_t result = 0;

        if (pCurrentPlayer != nullptr && (reinterpret_cast<int32_t>(pCurrentPlayer) - 0x1F30) != 0) {
            // Compare the controller ID of this entity with the controller ID stored in the player's state.
            // The player structure has a field at offset -0x48 (i.e., pCurrentPlayer - 0x48 points to that field)
            if (*(pCurrentPlayer - 0x12) == m_controllerID) { // Note: ( -0x48 / 4 ) = -0x12 as int offset
                return 1;
            }

            // If the player has no controller ID set, and this entity allows player control, try to assign control.
            if (*(pCurrentPlayer - 0x12) == 0 && m_playerControlCapable != 0) {
                result = setupPlayerControl(
                    reinterpret_cast<Sentient*>(reinterpret_cast<uint8_t*>(pCurrentPlayer) - 0x1F30),
                    g_unknownGlobal,  // 0x00D5E20C
                    1
                );
            }
        }
        return result;
    }
};