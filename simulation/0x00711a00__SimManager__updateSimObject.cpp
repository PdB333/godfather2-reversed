// FUNC_NAME: SimManager::updateSimObject

/*
 * Function: 0x00711a00
 * Role: Updates a simulation object (ghost or NPC) - part of EARS SimManager
 * Handles local vs remote interpolation/simulation based on ghost state.
 */

void __thiscall SimManager::updateSimObject(int thisPtr, int param2, int objectPtr)
{
    char cVar1;
    int baseFrom4, baseFromC, iVar2, iVar5;
    int *piVar4;
    int unaff_EDI; // from register EDI - likely a related object pointer (e.g., Controller or InputState)
    int returnAddr; // unaff_retaddr - possibly a return address or register (EAX?)
    float fVar6;
    int uVar7;
    undefined4 *puVar8;

    iVar5 = objectPtr;

    // Validate object structure: check pointers at +0x4 and +0xC are non-null and not sentinel 0x48
    if ( (objectPtr != 0) &&
         (*(int*)(objectPtr + 0x4) != 0) && (*(int*)(objectPtr + 0x4) != 0x48) &&
         (*(int*)(objectPtr + 0xC) != 0) && (*(int*)(objectPtr + 0xC) != 0x48) )
    {
        // Get base object from pointer at +0x4 (subtract 0x48 header size)
        if (*(int*)(objectPtr + 0x4) == 0)
            piVar4 = (int*)0x0;
        else
            piVar4 = (int*)(*(int*)(objectPtr + 0x4) - 0x48);

        objectPtr = 0; // reuse temp

        // Virtual call on base object at vtable+0x10 - likely RTTI or state check with magic constant
        cVar1 = (**(code**)(*piVar4 + 0x10))(0x55859efa, &objectPtr);

        if ( (cVar1 != '\0') && (returnAddr != 0) )
        {
            cVar1 = isObjectIdValid(returnAddr); // FUN_0072f180
            if (cVar1 == '\0')
            {
                // Try the other pointer at +0xC
                if (*(int*)(iVar5 + 0xC) == 0)
                    baseFromC = 0;
                else
                    baseFromC = *(int*)(iVar5 + 0xC) - 0x48;

                cVar1 = isObjectIdValid(baseFromC);
                if (cVar1 == '\0')
                    return;
            }

            // Determine which base object to use: prefer the one that fails isValid? Logic is ambiguous.
            if (*(int*)(iVar5 + 0xC) == 0)
                baseFromC = 0;
            else
                baseFromC = *(int*)(iVar5 + 0xC) - 0x48;

            cVar1 = isObjectIdValid(baseFromC);
            if (cVar1 == '\0')
                iVar5 = *(int*)(iVar5 + 0xC); // use raw pointer from +0xC
            else
                iVar5 = *(int*)(iVar5 + 0x4); // use raw pointer from +0x4

            if (iVar5 == 0)
                iVar5 = 0;
            else
                iVar5 = iVar5 - 0x48; // adjust to base object

            // Virtual call on thisPtr+4's vtable at +0xBC - likely a feasibility check (e.g., isVisible, shouldUpdate)
            fVar6 = (float)(**(code**)(**(int**)(thisPtr + 0x4) + 0xBC))(iVar5);

            if (fVar6 != 0.0f)
            {
                iVar2 = isGhostedLocal(iVar5); // FUN_0071ce70 - returns nonzero if ghost is local

                if (iVar2 == 0)
                {
                    // Remote object: interpolate from cache
                    int transformPtr = getTransformFromCache(); // FUN_0077dd80 - returns pointer to global transform
                    int vtableFromThisC = **(int**)(thisPtr + 0xC); // Get vtable pointer from this+0xC
                    puVar8 = &stack0xfffffffc; // stack buffer for interpolation output
                    uVar7 = 0;
                    fVar6 = (float)getCurrentTime(transformPtr); // FUN_00712ef0
                    cVar1 = (**(code**)(vtableFromThisC + 0x18))(iVar5, 0, fVar6, 0, puVar8); // InterpolateSimObject

                    int localFlag = DAT_00d5ccf8; // global state
                    if (cVar1 != '\0')
                        localFlag = unaff_EDI;

                    iVar2 = interpolateSimObject(iVar5, localFlag); // FUN_007112c0
                }
                else
                {
                    // Local object: apply input and simulate
                    cVar1 = applySimInput(unaff_EDI); // FUN_0071c320 - applies input from controller/AI
                    int localFlag = DAT_00d5ccf8;
                    if (cVar1 != '\0')
                        localFlag = unaff_EDI;

                    simulateObject(*(undefined4*)(thisPtr + 0x4), iVar5, localFlag); // FUN_0071c720
                }

                updateDebugVisuals(iVar2, 0); // FUN_00716720 - update shadow/hud
            }
        }
    }
    return;
}