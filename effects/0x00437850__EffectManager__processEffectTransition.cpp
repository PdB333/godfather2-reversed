// FUNC_NAME: EffectManager::processEffectTransition
int __thiscall EffectManager::processEffectTransition(void) {
    // this +0x08 : mEffectListEnd (pointer to end of effect list)
    // this +0x0C : mCurrentEffect (pointer to current effect entry)
    uint roundedVal;
    int validCheck;
    longlong *scratch;
    int *nextEntry;
    float effectValue;
    float interpolated;

    int *currentEntry = *(int **)(this + 0xC);
    float resultValue = 0.0f;

    // Bounds and null check
    if (*(int **)(this + 8) <= currentEntry) {
        return 0;
    }
    if (currentEntry == (int *)0x0) {
        return 0;
    }

    // Check effect type (3 = start? 4 = end? need validation)
    if (*currentEntry != 3) {
        if (*currentEntry != 4) {
            return 0;
        }
        // Type 4 requires external validity check
        validCheck = FUN_00636850(&scratch);
        if (validCheck == 0) {
            return 0;
        }
    }

    // Fetch effect value at offset +4 (e.g., lifetime or interpolation factor)
    longlong *currentPtr = *(longlong **)(this + 0xC);
    if ((currentPtr < *(longlong **)(this + 8)) && (currentPtr != (longlong *)0x0)) {
        if ((int)*currentPtr != 3) {
            if (((int)*currentPtr != 4) || (validCheck = FUN_00636850(&scratch), validCheck == 0))
                goto skipFetch;
            currentPtr = &scratch;
        }
        effectValue = *(float *)((int)currentPtr + 4);
    } else {
skipFetch:
        effectValue = 0.0f;
    }

    // Prepare next entry pointer
    nextEntry = (int *)(*(int *)(this + 0xC) + 8); // next entry at offset +8 of current (likely next pointer)
    scratch = (longlong *)ROUND(effectValue);
    roundedVal = (uint)scratch;

    // Check if the next entry exists and is valid
    if (((nextEntry < *(int **)(this + 8)) && (nextEntry != (int *)0x0)) &&
        ((*nextEntry == 3 || ((*nextEntry == 4 && (validCheck = FUN_00636850(&scratch), validCheck != 0)))))) {
        float fVar5 = (float)FUN_006259b0(this, 2); // get interpolation parameter (e.g., progress)
        interpolated = fVar5;
        if (0.0f < fVar5) {
            effectValue = DAT_00e2b050; // global max lifetime/value
            if (interpolated < DAT_00e2b050) goto apply;
        } else {
            effectValue = 0.0f;
        }
        interpolated = effectValue;
    }
apply:
    if (roundedVal < 2) {
        FUN_00458370(interpolated); // apply modified value (e.g., alpha, scale)
    }
    return 0;
}