// FUNC_NAME: WorldLightParameters::initFromConfig
void __thiscall WorldLightParameters::initFromConfig(void *this, uint configHandle)
{
    uint *lightStruct;
    uint value;
    uint idx;
    int *activeCountPtr;
    char keyBuf[68];

    idx = 0;
    activeCountPtr = (int *)((int)this + 0x14);
    *(uint *)((int)this + 4) = configHandle;
    *(int *)((int)this + 8) = 0;
    do {
        lightStruct = (uint *)((int)this + 0xc + *(int *)((int)this + 8) * 0x14);
        _sprintf(keyBuf, "%s[%d].type", "g_WorldLightParameters", idx);
        value = FUN_0060a580(configHandle, keyBuf);
        *lightStruct = value;
        _sprintf(keyBuf, "%s[%d].position", "g_WorldLightParameters", idx);
        value = FUN_0060a580(configHandle, keyBuf);
        lightStruct[1] = value;
        _sprintf(keyBuf, "%s[%d].color", "g_WorldLightParameters", idx);
        value = FUN_0060a580(configHandle, keyBuf);
        lightStruct[2] = value;
        _sprintf(keyBuf, "%s[%d].direction", "g_WorldLightParameters", idx);
        value = FUN_0060a580(configHandle, keyBuf);
        lightStruct[3] = value;
        _sprintf(keyBuf, "%s[%d].property", "g_WorldLightParameters", idx);
        value = FUN_0060a580(configHandle, keyBuf);
        lightStruct[4] = value;
        if (*activeCountPtr != 0) {
            *(int *)((int)this + 8) = *(int *)((int)this + 8) + 1;
        }
        activeCountPtr = activeCountPtr + 5;
        idx = idx + 1;
    } while (idx < 4);
    return;
}