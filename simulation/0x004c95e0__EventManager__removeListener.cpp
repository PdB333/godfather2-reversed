// FUNC_NAME: EventManager::removeListener
// Function at 0x004c95e0: Iterate over a linked list of listener objects, find one with matching ID (at +0x290),
// and deactivate it (clear flag at +0x04, zero out ID). Uses a global pointer (DAT_01223508) for removal.
// Offsets:
// param_1 (this): +0x10 -> pointer to iterator context
// Iterator context: +0x1c -> pointer to head pointer (pointer to first node)
// List node: +0x10 -> pointer to listener object
// Listener object: +0x04 -> byte (active flag), +0x290 -> int (ID)

void EventManager::removeListener( int param_2 )
{
    int* pIteratorContext = *(int**)(this + 0x10);
    int* pNode = **(int***)(pIteratorContext + 0x1c);  // pNode = first node in list

    while ( true ) {
        int* pHead = *(int**)(*(int*)(this + 0x10) + 0x1c);  // re-read head (may change)
        // Check iterator validity: pIteratorContext must not be null and still match this->m_pIterator
        if ( pIteratorContext == 0 || pIteratorContext != *(int**)(this + 0x10) ) {
            __assert_fail();  // FUN_00b97aea – likely assertion failure
        }

        if ( pNode == pHead )
            break;   // reached end of list

        if ( pIteratorContext == 0 ) {
            __assert_fail();
        }
        if ( pNode == *(int**)(pIteratorContext + 0x1c) ) {
            __assert_fail();   // sanity check – node should not equal head pointer?
        }

        int* pListener = *(int**)(pNode + 0x10);   // listener object
        int listenerId = *(int*)(pListener + 0x290);

        if ( listenerId == param_2 ) {
            if ( (*(char*)(pListener + 0x04) != 0) && (listenerId != 0) ) {
                removeFromGlobalList( DAT_01223508, listenerId );   // FUN_005ddd90
                *(char*)(pListener + 0x04) = 0;   // clear active flag
            }
            *(int*)(pListener + 0x290) = 0;   // clear ID
        }

        advanceIterator();   // FUN_004cab50 – move to next node
    }
    return;
}