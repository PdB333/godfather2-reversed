// FUNC_NAME: clearLinkedListArray
// Address: 0x008285c0
// Role: Clears an array of linked lists by freeing all nodes and zeroing the array entries.
// Each array element is a pointer to the head of a singly linked list.
// Each node has a next pointer at offset +0x8.
// The callee FUN_009c8f10 is assumed to free/deallocate a single node.

void clearLinkedListArray(void** array, uint count)
{
    uint i = 0;
    if (count != 0) {
        do {
            // Get the head of the current linked list
            void* currentNode = array[i];
            while (currentNode != nullptr) {
                // Save the next pointer before freeing the current node
                void* nextNode = *(void**)((char*)currentNode + 8);
                // Free the current node (likely operator delete or custom dealloc)
                FUN_009c8f10(currentNode);
                currentNode = nextNode;
            }
            // Clear the array entry
            array[i] = nullptr;
            i++;
        } while (i < count);
    }
}