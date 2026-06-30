// FUNC_NAME: NPC::checkRandomChance (0x007227c0)
// This function evaluates a random chance based on a stored probability threshold.
// It generates a random float in [0,1] and checks if it is below the threshold at +0x13c.
// Returns 1 if the roll succeeds, 0 otherwise.

int __thiscall NPC::checkRandomChance(NPC* this)
{
    int randomInt = _rand();
    // The global float converts rand() to a value in [0,1] (likely g_randomScale)
    float roll = (float)randomInt * DAT_00e44590; // g_randomScale
    float threshold = *(float*)((int)this + 0x13c); // +0x13c: m_probabilityThreshold
    if (roll < threshold) {
        return 1;
    }
    return 0;
}