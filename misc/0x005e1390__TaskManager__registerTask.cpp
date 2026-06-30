// FUNC_NAME: TaskManager::registerTask
// Address: 0x005e1390
// Role: Registers a task object and optionally associates it with a context ID. The task object has a vtable with methods at offsets 4, 8, and 0xC (presumably setContext, onAttach, onFinish).
// The function stores the task pointer at this+4, calls task's vtable[2] (onAttach?), then if context is non-zero, allocates a task ID via some external function and stores it at this+8,
// then calls task's vtable[1] (setContext?), and finally calls task's vtable[3] (onFinish?). If context is zero, the task ID is set to 0 and only vtable[3] is called.

class TaskManager {
public:
    // Registered task object (offset 0x04)
    Task* m_task;
    // Allocated task ID (offset 0x08)
    int m_taskId;

    // __thiscall
    void registerTask(Task* task, int context) {
        // Store the task pointer
        m_task = task;

        // Call task's init/attach method (vtable offset 8)
        task->onAttach();

        if (context != 0) {
            // Allocate a task ID using the external allocation function
            int allocatedId = allocateTaskId(context, m_task);
            m_taskId = allocatedId;

            // Call task's setContext method (vtable offset 4)
            task->setContext(context, 0);

            // Call task's finalize method (vtable offset 0xC)
            task->onFinish();
        } else {
            // No context: set task ID to 0
            m_taskId = 0;

            // Call task's finalize method (vtable offset 0xC)
            task->onFinish();
        }
    }
};

// External function used to allocate a task ID (0x004265d0)
int allocateTaskId(int context, Task* task);