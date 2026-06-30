// FUNC_NAME: MemoryPool::removeFreeBlock
void __fastcall MemoryPool::removeFreeBlock(void* unused, int listHead, int nodeOffset)
{
    // TLS pointer to per-thread pool data
    int tlsData = *(int*)(__readfsdword(0x2C) + 0x2C);
    int poolBase = *(int*)(tlsData + 8); // base address of the pool's memory region

    // listHead points to a structure with head and tail offsets at +0x14 and +0x18
    int* headPtr = (int*)(listHead + 0x14);
    int* tailPtr = (int*)(listHead + 0x18);

    if (nodeOffset == *headPtr) {
        // Removing the head node
        int nextNode = *(int*)(poolBase + nodeOffset);       // node->next (offset 0)
        int prevNode = *(int*)(poolBase + nodeOffset + 4);   // node->prev (offset 4)
        *headPtr = nextNode;
        *tailPtr = prevNode;
        if (nextNode != 0) {
            // Clear the next node's prev pointer (at offset 8 from node start)
            *(int*)(poolBase + nextNode + 8) = 0;
            *(int*)(poolBase + nextNode + 0xC) = 0;
        }
    } else {
        // Removing a non-head node
        int nextNode = *(int*)(poolBase + nodeOffset + 8);   // node->next (offset 8)
        if (nextNode != 0) {
            // Update next node's prev to point to this node's prev
            *(int*)(poolBase + nextNode) = *(int*)(poolBase + nodeOffset);         // copy prev
            *(int*)(poolBase + nextNode + 4) = *(int*)(poolBase + nodeOffset + 4); // copy next? Actually copy second dword
        }
        int prevNode = *(int*)(poolBase + nodeOffset);       // node->prev (offset 0)
        if (prevNode != 0) {
            // Update prev node's next to point to this node's next
            *(int*)(poolBase + prevNode + 8) = *(int*)(poolBase + nodeOffset + 8);   // copy next
            *(int*)(poolBase + prevNode + 0xC) = *(int*)(poolBase + nodeOffset + 0xC); // copy second dword
        }
    }
}