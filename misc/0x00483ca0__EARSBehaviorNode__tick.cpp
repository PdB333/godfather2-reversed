// FUNC_NAME: EARSBehaviorNode::tick
void __thiscall tick(EARSBehaviorNode* this)
{
    // +0x0C: m_child? - context or child object
    // Initialize child context
    initChildContext(this + 0x0C); // FUN_00484070

    int updateResult = *(int*)(this + 0x04);   // +0x04: m_pendingStatus or m_currentResult
    // g_pCurrentNode (likely a global pointer to the currently processed node) - from preserved register
    EARSBehaviorNode* currentNode = g_pCurrentNode; // local_10
    // g_pRunningChild (another global tracking the active child) - from preserved register
    EARSBehaviorNode* runningChild = g_pRunningChild; // local_c

    if (currentNode == nullptr || currentNode != this)
    {
        // Debug assertion: currentNode must be this
        debugBreak(); // FUN_00b97aea
    }

    if (runningChild != (EARSBehaviorNode*)updateResult)
    {
        // A different child is running
        if (currentNode == nullptr)
        {
            debugBreak();
        }
        if (runningChild == *(EARSBehaviorNode**)(currentNode + 0x04)) // +0x04 of currentNode
        {
            debugBreak();
        }
        // Call virtual function at offset +0x10 on the child node (e.g., child->onExecute)
        child->vtable.onExecute(runningChild, this + 0x0C); // (**(code **)(local_c + 0x10))(in_EAX + 0xc)
        return;
    }

    // No running child; process node's own result
    int nodeResult = *(int*)(this + 0x10); // +0x10: m_result (0 = success, 1 = failure?)
    if (nodeResult != 0)
    {
        // Global scheduler structure (g_pScheduler)
        if (*g_pScheduler == EARS_SCHEDULER_MODE_1)
        {
            uint currentTime = g_pScheduler->currentTime;
            uint delta = nodeResult + g_pScheduler->accumulatedTime;
            if (currentTime < delta)
            {
                g_pScheduler->accumulatedTime = currentTime;
                return;
            }
            g_pScheduler->accumulatedTime = delta;
        }
        else if (*g_pScheduler == EARS_SCHEDULER_MODE_2)
        {
            // Mode 2: callback with node result
            g_pScheduler->callback(g_pScheduler->callbackData, nodeResult);
            return;
        }
    }
    // No action
}