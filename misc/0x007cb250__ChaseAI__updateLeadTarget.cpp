// FUNC_NAME: ChaseAI::updateLeadTarget

void __thiscall ChaseAI::updateLeadTarget(void* thisPtr, int* callbackData) {
    char conditionFlag;
    int objA, objB, objC;
    int tempObj;
    float* pfVar5;
    bool isConditionB;
    float* pfVar7;
    int uVar8, uVar9, uVar11;
    float fVar10;
    int iVar2;
    float normX, normY, normZ;
    float leadX, leadY, leadZ;
    float diffX, diffY, diffZ;
    float vecX, vecY, vecZ;
    uint* flagsPtr;

    // Call the callback function pointer; return value is a message ID
    if ((**(int (__stdcall**)())(*callbackData))() != 0x27a0f69c) {
        return; // Not the expected message
    }

    // Obtain three objects (likely from pool)
    objA = FUN_00471610(); // First object
    objB = FUN_00471610(); // Second object (target?)
    objC = FUN_00471610(); // Third object (reference?)

    // Compute direction vector from objB to objC
    diffX = *(float*)(objC + 0x30) - *(float*)(objB + 0x30); // +0x30 = position.x
    diffY = *(float*)(objC + 0x34) - *(float*)(objB + 0x34); // +0x34 = position.y
    diffZ = *(float*)(objC + 0x38) - *(float*)(objB + 0x38); // +0x38 = position.z

    // Normalize the vector
    vecX = diffX;
    vecY = diffY;
    vecZ = diffZ;
    FUN_0056afa0(&vecX, &vecX); // Normalize in place
    normX = vecX;
    normY = vecY;
    normZ = vecZ;

    // Calculate lead position ahead of objA along the normalized direction
    leadX = normX * DAT_00d5ccf8 + *(float*)(objA + 0x30); // DAT_00d5ccf8 = lead distance
    leadY = normY * DAT_00d5ccf8 + *(float*)(objA + 0x34);
    leadZ = normZ * DAT_00d5ccf8 + *(float*)(objA + 0x38);

    // Create a new object (type 0x40122) at the lead position
    uVar8 = 0;
    uVar9 = 0x80000000;
    uVar11 = 0x40122;
    pfVar7 = &leadX;
    tempObj = FUN_00471610(pfVar7, 0x40122, 0x80000000, 0, 0);
    FUN_00542650(tempObj + 0x30, pfVar7, 0x40122, 0x80000000, 0, 0); // Set position

    // Update timers (probably frame time accumulation)
    fStack_5c += DAT_00d58cbc; // DAT_00d58cbc = frame time (dt)
    fStack_4c += DAT_00d58cbc;
    // Other stack initializations for debug/output structure
    uStack_ac = -1;
    uStack_a0 = -1;
    ppuStack_d0 = &PTR_FUN_00e32a8c; // Some callback table
    iStack_70 = 0;
    uStack_b0 = _DAT_00d5780c; // Probably a color or constant
    uStack_80 = 0;
    uStack_cc = _DAT_00d5780c;
    FUN_009e5ed0(auStack_60, &ppuStack_d0); // Possibly format debug string

    isConditionB = iStack_70 != 0;

    // Check for existence of sub-object (at offset +0x1b4) and evaluate condition
    if (*(int*)(thisPtr + 0x1b4) == 0) {
        iVar2 = 0;
    } else {
        iVar2 = *(int*)(thisPtr + 0x1b4) - 0x48; // Base pointer of sub-object
    }
    conditionFlag = FUN_007f8240(iVar2, DAT_00d5c454); // Check some global state
    fVar10 = _DAT_00d5cf70; // Default speed/scale

    if (conditionFlag == 0 || isConditionB) {
        // Use target object (objA) as new lead target
        iVar2 = FUN_00471610();
        fVar10 = DAT_00d58cbc; // Use frame time
        uVar11 = 1;
        uVar9 = 0;
        *(long long*)(thisPtr + 0x194) = *(long long*)(iVar2 + 0x30); // Store target position (x,y)
        *(float*)(thisPtr + 0x19c) = *(float*)(iVar2 + 0x38); // Store target z
        pfVar7 = &normX;
        iVar2 = FUN_00471610(pfVar7, 0, fVar10, 0, 1);
        pfVar5 = (float*)(iVar2 + 0x30);
    } else {
        // Use computed lead position as target
        uVar11 = 1;
        uVar9 = 0;
        uVar8 = 0;
        pfVar7 = &normX;
        pfVar5 = &leadX;
        *(long long*)(thisPtr + 0x194) = *(long long*)(&leadX); // Store lead x,y
        *(float*)(thisPtr + 0x19c) = leadZ; // Store lead z
    }

    // Apply the movement/steering based on target and direction
    FUN_00754d30(pfVar5, pfVar7, uVar8, fVar10, uVar9, uVar11);

    // Set flags: mark that target has been updated
    flagsPtr = (uint*)(thisPtr + 0x1d0);
    *flagsPtr |= 0x80000;
    if ((*flagsPtr & 0x60000) == 0) {
        *flagsPtr |= 0x200000;
    }
}