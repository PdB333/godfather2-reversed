// FUNC_NAME: PlayerAction::tryActivate

// Function address: 0x00783bf0
// Attempts to activate a player action (e.g., takedown, combat move).
// Returns 1 if activation just occurred (flag was not set), 0 if already active or random chance failed.

// Offsets in this (param_1):
// +0x0c: Pointer to owner character (e.g., Player or NPC)
// +0x20: Action animation state (used to start an animation)
// +0x24: Linked list head (next pointer) for active actions
// +0x28: Linked list previous pointer
// +0x38: Probability when param_3 == 0
// +0x3c: Probability when param_3 == 1
// +0x40: Some threshold float (compared to globals)
// +0x54: Handle/pointer to created effect object
// +0x58: Flags:
//        bit 1: action is active (isActivating)
//        bit 3: cleanup callback has been registered
// Offsets in owner character (+0xc):
// +0x1f5c: Some flag (set bit 0x40000000 during activation)
// +0x2690: Activation counter
// +0x26f8: Cleanup callback function pointer slot (8 bytes)
// +0x2700: Callback data (16 bytes)

byte __thiscall PlayerAction::tryActivate(int thisPtr, int* targetNode, int index)
{
    bool bHasValidTarget = false;
    float randomValue = 0.0f;
    int originalFlags = *(int*)(thisPtr + 0x58);
    int* characterPtr = *(int**)(thisPtr + 0x0c);

    // Check if target node is valid and has a specific property (hash 0x383225a1)
    if (targetNode != nullptr)
    {
        char result = (**(code**)(*targetNode + 0x10))(0x383225a1, &randomValue);
        if (result && randomValue != 0.0f)
        {
            bHasValidTarget = true;
        }
    }

    // Check if target is valid via another method (maybe distance, line of sight, etc.)
    char cVar7 = isTargetValid(targetNode);  // FUN_00785ee0

    // If the action is not already active (bit 1 clear)
    if ((originalFlags >> 1 & 1) == 0)
    {
        // Check global lock
        if (isGlobalLockActive() == false)
        {
            float threshold = *(float*)(thisPtr + 0x40);
            if (threshold == DAT_00d5ccf8 || threshold < DAT_01205228)
            {
                float baseProbability = 1.0f; natural constants - assume DAT_00d5780c is 1.0
                if (targetNode != nullptr)
                {
                    if (bHasValidTarget || cVar7 != 0)
                    {
                        int* component = getComponentByHash(targetNode, 0x55859efa); // e.g., WeaponComponent
                        if (component != nullptr && isComponentEnabled(*(int*)(component + 0x1ed4)) != 0)
                        {
                            baseProbability = getRandomFloat01();
                        }
                    }
                }
                float roll = ((float)rand() * DAT_00e44590);  // Global random factor
                float prob = (index == 0) ? *(float*)(thisPtr + 0x38) : *(float*)(thisPtr + 0x3c);
                if (roll < prob * baseProbability)
                {
                    goto LAB_00783d05;
                }
            }
        }
        return 0;
    }

LAB_00783d05:
    // Action activation logic
    // Check and set debug mode for some string (DAT_00e52468)
    if (isDebugMode(*(int*)(thisPtr + 0x0c), DAT_00e52468) == 0)
    {
        setDebugMode(*(int*)(thisPtr + 0x0c), DAT_00e52468);
    }

    // If no current animation state, set owner flags and play sound/effect
    if (*(int*)(thisPtr + 0x20) == 0 && (bHasValidTarget || cVar7 != 0))
    {
        // Set activation flag on owner
        int* ownerFlagPtr = (int*)(characterPtr + 0x1f5c / 4);
        *ownerFlagPtr |= 0x40000000;

        int* activationCounterPtr = (int*)(characterPtr + 0x2690 / 4);
        *activationCounterPtr = *activationCounterPtr + 1;

        // Play activation sound (if UI active and not in main menu)
        if (characterPtr != nullptr && isUIActive(DAT_0112a9fc) != 0)
        {
            unsigned int context = 0;
            int soundContext = getSoundContext(0, 0);
            playSoundEvent(0xc970896, 0, soundContext, context); // Likely sound hash
            releaseSoundContext();
        }

        // Start action animation
        if (startActionAnimation(thisPtr + 0x20) != 0)
        {
            int effect = createEffect(0x31, *(int*)(thisPtr + 0x0c), 0, 9, 0, 0, 1, 0, 2, 0, 0, 0, 0);
            *(int*)(thisPtr + 0x54) = effect;
            if (effect != 0)
            {
                setEffectTransform(effect, 1, DAT_00d5ccf8, DAT_00d5ccf8);
            }
        }
    }

    // Unlock player input lock if needed (from another system)
    int* playerPtr = getPlayerCharacter();
    if (playerPtr != nullptr && (*(uint*)(playerPtr + 0x5c) >> 0x13 & 1) != 0)
    {
        int* controller = getPlayerController(playerPtr);
        if (*(char*)(controller + 0x1a4) == 0)
        {
            setControllerInputLock(controller, -1);
        }
    }

    // If target was validated by hash, perform list insertion (scoped RAII)
    if (bHasValidTarget)
    {
        // Temporary list node on stack
        int** ppTempHead = &PTR_FUN_00e31e2c; // Some global list head
        int* listNode;
        if (characterPtr == nullptr)
        {
            listNode = nullptr;
        }
        else
        {
            listNode = characterPtr + 0x48 / 4; // offset 0x48
        }
        int oldNext = 0;
        if (listNode != nullptr)
        {
            oldNext = *(int*)(listNode + 4);
            *(int**)(listNode + 4) = &listNode; // circular? self-reference
        }
        int** tempPrev = &ppTempHead;
        int oldGlobal = DAT_0112af60;
        // Some initialization
        someInit(&oldGlobal, 0);
        if (listNode != nullptr)
        {
            removeFromList(&listNode);
        }
    }

    // Pause handling
    if (isPaused() != 0)
    {
        setPauseFlag(0x8000);
    }

    // Scoped list insertion into a global list (maybe "active actions")
    // Prepare stack node for scoped insertion
    int stackNext = 0;
    int stackPrev = 0;
    int stackDummy = 0;
    int** ppGlobalHead = &PTR_FUN_00d5dbbc; // Global action list head
    int* stackNode = nullptr;
    int oldGlobalNext = 0;
    byte stackPad = 0;
    float stackPad2 = DAT_01205228;
    int stackPad3 = 0x358412ab;

    if (targetNode != nullptr && targetNode + 0x12 != nullptr)
    {
        oldGlobalNext = targetNode[0x13];
        targetNode[0x13] = (int)&stackNode; // Link stack node into target's list
        stackNode = targetNode + 0x12;      // stackNode points to target's prev field
    }

    // Setup exception handler wrapper (try/catch-like)
    int exceptionData = DAT_0112ad8c;
    int** ppExcData = &ppGlobalHead;
    byte excPad = 0;
    int excContext = (characterPtr == nullptr) ? 0 : (characterPtr + 0x3c);
    wrapWithExceptionHandler(&exceptionData, excContext, 0);

    // Update this's action list head to point to target's prev field
    int** thisListHead = (int**)(thisPtr + 0x24);
    int* targetPrevField = (targetNode == nullptr) ? nullptr : (targetNode + 0x12);

    if (*thisListHead != targetPrevField)
    {
        if (*thisListHead != nullptr)
        {
            removeFromList(thisListHead);
        }
        *thisListHead = targetPrevField;
        if (targetPrevField != nullptr)
        {
            *(int*)(thisPtr + 0x28) = targetPrevField[1]; // old next?
            targetPrevField[1] = (int)thisListHead; // back-link?
        }
    }

    // Register cleanup callback if not already done (bit 3)
    if ((*(uint*)(thisPtr + 0x58) >> 3 & 1) == 0)
    {
        // Store callback function pointer and data in owner character
        char callbackFunction[8];
        *(int*)(callbackFunction) = (int)&actionCleanupCallback; // FUN_007832c0
        *(int*)(callbackFunction + 4) = thisPtr - 0x1c; // data?
        // Write to owner +0x26f8 (16 bytes)
        *(long long*)(characterPtr + 0x26f8 / 4) = *(long long*)callbackFunction;
        *(long long*)(characterPtr + 0x2700 / 4) = 0;
        // Additional setup
        *(undefined8*)(characterPtr + 0x2708 / 4) = 0x782af000000000; // packed (0, LAB_00782af0)
        *(int*)(thisPtr + 0x58) |= 8; // set bit 3
        int temp = thisPtr - 0x1c; // probably saved for cleanup
    }

    // Clean up stack node if it was inserted
    if (stackNode != nullptr)
    {
        removeFromList(&stackNode);
    }

    // Return whether action just became active (0) or was already active (1)?
    // originalFlags bit1: 0 -> return 1, 1 -> return 0
    return (byte)(~(originalFlags >> 1)) & 1;
}