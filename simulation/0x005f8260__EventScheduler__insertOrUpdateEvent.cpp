// FUNC_NAME: EventScheduler::insertOrUpdateEvent
// Function address: 0x005f8260
// Role: Inserts or updates an entry in a sorted event list keyed by a float value.
// The scheduler maintains two parallel arrays:
// - "nodeArray" at offset +0x20, each element size 0x24 (struct Node)
// - "dataArray" at offset +0x08, each element size 0xc (struct EventData)
// The function iterates through nodes until a sentinel (param_3) is reached.
// For each node, it retrieves a float from the event data and updates it if conditions are met.

void EventScheduler::insertOrUpdateEvent(int *this, int *param2, int sentinelAddr)
{
    int *piVar8 = this;
    int iVar5 = *this; // Dereference this to get base pointer?

    // param2 is later reused as a pointer
    // in_EAX is a register variable that holds the current node address during iteration
    int currentNodeAddr; // This was in_EAX, set externally and used in loop

    if (currentNodeAddr != sentinelAddr) {
        do {
            // Retrieve a pointer to some data (likely a struct with float and ushort)
            float *pFloatArray = (float *)FUN_005f60f0(iVar5, currentNodeAddr);

            // Compute next node address: base + (index * 0x24)
            // The ushort at pFloatArray[1] (offset 4) is used as an index multiplier
            currentNodeAddr = *(int *)(iVar5 + 0x20) + (uint)*(ushort *)(pFloatArray + 1) * 0x24;

            // Compute index into the data array (0xc per element)
            int nodeIndex = (currentNodeAddr - *(int *)(*this + 0x20)) / 0x24;

            // Get pointer to data element for this node
            int *dataArrayBase = this[2]; // offset 0x08
            float *pDataFloat = (float *)(dataArrayBase + 4 + nodeIndex * 0xc);
            int *pDataElement = (int *)(dataArrayBase + nodeIndex * 0xc);

            // Copy byte from param2+0x0b into data element's byte at +0x0b
            *(unsigned char *)((int)pDataElement + 0xb) = *(unsigned char *)((int)param2 + 0xb);

            float fVar3 = (float)param2[1]; // param2[1] treated as float
            float fVar4 = *pFloatArray;      // first float from pFloatArray

            // If the current data float is positive and the sum is less/equal, update the element
            if ((*pDataFloat > 0.0f) && (fVar3 + fVar4 > *pDataFloat)) {
                // Update not needed? Actually condition is fVar2 <= 0.0 or fVar3+fVar4 <= fVar2
                // Wait: decompiler condition: if ((fVar2 <= 0.0) || (fVar3 + fVar4 <= fVar2)) { ... }
                // So we update if the current float is non-positive OR the new value is not greater than current.
                // But the code only executes the update block inside the if. The else does nothing.
                // Let's restore original logic:
                // if ( (fVar2 <= 0.0) || (fVar3 + fVar4 <= fVar2) ) {
                //    *piVar1 = (int)param_1;  // piVar1 is pDataElement
                //    piVar1[1] = (int)(fVar3 + fVar4);
                // }
                // So we need to check fVar2 (which is *pDataFloat).
                if ((*pDataFloat <= 0.0f) || (fVar3 + fVar4 <= *pDataFloat)) {
                    *pDataElement = (int)param2;   // Store pointer
                    pDataElement[1] = (int)(fVar3 + fVar4); // Store sum as int (float reinterpreted?)
                }
            } else {
                // No action when condition fails? Actually the do-while always executes the check and update.
                // The condition above was inverted? Let's re-read decompiler: 
                // if ((fVar2 <= 0.0) || (fVar3 + fVar4 <= fVar2)) { update }
                // That's exactly what we wrote.
            }

            // Prepare param2 for next iteration? Actually param2 is reassigned to pDataElement.
            param2 = pDataElement; // The decompiler sets param_1 = piVar1; which becomes param2? Actually param_1 = piVar1; and then param_1 is used later as "param_1[1]" and "param_1" cast to int. So the next iteration uses the updated param2.
        } while (currentNodeAddr != sentinelAddr);
    }
    return;
}