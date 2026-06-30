// FUNC_NAME: AnimationController::updateState
void AnimationController::updateState(void* animData, void* manager, float deltaTime, int param5, uint flags, int param7) {
    // animData points to some animation data structure
    int* dataBase = *(int**)((char*)animData + 0x4) + 2; // local_18[0] = (*(int*)(param_2+4) + 8)
    int* extraData = *(int**)((char*)animData + 0xC); // iVar2 = param_2+0xC
    uint uVar3 = *(uint*)(extraData + 1); // extraData[1] is flags or type
    int localState = *(int*)(extraData + 5); // extraData[0x14] -> local_20? Wait, local_20 is set from extraData+0x14 but then passed to FUN_00573db0
    // Actually local_20 = extraData[5] (since 0x14/4 =5)
    int animControllerPtr = *(int*)((char*)this + 0x70); // this->animControllerBase
    int local_1c;
    int resolvedIndex = resolveStateId(&localState, dataBase, &local_1c); // FUN_00573db0(&local_20)

    // Sanity check for resolved index
    int index = -1;
    if (local_1c != 0) {
        int indexPtr = *(int*)(local_1c + 0x14);
        if (indexPtr >= 0 && indexPtr < *(int*)(animControllerPtr + 0x20)) {
            index = indexPtr;
        }
    }
    int animEntryPtr = 0;
    if (index != -1) {
        animEntryPtr = *(int*)(animControllerPtr + 0x24) + index * 8;
    }

    // Initialize animation index if not set
    if (*(short*)((char*)this + 0x74) == -1) {
        short selectedAnim;
        if ((uVar3 & 0xFF) < 10) {
            selectedAnim = (short)*(undefined4*)(extraData + 7); // extraData[0x1c]
        } else {
            selectedAnim = (short)*(undefined4*)(extraData + 4); // extraData[0x10]
        }
        *(short*)((char*)this + 0x74) = selectedAnim;
    }

    // Update animation from data
    updateAnimFromData(extraData, animEntryPtr); // FUN_00592960(iVar2, iVar7)

    float currentTime = deltaTime;
    // Process animation if not in blend state (flag 0x10)
    if ((flags & 0x10) == 0) {
        processAnimBlend(extraData, this, deltaTime, param5); // FUN_00581530(iVar2, param_1, param_4, param_5)
        char blendResult = getBlendResult(deltaTime, flags); // FUN_005817c0(param_4, param_6)
        if (blendResult != 0) {
            uint* flagPtr = (uint*)(*(int*)((char*)this + 0x7C) + 0x10);
            *flagPtr |= 2;
        }
    }

    int temp = *dataBase; // local_20 = *local_18[0]
    // Check if sequence number is within range
    if (*(uint*)((char*)manager + 4) <= (uint)(int)*(short*)((char*)animData + 2)) {
        dataBase = nullptr;
        resetStateHandler(dataBase); // FUN_00591c00(local_18)
        currentTime = deltaTime;
    }

    // Determine next animation index from extraData
    int nextAnim;
    if ((*(uint*)(extraData + 1) & 0xFF) < 10) {
        nextAnim = *(int*)(extraData + 6); // extraData[0x18]
    } else {
        nextAnim = *(int*)(extraData + 2); // extraData[0x8]
    }

    bool hasNextAnim = false;
    if (*(char*)(*(int*)((char*)this + 0x7C) + 0x30) == 0) {
        int tempExtra = *(int*)((char*)animData + 0xC);
        int nextTemp;
        if ((*(uint*)(tempExtra + 4) & 0xFF) < 10) {
            nextTemp = *(int*)(tempExtra + 8);
        } else {
            nextTemp = *(int*)(tempExtra + 0x18);
        }
        if (nextTemp != 0) {
            hasNextAnim = true;
        }
    } else {
        hasNextAnim = true;
    }
    *(char*)(*(int*)((char*)this + 0x7C) + 0x30) = (char)hasNextAnim;

    // Branch based on flags
    if ((flags & 4) != 0) {
        playAnimTransition(currentTime, localState, param7, flags); // FUN_00592e20
        return;
    }
    playAnimState(currentTime, param5, nextAnim, localState, param7, flags); // FUN_005929c0
}

// Note: The function signatures of callees are approximated. Actual implementations may differ.
// This reconstruction focuses on readability and alignment with game logic patterns.