// FUNC_NAME: NPC::getPursuitDistance

// Function address: 0x008e9b70
// Member function of NPC class, returns the max distance the NPC will pursue the player.
// Returns 999999 if NPC is not in a pursuit-capable state (flag 0x40 bit 0 clear).
// Base distance = npcData->aggressionLevel (offset 0x0c) * 1000 (converted to int).
// Modified by random factor and global difficulty setting.

class NPC {
public:
    // Virtual table at +0x0
    // Unknown at +0x4
    NPCExtendedData* m_pData;  // +0x8 : pointer to extended NPC data block
    int m_aggressionLevel;     // +0xc : aggression/fear scale, multiplied by 1000 for distance
    // ... other members
};

struct NPCExtendedData {
    // ... many fields
    BYTE m_flags;              // +0x40 : bit0 – can-pursuit flag
    // ... 
};

// External functions (from EARS engine)
int __cdecl getRandomSeed();                    // FUN_00471610 : returns a time/seed value
bool __cdecl isNightTime(int seed, int, int);   // FUN_006c0050 : checks if night (if true, subtract 500)
float __cdecl getDifficultyFactor(int seed);    // FUN_006bfff0 : returns a difficulty multiplier (0.0..1.0)

extern float g_globalDifficultyCutoff;  // DAT_00d62bd4 : global threshold for difficulty reduction

int __thiscall NPC::getPursuitDistance() {
    // Check if NPC is allowed to pursue (e.g., not fleeing, not dead)
    if (!(m_pData->m_flags & 1)) {
        return 999999;  // Sentinel: no pursuit range
    }

    // Base distance: aggression level scaled to world units (multiply by 1000)
    int baseDistance = m_aggressionLevel * 1000;

    // Seed generation using current time + 0x30 (likely to randomize)
    int seed = getRandomSeed() + 0x30;

    // Night time penalty: reduce distance by 500 units during night
    if (isNightTime(seed, 0, 0)) {
        baseDistance -= 500;
    }

    // Difficulty factor from global or seed
    float difficultyFactor = getDifficultyFactor(seed);

    // Apply difficulty modifier: limit reduction by global cutoff
    if (g_globalDifficultyCutoff < difficultyFactor) {
        return baseDistance - (int)g_globalDifficultyCutoff;
    }

    return baseDistance - (int)difficultyFactor;
}