// FUNC_NAME: PoolManager::releaseAllPools
void PoolManager::releaseAllPools(void)
{
    uint poolCount;
    int *poolNode;
    int *level2Node;
    int *level3Node;
    int *nextLevel2Node;
    int *nextLevel3Node;
    int level2Count;
    int level3Count;
    uint i;

    poolCount = this->poolCount; // +0xAC
    i = 0;
    if (poolCount != 0) {
        do {
            poolNode = *(int **)(this->poolArray + i * 4); // +0xA8
            if (poolNode != (int *)0x0) {
                level2Node = (int *)*poolNode; // first level2 node in this pool
                for (level2Count = poolNode[10]; level2Count != 0; level2Count = level2Count + -1) {
                    nextLevel2Node = level2Node;
                    if (level2Node != (int *)0x0) {
                        level3Node = (int *)*level2Node; // first level3 node in this level2
                        for (level3Count = level2Node[0x12]; level3Count != 0; level3Count = level3Count + -1) {
                            nextLevel3Node = level3Node;
                            if (level3Node != (int *)0x0) {
                                nextLevel3Node = (int *)level3Node[0xb]; // save next level3 node
                                // Free level3 node to free list
                                *level3Node = this->freeListLevel3; // +0xA4
                                this->usedCountLevel3--; // +0x80
                                this->freeCountLevel3++; // +0x7C
                                this->freeListLevel3 = (int)level3Node;
                            }
                            level3Node = nextLevel3Node;
                        }
                        nextLevel2Node = (int *)level2Node[0x13]; // save next level2 node
                        // Free level2 node to free list
                        *level2Node = this->freeListLevel2; // +0x6C
                        this->usedCountLevel2--; // +0x48
                        this->freeCountLevel2++; // +0x44
                        this->freeListLevel2 = (int)level2Node;
                    }
                    level2Node = nextLevel2Node;
                }
                // Free pool node to free list
                *poolNode = this->freeListLevel1; // +0x34
                this->usedCountLevel1--; // +0x10
                this->freeCountLevel1++; // +0x0C
                this->freeListLevel1 = (int)poolNode;
            }
            i = i + 1;
        } while (i < poolCount);
    }
    this->poolCount = 0;
    FUN_009c8f10(this->poolArray); // free the array itself
    this->poolArray = 0;
    this->someField = 0; // +0x2C
    // Call virtual destructors on sub-objects
    (this->vtable[1])(); // vtable +4
    (this->subObject1->vtable[1])(); // +0x38
    (this->subObject2->vtable[1])(); // +0x70
    return;
}