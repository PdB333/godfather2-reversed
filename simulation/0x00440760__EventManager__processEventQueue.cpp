// FUNC_NAME: EventManager::processEventQueue
// Function address: 0x00440760
// Role: Processes scheduled events/timers from a queue. Handles type-specific actions:
//   - Type 0x012069c4: Walk a per-slot list of pending events and fire them if delay expired.
//   - Type 0x012067cc: Immediately execute a secondary event handler (FUN_004408c0).

void __thiscall EventManager::processEventQueue(EventManager* this, EventTypeInfo* info) {
    uint currentTime = DAT_01205224;            // Global tick counter

    if (info->type == EVENT_TYPE_TIMER) {        // 0x012069c4
        // Get slot pointer from indexed array
        int slotIndex = *(short*)((char*)this + 0x12);  // +0x12: slot index
        int* slotArray = *(int**)((char*)this + 0x14); // +0x14: pointer to array of slot structs
        int* slot = (int*)(slotArray + slotIndex);     // slot struct base

        if (*(int*)(slot + 0x1c/4) != 0) {            // +0x1c: count of pending events in this slot
            while (true) {
                // Get head of event node list (circular sentinel)
                int* head = **(int***)(slot + 0x18/4); // +0x18: pointer to list head
                if (head == *(int**)(slot + 0x18/4)) { // Circular sentinel check (empty list)
                    FUN_00b97aea();                    // assert/abort?
                }

                // Check if event's target time has been reached
                if (currentTime < (uint)head[5])       // head[5] = +0x14: target time
                    break;                             // Not yet due, exit loop

                // Fetch event data
                int objectId = head[3];                // +0x0c: object ID
                int* targetObject = head[2];           // +0x08: pointer to target object (or NULL)
                int* callbackObject = head[6];         // +0x18: callback interface pointer

                byte dummy = 0;                        // local_c (unused?)
                FUN_00408a00(&objectId, 0);            // Acquire reference on object ID

                // If target object exists and has a valid reference flag
                if (targetObject != NULL && objectId != 0 &&
                    ((*(byte*)((char*)targetObject + 4) & 1) != 0)) {  // +0x04: ref count flag

                    // Look up object in global hash table (ID -> object)
                    uint hashIndex = (uint)(objectId & 0xFFF);
                    void** bucket = (void**)DAT_01162380; // Global hash table base
                    void* objNode = bucket[hashIndex];
                    while (objNode != NULL && *(int*)((char*)objNode + 16) != (int)objectId) { // +0x10: ID field
                        objNode = *(void**)objNode;       // next pointer at +0x00
                    }

                    if (objNode != NULL) {
                        ushort flags = *(ushort*)((char*)objNode + 0x16); // +0x16: flags word
                        *(ushort*)((char*)objNode + 0x16) = flags | 1;   // Set bit 0 (active flag)

                        // Call target object's method (vtable offset 4)
                        (**(code**)(*targetObject + 4))(&objectId);

                        // Restore flag (clear bit 0)
                        *(ushort*)((char*)objNode + 0x16) = (flags & 1) | (*(ushort*)((char*)objNode + 0x16) & 0xFFFE);

                        // If it came from a valid reference and was not active before, release reference
                        if (*(int*)((char*)objNode + 12) != 0 && (flags & 1) == 0) { // +0x0c: ref count
                            FUN_00408af0();       // Release reference
                        }
                    }
                }

                // If callback object exists and is not flagged, invoke its method with argument 1
                if (callbackObject != NULL && ((*(byte*)((char*)head + 0x1c) & 1) == 0)) { // +0x1c: callback flags
                    (**(code**)*(int**)callbackObject)(1);  // Call vtable[0] (first virtual function)
                }

                // Remove processed event node from the slot list
                FUN_00440e30(slot, (char*)local_1c, slot, **(void***)(slot + 0x18/4));
                // After removal, check if slot is now empty
                if (*(int*)(slot + 0x1c/4) == 0)
                    return;
            }
        }
    }
    else if (info->type == EVENT_TYPE_IMMEDIATE) { // 0x012067cc
        // Immediate action: call handler with secondary data
        FUN_004408c0(info->data, 0, 0);             // info->data at offset 4
    }
    return;
}