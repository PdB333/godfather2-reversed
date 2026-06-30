//FUNC_NAME: JobManager::addJob
// Function address: 0x005f7be0
// Role: Adds a job to the job queue, allocating a node and linking it into a doubly linked list.
// The function uses an implicit list head pointer passed in ESI (likely a member variable of the class).

int __thiscall JobManager::addJob(int thisPtr, int jobId)
{
    int jobObject;
    int jobData;
    int *allocatedNode;
    int *eventObject;
    int listHeadPtr; // unaff_ESI - passed implicitly, likely &(this->jobListHead)
    int local_4;
    int local_8;
    int local_c;
    int local_10 = 0;

    // Get a job object from the pool (FUN_005f79a0)
    jobObject = getJobFromPool(thisPtr, jobId, &local_10);
    if (jobObject != 0) {
        // Check if the job system is active (this+0x28 points to a condition object, offset 0x14 is a flag)
        if (*(int *)(*(int *)(thisPtr + 0x28) + 0x14) != 0) {
            // Allocate an event object (size unknown, likely a job event structure)
            eventObject = (int *)allocateEventObject(); // FUN_004abf10
            if (eventObject != 0) {
                eventObject[1] = 0;
                *eventObject = (int)&PTR_FUN_00e407c8; // vtable pointer
                eventObject[2] = jobObject;
                eventObject[3] = local_10;
                eventObject[4] = g_currentTime; // DAT_00e2eff4
            }

            // Get the job object pointer from this+0x6c
            jobObject = *(int *)(thisPtr + 0x6c);
            local_10 = *(int *)(jobObject + 4);

            // Get allocator context from this+0x58
            int *allocContext = *(int **)(thisPtr + 0x58);
            if (allocContext == 0) {
                local_c = 0;
                local_8 = 0;
                local_4 = 0;
                allocContext = &local_c;
            }

            // Allocate a node of size 0xc using the allocator at this+0x54
            allocatedNode = (int *)((*(code **)(*(int *)(thisPtr + 0x54)))(0xc, allocContext));
            if (allocatedNode != 0) {
                *allocatedNode = jobObject; // node->data = jobObject
            }

            int *nextField = allocatedNode + 1; // node->next
            if (nextField != 0) {
                *nextField = listHeadPtr; // node->next = old head pointer
            }

            if (allocatedNode + 2 != 0) {
                allocatedNode[2] = local_4; // node->prev = local_4 (unused?)
            }

            // Insert node into list (FUN_005fa010 likely does additional linking)
            insertNodeIntoList(); // FUN_005fa010

            // Link the node: set head's next pointer to new node
            *(int **)(jobObject + 4) = allocatedNode;
            // Update the head pointer (stored at listHeadPtr) to point to new node
            *(int **)*nextField = allocatedNode;

            return local_4;
        }
        // If job system not active, handle failure
        handleAddJobFailure(thisPtr, jobObject); // FUN_005f7e50
    }
    return 0;
}