// FUNC_NAME: EARSListenerList::removeListener
void __fastcall EARSListenerList::removeListener(EARSListenerList *this, EARSListener *listener)
{
    int *pPrev;
    int *pCurr;
    int *pNext;

    pPrev = (int *)&this->first; // pPrev = listener link pointer
    this->vtable = (int)&PTR_LAB_00e4081c; // some base vtable?
    
    if (*(int *)pPrev != 0) {
        pCurr = *(int **)(*(int *)pPrev + 4); // pCurr = current node's next pointer
        if (pCurr == pPrev) {
            // Only one element, remove it directly
            *(int *)(*(int *)pPrev + 4) = (int)&this->last; // +0x08: last pointer
            this->vtable = (int)&PTR___purecall_00e407a4;
            return;
        }
        
        pNext = (int *)pCurr[1]; // pCurr->next
        while (pNext != pPrev) {
            pCurr = (int *)pCurr[1]; // pCurr = pCurr->next
            pNext = (int *)pCurr[1]; // pNext = pCurr->next
        }
        
        // Remove node by updating previous node's next pointer
        pCurr[1] = (int)&this->last; // +0x08: last pointer
    }
    
    this->vtable = (int)&PTR___purecall_00e407a4;
}