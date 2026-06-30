// FUNC_NAME: TaskQueue::addTask
// Function address: 0x006b4b50
// Role: Adds a task/object to the dynamic task list, manages capacity and flags

#include <cstdint>

class TaskQueue {
public:
    // +0x00 : vtable? (not shown)
    // +0x38 : callback handle or notification identifier
    uint32_t m_callbackHandle; // +0x38
    // +0x5c : flags (bit 0x800000 = pending? bit 0x400000 = something?)
    uint32_t m_flags;          // +0x5c
    // +0x88 : some state flag (0 = idle?)
    uint32_t m_stateFlag88;    // +0x88
    // +0xa0 : another state flag
    uint32_t m_stateFlagA0;    // +0xa0
    // +0xa8 : pointer to array of task IDs (int*)
    int* m_taskArray;          // +0xa8
    // +0xac : current number of tasks
    int m_taskCount;           // +0xac
    // +0xb0 : capacity of task array
    int m_taskCapacity;        // +0xb0
    // +0xb8 : yet another flag
    uint32_t m_stateFlagB8;    // +0xb8

public:
    // Default constructor etc.
};

// Forward declarations of called functions (replace with actual names if known)
int __fastcall acquireTaskId();      // FUN_006b4080
int __fastcall acquireTaskIdAlt();   // FUN_006b2c70
void __fastcall notifyCallback(uint32_t handle); // FUN_00790d30
void __fastcall resizeTaskArray(int newCapacity); // FUN_006b1e10
void lockGlobalMutex();              // FUN_004086d0 (takes DAT_0112a640 as arg)
void unlockGlobalMutex();            // FUN_00408680 (takes DAT_0112a640 as arg)

// The main function
void __fastcall TaskQueue::addTask(TaskQueue* this) {
    int taskId;
    int* pSlot;

    // Try to get a task ID from two possible sources
    taskId = acquireTaskId();
    if (taskId == 0) {
        taskId = acquireTaskIdAlt();
    }
    if (taskId == 0) {
        return; // No valid task
    }

    // Mark the task as pending (set bit 0x800000) and clear bit 0x400000 (or whatever)
    uint32_t* pFlags = &this->m_flags;
    *pFlags |= 0x800000;
    *pFlags &= 0xfbffffff; // clear bit 0x400000 (0x04000000? Actually 0xfbffffff = ~0x04000000)

    // Notify callback/handler
    notifyCallback(this->m_callbackHandle);

    // Check if we need to grow the task array
    if (this->m_taskCount == this->m_taskCapacity) {
        int newCapacity = (this->m_taskCapacity == 0) ? 1 : (this->m_taskCapacity * 2);
        resizeTaskArray(newCapacity);
        this->m_taskCapacity = newCapacity; // Assuming resize updates capacity? Not shown but likely.
    }

    // Compute pointer to the next slot and store task ID
    pSlot = this->m_taskArray + this->m_taskCount;
    this->m_taskCount++;
    if (pSlot != nullptr) {
        *pSlot = taskId;
    }

    // Check if all state flags indicate idle: if so, lock global mutex; else unlock
    if ((this->m_stateFlag88 == 0) &&
        (this->m_stateFlagA0 == 0) &&
        (this->m_taskCount == 0) &&
        (this->m_stateFlagB8 == 0)) {
        lockGlobalMutex();   // Acquire exclusive access
        return;
    }
    unlockGlobalMutex();     // Release exclusive access
}