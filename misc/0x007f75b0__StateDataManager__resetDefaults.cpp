// FUNC_NAME: StateDataManager::resetDefaults
void __thiscall StateDataManager::resetDefaults(void)
{
    int defaultVal = g_someDefaultValue; // _DAT_00d5780c, likely 0xFFFFFFFF or invalid sentinel

    // +0xa80: single byte flag, cleared to 0
    *(char *)(this + 0xa80) = 0;

    // +0xa84..+0xa98: six consecutive ints zeroed (first group)
    *(int *)(this + 0xa84) = 0;
    *(int *)(this + 0xa88) = 0;
    *(int *)(this + 0xa8c) = 0;
    *(int *)(this + 0xa90) = 0;
    *(int *)(this + 0xa94) = 0;
    *(int *)(this + 0xa98) = 0;

    // +0xa9c: first group tail set to default
    *(int *)(this + 0xa9c) = defaultVal;

    // +0xaa0..+0xaa8: three ints zeroed (second group)
    *(int *)(this + 0xaa0) = 0;
    *(int *)(this + 0xaa4) = 0;
    *(int *)(this + 0xaa8) = 0;

    // +0xaac: second group tail set to default
    *(int *)(this + 0xaac) = defaultVal;

    // +0xab0..+0xab8: three ints zeroed (third group)
    *(int *)(this + 0xab0) = 0;
    *(int *)(this + 0xab4) = 0;
    *(int *)(this + 0xab8) = 0;

    // +0xabc: third group tail set to default
    *(int *)(this + 0xabc) = defaultVal;
}