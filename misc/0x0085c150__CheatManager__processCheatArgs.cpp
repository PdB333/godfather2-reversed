// FUNC_NAME: CheatManager::processCheatArgs
char CheatManager::processCheatArgs(int cheatId, int argCount, int argIndex) {
    if ((argIndex == 0) || (argIndex == 1)) {
        // Begin reading cheat parameters
        CheatManager::beginParamRead(cheatId, 0x7c32d73b);
        while (CheatManager::hasMoreParams()) {
            CheatManager::readInt32(); // skip param token
            uint paramType = CheatManager::getParamType();
            switch(paramType) {
            case 0: // float param
                CheatManager::readInt32();
                g_cheatFloat1 = *(float *)(g_paramBuffer + 8);
                break;
            case 1: // float param
                CheatManager::readInt32();
                g_cheatFloat2 = *(float *)(g_paramBuffer + 8);
                break;
            case 2: // float param
                CheatManager::readInt32();
                g_cheatFloat3 = *(float *)(g_paramBuffer + 8);
                break;
            case 3: // int param
                CheatManager::readInt32();
                g_cheatInt1 = *(uint *)(g_paramBuffer + 8);
                break;
            case 4: // int param
                CheatManager::readInt32();
                g_cheatInt2 = *(uint *)(g_paramBuffer + 8);
                break;
            case 5: // bool param
                CheatManager::readInt32();
                g_cheatBool1 = *(int *)(g_paramBuffer + 8) != 0;
                break;
            case 6: // string param
                CheatManager::readInt32ToBuffer(g_stringBuffer);
                CheatManager::processStringParam(g_stringBuffer);
                break;
            case 7: // uint param
                CheatManager::readInt32();
                g_cheatUint1 = *(uint *)(g_paramBuffer + 8);
                break;
            case 8: // float param with multiplier
                CheatManager::readInt32();
                g_cheatFloat4 = *(float *)(g_paramBuffer + 8) * g_globalFloatMultiplier;
                break;
            case 9: // float param with multiplier
                CheatManager::readInt32();
                g_cheatFloat5 = *(float *)(g_paramBuffer + 8) * g_globalFloatMultiplier;
                break;
            case 10: // first part of 2-int param
                CheatManager::readInt32();
                g_cheatPair1.first = *(uint *)(g_paramBuffer + 8);
                break;
            case 0xb: // second part of 2-int param
                CheatManager::readInt32();
                g_cheatPair1.second = *(uint *)(g_paramBuffer + 8);
                break;
            case 0xc: // first part of another pair
                CheatManager::readInt32();
                g_cheatPair2.first = *(uint *)(g_paramBuffer + 8);
                break;
            case 0xd: // second part with rounding
                CheatManager::readInt32();
                g_cheatPair2.second = (uint)round(*(float *)(g_paramBuffer + 8) * g_globalFloatMultiplier2);
            }
            CheatManager::endParamRead();
        }
        // Calculate derived values
        g_derivedResult = (g_cheatFloat3 - g_cheatFloat1) * g_cheatFloat2;
        g_normalizedResult = (g_globalBaseValue - g_derivedResult) / 
            ((g_globalBaseValue - g_cheatFloat1) - (g_cheatFloat3 - g_cheatFloat1));
    }
    if (argIndex == 0) {
        CheatManager::applyCheatResult();
    }
    return 1;
}