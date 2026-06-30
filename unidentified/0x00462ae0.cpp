// FUN_00462ae0: ListManager::processMatchingObjects
void __fastcall processMatchingObjects(void* pObjectWithId, void* pListManager, void* callbackData)
{
    int targetId = *(int*)((char*)pObjectWithId + 8); // +0x8: unique identifier
    NodeEntry* currentEntry = *(NodeEntry**)((char*)pListManager + 0x28); // +0x28: head of linked list
    bool found = false;

    while (currentEntry != nullptr)
    {
        // Each entry points to a game object; the object's type descriptor (at +0x70) holds an ID at +8
        int objectId = *(int*)(*(int*)((char*)currentEntry->pObject + 0x70) + 8);
        if (objectId == targetId)
        {
            FUN_005792a0(callbackData); // process matched object
            found = true;
        }
        else if (found)
        {
            // After first match, stop at first non-matching entry (list is sorted by ID)
            return;
        }
        currentEntry = currentEntry->pNext;
    }
}