// FUNC_NAME: ObjectManager::processObjects
void __cdecl ObjectManager::processObjects(int param1, bool param2)
{
    int node = g_headNode; // DAT_01205514, head of linked list
    g_globalFlag = param2; // DAT_0120551d, flag store

    ObjectManager::preProcess(); // FUN_0051bb80

    int* currentPtr = &g_headNode;
    int currentNode = node;
    while (currentNode != 0)
    {
        currentNode = *currentPtr; // load from pointer (could be head or next)
        if (!(*(uint*)(currentNode + 0xC) & 0x200000)) // +0x0c: objectFlags, bit 21
        {
            // Object not flagged for deletion, process normally
            currentPtr = (int*)(currentNode + 0x14); // +0x14: next pointer
            if (param2 == false || (*(uint*)(currentNode + 0xC) & 0x400000) != 0) // bit 22
            {
                ObjectManager::callObjectMethod(currentNode, param1); // FUN_0051abd0
            }
        }
        else
        {
            // Object flagged for deletion, remove from list
            *currentPtr = *(int*)(currentNode + 0x14); // unlink node

            ObjectManager::postRemove(); // FUN_0051a5e0

            // Allocate space for a removal record in custom allocator
            int** allocPtr = (int**)(DAT_01206880 + 0x14); // +0x14: allocator current pointer
            **(int***)(DAT_01206880 + 0x14) = &PTR_LAB_01125180; // set vtable
            *allocPtr = *allocPtr + 4;
            int* alignedPtr = (int*)((*allocPtr + 3) & 0xFFFFFFFC);
            *allocPtr = (int)alignedPtr;
            *alignedPtr = currentNode; // store removed node pointer
            *allocPtr = *allocPtr + 4;
        }
        currentNode = *currentPtr;
    }

    ObjectManager::processRemovalQueue(param1); // FUN_0052e780
}