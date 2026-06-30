// FUNC_NAME: RenderNode::initialize
// Reconstructed C++ for FUN_00720c90 (0x00720c90) - RenderNode initialization with linked list insertion and data copy
// This function initializes a RenderNode and inserts it into a parent object's list.
// Offsets:
//   +0x00: pointer to parent list head (or 0 if unattached)
//   +0x04: next pointer in singly linked list
//   +0x08: pointer to allocated child (size 0xd0) or 0
//   +0x0C: 8-byte data block (e.g., transform or position)
//   +0x14: 8-byte data block
//   +0x1C: count of elements in internal array at +0x30
//   +0x20: pointer to internal array (pointing to +0x30)
//   +0x30: array of ints (size determined by count)

void __thiscall RenderNode::initialize(
    int *thisNode,
    int *parentObject,
    int handle,
    float posX,
    float posY,
    float posZ,
    RenderNodeData *data       // structure with two 8-byte values, an int count, and an int array
)
{
    int *parentNode;            // pointer to list head inside parentObject
    uint loopIndex;
    int newChild;
    uint localCount;
    float local_30, local_2c, local_28, local_20, local_1c, local_18;

    // Determine parent list head.
    // The parent object contains a list node at offset 0x48.
    if (parentObject == (int *)0) {
        parentNode = (int *)0;
    } else {
        parentNode = parentObject + 0x12;   // +0x48 bytes assuming int* (4 bytes each, 0x48/4 = 0x12)
    }

    // Insert this node into the parent's singly-linked list.
    if (thisNode[0] != (int)parentNode) {
        if (thisNode[0] != 0) {
            // Remove from previous list
            FUN_004daf90(thisNode);
        }
        thisNode[0] = (int)parentNode;                    // store pointer to list head
        thisNode[1] = parentNode[1];                      // copy parent's next pointer to our next
        parentNode[1] = (int)thisNode;                    // parent's next points to us
    }

    // Load global constants (likely screen dimensions, time, aspect ratio, etc.)
    local_2c = _DAT_00d5cf70;           // e.g., delta time or aspect
    local_30 = DAT_00e44564 - posX;     // e.g., screen width - x
    local_18 = posY * _DAT_00d5c458;    // e.g., y * some factor
    local_28 = posY * DAT_00e44718;     // e.g., y * screen height factor?

    // Copy data from input structure to node fields
    *(undefined8 *)(thisNode + 3) = *data;          // copy first 8 bytes
    *(undefined8 *)(thisNode + 5) = data[1];        // copy second 8 bytes
    thisNode[7] = *(int *)((int)data + 8);          // copy count from data->count
    local_20 = posX;
    thisNode[6] = (int)(thisNode + 0x30);           // pointer to internal array at +0x30

    // Copy integer array from data into internal array
    localCount = 0;
    local_1c = posZ + local_2c;
    if (*(int *)((int)data + 8) != 0) {             // if count > 0
        loopIndex = 0;
        do {
            localCount = localCount + 1;
            thisNode[loopIndex + 0x30] = *(int *)(*(int *)((int)data + 0xc) + loopIndex * 4);
            loopIndex = (uint)localCount;
        } while (loopIndex < (uint)*(int *)((int)data + 8));
    }

    // Call helper to set up additional data (e.g., viewport or camera)
    FUN_00720a60(handle, posX, posY, posZ);

    // If we already have a child object, release it
    if (thisNode[2] != 0) {
        FUN_00851230(thisNode[2]);      // Release/Free child
        FUN_009f01a0();                 // Some cleanup
        thisNode[2] = 0;
    }

    // Allocate new child object of size 0xd0 bytes
    TlsGetValue(DAT_01139810);          // Get thread-local storage
    newChild = FUN_00aa2680(0xd0, 0x31); // Allocate with tag 0x31
    *(undefined2 *)(newChild + 4) = 0xd0; // Store size at +4

    // Initialize child with transform data from thisNode
    int transformID = FUN_00540cc0(thisNode + 3); // Compute ID or index from data
    newChild = FUN_009f59e0(&local_30, transformID); // Create child using local_30 (probably position)
    thisNode[2] = newChild;

    // If child was created, notify parent of new child
    if (newChild != 0) {
        int parentIdx;
        if (thisNode[0] == 0) {
            parentIdx = 0;
        } else {
            parentIdx = thisNode[0] - 0x48 / sizeof(int); // Reverse of +0x48 offset to get parentObject
        }
        FUN_0043b490();                     // Prepare notification?
        FUN_009f01f0(0x2001, parentIdx, 0); // Send event with type 0x2001
    }

    FUN_00851210(thisNode[2]);              // Add reference or start using child
    return;
}