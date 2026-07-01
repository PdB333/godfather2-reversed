// FUNC_NAME: Sentient::playReactionSound
// Address: 0x007c7240
// Role: Plays a reaction/contextual sound based on player state and current scenario

#include <cstdint>

// Forward declarations
int __fastcall getCurrentScenarioManager();          // FUN_007ab1e0
char __fastcall isGameplayActive();                  // FUN_008a4380
void __fastcall setEffectTimer(int id, int delay);   // FUN_0079f100

extern int AUDIO_DEFAULT_FLAGS;   // _DAT_00d5780c
extern int AUDIO_CUTSCENE_FLAGS;  // DAT_00e52f6c

class SomeComponent {
public:
    // +0x249f: bit 0 indicates something (e.g., cutscene flag)
    uint8_t m_flags[0x24A0]; // placeholder for actual structure
};

class Sentient {
public:
    // Virtual table at offset 0
    // Vtable entry at +0x2c: virtual void __thiscall playSound(int soundId, int arg1, int arg2, int arg3, int flags, float volume)

    // Offsets (relative to this pointer):
    // +0x118 (0x46 * 4): m_reactionState (0=neutral, 1=?, 2=?)
    int m_reactionState;
    // +0x058 (0x16 * 4): m_someComponent (pointer to SomeComponent)
    SomeComponent* m_someComponent;
    // ... other members ...

    void playReactionSound();
};

void Sentient::playReactionSound() {
    int scenarioPtr = getCurrentScenarioManager();
    int soundId;

    if (scenarioPtr == 0 || *(char*)(scenarioPtr + 0x1AA) != 2) {
        // Not in a specific scenario (e.g., combat)
        soundId = (m_reactionState != 2) ? 0x2A3B30A5 : 0xCCCA4102;
    } else {
        // In a scenario where the extra condition holds
        soundId = (m_reactionState != 2) ? 0xB69F5A60 : 0xCB7328EF;
    }

    int flags = AUDIO_DEFAULT_FLAGS;
    char gameplayActive = isGameplayActive();
    if (gameplayActive == 0 && (m_someComponent->m_flags & 1) != 0) {
        flags = AUDIO_CUTSCENE_FLAGS;
    }

    // Call virtual playSound with soundId, three flags=1, flags parameter, volume=1.0f
    typedef void (__thiscall* PlaySoundFunc)(void*, int, int, int, int, int, float);
    (*reinterpret_cast<PlaySoundFunc>(*(uint32_t*)this + 0x2C))(
        this, soundId, 1, 1, 1, flags, 1.0f);

    setEffectTimer(9, 0);
}