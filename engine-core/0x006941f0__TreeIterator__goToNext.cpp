// FUNC_NAME: TreeIterator::goToNext
void __fastcall TreeIterator::goToNext(TreeIterator* thisPtr)
{
    char cActive;
    int iNext;
    Node** ppChild1;
    Node** ppChild2;
    
    if (thisPtr->m_pRoot == 0) {
        FUN_00b97aea();
    }
    iNext = thisPtr->m_pCurrent;
    if (*(char *)(iNext + 0x29) == '\0') {
        ppChild1 = *(Node***)(iNext + 8);
        if (*(char *)((int)ppChild1 + 0x29) != '\0') {
            iNext = *(int *)(iNext + 4);
            cActive = *(char *)(iNext + 0x29);
            while ((cActive == '\0' && (thisPtr->m_pCurrent == *(int *)(iNext + 8)))) {
                thisPtr->m_pCurrent = iNext;
                iNext = *(int *)(iNext + 4);
                cActive = *(char *)(iNext + 0x29);
            }
            thisPtr->m_pCurrent = iNext;
            return;
        }
        cActive = *(char *)(*ppChild1 + 0x29);
        ppChild2 = (Node**)*ppChild1;
        while (cActive == '\0') {
            cActive = *(char *)(*ppChild2 + 0x29);
            ppChild1 = ppChild2;
            ppChild2 = (Node**)*ppChild2;
        }
        thisPtr->m_pCurrent = (int)ppChild1;
        return;
    }
    FUN_00b97aea();
    return;
}