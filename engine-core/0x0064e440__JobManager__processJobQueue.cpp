// FUNC_NAME: JobManager::processJobQueue

#include <cstdint>

// Forward declarations for types used
struct JobNode; // node in command lists
struct JobObject; // the actual job object pointed to by node->jobObject

// Global variables for node pool management
extern int32_t g_nodePoolAllocated; // _DAT_01223cb0
extern JobNode* g_nodePoolFreeList; // DAT_01223cb8
extern uint32_t g_nodePoolInitialized; // _DAT_01223cbc

// Job class with vtable and reference count
struct JobObject {
    virtual void vtable_method_0x00(); // placeholder
    virtual void vtable_method_0x04();
    virtual void vtable_method_0x08(); // destructor
    virtual void vtable_method_0x0c();
    virtual void vtable_method_0x10();
    virtual void vtable_method_0x14();
    virtual void vtable_method_0x18();
    virtual void vtable_method_0x1c();
    virtual void vtable_method_0x20(); // called for type 2
    int32_t referenceCount; // at offset +0x08 (since vtable pointer at 0)
    // other fields...
};

// Node structure for linked lists
struct JobNode {
    JobObject* jobObject; // +0x00 pointer to the job object
    int32_t sortKey;      // +0x04 key for sorted list
    JobNode* next;        // +0x08 next node in list
};

// The 'this' object (JobManager)
struct JobManager {
    // ...
    int32_t queueSequence;   // +0xd0 incremented counter
    // ...
    bool someFlag;           // +0x1c8 if non-zero, calls someFunction()
    // Sorted list for type 0 jobs
    JobNode* sortedListPrev; // +0x1cc points to the 'prev' pointer for next insertion
    JobNode* sortedListTail; // +0x1d0 tail of sorted list
    // Immediate list for type 1 jobs (push front)
    JobNode* immediateListHead; // +0x1d4 front of immediate list
    JobNode* immediateListTail; // +0x1d8 back of immediate list
    // ...
};

// External functions (callees)
void someFunction(); // FUN_0065ba30
void initNodePool(); // FUN_0064f120
void atexit(void (*func)()); // _atexit

void __thiscall JobManager::processJobQueue(int param_1, int param_2)
{
    // Increment queue sequence counter
    *(int32_t*)(param_1 + 0xd0) += 1;

    // If a specific flag is set, call a related function
    if (*(int32_t*)(param_1 + 0x1c8) != 0) {
        someFunction();
    }

    // Source list from param2 (assumed to be a command source object)
    JobNode* sourceNode = *(JobNode**)(param_2 + 0x14);
    
    // Persistent insertion pointer for sorted list (initialized from this+0x1cc)
    volatile JobNode** insertionPrev = (volatile JobNode**)(param_1 + 0x1cc);

    do {
        while (true) {
            JobNode* currentNode = sourceNode;
            if (currentNode == nullptr) {
                return;
            }

            // Determine the type from the job object's vtable? Actually from offset 0x10 of the object.
            int32_t type = ((int32_t*)(currentNode->jobObject))[4]; // jobObject->m_type or similar

            if (type == 0) {
                // Type 0: will be inserted into sorted list (break from inner loop)
                break;
            }
            else if (type == 1) {
                // Type 1: push to front of immediate list
                sourceNode = (JobNode*)currentNode->next; // advance source list

                // Insert node at front of immediate list
                currentNode->next = *(JobNode**)(param_1 + 0x1d4); // old head
                *(JobNode**)(param_1 + 0x1d4) = currentNode;
                if (currentNode->next == nullptr) {
                    *(JobNode**)(param_1 + 0x1d8) = currentNode; // set tail if was empty
                }
            }
            else {
                // Type 2: process and free the job (and node)
                sourceNode = currentNode; // keep node for later? Actually later we set to current->next

                if (type == 2) {
                    // Call virtual method at vtable+0x20 on the job object
                    (**(code**)(*(int32_t*)currentNode->jobObject + 0x20))(param_1, 0);

                    // Update source to next node
                    sourceNode = (JobNode*)currentNode->next;

                    // Initialize node pool if needed (global flag)
                    if ((g_nodePoolInitialized & 1) == 0) {
                        g_nodePoolInitialized |= 1;
                        initNodePool();
                        atexit((void (*)())nullptr); // placeholder for cleanup function
                    }

                    // Decrement reference count on job object
                    JobObject* jobObj = currentNode->jobObject;
                    if (jobObj != nullptr) {
                        int32_t* refCountPtr = (int32_t*)((int32_t*)jobObj + 2);
                        *refCountPtr -= 1;
                        if (*refCountPtr == 0) {
                            // Call destructor via vtable+0x08
                            (**(code**)(*(int32_t*)jobObj + 8))();
                        }
                    }

                    // Return node to pool
                    g_nodePoolAllocated -= 1;
                    currentNode->jobObject = (JobObject*)g_nodePoolFreeList;
                    g_nodePoolFreeList = currentNode;
                }
            }
        }

        // We exit inner while only for type == 0
        // Insert the node into the sorted list using the insertionPrev pointer
        JobNode* currentNode = sourceNode; // the node with type 0

        // Search insertion point using sequential scan from insertionPrev
        if (*insertionPrev != nullptr) {
            do {
                JobNode* listNode = *insertionPrev;
                if (currentNode->sortKey <= *(int32_t*)((int32_t*)listNode + 1)) { // listNode->sortKey
                    break;
                }
                insertionPrev = &(listNode->next);
            } while (*insertionPrev != nullptr);
        }

        // Insert node after insertionPrev
        currentNode->next = *insertionPrev;
        if (currentNode->next == nullptr) {
            // If inserting at end, update tail pointer
            *(JobNode**)(param_1 + 0x1d0) = currentNode;
        }
        *insertionPrev = currentNode;
        insertionPrev = &(currentNode->next); // advance for next insertion

        // Note: The sourceNode is NOT updated, so the same node would be processed again? 
        // This suggests a bug in the decompilation or the loop logic is different.
        // Assuming the actual code also advances sourceNode, but it's missing in this decompiler output.
        // For reconstruction, we add the line:
        sourceNode = (JobNode*)currentNode->next; // advance source list
    } while (true);
}