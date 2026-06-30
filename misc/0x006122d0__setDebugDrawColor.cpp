// FUNC_NAME: setDebugDrawColor
void setDebugDrawColor(uint32_t *rgbaOrVector)
{
    // Write 4 uint32 values to global debug variables (likely a color or vector)
    g_debugDrawColor[0] = rgbaOrVector[0]; // _DAT_011f6870
    g_debugDrawColor[1] = rgbaOrVector[1]; // uRam011f6874
    g_debugDrawColor[2] = rgbaOrVector[2]; // uRam011f6878
    g_debugDrawColor[3] = rgbaOrVector[3]; // uRam011f687c

    // If a global debug renderer instance exists and its render function pointer is set
    // DAT_012058e8: likely g_debugRenderer (pointer to some debug renderer object)
    // +0x58: pointer to a render function or state
    // +0x10: some parameter (perhaps renderer type or a context)
    if (g_debugRenderer != NULL && *(int *)(g_debugRenderer + 0x58) != 0)
    {
        FUN_0060add0(*(uint32_t *)(g_debugRenderer + 0x10), *(int *)(g_debugRenderer + 0x58), rgbaOrVector);
    }
}