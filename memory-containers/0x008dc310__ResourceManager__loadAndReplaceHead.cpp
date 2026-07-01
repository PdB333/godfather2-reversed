// FUNC_NAME: ResourceManager::loadAndReplaceHead
// Address: 0x008dc310
// Role: Loads a resource identified by a 128-bit key and inserts it at the head of a doubly linked list,
//       replacing the previous head. The list uses intrusive prev pointers stored at offset +0x08.
//       Called by similar functions (0x008dc3f0, 0x008dc450, 0x008dc4b0), likely different resource types.

int* __thiscall ResourceManager::loadAndReplaceHead(int** headPtr, int resourceKey[4])
{
    // Clear the head pointer initially (safety reset)
    *headPtr = 0;

    // Check if the resource key is non-zero (all 4 ints zero indicates an invalid/empty key)
    if (resourceKey[0] != 0 || resourceKey[1] != 0 || resourceKey[2] != 0 || resourceKey[3] != 0)
    {
        // Obtain a base path or extension (e.g., ".str", ".fx") from a global/static
        const char* extension = (const char*)FUN_00471610(); // likely returns "\\" or something

        // Build a full path in a local buffer (76 bytes)
        char pathBuffer[76]; // stack buffer for full path
        FUN_0044b4e0(pathBuffer, extension); // copies extension into buffer (maybe strcpy)

        // Load the resource from file. The function signature:
        //   int* FUN_004df330(int* outOldNode, int* key, char* path, int maxSize, int flags, void* this, int timeout, int extra)
        // Returns a pointer to a node pointer (the new resource node).
        // It also stores the previous (or a related) node in outOldNode.
        int oldNode; // local_54 – will hold a node pointer after the call
        int* newNodePtr = (int*)FUN_004df330(&oldNode, resourceKey, pathBuffer, 0x1ff, 0, this, 0xffffffff, 0);

        // If there is already a head in the list, unlink it by clearing its prev pointer
        // and resetting the head pointer
        if (*headPtr != 0)
        {
            *(int*)(*headPtr + 8) = 0; // clear prev pointer of the old head (offset +8)
            *headPtr = 0;               // null the head pointer
        }

        // The newNodePtr points to an int which is the actual node address.
        int newNode = *newNodePtr;   // dereference to get the new resource node
        *headPtr = newNode;          // set head to this node

        if (newNode != 0)
        {
            // Set the prev pointer of the new node to point to the head pointer itself
            *(int**)(newNode + 8) = headPtr; // prev points to head pointer (offset +8)

            // Clear the location held by newNodePtr (likely the internal storage)
            *newNodePtr = 0;
        }

        // If the oldNode is non-zero, clear its prev pointer (it may have been saved by the load function)
        if (oldNode != 0)
        {
            *(int*)(oldNode + 8) = 0;
        }
    }

    return headPtr; // return the pointer to the head pointer
}