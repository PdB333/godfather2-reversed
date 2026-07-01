// FUNC_NAME: ChaseManager::processCompletedItems
// Function at 0x008add00: processes and removes completed items from an active list, then handles player-to-controller binding if applicable.
// Called from ChaseManager::update (0x008af870) and ChaseManager::onChaseEnd? (0x008af190)

void __thiscall ChaseManager::processCompletedItems(void* thisPtr, void* item) {
    // +0xf0: m_activeItemCount (uint)
    uint activeCount = *(uint*)((byte*)thisPtr + 0xf0);
    if (activeCount == 0) {
        goto end;
    }

    // +0xec: m_activeItemList (array of pairs: pointer + ref/link)
    int* itemArray = *(int**)((byte*)thisPtr + 0xec);
    uint index = 0;
    do {
        int* currentEntry = itemArray + index * 2; // each entry is 2 ints
        int itemPtr = *currentEntry; // first int: pointer to the tracked object
        if (itemPtr != 0) {
            // The actual object is at itemPtr - 0x48 (header size)
            int* objectHeader = (int*)(itemPtr - 0x48);
            if (objectHeader != 0) {
                // Check match by comparing type ID at +0x1eb0 with item's type at +0x14
                if (*(int*)(itemPtr + 0x1eb0) == *(int*)((byte*)item + 0x14)) {
                    // Call virtual function at vtable offset 0x1d0 (likely "onItemCompleted") on the object with 'item' as argument
                    (*(void (__thiscall**)(void*, void*))(*(int*)objectHeader + 0x1d0))(thisPtr, item);

                    // Prepare for releasing the item from the active list
                    // Store the original second int (probably reference link or next pointer)
                    int savedLink = *(int*)(itemPtr + 4);
                    int stackLink = 0;
                    // Link item's second int to a temporary stack variable
                    *(int*)(itemPtr + 4) = (int)&stackLink;
                    // The stackLink now points to the item
                    stackLink = itemPtr;

                    // Decrement reference count (FUN_008acfe0 likely "SmartPtr::release" or remove from list)
                    releaseSmartPtr(&stackLink);
                    // If still alive after release, free memory
                    if (stackLink != 0) {
                        operatorDelete(&stackLink);
                    }

                    // Remove the item entry from the active list by index (FUN_008ab630)
                    removeItemFromList(index);

                    // --- Second part: handle player-controller binding if global state is active ---
                    if (g_someGlobalFlag != 0) {
                        uint playerCount = getActivePlayerCount();  // FUN_0043ff40
                        int* controllerManager = *(int**)(g_globalManagerPtr + 0x40);  // e.g., ControllerManager*
                        if (controllerManager != 0 && controllerManager[0x36] == 2) { // state == 2 (ready to bind)
                            uint j = 0;
                            if (playerCount != 0) {
                                do {
                                    // Player entry pointers from g_someGlobalFlag+4
                                    int* playerList = *(int**)(g_someGlobalFlag + 4);
                                    int playerPtr = *(int*)((byte*)playerList + j * 4);
                                    if (playerPtr != 0) {
                                        // Player object is at playerPtr - 0x1f30 (large negative offset, likely part of big structure)
                                        int* playerObject = (int*)(playerPtr - 0x1f30);
                                        if (playerObject != 0) {
                                            char isAlive = isPlayerAlive();  // FUN_00481640 (global function, no arg?)
                                            if (isAlive != 0) {
                                                // Check IDs at -0x38 and -0x3c (likely controller slot indices)
                                                if (*(int*)(playerPtr - 0x38) != -1 && *(int*)(playerPtr - 0x3c) != -1) {
                                                    // Call virtual function at vtable offset 0x2cc on playerObject (returns bool)
                                                    char shouldBind = (*(char (__thiscall**)(void*))(*(int*)playerObject + 0x2cc))(playerObject);
                                                    if (shouldBind == 0) {
                                                        // Bind controller slot (vtable+0xcc) and player (vtable+0xc4) via controllerManager
                                                        (*(void (__thiscall**)(void*, int))(*(int*)controllerManager + 0xcc))(controllerManager, *(int*)(playerPtr - 0x38));
                                                        (*(void (__thiscall**)(void*, int*))(*(int*)controllerManager + 0xc4))(controllerManager, playerObject);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    j++;
                                } while (j < playerCount);
                            }
                        }
                    }
                    break; // Only process the first matching item? (break after loop)
                }
            }
        }
        index++;
        itemArray += 2; // advance to next pair
    } while (index < activeCount);

end:
    postUpdate(); // FUN_009847c0 (e.g., frame sync)
    return;
}