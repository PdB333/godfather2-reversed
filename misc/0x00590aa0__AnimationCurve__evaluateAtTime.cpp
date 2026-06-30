// FUNC_NAME: AnimationCurve::evaluateAtTime
float AnimationCurve::evaluateAtTime(void* curveContext, CurveData* curveData, KeyframeList* keyList)
{
    float keyValue;
    uint32_t index;
    KeyframeList* list;
    float fVar4;
    float fVar5;

    list = keyList;
    validateCurve(curveContext, curveData, keyList);  // FUN_00591440

    // Obtain index from curve data structure (offset +0x4 -> object +0xc)
    index = *(uint32_t*)(*(int*)((char*)curveData + 4) + 0xc);

    // Bounds check: if keyCount <= index, trigger assertion
    if ((uint32_t)list->keyCount <= index) {
        keyList = nullptr;
        assertFail(&keyList);  // FUN_00591c00
    }

    // Read key value from array at given index
    keyValue = *(float*)((uintptr_t)list->keyArray + index * 4);

    // If interpolation mode is less than 2 (constant?), return a global constant
    if (*(char*)((char*)curveData + 1) < 2) {
        return (float10)kCurveConstant;  // DAT_00e2b1a4
    }

    fVar4 = keyValue;
    getPreviousOrBaseValue();  // FUN_00591160 (modifies some state)
    keyList = (KeyframeList*)(uintptr_t)fVar4;  // Reinterpret float as pointer (bitcast)
    getPreviousOrBaseValue();  // FUN_00591160

    if (keyValue <= 0.0f) {
        return (float10)(float)(uintptr_t)keyList;  // Return original key value
    }

    fVar5 = fVar4;
    if ((keyValue < kCurveConstant) && (fVar5 = (float)(uintptr_t)keyList, (float)(uintptr_t)keyList != fVar4)) {
        // Perform linear interpolation between two values
        return (float10)((fVar4 - (float)(uintptr_t)keyList) * keyValue + (float)(uintptr_t)keyList);
    }
    return (float10)fVar5;
}