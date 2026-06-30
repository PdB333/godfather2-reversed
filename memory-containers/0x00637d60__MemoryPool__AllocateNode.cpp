// FUNC_NAME: MemoryPool::AllocateNode
int* __thiscall MemoryPool::AllocateNode(void* context, PoolList* listMgr, int* data)
{
    int* freeNode;
    int* node;
    int* poolNode;
    int* poolHead;
    int* poolTail;
    
    // Get the pool singleton
    poolNode = MemoryPool::GetPool(); // 0x00637490
    node = poolNode;
    
    // If there is a free node in the pool (offset +0x08 flags != 0)
    if (poolNode[2] != 0) {
        poolHead = MemoryPool::GetPool(); // 0x00637490 - same singleton
        node = *(int**)(listMgr + 0x14); // listMgr->head
        if (poolHead == poolNode) {
            // Free node is the first node; detach it
            node[4] = poolNode[4]; // node->next = poolNode->next
            poolNode[4] = (int)node; // poolNode->next = node
        } else {
            // Walk to find the node before poolNode in the free list
            poolTail = (int*)poolHead[4];
            while (poolTail != poolNode) {
                poolHead = (int*)poolHead[4];
                poolTail = (int*)poolHead[4];
            }
            // Remove poolNode from free list
            poolHead[4] = (int)node;
            // Copy poolNode's data to node
            *(int64_t*)node = *(int64_t*)poolNode;
            *(int64_t*)(node + 2) = *(int64_t*)(poolNode + 2);
            node[4] = poolNode[4];
            // Clear poolNode's flags and next pointer
            poolNode[4] = 0;
            poolNode[2] = 0;
            // Return the old poolNode (now free) as the allocated node?
            node = poolNode;
        }
    }
    
    // Copy incoming data into node (first two ints)
    *node = *data;
    node[1] = data[1];
    
    // Check if list is full (head == tail?)
    if (*(int**)(listMgr + 0x14) != 0) {
        do {
            if (*(int*)(listMgr + 0x14) == *(int*)(listMgr + 0x10)) {
                // List is full, need to expand
                node[2] = 1; // mark as expanded?
                node[3] = 0;
                MemoryPool::ExpandList(listMgr, &context, &data); // 0x00637790
                int newCount = MemoryPool::GetNextFreeIndex(); // 0x006367a0
                MemoryPool::InsertNode(context, listMgr, newCount + 1); // 0x00637a50
                
                // Return appropriate node type based on data type
                if (*data == 3) {
                    if ((float)(int)(float)data[1] == (float)data[1]) {
                        node = MemoryPool::CreateFloatNode(); // 0x00637f10
                        *node = 0;
                        return node;
                    }
                } else if (*data == 4) {
                    node = MemoryPool::CreateStringNode(); // 0x00637f90
                    *node = 0;
                    return node;
                }
                node = MemoryPool::CreateDefaultNode(); // 0x00637ea0
                *node = 0;
                return node;
            }
            // Move to previous node in list
            poolNode = (int*)(*(int*)(listMgr + 0x14) - 0x14);
            *(int**)(listMgr + 0x14) = poolNode;
        } while (*poolNode != 0);
    }
    
    // Return pointer to the data area (offset +0x08 from node)
    return node + 2;
}