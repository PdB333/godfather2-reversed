// FUNC_NAME: Player::hasActiveObjectiveOfType
bool __fastcall Player::hasActiveObjectiveOfType(void* this) {
    // Check if the entity pointer at +0x8 is valid
    if (*(void**)((int)this + 8) == nullptr) {
        return false;
    }

    // Get a global game state manager (singleton)
    int* gameStateMgr = reinterpret_cast<int*>(FUN_00ad8d40());
    if (gameStateMgr == nullptr) {
        return false;
    }

    // Query the game state via vtable[0x34] and vtable[0x24]
    // First call: likely returns a pointer to a subsystem or returns non-zero if in certain state
    int result1 = reinterpret_cast<int(__thiscall*)(void*)>(
        (*(int**)(*gameStateMgr))[0x34 / 4]
    )(gameStateMgr);
    if (result1 == 0) {
        return false;
    }

    // Second call: retrieve a pointer to an object (e.g., objective manager) using same vtable slot?
    // Unusual pattern, likely a mis-decompile; but following original logic:
    int* objMgr = reinterpret_cast<int*>(
        reinterpret_cast<int(__thiscall*)(void*)>(
            (*(int**)(*gameStateMgr))[0x34 / 4]
        )(gameStateMgr)
    );
    if (objMgr == nullptr) {
        return false;
    }

    // Check if the manager is valid via vtable[0x24]
    int result2 = reinterpret_cast<int(__thiscall*)(void*)>(
        (*(int**)(*objMgr))[0x24 / 4]
    )(objMgr);
    if (result2 == 0) {
        return false;
    }

    // Iterate over a linked list of objectives (or components) from this+0x3bc
    // Structure of list container at this+0x3bc: [   something   ] [ headPtr at +8 ]
    // Each node: [ type at +4 ] [ next at +8 ]
    int listContainer = *(int*)((int)this + 0x3bc);
    int* currentNode;
    if (listContainer == 0) {
        currentNode = nullptr;
    } else {
        currentNode = *(int**)(listContainer + 8); // head of list
    }

    int count = 0;
    while (currentNode) {
        // Type stored at offset +4 (0-based: node[1])
        if (*(int*)(currentNode + 1) == 3) {
            count++;
        }
        // Next pointer at offset +8 (node[2])
        currentNode = *(int**)((int)currentNode + 8);
    }

    return count > 0;
}