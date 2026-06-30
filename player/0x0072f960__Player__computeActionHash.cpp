// FUNC_NAME: Player::computeActionHash

#include <cstdint>

// Forward declarations of helper functions (likely internal to the module)
int __fastcall handlePausedState();                     // 0x00716160
int __fastcall checkGameMode();                        // 0x00717700
uint32_t __fastcall getRandomInt();                     // 0x00800b60

// Magic hashes / IDs returned by this function
const int32_t HASH_ACT_A = 0x992ba90a;
const int32_t HASH_ACT_B = 0x2389cb85;
const int32_t HASH_ACT_C = -0x2f24fc57;                // 0xD0DB03A9
const int32_t HASH_ACT_D = -0x1edf2944;                // 0xE120D6BC
const int32_t HASH_ACT_E = -0x1edf2943;                // 0xE120D6BD
const int32_t HASH_ACT_F = -0x190af90d;                // 0xE6F506F3
const int32_t HASH_ACT_G = 0x5e358a5f;

// Structure offsets are based on decompiled analysis of the Player class
// +0x8e0 : flags bitfield (paused flag at bit 1)
// +0x1f54 : state flags
// +0x1f5c : more state flags

int32_t __fastcall Player::computeActionHash() {
    int32_t result = 0;

    // Check if currently in a paused/blocking state (bit 1 of offset +0x8e0)
    if ((*(uint32_t*)((uint8_t*)this + 0x8e0) >> 1) & 1) {
        return handlePausedState();
    }

    // Determine game mode / scenario context
    int32_t modeCheck = checkGameMode();
    if (modeCheck == 0) {
        // Not in special mode (e.g., multiplayer or event)
        uint32_t randomVal = getRandomInt();
        switch (randomVal) {
        case 0: {
            // Check specific state bits (bit 13 of +0x1f54, bits 22,21,19,20 of +0x1f5c)
            uint32_t flags1 = *(uint32_t*)((uint8_t*)this + 0x1f54);
            uint32_t flags2 = *(uint32_t*)((uint8_t*)this + 0x1f5c);
            if ((flags1 >> 0xd) & 1) {
                // Depends on bit 22 of flags2
                return (-((flags2 >> 0x16) & 1)) & 0x410df3ed) + 0x992ba90a; // Note: this combines with bit 22 to produce a value
                // Simplified: if bit 22 set, result = 0x992ba90a else something else (mask arithmetic)
            }
            if ((flags2 >> 0x15) & 1) {
                return HASH_ACT_B; // 0x2389cb85
            }
            result = HASH_ACT_C; // default if no flag matches
            if ((flags2 >> 0x13) & 1) {
                return HASH_ACT_D;
            }
            if ((flags2 >> 0x14) & 1) {
                return HASH_ACT_E;
            }
            break;
        }
        case 1:
            return HASH_ACT_C;
        case 2:
        case 3:
        case 4:
            result = HASH_ACT_F;
        }
        return result;
    }
    else {
        // In special mode (e.g., multiplayer)
        uint32_t randomVal = getRandomInt();
        switch (randomVal) {
        case 0:
            return HASH_ACT_C;
        case 1:
            return HASH_ACT_G;
        case 2:
        case 3:
        case 4:
            return HASH_ACT_F;
        default:
            return 0;
        }
    }
}