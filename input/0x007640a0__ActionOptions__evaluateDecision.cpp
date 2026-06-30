// FUNC_NAME: ActionOptions::evaluateDecision
void __thiscall ActionOptions::evaluateDecision(int actionIndex)
{
    // Get base pointer from this + 0x78 (likely a decision entry array)
    int* pBase = *reinterpret_cast<int**>(reinterpret_cast<char*>(this) + 0x78);
    if (pBase == nullptr) {
        return;
    }

    // Each decision entry is 0xC bytes, starting at offset 0x70 from the base
    int* entry = reinterpret_cast<int*>(reinterpret_cast<char*>(pBase) + 0x70 + actionIndex * 0xC);
    if (*entry == 0) {          // +0x00: enabled flag
        return;
    }

    int actionHandle = entry[2]; // +0x08: handle to action data
    if (actionHandle == 0) {
        return;
    }

    // Lookup weight data (hash 0xd206b9b0) – result stored but unused
    int unusedWeightResult = 0;
    bool weightLookupOk = (FUN_005fd340(*reinterpret_cast<short*>(actionHandle + 0x12), 0xd206b9b0, &unusedWeightResult) != 0);
    if (!weightLookupOk) {
        return;
    }

    // Lookup condition data (hash 0x2e8be078)
    int conditionData = 0;
    float* weightValuePtr = nullptr;
    bool conditionLookupOk = (FUN_005fd340(*reinterpret_cast<short*>(actionHandle + 0x12), 0x2e8be078, &conditionData) != 0);

    bool decisionResult = true;

    if (conditionLookupOk) {
        float threshold = 0.0f;
        // Check condition data validity: non-null pointer, data non-zero, type byte at +6 == 0x03
        if (weightValuePtr != nullptr && conditionData != 0 && *reinterpret_cast<char*>(conditionData + 6) == 0x03) {
            threshold = *weightValuePtr;
        }
        int randVal = _rand();
        // Compare threshold against random scaled by global factor
        if (threshold < static_cast<float>(randVal) * DAT_00e44590) {
            decisionResult = false;   // Random roll failed
        }
    }

    // Action trigger GUID (magic constants)
    struct {
        int a;
        int b;
        int c;
        int d;
    } actionGuid = { 0xbadbadba, 0xbeefbeef, 0xeac15a55, 0x91100911 };

    if (decisionResult && FUN_00751cf0(&actionGuid) != 0) {
        FUN_00446100(&actionGuid, 0);
    }
}