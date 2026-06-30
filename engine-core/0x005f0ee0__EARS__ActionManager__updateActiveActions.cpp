// FUNC_NAME: EARS::ActionManager::updateActiveActions
void EARS::ActionManager::updateActiveActions(int* listHead, int* pendingListHead) {
    int currentNode;
    int nextNode;
    bool isUpdating = DAT_0120569e;  // global flag
    ActionManager* manager = DAT_01223510;  // singleton manager with vtable
    int node;

    // Process pending list (listHead[3]) — just calls manager update each iteration
    for (node = pendingListHead[3]; node != 0; node = *(int*)(node + 4)) {
        if (manager != 0) {
            manager->updateInternal();
            manager = DAT_01223510;  // reset pointer (likely volatile)
        }
    }

    // Main processing loop over active list (listHead[0])
    currentNode = *listHead;
    while (currentNode != 0) {
        nextNode = *(int*)(currentNode + 4);
        if (manager != 0) {
            manager->updateInternal();
            manager = DAT_01223510;
        }

        // Play the action (call with ID and parameters)
        playAction(*(short*)(currentNode + 8),                     // actionId
                   *(int*)(currentNode + 0x18),                    // target
                   (*(byte*)(currentNode + 0x10) >> 5) & 1,       // flags bit5
                   (int)*(char*)(currentNode + 0x1d),             // timer
                   *(int*)(currentNode + 0x24));                  // duration/state

        if ((*(byte*)(currentNode + 0x10) & 0x20) == 0) {         // bit5 not set => not looping
            if (*(char*)(currentNode + 0x1d) < 1) {              // timer expired
                char isDone = (**(code**)(manager->vtable + 0x3c))(*(short*)(currentNode + 8));
                manager = DAT_01223510;
                if (isDone != 0) {
                    playAction(*(short*)(currentNode + 8));       // finish play (with short ID)
                    processFinishedAction();
                    manager = DAT_01223510;
                }
            } else {
                *(char*)(currentNode + 0x1d) -= 1;               // decrement timer
            }
        }

        currentNode = nextNode;
    }

    if (isUpdating) {
        // Final cleanup pass for actions with zero duration
        currentNode = *listHead;
        while (currentNode != 0) {
            nextNode = *(int*)(currentNode + 4);
            playAction(*(short*)(currentNode + 8),
                       *(int*)(currentNode + 0x18),
                       (*(byte*)(currentNode + 0x10) >> 5) & 1,
                       (int)*(char*)(currentNode + 0x1d),
                       *(int*)(currentNode + 0x24));

            if ((*(int*)(currentNode + 0x24) == 0) &&             // duration zero => immediate action
                (manager != 0)) {
                char isNotDone = (**(code**)(manager->vtable + 0x3c))(*(short*)(currentNode + 8));
                manager = DAT_01223510;
                if (isNotDone == 0) {
                    *(short*)(currentNode + 0x10) &= 0xFFBF;      // clear bit6 (0x40)
                    (**(code**)(manager->vtable + 0x20))(*(short*)(currentNode + 8)); // destroy
                    playAction(*(short*)(currentNode + 8), *(int*)(currentNode + 0x18));
                    manager = DAT_01223510;
                    if ((*(byte*)(currentNode + 0x10) & 0x40) == 0) { // after clear, check bit6
                        finalizeCleanup();
                        manager = DAT_01223510;
                    }
                }
            }
            currentNode = nextNode;
        }
    }
}