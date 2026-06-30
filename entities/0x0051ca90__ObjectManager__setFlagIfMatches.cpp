// FUNC_NAME: ObjectManager::setFlagIfMatches
// Function address: 0x0051ca90
// This function iterates a linked list of objects (global head at 0x01205514) and sets a flag (0x20000000) at offset +0x0C on nodes where:
//   - The input parameter (objectId) is 0 (match all), or
//   - The node's object pointer (at +0xC4) is non-null and its adjusted value (base - 0x48) equals objectId.
// This is likely a "mark for update / ghost" operation in the EA EARS engine.

// Offsets documented:
// +0x0C: uint32 flags (bit 29 = 0x20000000 used here)
// +0x14: pointer to next node in the linked list
// +0xC4: pointer to some sub‑object (used to derive a match value)

void __fastcall ObjectManager::setFlagIfMatches(void* thisPointer, int objectId)
{
    int* nodePtr;
    int currentNode;
    int adjustedValue;

    // Global head of the linked list of objects
    currentNode = DAT_01205514;
    if (DAT_01205514 != 0) {
        do {
            if (objectId == 0) {
                // objectId == 0 matches every node
SET_FLAG:
                // Set bit 0x20000000 (bit 29) in the flags field
                *(uint32*)(currentNode + 0x0C) |= 0x20000000;
            }
            else {
                // Derive a comparison value from the node's sub‑object pointer at +0xC4
                if (*(int*)(currentNode + 0xC4) == 0) {
                    adjustedValue = 0;
                }
                else {
                    adjustedValue = *(int*)(currentNode + 0xC4) - 0x48;
                }
                // If the derived value matches the given objectId, set the flag
                if (objectId == adjustedValue) {
                    goto SET_FLAG;
                }
            }
            // Move to the next node (offset +0x14 is the 'next' pointer)
            nodePtr = (int*)(currentNode + 0x14);
            currentNode = *nodePtr;
        } while (*nodePtr != 0);
    }
}