// FUNC_NAME: StoreEffectParameters
void StoreEffectParameters(uint32_t* pData) {
    // Copy 8 dwords (32 bytes) from input to global effect data buffer
    g_EffectDataBuffer[0] = pData[0];
    g_EffectDataBuffer[1] = pData[1];
    g_EffectDataBuffer[2] = pData[2];
    g_EffectDataBuffer[3] = pData[3];
    g_EffectDataBuffer[4] = pData[4];
    g_EffectDataBuffer[5] = pData[5];
    g_EffectDataBuffer[6] = pData[6];
    g_EffectDataBuffer[7] = pData[7];

    // Check if current rendering state matches a specific structure and effect type
    if (g_pCurrentState == &g_StateStruct && 
       (g_EffectType == g_EffectTypeConstant1 || 
        g_EffectType == g_EffectTypeConstant2 || 
        g_EffectType == g_EffectTypeConstant3)) {
        // Apply the effect with stored data
        FUN_0060ab00(g_EffectType, g_EffectExtraData, &g_EffectDataBuffer, 8);
    }
}