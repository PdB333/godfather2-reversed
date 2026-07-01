// FUNC_NAME: AIComponent::updateMovement

// Function address: 0x00897520
// Responsible for processing movement/wander behavior, including target selection and path smoothing.
// Uses EARS engine thread-local storage and object querying.

void __thiscall AIComponent::updateMovement(int thisPtr, undefined4 deltaTime, int *pAction, float *position)
{
    float fVar1;
    int iVar2;
    byte cVar3;
    undefined4 uVar4;
    int iVar5;
    undefined4 *puVar6;
    int iVar7;
    int *piVar8;
    int local_418;
    int local_414;
    float directionX;   // local_410
    float directionY;   // local_40c
    float directionZ;   // local_408
    float targetPosX;   // local_404
    float targetPosY;   // local_400
    float targetPosZ;   // local_3fc
    int *queryResult[2]; // local_3f8
    undefined **someVtable; // local_3f0
    undefined4 local_3ec;
    byte unknownHash[16]; // local_3e0
    undefined4 local_3d0;
    undefined4 local_3cc;
    undefined4 local_3c0;
    undefined4 local_3a0;
    undefined4 local_390;
    byte someBuffer[80]; // local_380
    undefined **stateMachineTable; // local_330[4] - actually array of 4 pointers?
    int objectArray;     // local_320
    int objectCount;     // local_31c
    uint objectIndexTemp; // uStack_318

    // Compute desired direction from action data.
    computeDirection(*pAction, &directionX);
    fVar1 = (float)pAction[1];
    iVar7 = *pAction;

    // Calculate target position: current position + direction * speed.
    targetPosX = directionX * fVar1 + position[0];
    targetPosY = directionY * fVar1 + position[1];
    targetPosZ = directionZ * fVar1 + position[2];

    // Movement interpolation flags based on action type.
    uVar4 = 2; // default movement mode
    if (iVar7 != 0x100) {
        uVar4 = 0x40002; // different mode for non-driving
    }
    // Smoothly move towards target.
    interpolateMovement(position, &targetPosX, uVar4, 0x4030000, 0, 0);

    if (iVar7 != 0x100) {
        // Path for non-driving (e.g., walking) actions.
        local_3cc = 0xffffffff;
        local_3c0 = 0xffffffff;
        local_390 = 0;
        local_3a0 = 0;
        someVtable = &PTR_FUN_00e32a8c; // external function table
        local_3d0 = g_externalData;     // __DAT_00d5780c
        local_3ec = g_externalData;
        initializeStateMachine(someBuffer, &someVtable, (byte)(pAction[2] & 1));
        finalizeMovementAction(pAction, deltaTime, position, &directionX, unknownHash);
    }
    else {
        // Path for driving (0x100) actions.
        iVar7 = 0;
        *(undefined4 *)(thisPtr + 0x54) = 0; // clear some member at +0x54
        debugLogSomething(); // FUN_0054af60
        initializeStateMachine(someBuffer, stateMachineTable, (byte)(pAction[2] & 1));
        getGlobalState(); // FUN_00a68720 (likely returns nothing important)
        if (0 < objectCount) {
            local_418 = 0;
            do {
                // Each object at fixed stride 0x60.
                iVar2 = *(int *)(local_418 + 0x50 + objectArray);
                if ((iVar2 != 0) && (isObjectValid(*(undefined4 *)(iVar2 + 0x1c), 1) == 1) &&
                    (*(char *)(iVar2 + 0x10) + iVar2 != 0)) {
                    createQuery(queryResult, 0x2001); // request query type 0x2001
                    piVar8 = (int *)0x0;
                    if (queryResult[0] != (int *)0x0) {
                        piVar8 = queryResult[0];
                    }
                    if (piVar8 != (int *)0x0) {
                        local_414 = 0;
                        cVar3 = (*(byte (__thiscall **)(int *, int *))(*(*piVar8) + 0x10))(0x77a210a2, &local_414);
                        if ((cVar3 != '\0') && (local_414 != 0)) {
                            puVar6 = (undefined4 *)getObjectField(&local_414, piVar8[7]);
                            *(undefined4 *)(thisPtr + 0x54) = *puVar6; // store result at +0x54
                            if (-1 < iVar7) {
                                iVar7 = iVar7 * 0x60 + objectArray; // compute final object index offset
                                goto LAB_008976aa;
                            }
                            break;
                        }
                    }
                }
                local_418 = local_418 + 0x60;
                iVar7 = iVar7 + 1;
            } while (iVar7 < objectCount);
        }
        iVar7 = 0;
LAB_008976aa:
        finalizeMovementAction(pAction, deltaTime, position, &directionX, iVar7); // pass found index or 0
        stateMachineTable[0] = &PTR_FUN_00e39c48;
        if (-1 < (int)objectIndexTemp) {
            // Thread-local storage cleanup.
            TlsGetValue(g_tlsIndex); // __DAT_01139810
            freeObjectArray(objectArray, (objectIndexTemp & 0x3fffffff) * 0x60, 0x17);
            return;
        }
    }
    return;
}