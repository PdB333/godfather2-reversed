// FUNC_NAME: ParentObject::attachChildNode
// Function at 0x00509160: Attaches a child node located at offset 0x48 from the given child object.
// Handles detachment of old node and sets backlink at node+4.
// Helper function FUN_004daf90 (releaseNode) is called to release the previously attached node.

void __thiscall ParentObject::attachChildNode(int childObject)
{
    int **ppNode = (int **)(this + 0x14); // Pointer to current child node (stored at this+0x14)
    int *newChildNode;

    // If childObject is non-null, the actual node is at offset 0x48 inside it
    if (childObject == 0) {
        newChildNode = (int *)0;
    } else {
        newChildNode = (int *)(childObject + 0x48);
    }

    // Only change if different
    if (*ppNode != newChildNode) {
        // Release old node if it existed
        if (*ppNode != 0) {
            releaseNode(ppNode); // FUN_004daf90 - detaches/ cleans up the previous node
        }
        // Store new node pointer
        *ppNode = newChildNode;
        // If new node is valid, set its backlink (at offset +4) to point to our pointer location
        if (newChildNode != 0) {
            *(int **)(newChildNode + 1) = ppNode; // newChildNode[1] = backlink address
        }
    }
}