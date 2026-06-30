// FUNC_NAME: TaskManager::updateAllQueues
void TaskManager::updateAllQueues(uint param_1)
{
    int iVar1;
    int iVar5;
    Task *task;
    Task *nextTask;

    iVar5 = 0;
    if (0 < g_taskManagerCount) {
        do {
            iVar1 = g_taskManagerList[iVar5];
            task = (Task *)*(int *)(iVar1 + 0x24); // m_currentList
            while (task != (Task *)0x0) {
                nextTask = (Task *)task->m_next; // offset +8
                *(int *)(iVar1 + 0x24) = (int)nextTask; // update head
                task->execute(); // vtable+4
                task = (Task *)*(int *)(iVar1 + 0x24);
            }
            // Swap lists
            uint temp = *(uint *)(iVar1 + 0x20); // m_activeList
            *(uint *)(iVar1 + 0x20) = *(uint *)(iVar1 + 0x1c); // m_pendingList -> m_activeList
            *(uint *)(iVar1 + 0x24) = temp; // m_currentList = old m_activeList
            *(uint *)(iVar1 + 0x1c) = 0; // m_pendingList = 0
            // Call manager virtual update
            (**(code **)(*(int *)iVar1 + 0x28))(param_1);
            iVar5 = iVar5 + 1;
        } while (iVar5 < g_taskManagerCount);
    }
    return;
}