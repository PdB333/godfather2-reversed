// FUNC_NAME: NetConnection::addPendingPacket
// Address: 0x00625f80
// This function searches for an existing packet element at the given index (or from the start if index < 1)
// of type 5 or 7 within a send queue. If the packet's target ID (read from +0x8 of the pointed object)
// is non-zero and different from the current send ID stored at +0x38 (relative to a pointer at +0x10),
// it appends a new packet element of type 5 with that target ID to the queue and returns 1.
// Returns 0 if nothing was added or invalid.

int __thiscall NetConnection::addPendingPacket(int index)
{
    // +0x08: int* mWritePtr (current write position in queue)
    // +0x0C: int* mQueueBase (base pointer - 8? actually used as base for index calculation)
    // +0x10: int* mConnectionContext (pointer to a structure with a send ID at +0x38)
    // Queue elements are 8 bytes: int type, int* value (pointer to an object with field at +0x08)
    
    int *pElement;
    int targetId;
    
    if (index < 1) {
        // Get pointer to the first element (index 0) using a helper function
        pElement = (int *)GetFirstElement();  // calls FUN_00625430
    }
    else {
        // Calculate pointer to element at given index
        pElement = (int *)(*(int *)(this + 0x0C) - 8 + index * 8);
        // If the calculated pointer is beyond current write position, invalid
        if (pElement >= *(int **)(this + 0x08)) {
            return 0;
        }
    }
    
    if (pElement != (int *)0x0) {
        // Check for element types 5 or 7
        if (*pElement == 5) {
            targetId = *(int *)(pElement[1] + 8);   // read target ID from the pointed object's +0x08
        }
        else if (*pElement == 7) {
            targetId = *(int *)(pElement[1] + 8);
        }
        else {
            return 0;   // unsupported type
        }
        
        // Add a new element if targetId is valid and not already the current send ID
        if (targetId != 0 && targetId != *(int *)(*(int *)(this + 0x10) + 0x38)) {
            int *pWrite = *(int **)(this + 0x08);
            *pWrite = 5;                          // type = 5 (reliable packet)
            pWrite[1] = targetId;                 // value = target ID
            *(int *)(this + 0x08) += 8;           // advance write pointer
            return 1;
        }
    }
    return 0;
}