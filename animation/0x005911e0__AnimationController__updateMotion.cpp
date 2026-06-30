// FUNC_NAME: AnimationController::updateMotion
void AnimationController::updateMotion(void* motionData, void* unknownObj, float deltaTime, undefined4 param5, uint flags, undefined4 param7)
{
    uint* pMotionFlags;
    int blendHandle;
    uint motionFlags;
    int blendIndex;
    char flagCheck;
    short shortID;
    int blendDataPtr;
    undefined4 motionInput;
    bool flagResult;
    float10 fVar10; // likely only used for float conversion
    float10 extraout_ST0;
    undefined4 local_20; // motionInput copy
    int local_1c; // blendHandle
    undefined4* pUnknownPtrArray[6]; // only index 0 used

    // +0x4 pointer in motionData, then +8
    pUnknownPtrArray[0] = (undefined4*)(*(int*)((char*)motionData + 4) + 8);

    // +0xc pointer in motionData
    int motionDataBase = *(int*)((char*)motionData + 0xc);

    motionFlags = *(uint*)(motionDataBase + 4);
    motionInput = *(undefined4*)(motionDataBase + 0x14);

    // +0x70 pointer in this, to blend data array?
    blendDataPtr = *(int*)((char*)this + 0x70);

    // Call to function that outputs blendHandle (local_1c) through passed address
    FUN_00573db0(&motionInput); // modifies local_1c via the struct? Actually takes address of motionInput, which is local_20? Wait, code: &local_20, but local_20 is separate. Actually the decompiler shows "FUN_00573db0(&local_20);" where local_20 is set from motionInput. So it takes address of local_20 variable. We'll adjust: local_20 = motionInput; then FUN_00573db0(&local_20); but we used local_20 as motionInput copy. So rename appropriately.
    // After call, local_1c (blendHandle) is set

    if (blendHandle == 0 || (blendIndex = *(int*)(blendHandle + 0x14), blendIndex < 0) || blendIndex >= *(int*)(blendDataPtr + 0x20))
    {
        blendDataPtr = 0;
    }
    else
    {
        blendDataPtr = *(int*)(blendDataPtr + 0x24) + blendIndex * 8;
    }

    // +0x74 short in this, animation ID?
    if (*(short*)((char*)this + 0x74) == -1)
    {
        if ((motionFlags & 0xff) < 10)
            shortID = *(undefined2*)(motionDataBase + 0x1c);
        else
            shortID = *(undefined2*)(motionDataBase + 0x10);
        *(short*)((char*)this + 0x74) = shortID;
    }

    FUN_00592960(motionDataBase, blendDataPtr);

    fVar10 = (float10)deltaTime;
    if ((flags & 0x10) == 0)
    {
        FUN_00581530(motionDataBase, this, deltaTime, param5);
        flagCheck = FUN_005817c0(deltaTime, flags);
        fVar10 = extraout_ST0;
        if (flagCheck != '\0')
        {
            pMotionFlags = (uint*)(*(int*)((char*)this + 0x7c) + 0x10);
            *pMotionFlags = *pMotionFlags | 2;
        }
    }

    motionInput = *pUnknownPtrArray[0];
    if (*(uint*)((char*)unknownObj + 4) <= (uint)(int)*(short*)((char*)motionData + 2))
    {
        pUnknownPtrArray[0] = (undefined4*)0x0;
        FUN_00591c00(pUnknownPtrArray);
        fVar10 = (float10)deltaTime;
    }

    uint animId;
    if ((motionFlags & 0xff) < 10)
        animId = *(uint*)(motionDataBase + 0x18);
    else
        animId = *(uint*)(motionDataBase + 8);

    if (*(char*)(*(int*)((char*)this + 0x7c) + 0x30) == '\0')
    {
        int tempPtr = *(int*)((char*)motionData + 0xc);
        if ((*(uint*)(tempPtr + 4) & 0xff) < 10)
            tempPtr = *(int*)(tempPtr + 8);
        else
            tempPtr = *(int*)(tempPtr + 0x18);
        flagResult = tempPtr != 0;
        if (!flagResult) goto LAB_0059133e;
    }
    flagResult = true;

LAB_0059133e:
    *(bool*)(*(int*)((char*)this + 0x7c) + 0x30) = flagResult;

    if ((flags & 4) != 0)
    {
        FUN_00592e20((float)fVar10, motionInput, param7, flags);
        return;
    }
    FUN_005929c0((float)fVar10, param5, animId, motionInput, param7, flags);
    return;
}