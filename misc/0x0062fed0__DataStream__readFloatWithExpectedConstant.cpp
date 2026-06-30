// FUNC_NAME: DataStream::readFloatWithExpectedConstant
int __thiscall DataStream::readFloatWithExpectedConstant(void) {
    int* pCur = *(int**)((int)this + 0xC);      // +0xC: current read pointer
    int* pEnd = *(int**)((int)this + 0x8);      // +0x8: end of data pointer

    // Validate initial state: pointer must not be null, must be within bounds, and first value must be type 5 (maybe a tag)
    if ((pEnd <= pCur) || (pCur == nullptr) || (*pCur != 5)) {
        // Error: expected a table tag (5)
        pCur = (int*)reportError("table");       // FUN_00627ac0
        pEnd = extraout_ECX;                     // preserve ECX after call? (likely unchanged)
    }

    pCur += 2;  // skip the type tag and possibly another integer? (advance 8 bytes)

    // Validate again after advancing
    if ((pEnd <= pCur) || (pCur == nullptr)) goto end;
    int type = *pCur;
    if (type != 3) {
        if (type != 4) goto end;
        // Type 4: read a float from current stream position
        float temp;
        int ok = readNextFloat(&temp);  // FUN_00636850
        if (ok == 0) goto end;
        // Build a local structure to simulate an inline type+value pair
        int localType = 3;
        float localValue = temp;
        pCur = (int*)&localType;       // point pCur to local data (not usual but decompiled suggests)
    }

    // Extract float value from position pCur[1] (type 3: value is next int reinterpreted as float)
    float value = *(float*)(pCur + 1);
    if (value == g_expectedValue) {     // DAT_00e2b05c
        // Try to advance further to find a matching value
        while (true) {
            pCur = (int*)(*(int*)((int)this + 0xC) + 8); // +0xC again? This seems odd: reset to buffer start+8?
            if (*(int**)((int)this + 0x8) <= pCur) break;
            if (pCur == nullptr) break;
            int t = *pCur;
            if (t == 3) continue;
            if (t == 4) {
                int ok = readNextFloat(??); // but argument is missing? Actually the decompiled passes &iStack_10 (already local)
                if (ok == 0) break;
                continue;
            }
            break;
        }
        // If loop exits without finding, fall through
        reportError("number");  // PTR_s_number_00e2a8a8
    }

end:
    value = 0.0f;
    storeFloatValue((int)value);  // FUN_006286b0 (takes int but passes float as int? maybe store as int)
    return 0;
}