// FUNC_NAME: cleanupPooledObjectsByPriority
// Address: 0x00610d70
// Role: Iterates through a pool of nodes (linked list or array), releasing objects that meet a priority threshold.
// Uses a global array (DAT_012058e0) as a secondary pool when the linked list ends.
// Node structure offsets: +0x04 = object pointer, +0x08 = priority (int), +0x38 = next node pointer

void cleanupPooledObjectsByPriority(int priorityThreshold)
{
    int* globalArray = (int*)DAT_012058e0;  // pointer to array of 0x1000 (4096) entries
    int* currentNode = getPoolHead();        // returns first node pointer (or NULL)
    
    if (currentNode != 0) {
        do {
            int* nextNode = *(int**)(currentNode + 0x38);  // next node in linked list
            
            // If no next node and global array is available, scan for first non-null entry in global array
            if (globalArray != 0) {
                uint index = 0;
                while (nextNode == 0 && index < 0x1000) {
                    nextNode = (int*)globalArray[index];
                    index++;
                }
            }
            
            // Release object if its priority falls within [priorityThreshold, 4)
            int nodePriority = *(int*)(currentNode + 8);
            if (priorityThreshold <= nodePriority && nodePriority < 4) {
                void* objectPtr = *(void**)(currentNode + 4);
                releaseObject(objectPtr, 0);  // second parameter flags type of release (0 = normal)
            }
            
            currentNode = nextNode;
        } while (nextNode != 0);
    }
}