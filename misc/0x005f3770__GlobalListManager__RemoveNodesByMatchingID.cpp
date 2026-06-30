// FUNC_NAME: GlobalListManager::RemoveNodesByMatchingID
void GlobalListManager::RemoveNodesByMatchingID(int iMatchingID)
{
    // Global linked list head stored at DAT_011a0ef0
    int* pCurrent = DAT_011a0ef0;
    
    if (pCurrent == nullptr)
        return;
    
    do
    {
        // Check if the node's type/identifier at offset +0x60 matches the parameter
        if (*(int*)(pCurrent + 0x60) == iMatchingID)
        {
            // Call cleanup function (likely removes/frees the node)
            FUN_005f1ef0(pCurrent);
        }
        
        // Advance to the next node (offset +4 is next pointer)
        int* pNextPtr = (int*)(pCurrent + 4);
        pCurrent = (int*)*pNextPtr;
    } while (*pNextPtr != 0);
}