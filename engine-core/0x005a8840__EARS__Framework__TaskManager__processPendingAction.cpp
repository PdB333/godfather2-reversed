// FUNC_NAME: EARS::Framework::TaskManager::processPendingAction
void TaskManager::processPendingAction(TaskManager* this) {
    TaskManager::baseUpdate();
    // Check if there is a pending action (short at offset +2 is a flag, e.g., m_hasPending)
    if ((*(short*)((int)this + 2) == 0) && 
        // Get the next pending item (returns a pointer to the item)
        (int item = TaskManager::getNextPendingItem(), item != 0)) {
        // Process the item: perform some action
        TaskManager::processItem();
        // Call a global handler function with the item and a constant (0x58 likely a message type or offset)
        (*g_pendingHandler)(item, 0x58);
    }
    return;
}