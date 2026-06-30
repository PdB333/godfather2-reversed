// Xbox PDB: EARS::Modules::BankHeistManager::PerBagUpdate
// FUNC_NAME: StatTracker::updateStat
void __fastcall StatTracker::updateStat(void* thisPtr) {
    int stateIndex = *(int*)((uintptr_t)thisPtr + 0x3d0);
    int state = *(int*)((uintptr_t)thisPtr + stateIndex * 0x30 + 0x34);
    uint value = *(int*)((uintptr_t)thisPtr + stateIndex * 0x30 + 0x20) / 10;

    if (state == 1) {
        statIncrement(0xc5d9c585, (float)(int)value, 0); // stat ID for "money earned"?
        *(int*)((uintptr_t)thisPtr + 0x3d8) += 1;
        float elapsed = (float)*(int*)((uintptr_t)thisPtr + 0x3d8);
        *(int*)((uintptr_t)thisPtr + 0x3e0) += value;
        if (*(int*)((uintptr_t)thisPtr + 0x3d8) < 0) {
            elapsed += 4294967296.0f; // ugly cast
        }
        float threshold = 0.0f;
        statGetValue(0x6c725335, &threshold); // stat ID for "some limit"
        if (threshold < elapsed) {
            statSetValue(0x6c725335, elapsed, 0);
        }
    } else if (state == 3) {
        *(int*)((uintptr_t)thisPtr + 0x3e4) += value;
    } else if (state == 0) {
        statIncrement(0xa25662c2, (float)(int)value, 0);
        *(int*)((uintptr_t)thisPtr + 0x3e4) += value;
    } else if (state == 2) {
        statIncrement(0x354e832f, (float)(int)value, 0);
        statIncrement(0xbcbcc88d, 1.0f, 0);
        *(int*)((uintptr_t)thisPtr + 1000) += value;
        *(int*)((uintptr_t)thisPtr + 0x3ec) += 1;
    }

    int postState = *(int*)((uintptr_t)thisPtr + (*(int*)((uintptr_t)thisPtr + 0x3d0) * 0x30) + 0x34);
    if (postState == 2 || postState == 0 || postState == 3) {
        int total = *(int*)((uintptr_t)thisPtr + 1000) + *(int*)((uintptr_t)thisPtr + 0x3e4);
        statSetInt(total); // updates some global stat?

        char buffer[32];
        sprintf_s(buffer, 32, "%06X.%06X", 
                  *(uint*)((uintptr_t)thisPtr + ( (*(int*)((uintptr_t)thisPtr + 0x3d0) + 1) * 0x30) ) & 0xffffff,
                  value & 0xffff);

        char* str = buffer;
        if (buffer[0] == '\0') str = "null";
        netSendMessage(0x53504750, 0x53574747, str); // FourCC "SPGP", "SWGG" (likely game events)
    }
}