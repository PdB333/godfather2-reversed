// FUNC_NAME: GameObjectManager::processStateChange
void GameObjectManager::processStateChange()
{
    // this+0x1ef8: some state/handle (e.g., m_nodeIndex, m_connectionId)
    if (*(int *)(this + 0x1ef8) == -1)
    {
        // this+0x48: pointer to a linked list node or smart pointer
        int* local_8 = (int*)(this + 0x48);
        int local_4 = 0; // unused, probably padding

        if (local_8 != nullptr)
        {
            local_4 = *(int*)(this + 0x4c); // +0x4c: could be refCount or similar
            *(int**)(this + 0x4c) = &local_8; // store address of local_8 into +0x4c
        }

        // Initialize or register using local_8 as argument
        FUN_008acfe0(&local_8); // likely some init function (e.g., listInsert, refInc)
        FUN_008af670();         // global or static function (e.g., globalStateUpdate)

        if (local_8 != nullptr)
        {
            FUN_004daf90(&local_8); // cleanup/destructor for the local_8 resource
            return;
        }
        // if local_8 was null, fall through to return
    }
    else
    {
        // Alternate path when state is not -1
        FUN_008ad820(this); // likely handles different state (e.g., processActive)
    }
}