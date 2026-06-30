// FUNC_NAME: getEffectiveSetting
/* Function address: 0x0041b1a0
 * Role: Returns either g_defaultSetting or g_alternateSetting based on a flag in the game state singleton.
 *       Used by callers at 0x009d9a30 and 0x009daf70 (likely menu or game mode selection).
 */

#pragma pack(push, 1)
struct GameStateSingleton {
    uint32_t field_0x00;                      // +0x00
    struct SecondState* pSecondState;         // +0x04 pointer to secondary state structure
};

struct SecondState {
    uint8_t  pad_0x0000[0x39F8];              // +0x0000 through +0x39F7
    int32_t  effectiveFlag;                   // +0x39F8
};
#pragma pack(pop)

static GameStateSingleton* g_someSingleton;    // DAT_012233a8
static uint32_t g_defaultSetting;              // DAT_012118c0
static uint32_t g_alternateSetting;            // DAT_0120536c

uint32_t getEffectiveSetting(void) {
    uint32_t result = g_defaultSetting;
    if (g_someSingleton->pSecondState->effectiveFlag != 0) {
        result = g_alternateSetting;
    }
    return result;
}