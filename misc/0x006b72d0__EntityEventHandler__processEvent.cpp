// FUNC_NAME: EntityEventHandler::processEvent
// Address: 0x006b72d0
// Handles various events (death, hit, damage, etc.) for an entity.
// Uses an event dispatch pattern where param_2 points to an event struct with type ID.
// The class has members at offsets: +0x158 (some component pointer), +0x254 (flags), +0xf4 (another pointer)
// A vtable-like structure is accessed at (this - 0x3c) for virtual calls.

void __thiscall EntityEventHandler::processEvent(void* thisPtr, int* eventData)
{
    float fVar1;
    float* pfVar2;
    int iVar3;
    undefined4 uVar4;
    undefined4 uVar5;
    float10 fVar6;
    float10 fVar7;
    float fStack_34;
    float fStack_30;
    float fStack_2c;
    undefined4 uStack_28;
    undefined1 auStack_24[4];
    undefined1 auStack_20[8];
    float fStack_18;

    // Increment reference count on event data? (likely an event object)
    FUN_008badd0(eventData);

    iVar3 = *eventData; // Event type ID
    if (iVar3 == EVENT_TYPE_DEATH) {
        *(uint*)((int)thisPtr + 0x254) |= 0x80000000; // Set death flag?
        FUN_004086d0(&EVENT_TYPE_DEATH); // Release event type constant? Or decrement ref?
        if (*(int*)((int)thisPtr + 0x158) != 0) {
            iVar3 = FUN_006b0ee0(*(int*)((int)thisPtr + 0x158)); // Get some damage manager?
            if (iVar3 != 0) {
                uVar4 = FUN_006b4860(); // Get something (maybe position or damage value)
                FUN_006b7240(uVar4, uVar4); // Apply damage to self? (two identical args)
            }
            FUN_00408680(&GLOBAL_0112a628); // Release global data
            FUN_00408680(&GLOBAL_0112a600);
            FUN_00408680(&GLOBAL_0112a610);
            return;
        }
    }
    else if (iVar3 == EVENT_TYPE_HIT) {
        // Hit event: check if the attacker's component matches our own component
        if (*(int*)(*(int*)(eventData[1] + 4) + 0x38) == *(int*)((int)thisPtr + 0x158)) {
            uVar4 = FUN_006b4860();
            uVar5 = FUN_006b4860(uVar4); // Possibly get two different values
            FUN_006b7240(uVar5, uVar4); // Apply damage with two values
            return;
        }
    }
    else if (iVar3 == EVENT_TYPE_DAMAGE) {
        iVar3 = eventData[1];
        // Check component match again
        if (*(int*)(*(int*)(iVar3 + 4) + 0x38) == *(int*)((int)thisPtr + 0x158)) {
            FUN_006b7240(*(float*)(iVar3 + 8), *(float*)(iVar3 + 0xc)); // Apply damage with direction?
            return;
        }
    }
    else if (iVar3 == EVENT_TYPE_STATE_CHANGE) {
        if ((*(uint*)((int)thisPtr + 0x254) >> 0x1d & 1) != 0) {
            *(uint*)((int)thisPtr + 0x254) &= 0xdfffffff; // Clear a flag
            if (*(void**)((int)thisPtr + 0xf4) != (void*)0x0) {
                // Call virtual function at vtable+0x44 with some ID (maybe stop effect)
                (**(code**)(**(int**)((int)thisPtr + 0xf4) + 0x44))(0xf86f4484, 4);
                return;
            }
        }
    }
    else if (iVar3 == EVENT_TYPE_PROXIMITY) {
        iVar3 = eventData[1];
        // Check that the event is not already handled (byte at +0x10) and component matches
        if ((*(char*)(iVar3 + 0x10) == '\0') &&
            (*(int*)(*(int*)(iVar3 + 4) + 0x38) == *(int*)((int)thisPtr + 0x158)) &&
            ((~*(byte*)((int)thisPtr + 0x254) & 1) != 0)) {
            // Get forward direction and position from virtual calls on some base class (vtable at this-0x3c)
            fVar6 = (float10)(**(code**)(*(int*)((int)thisPtr + -0x3c) + 0xc0))(); // Get something like forward vector length?
            fStack_34 = (float)fVar6;
            fVar6 = (float10)(**(code**)(*(int*)((int)thisPtr + -0x3c) + 0xc4))(); // Get another length?
            if ((float10)fStack_34 < fVar6 * (float10)FLOAT_00d5c458) { // Some threshold
                (**(code**)(*(int*)((int)thisPtr + -0x3c) + 0x104))(auStack_20); // Get world position?
                fVar1 = *(float*)(iVar3 + 0xc); // Radius or distance
                pfVar2 = *(float**)(iVar3 + 8); // Direction vector
                fStack_34 = *pfVar2;
                fStack_30 = pfVar2[1];
                fStack_2c = pfVar2[2];
                uStack_28 = 0;
                fVar6 = (float10)FUN_00414c30(auStack_24, &fStack_34); // Dot product? Actually distance squared from event point?
                fVar7 = (float10)(fVar1 * fStack_18); // fStack_18 is from the position vector (maybe z-component)
                if (fVar6 < fVar7 * fVar7) {
                    *(undefined1*)(iVar3 + 0x10) = 1; // Mark event as consumed
                }
            }
        }
    }
    return;
}