// FUNC_NAME: AnimationCurve::evaluatePoint
// A function that evaluates a point on an animation curve given input parameters and mode flags.
// Uses a keyframe array and interpolates between keyframes, handling wrap/ping-pong modes.

void __thiscall AnimationCurve::evaluatePoint(AnimationCurve* this, int outValue, CurveData* curveData, KeyframeArray* keyframes, float inX, float inY, uint mode, int extraParam)
{
    short currentKeyIndex;
    short nextKeyIndex;
    CurveState* curveState; // iVar3
    uint currentIndex;
    int* tempArray;
    bool swapCoords;
    int* keyframeData;
    float lerpFactor;
    int* tempPtr;
    float fVar10;
    float fVar11;
    float fVar12;
    int* localPtr;

    keyframeData = keyframes;
    tempPtr = (int*)0x0;
    curveState = *(CurveState**)(curveData + 4); // +0x04
    fVar11 = inX;
    fVar12 = inY;
    localPtr = this;

    // Determine if we should skip main interpolation based on mode and input order
    if (((mode >> 1 ^ mode) & 1) == 0) {
        if ((0.0 <= inY) || (inX < 0.0)) {
            swapCoords = false;
        } else {
            swapCoords = true;
        }
        if ((inY <= inX) && (!swapCoords)) goto LAB_0058d332;
    } else if (inX <= inY) goto LAB_0058d332;

    // Get current index from curve state
    currentIndex = *(uint*)(curveState + 4); // +0x04
    // Ensure keyframe array has capacity
    if ((uint)keyframes->size <= currentIndex) {
        keyframeData = (KeyframeArray*)0x0;
        FUN_00591c00(&keyframeData); // reallocate array
    }
    keyframeData = keyframes->data[currentIndex]; // fetch keyframe at currentIndex
    currentIndex = *(uint*)(curveState + 4);
    float fVar8 = *(float*)(curveState + 0xc); // end value?
    float fVar10 = *(float*)(curveState + 0x8); // start value?
    
    if (fVar8 < fVar10 || fVar8 == fVar10) {
        // Use start value
        if ((uint)keyframes->size <= currentIndex) {
            localPtr = (int*)0x0;
            FUN_00591c00(&localPtr);
        }
        tempPtr = (int*)0x0;
        keyframes->data[currentIndex] = *(float*)(curveState + 0x8);
        fVar11 = inX;
        fVar12 = inY;
    } else {
        // Interpolate between start and end
        if ((uint)keyframes->size <= currentIndex) {
            localPtr = (int*)0x0;
            FUN_00591c00(&localPtr);
        }
        tempPtr = (int*)0x0;
        int baseArray = keyframes->data;
        float startVal = *(float*)(curveState + 0x8);
        float endVal = *(float*)(curveState + 0xc);
        float step = (endVal - startVal);
        FUN_00593700(); // some helper, may compute step size or clamp
        // Calculate interpolated value with offset constant (DAT_00e2b1a4 likely 1.0f)
        keyframes->data[currentIndex] = fVar8 * (step + DAT_00e2b1a4) + startVal;
        fVar11 = inX;
        fVar12 = inY;
    }

    // Further work with keyframe arrays and short indices from curveData
    currentIndex = *(uint*)(curveState + 4);
    if ((uint)keyframes->size <= currentIndex) {
        localPtr = tempPtr;
        FUN_00591c00(&localPtr);
        tempPtr = (int*)0x0;
        fVar11 = inX;
        fVar12 = inY;
    }
    float currentVal = keyframes->data[currentIndex];
    if (currentVal != (float)keyframeData) // comparing float to pointer cast, likely meant as identity check
    {
        currentKeyIndex = *(short*)(curveData + 2); // +0x02
        if ((uint)keyframes->size <= (uint)(int)currentKeyIndex) {
            localPtr = tempPtr;
            FUN_00591c00(&localPtr);
            tempPtr = (int*)0x0;
            fVar11 = inX;
            fVar12 = inY;
        }
        nextKeyIndex = *(short*)(curveData + 2);
        localPtr = (int*)(keyframes->data[currentKeyIndex] / (currentVal + DAT_00e2b1a4));
        if ((uint)keyframes->size <= (uint)(int)nextKeyIndex) {
            keyframeData = tempPtr;
            FUN_00591c00(&keyframeData);
            tempPtr = (int*)0x0;
            fVar11 = inX;
            fVar12 = inY;
        }
        currentKeyIndex = *(short*)(curveData + 2);
        localPtr = (int*)((keyframes->data[nextKeyIndex] + DAT_00e2b1a4) * (float)localPtr);
        if ((uint)keyframes->size <= (uint)(int)currentKeyIndex) {
            keyframeData = tempPtr;
            FUN_00591c00(&keyframeData);
            tempPtr = (int*)0x0;
            fVar11 = inX;
            fVar12 = inY;
        }
        keyframes->data[currentKeyIndex] = (int*)localPtr; // store modified value
    }

LAB_0058d332:
    // Post-processing: wrap input values based on step size
    currentKeyIndex = *(short*)(curveData + 2);
    if ((uint)keyframes->size <= (uint)(int)currentKeyIndex) {
        keyframeData = tempPtr;
        FUN_00591c00(&keyframeData);
        tempPtr = (int*)0x0;
        fVar11 = inX;
        fVar12 = inY;
    }
    int baseArray = keyframes->data;
    nextKeyIndex = *(short*)(curveData + 2);
    if ((uint)keyframes->size <= (uint)(int)nextKeyIndex) {
        keyframeData = tempPtr;
        FUN_00591c00(&keyframeData);
        fVar11 = inX;
        fVar12 = inY;
    }
    float fVar8 = keyframes->data[currentKeyIndex] / (keyframes->data[nextKeyIndex] + DAT_00e2b1a4);
    
    // Wrap fVar11 and fVar12 modulo step
    if (fVar8 == DAT_00e2b1a4) {
        inX = fVar11 - (float)(int)fVar11;
    } else {
        float step = fVar8 - DAT_00e2b1a4;
        if (step < fVar11) {
            inX = fVar11 - (float)(int)(fVar11 / step) * step;
        }
    }
    if (fVar8 == DAT_00e2b1a4) {
        inY = fVar12 - (float)(int)fVar12;
    } else {
        float step = fVar8 - DAT_00e2b1a4;
        if (step < fVar12) {
            inY = fVar12 - (float)(int)(fVar12 / step) * step;
        }
    }

    // Call the actual evaluator with wrapped inputs
    FUN_0058afb0(outValue, curveData, keyframes, inX, inY, mode, extraParam);
    return;
}