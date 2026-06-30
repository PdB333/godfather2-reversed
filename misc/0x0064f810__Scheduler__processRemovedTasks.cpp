// FUNC_NAME: Scheduler::processRemovedTasks
// Address: 0x0064f810
// Role: Processes a linked list of nodes associated with removed scheduled tasks.
//       For each node, if the task's flag indicates it is being removed (bit 3),
//       clears a flag on the task object and calls a virtual callback.
//       If the task has a valid priority index (bit 5), it removes the task from
//       the scheduler's priority array using a swap with the last element.

struct ScheduledTask {
    void **vtable;        // +0x00 vtable pointer
    int unknown04;        // +0x04 set to 0 in removal
    char pad08[0x18];     // +0x08 to +0x1F
    uint32 flags20;       // +0x20 bit manipulation (clear bit 3)
    int priorityIndex;    // +0x2c index in the scheduler's priority array
};

struct RemovalNode {
    char pad00[4];        // +0x00 unused
    uint32 flags04;       // +0x04 (bit 3 = remove, bit 5 = has priority index)
    ScheduledTask *task;  // +0x08
    RemovalNode *next;    // +0x0c
};

struct RemovalList {
    char pad18[0x18];
    RemovalNode *head;    // +0x18
};

struct Scheduler {
    char pad1fc[0x1fc];
    ScheduledTask **priorityArray; // +0x1fc
    int threshold;                 // +0x200 (max allowed priority)
    int count;                     // +0x204 (number of scheduled tasks)
};

void __thiscall Scheduler::processRemovedTasks(Scheduler *this, RemovalList *list) {
    // Lock the removal list (likely mutex)
    FUN_0064e550(list);

    RemovalNode *current = list->head;
    while (current != 0) {
        // If the node points to itself via task pointer? Actually check if
        // current->task->somePointer == current? The decompiled code: 
        // if (*(int *)(*(int *)(current + 8) + 8) == current) 
        // This likely means task->selfPointer == current (for sanity)
        if (current->task->unknown04 == (int)current) {
            // Clear the self-reference
            current->task->unknown04 = 0;
        }

        RemovalNode *next = current->next;

        // Check flag bit 3 (0x08) - indicates task is being removed
        if ((current->flags04 & 0x8) == 0) {
            // Flag bit 3 is not set, so check bit 5 (0x20) - has priority index
            if ((current->flags04 & 0x20) != 0) {
                ScheduledTask *task = current->task;
                // Only remove from priority array if the task's index is not 0x400
                // and its index is within the current threshold
                if ((task->priorityIndex != 0x400) &&
                    (task->priorityIndex < this->threshold)) {
                    task->unknown04 = 0;
                    FUN_0064d500(); // Possibly signals a reschedule
                }
                // Decrement the count of scheduled tasks
                this->count--;

                // If the task's index is not equal to the new count, swap it
                // with the last element in the priority array
                if (task->priorityIndex != this->count) {
                    int lastIndex = this->count;
                    ScheduledTask *lastTask = this->priorityArray[lastIndex];

                    // Update the last task's index to the removed task's old index
                    lastTask->priorityIndex = task->priorityIndex;

                    // Swap the array entries
                    this->priorityArray[task->priorityIndex] = lastTask;
                    this->priorityArray[lastIndex] = task;

                    // Update the removed task's index to the new count (old last position)
                    task->priorityIndex = lastIndex;
                }
            }
        } else {
            // Flag bit 3 is set: means task is being removed with callback
            ScheduledTask *task = current->task;
            // Clear bit 3 from the task's flags20
            task->flags20 &= 0xfffffff7; // clear bit 3

            // If the task has a valid vtable, call its onRemoved callback
            if (task->vtable != 0) {
                // vtable entry at offset 0x18 (6th function) is a callback
                // called with this scheduler as argument
                void (*onRemoved)(Scheduler *) = 
                    (void (*)(Scheduler *))task->vtable[0x18 / 4];
                if (onRemoved != 0) {
                    onRemoved(this);
                }
            }
        }

        // Free the removal node
        FUN_009c8eb0(current);

        current = next;
    }
}