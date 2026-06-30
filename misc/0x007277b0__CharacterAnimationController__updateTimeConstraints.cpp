// FUNC_NAME: CharacterAnimationController::updateTimeConstraints
bool __fastcall CharacterAnimationController::updateTimeConstraints(int thisObj) // thisObj in ECX (__fastcall with 1 param)
{
    short boneCount;
    bool anyBoneFound;
    uint boneIndices[4]; // up to 4 bone indices
    float timeVar;
    float timeOffsetA;
    float timeOffsetB;
    float lowerBound;
    float upperBound;
    // Vector structs (x,y,z,w) for plane definition
    float plane1[4]; // x=0, y=lowerBound, z=0, w=constant
    float plane2[4]; // x=0, y=upperBound, z=0, w=constant
    int retCode;
    uint unknownResult;
    char local_29c[20]; // buffer for some call
    char local_170[284]; // buffer for other call
    char local_274[260]; // destination for thread-local copy
    char *destPtr;
    undefined **ppVtable;
    int copySize;
    int copyCount;
    char unknownFlag;

    timeVar = GetSomeTime(); // FUN_0054eb00 returns float (frame time?)

    // Get time offsets from globals (likely current animation phase or loop bounds)
    timeOffsetA = DAT_00e51868; // first offset
    timeOffsetB = DAT_00e5186c; // second offset

    if (*(byte *)(thisObj + 0x116) == 2) {
        timeOffsetA = DAT_00e51860; // different offsets for layer 2
        timeOffsetB = DAT_00e51864;
    }

    // Calculate time bounds for constraint planes
    lowerBound = (timeOffsetA + timeVar) - timeOffsetB;
    upperBound = timeOffsetB + timeVar;

    // Initialize first plane: (0, lowerBound, 0, constantW)
    plane1[0] = 0.0f;
    plane1[1] = lowerBound;
    plane1[2] = 0.0f;
    plane1[3] = _DAT_00d5780c; // likely 1.0f or some plane constant

    // Initialize second plane: (0, upperBound, 0, constantW)
    plane2[0] = 0.0f;
    plane2[1] = upperBound;
    plane2[2] = 0.0f;
    plane2[3] = _DAT_00d5780c;

    // Adjust planes using the time offset (e.g., clamp or transform)
    AdjustPlanes(plane1, plane2, timeOffsetB); // FUN_00a65bb0

    // Start some animation operation (maybe begin skeleton update)
    BeginAnimationOperation(); // FUN_00549bf0

    // Get current skeleton state into buffer
    GetCurrentSkeletonState(local_170); // FUN_00549cf0

    // Collect bone indices from the object's bone list
    boneCount = *(short *)(thisObj + 0xb4);
    for (int i = 0; i < boneCount; ++i) {
        boneIndices[i] = GetNextBoneIndex(); // FUN_0043b490
    }

    // Post animation message with bone indices (event 0x40102, subtype 0x20001)
    SendAnimationMessage(0x40102, 0x20001, boneIndices, boneCount); // FUN_00540bc0

    // Process result from animation message
    unknownResult = ProcessAnimationResult(local_29c); // FUN_00540cc0

    // Set up a callback/event structure for later execution
    destPtr = local_274;
    ppVtable = &PTR_LAB_00e3572c; // vtable pointer for some object
    copySize = -0x7ffffff0; // negative large number, used as flag? (maybe -16?)
    copyCount = 0;
    unknownFlag = 0;

    // Store something related to this object's animation state (offset +0x130)
    StoreAnimationState(thisObj + 0x130); // FUN_00549d40

    // Execute the stored event (0 parameters)
    ExecuteAnimationEvent(&ppVtable, 0); // FUN_00549ea0

    copySize = copySize; // actually was set from local_278, but we'll use the stored value
    anyBoneFound = (copyCount > 0);
    ppVtable = &PTR_LAB_00e3572c; // reset vtable pointer

    // If a copy size >= 0, do thread-local copy (debug logging?)
    if (copySize >= 0) {
        TlsGetValue(DAT_01139810); // TLS handle
        CopyDataToThreadLocal(local_274, copySize << 4, 0x17); // FUN_00aa26e0 maybe copies 23 bytes??
    }

    // Set vtable to another pointer (cleanup?)
    ppVtable = &PTR_LAB_00dcf968;

    // Finalize animation operation
    EndAnimationOperation(); // FUN_00549cb0

    return anyBoneFound; // true if any bone indices were retrieved
}