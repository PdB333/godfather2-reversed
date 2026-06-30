// FUNC_NAME: Sentient::allocateAndExecuteTask

void __fastcall Sentient::allocateAndExecuteTask(Sentient* thisPtr)
{
    ActionData* pAction = *(ActionData**)(thisPtr + 8);
    short actionType = *(short*)(pAction + 2);
    if (actionType != 0x50) {
        (**(code**)(*DAT_01205590 + 4))(); // assert or error handler
    }

    TaskManager* pTaskManager = *(TaskManager**)(thisPtr + 0x1bc);

    // Generate a 12-byte identifier from action data fields
    // Likely used to match tasks to pending actions
    char localId[12];
    (**(code**)(*DAT_012055a8 + 0x34))(
        *(undefined4*)(pAction + 0x40),
        *(undefined4*)(pAction + 0x44),
        *(undefined4*)(pAction + 0x48),
        localId);

    // Allocate a task slot from the free list
    int taskIndex = *(int*)(pTaskManager + 0x1c); // free list head
    if (taskIndex == -1) {
        (**(code**)(*DAT_01205590 + 4))(); // no free slots -> error
    }
    else {
        // Update free list: pop head
        *(int*)(pTaskManager + 0x1c) = *(int*)(*(int*)(pTaskManager + 0x18) + taskIndex * 4);
        // Mark slot as in-use (-2 sentinel)
        *(int*)(*(int*)(pTaskManager + 0x18) + taskIndex * 4) = -2;
        // Start the task object (vtable+0x54)
        (**(code**)(*(int*)(*(int*)(pTaskManager + 0x14) + taskIndex * 4) + 0x54))();
    }

    // Store the allocated task index in the per-object task array
    // Array: m_taskIndices at offset 0x59, indexed by m_numTasks at offset 0x58
    uint8_t numTasks = *(uint8_t*)(thisPtr + 0x58);
    *(char*)(thisPtr + 0x59 + numTasks) = (char)taskIndex;

    // Verify slot is still -2 (should be after allocation)
    if (*(int*)(*(int*)(pTaskManager + 0x18) + taskIndex * 4) != -2) {
        (**(code**)(*DAT_01205590 + 4))();
    }

    // Get the task object pointer for the allocated slot
    int* pTaskObject = *(int**)(*(int*)(pTaskManager + 0x14) + taskIndex * 4);
    if (pTaskObject == nullptr) {
        (**(code**)(*DAT_01205590 + 4))();
        return;
    }

    // Prepare parameters for the "can execute" check
    bool bFlag38 = *(int*)(pAction + 0x38) != 0;
    bool bFlag3C = *(int*)(pAction + 0x3C) != 0;
    int paramStack; // local variable for output
    // vtable+0x50: canExecuteTask(taskAction, actionPos, this, action38, bFlag38, bFlag3C, &paramStack)
    bool canExecute = (**(code**)(*pTaskObject + 0x50))(
        pAction + 4,
        pAction + 0x14,
        thisPtr,
        *(undefined4*)(pAction + 0x34),
        bFlag38,
        bFlag3C,
        &paramStack);

    if (!canExecute) {
        // If task cannot be executed now, deallocate the slot
        int* slotArray = *(int**)(pTaskManager + 0x18);
        if (slotArray[taskIndex] != -2) {
            (**(code**)(*DAT_01205590 + 4))();
        }
        if (slotArray[taskIndex] == -2) {
            // Return slot to free list
            slotArray[taskIndex] = pTaskManager->freeListHead;
            pTaskManager->freeListHead = taskIndex;
        }
        return;
    }

    // Task executed successfully; increment task counter and possibly store previous task
    if (numTasks != 0) {
        uint8_t prevTaskIndex = *(uint8_t*)(thisPtr + 0x58 + numTasks); // array at offset 0x58? overlaps?
        int* otherSlotArray = *(int**)(pTaskManager + 0x18);
        if (otherSlotArray[prevTaskIndex] != -2) {
            (**(code**)(*DAT_01205590 + 4))();
        }
        // Store pointer to the previous task (for chaining?)
        *(int*)(pTaskManager + 0x78) = *(int*)(*(int*)(pTaskManager + 0x14) + prevTaskIndex * 4);
        *(uint8_t*)(thisPtr + 0x58) = numTasks + 1;
    }
    else {
        // No previous task, clear the pointer
        *(int*)(pTaskManager + 0x78) = 0;
        *(uint8_t*)(thisPtr + 0x58) = 1;
    }
}