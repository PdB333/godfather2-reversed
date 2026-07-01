// Xbox PDB: EARS_Apt_UIPlayerFamilyTree_ToggleRivalMemberMarkedForExecution
// FUNC_NAME: DonControlGadget::markRivalForExecution
// Address: 0x0097f800
// Role: Handles marking a rival for execution in Don Control mode.
//        Checks gadget state, toggles mark on selected character, plays sounds/logs events.

#include <cstdint>

// Forward declarations of called functions (assumed based on EA engine)
bool isPlayerInDonControlMode();                               // FUN_008fda60
int getCharacterFromId(uint32_t charId);                      // FUN_008ff210
void toggleRivalMarkedState(int charRef);                     // FUN_008ff3f0
void logEvent(const char* eventName, int param1, void* data, int param2); // FUN_005a04a0
void playUISound(void* soundData, int flags);                 // FUN_00402050
void playSound(void* soundParams, int flags);                 // FUN_00408a00

// Global data (from game binary)
extern uint32_t DAT_011302c0;    // Default sound asset reference
extern void* DAT_00d8fe44;       // Additional event data (maybe struct)
extern void* DAT_011302e8;       // UI sound asset reference

class DonControlGadget {
public:
    // Offset 0x104: Current gadget state (0 = idle, 7 = maybe execution cancelled)
    int32_t m_state;
    // Offset 0x11C: Selected rival character ID
    uint32_t m_selectedTargetId;
    // Offset 0x129: Toggle flag for marking
    bool m_isMarked;

    void markRivalForExecution();
};

void DonControlGadget::markRivalForExecution() {
    struct SoundParams {
        uint32_t soundAssetId;   // +0x00
        uint32_t field_4;        // +0x04
        uint8_t  field_8;        // +0x08
    } soundParams;

    // If gadget is in an idle or cancelled state, play default sound and return
    if (m_state == 0 || m_state == 7) {
        soundParams.soundAssetId = DAT_011302c0;
        soundParams.field_4 = 0;
        soundParams.field_8 = 0;
        playSound(&soundParams, 0);
        return;
    }

    int charRef = getCharacterFromId(m_selectedTargetId);
    if (charRef != 0 && isPlayerInDonControlMode()) {
        // If already marked, reset charRef to allow toggling off
        if (m_isMarked) {
            charRef = 0;
        }
        toggleRivalMarkedState(charRef);
        // Flip the marking flag
        m_isMarked = !m_isMarked;
        // Log the event and play UI sound
        logEvent("RivalMarkForExecution", 0, &DAT_00d8fe44, 0);
        playUISound(&DAT_011302e8, 0);
        return;
    }

    // Fallback: play default sound if conditions not met
    soundParams.soundAssetId = DAT_011302c0;
    soundParams.field_4 = 0;
    soundParams.field_8 = 0;
    playSound(&soundParams, 0);
}