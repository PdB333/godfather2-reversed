// FUNC_NAME: getDamageReactionParameters

static char& g_bReactionDisabled = *(char*)0x012054ea; // possibly a global flag for cutscene/god mode

// Lookup table for damage reaction parameters, indexed by reaction ID (0-23, clamped to 3 if out of range)
static const short g_reactionTable[24][5] = {
    {5, 2, 1, 2, 1},   // 0
    {5, 6, 1, 2, 1},   // 1
    {5, 2, 1, 2, 1},   // 2
    {2, 1, 1, 2, 1},   // 3
    {9, 1, 1, 7, 1},   // 4
    {9, 2, 1, 7, 2},   // 5
    {9, 1, 1, 1, 2},   // 6
    {9, 1, 1, 2, 1},   // 7
    {5, 6, 1, 1, 2},   // 8
    {5, 2, 1, 1, 2},   // 9
    {2, 2, 1, 2, 2},   // 10
    {2, 2, 1, 1, 2},   // 11
    {7, 2, 1, 7, 2},   // 12
    {7, 2, 1, 1, 2},   // 13
    {8, 2, 1, 8, 2},   // 14
    {8, 2, 1, 1, 2},   // 15
    {1, 2, 1, 1, 5},   // 16
    {1, 2, 1, 8, 1},   // 17
    {1, 2, 1, 2, 2},   // 18
    {1, 2, 3, 2, 2},   // 19
    {7, 8, 1, 2, 1},   // 20
    {7, 8, 1, 1, 2},   // 21
    {8, 7, 1, 2, 1},   // 22
    {8, 7, 1, 1, 2}    // 23
};

// Forward declaration of the reaction application function (6 parameters)
void applyDamageReaction(int reactionType, int direction, int impact, int param4, int param5, int param6);

// Called when reaction is globally disabled (e.g. during cutscenes)
void applyReactionDisabled(void); // FUN_004e3660

// Get reaction parameters based on hit type (passed in EAX)
void __fastcall getDamageReactionParameters(uint hitType)
{
    if (g_bReactionDisabled) {
        applyReactionDisabled();
        return;
    }

    // Clamp hitType to valid range; if out of bounds, use index 3
    if (hitType > 23) {
        hitType = 3;
    }

    const short* entry = g_reactionTable[hitType];
    applyDamageReaction(entry[0], entry[1], entry[2], entry[3], entry[4], 1);
}