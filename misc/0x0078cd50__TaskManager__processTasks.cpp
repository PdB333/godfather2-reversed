// FUNC_NAME: TaskManager::processTasks
void __thiscall TaskManager::processTasks(void* this, uint32_t someParam)
{
    char isDone;
    int32_t taskType;
    uint32_t taskData;

    // Initialize task system with given parameter
    initializeTaskSystem(someParam);
    registerTaskCallback(someParam, 0x578d3c87); // Some task ID constant

    isDone = isTaskQueueEmpty();
    while (isDone == '\0') {
        processNextTask(); // Advance to next task in queue

        taskType = getCurrentTaskType();
        if (taskType == 0) {
            // Type 0: simple data task
            processNextTask();
            taskData = getCurrentTaskData();
            setTaskData(this + 0x50, taskData); // Store data at offset +0x50
        }
        else if (taskType == 1) {
            // Type 1: task with sub-manager at +0x58
            void* subManager1 = this + 0x58;
            processNextTask(subManager1);
            executeSubTask(subManager1);
        }
        else if (taskType == 2) {
            // Type 2: task with sub-manager at +0x68
            void* subManager2 = this + 0x68;
            processNextTask(subManager2);
            executeSubTask(subManager2);
        }

        advanceTaskQueue(); // Move to next task
        isDone = isTaskQueueEmpty();
    }
}