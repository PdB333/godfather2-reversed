// FUNC_NAME: PoolAllocator::allocate
// Address: 0x00637d60
// Role: Allocates a block from a pool based on type and size.
// The pool maintains a free list of nodes. Each node has a header (5 ints = 0x14 bytes)
// containing: type (int), size/float (int), flags (int), unused, next pointer.
// The pool descriptor (param_2) has fields at +0x10 (freeListTail?) and +0x14 (freeListHead?).
// When the free list is exhausted, it coalesces pools and allocates more memory.
// Returns a pointer to the data area (header + 2 ints) or a special type-specific allocator.

#include <cstdint>

// Forward declarations of internal helpers (EARS internal)
int* getPoolHead();                                    // 0x00637490
void  coalescePool(int pool, int* param2, int* param3); // 0x00637790 (takes addresses of params)
int   calculateSize();                                   // 0x006367a0
void* allocateExpanded(int context, int pool, int size); // 0x00637a50
int*  allocateType3();   // 0x00637f10
int*  allocateType4();   // 0x00637f90
int*  allocateDefault(); // 0x00637ea0

int* PoolAllocator::allocate(int context, int poolDescriptor, int* blockInfo)
{
    int* head;
    int* node;
    int* current;
    int* temp;
    int size;
    int* result;

    head = getPoolHead();                            // Get the head of the global pool list
    node = head;                                     // Start with head node

    if (head[2] != 0)                                 // If the head node is used (has a flag)
    {
        current = getPoolHead();                      // Re-get head (maybe to get current pool?)

        // Retrieve pointer to the first free node from pool descriptor (+0x14)
        node = *(int**)(poolDescriptor + 0x14);

        if (current == head)                          // If current pool is the same as head pool
        {
            // Insert node after head in the free list
            node[4] = head[4];   // next pointer
            head[4] = (int)node; // head now points to node
        }
        else
        {
            // Walk free list to find the node before head
            temp = (int*)current[4];
            while (temp != head)
            {
                current = (int*)current[4];
                temp = (int*)current[4];
            }
            // Remove head from free list
            current[4] = (int)node;
            // Copy head header to node
            *(int64_t*)node = *(int64_t*)head;
            *(int64_t*)(node + 2) = *(int64_t*)(head + 2);
            node[4] = head[4];
            head[4] = 0;        // clear head's next
            head[2] = 0;        // mark head as unused
            node = head;        // set node back to head (now freed)
        }
    }

    // Copy type and size from blockInfo into the allocated node
    *node = *blockInfo;
    node[1] = blockInfo[1];

    // Check if the free list head pointer is valid
    if (*(int**)(poolDescriptor + 0x14) != 0)
    {
        do {
            // If free list head equals free list tail, pool is exhausted
            if (*(int*)(poolDescriptor + 0x14) == *(int*)(poolDescriptor + 0x10))
            {
                node[2] = 1;   // mark node as used
                node[3] = 0;   // clear unknown
                // Coalesce and resize the pool
                coalescePool(poolDescriptor, &poolDescriptor, &blockInfo);
                size = calculateSize();
                // Allocate additional memory: note the +1
                allocateExpanded(context, poolDescriptor, size + 1);

                // Based on the type (first int of blockInfo), return proper allocator
                if (*blockInfo == 3)
                {
                    // Type 3: float check (exact representation)
                    if ((float)(int)(float)blockInfo[1] == (float)blockInfo[1])
                    {
                        result = allocateType3();
                        *result = 0;
                        return result;
                    }
                }
                else if (*blockInfo == 4)
                {
                    result = allocateType4();
                    *result = 0;
                    return result;
                }
                // Default type
                result = allocateDefault();
                *result = 0;
                return result;
            }
            // Walk backwards through free list nodes (each node is 0x14 bytes)
            temp = (int*)(*(int*)(poolDescriptor + 0x14) - 0x14);
            *(int**)(poolDescriptor + 0x14) = temp;
        } while (*temp != 0);
    }

    // Return pointer to data area (skip first 2 ints of header)
    return node + 2;
}