// FUNC_NAME: AudioManager::updateMusicForState
// Function address: 0x0096a810
// Sets the background music based on the current state (e.g., combat vs free roam).
// Offset +0x4 of the `this` pointer is interpreted as an integer state (1 = combat, else free roam).

#pragma pack(push, 1)
struct AudioEventId {
    uint32_t id1;    // +0x00
    uint32_t id2;    // +0x04
    uint8_t  id3;    // +0x08
};
#pragma pack(pop)

extern void audioStopMusic();                 // FUN_00967450: stops currently playing music
extern void audioSetMusicEvent(AudioEventId* event, int unk0); // FUN_00408a00: posts a music event

extern const uint32_t kMusicIdCombat;    // DAT_011302c0
extern const uint32_t kMusicIdFreeRoam;  // DAT_011304d8

class AudioManager {
public:
    int m_currentState; // +0x04: 1 = combat, else free roam

    void __thiscall updateMusicForState();
};

void __thiscall AudioManager::updateMusicForState() {
    AudioEventId event;

    if (m_currentState != 1) {
        // Not in combat: stop current music, then start free roam music
        audioStopMusic();

        event.id1 = kMusicIdFreeRoam;
        event.id2 = 0;
        event.id3 = 0;
        audioSetMusicEvent(&event, 0);
    } else {
        // In combat: directly set combat music (music already handled elsewhere)
        event.id1 = kMusicIdCombat;
        event.id2 = 0;
        event.id3 = 0;
        audioSetMusicEvent(&event, 0);
    }
}