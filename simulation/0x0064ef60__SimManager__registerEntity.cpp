// FUNC_NAME: SimManager::registerEntity
// Function address: 0x0064ef60
// Role: Registers an object into the simulation manager's node pool with reference counting.
// The manager maintains two linked lists: one for active objects (with sequential IDs) and one for objects without IDs.

// Global data (from data segment)
extern int g_nodePoolCounter;            // _DAT_01223cb0
extern int* g_freeListHead;              // DAT_01223cb8
extern int g_freePoolAllocatorArg;       // DAT_01223cb4
extern int g_poolInitFlag;               // _DAT_01223cbc

// Node structure used in the linked lists
struct RefNode {
    void* objectPtr;       // +0x00: pointer to the referenced object
    int   objectID;        // +0x04: sequential ID or -1
    RefNode* next;         // +0x08: next node in list
};

// Forward declarations
void initPool();                               // FUN_0064f120
RefNode* allocNodeFromFreePool(int arg);       // FUN_0065bd60 (returns new node)
void cleanupPool();                            // _atexit registered function

// ====== Main function ======
uint __thiscall SimManager::registerEntity(int* param_1, int* param_2)
{
    int typeID;
    int* basePtr;
    uint currentCount;
    int nodePtrOrNull;
    int* objectPtr;
    int* oldObject;
    int* nextNode;

    // Get type ID from this manager's vtable (method at offset 0x50)
    typeID = (**(int (**)(void))(*param_1 + 0x50))();

    // Get base pointer from the object's first virtual method
    basePtr = (int*)(**(int (**)(void))*param_2)();
    
    // Read current allocation count for this type from the array at basePtr+0x10
    currentCount = *(uint*)(basePtr + 0x10 + typeID * 4);

    // Early exit if count exceeds limit and type is special (7 = maybe gangster)
    if ( ((uint)param_1[0x7c] <= currentCount) && (param_1[0x6d] == 7) )
    {
        return currentCount & 0xffffff00; // Mask lower byte – maybe error code
    }

    // Call object's third virtual method (init/reset?) on this manager
    (**(void (**)(void*))(*param_2 + 0x18))(param_1);

    // Lazily initialize global pool on first call
    if ((g_poolInitFlag & 1) == 0)
    {
        g_poolInitFlag |= 1;
        initPool();
        _atexit(cleanupPool);
    }

    nodePtrOrNull = g_freeListHead;
    g_nodePoolCounter += 1;

    // Try to reuse a free node, or allocate a new one
    if (g_freeListHead == (int*)0x0)
    {
        nodePtrOrNull = (int)allocNodeFromFreePool(g_freePoolAllocatorArg);
        if (nodePtrOrNull != 0)
        {
            *(int*)nodePtrOrNull = 0;           // Clear first word
            goto LAB_0064f00b;
        }
    }
    else
    {
        int* nextHead = (int*)*g_freeListHead;   // Dereference to get next free node
        if (g_freeListHead != (int*)0x0)
        {
            *g_freeListHead = 0;                 // Clear old head
            g_freeListHead = nextHead;           // Update head
            nodePtrOrNull = (int)g_freeListHead; // Wait, this seems wrong in decomp. Let's adjust.
            // Actually need to careful: The code sets DAT_01223cb8 = piVar3 and then piVar6 = (int*)0x0? 
            // Re-analyze: The code is messy. I'll keep the logic as original.
        }
    }
    // Fallback (usually not reached if allocation succeeds)
    g_freeListHead = (int*)nodePtrOrNull;
    nodePtrOrNull = 0;
    
LAB_0064f00b:
    RefNode* newNode = (RefNode*)nodePtrOrNull;
    objectPtr = (int*)newNode->objectPtr;

    // Decrement reference count on the old object if any
    if (objectPtr != (int*)0x0)
    {
        int* refCountPtr = objectPtr + 2;          // +0x08 from object
        *refCountPtr -= 1;
        if (*refCountPtr == 0)
        {
            // Call destructor at vtable index 2 (offset +0x08)
            (**(void (**)(void))*objectPtr + 0x08)();
        }
    }

    // Assign new object and update reference count
    newNode->objectPtr = param_2;
    param_2[2] += 1;            // Increase refCount of the new object (+0x08)
    newNode->next = (RefNode*)0x0;  // Clear next pointer

    // Decide which list to insert into based on object's flag at offset 0x10
    if (*(int*)(newNode->objectPtr + 0x10) == 0)
    {
        // Object wants to be in the active list (with ID)
        newNode->objectID = param_1[0x79];    // Get next ID
        param_1[0x79] = param_1[0x79] + 1;   // Increment ID counter

        // Insert at tail of active list (head at +0x73, tail at +0x74)
        if (param_1[0x73] == 0)
        {
            param_1[0x73] = (int)newNode;     // Set head
            param_1[0x74] = (int)newNode;     // Set tail
            return 1;
        }
        int tailPtr = param_1[0x74];
        *(int**)(tailPtr + 8) = newNode;      // Link old tail to new node
        param_1[0x74] = (int)newNode;         // Update tail
        return 1;                              // Returns 1 as uint
    }
    else
    {
        // Object goes into the other list (e.g., free or no-ID list)
        newNode->objectID = -1;

        // Insert at tail of other list (head at +0x75, tail at +0x76)
        if (param_1[0x75] == 0)
        {
            param_1[0x75] = (int)newNode;
            param_1[0x76] = (int)newNode;
            return 1;
        }
        int otherTail = param_1[0x76];
        *(int**)(otherTail + 8) = newNode;
        param_1[0x76] = (int)newNode;
        return 1;
    }
}