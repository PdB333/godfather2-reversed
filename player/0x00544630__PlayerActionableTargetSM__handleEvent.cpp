// FUNC_NAME: PlayerActionableTargetSM::handleEvent
void __thiscall PlayerActionableTargetSM::handleEvent(void* thisPtr, void* eventData) {
    FUN_00542b60(eventData); // base class update with event data

    // +0x198 vtable: isActive() - check if state machine is active
    bool isActive = (**(code**)(*(int*)thisPtr + 0x198))();
    if (!isActive) {
        // Look up interaction manager by hash 0x33a16735 ("InteractionManager")
        int* manager = FUN_004b9ca0(eventData, 0x33a16735);
        int* targetList = nullptr;
        if (manager != nullptr) {
            targetList = *(int**)(manager + 0x14); // +0x14 offset to container
        }
        if (targetList != nullptr) {
            targetList = *(int**)(targetList + 8); // +8 offset to array
            int index = *(int*)(targetList + 0xc); // +0xc element count
            int* selectedTarget = nullptr;
            // Iterate over target list in reverse
            do {
                index--;
                if (index < 0) goto find_target_done;
                selectedTarget = *(int**)(*(int*)(targetList + 8) + index * 4); // array of pointers
                // +0x24c vtable: isValidTarget(ptr)
                bool isValid = (**(code**)(*(int*)thisPtr + 0x24c))(selectedTarget);
            } while (!isValid);
find_target_done:
            if (selectedTarget != nullptr) {
                // +0x18 vtable: getTargetHandle()
                int targetHandle = (**(code**)(*(int*)selectedTarget + 0x18))();
                *(int*)((int)thisPtr + 0x2E8) = targetHandle; // +0x2E8 = this+0xba
                // Attach component to target (slot 5)
                FUN_00556c80(selectedTarget, thisPtr, 5);
                // Set user data tag: (uint)(this+0xbc) >> 2 | 0xC0000000
                *(uint*)(targetHandle + 0x2C) = ((uint)((int)thisPtr + 0x2F0) >> 2) | 0xC0000000;
                FUN_0043b490();
                FUN_009f01f0(0x2001, thisPtr, 0); // event dispatch
                FUN_009f01a0();
            }
        }
        if (*(int*)((int)thisPtr + 0x2E8) == 0) { // no target handle yet
            int newTarget = FUN_005627a0(); // create default target
            *(int*)((int)thisPtr + 0x2E8) = newTarget;
            FUN_00556ab0(0, 0, thisPtr, 5, 0xFFFFFFFF); // attach default target to slot 5
            *(uint*)(newTarget + 0x2C) = ((uint)((int)thisPtr + 0x2F0) >> 2) | 0xC0000000;
            FUN_0043b490();
            FUN_009f01f0(0x2001, thisPtr, 0);
            FUN_009f01a0();
        }
        if (*(int*)((int)thisPtr + 0x2E8) != 0) {
            // +0x96 offset in target: clear some field
            *(short*)(*(int*)((int)thisPtr + 0x2E8) + 0x96) = 0;
        }
        if (*(int*)((int)thisPtr + 0x2E8) != 0) {
            FUN_009f4240(4, 1, 0);
            FUN_009f3cc0(2);
        }
    }

    // Parse event data into local variables
    // The following is a complex iterator over a data structure (likely a property bag or message)
    // Uses stack-based binary tree iterator pattern
    // After parsing, the extracted values are stored into the object at +0x360 (this+0xd8)
    int* parsedVal1 = DAT_00e39f98; // global
    int* parsedVal2 = DAT_00e446f4;
    int* parsedVal4 = DAT_00e39f98;
    int* parsedVal3 = DAT_00e2e714;
    FUN_0043aff0(eventData, 0x197C1972); // deserialize helper

    // Iterator state variables (stack)
    // This is a simplified representation of the loop; actual code handles tree traversal
    // We assume the loop extracts four values: parsedVal1..parsedVal4
    // The loop terminates when the iterator is exhausted
    // After the loop, the values are stored in local variables (simplified here)
    // In the original, they are assigned during the switch cases (0xb,0xc,0xd,0xe,0xf)
    // For brevity, we keep the extracted values as they are

    // +0x238 vtable: processParsedData(eventData)
    (**(code**)(*(int*)thisPtr + 0x238))(eventData);
    // Call another update method (maybe apply parsed data)
    FUN_00546010(thisPtr);

    // Check active again
    bool active = (**(code**)(*(int*)thisPtr + 0x198))();
    if (!active) {
        // +0x244 vtable: postUpdate()
        (**(code**)(*(int*)thisPtr + 0x244))();
        if (*(int*)((int)thisPtr + 0x390) != 0) { // +0x390 = this+0xe4
            (**(code**)(*(int*)thisPtr + 0x240))(); // +0x240 vtable: some update
        }
    } else {
        FUN_009f2000(); // if active, do something else
    }

    if (*(int*)((int)thisPtr + 0x360) != 0) { // +0x360 = this+0xd8
        // Write parsed values into structure at offset +0xd8
        *(void**)(*(int*)((int)thisPtr + 0x360) + 0xFC) = (void*)*(int*)&unaff_EBX; // unaff_EBX is a global register value (likely int)
        *(int**)(*(int*)((int)thisPtr + 0x360) + 0x100) = parsedVal1;
        *(int**)(*(int*)((int)thisPtr + 0x360) + 0xF0) = parsedVal2;
        *(int**)(*(int*)((int)thisPtr + 0x360) + 0xF4) = parsedVal3;
        *(int**)(*(int*)((int)thisPtr + 0x360) + 0xF8) = parsedVal4;
    }
}