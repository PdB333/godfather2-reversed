// FUN_NAME: EntityDataManager::addEntityToSlot
// Function address: 0x00876540
// This function creates a new scene entity (SpatialNode) with given position, rotation, and parent,
// then adds it to a slot-specific linked list in the manager.

// Note: EARS engine internal calls are given descriptive names based on observed behavior.
// Memory allocation, matrix/transform operations, and scene graph attachment are abstracted.

class EntityDataManager {
    // Offset 0xdc4: Array of linked list heads for entity slots (each slot 8 bytes: pointer + next)
};

void __thiscall EntityDataManager::addEntityToSlot(
    int index,                     // param_2: Slot index (e.g., entity type/group)
    const float* position,         // param_3: 3D position (x, y, z)
    const unsigned int* quaternion,// param_4: Quaternion (4 floats) for rotation
    unsigned int parentHandle1,    // param_5: Parent scene graph handle (type unknown)
    unsigned int parentHandle2,    // param_6: Additional parent info
    unsigned int parentNode,       // param_7: Parent node ID for attachment
    unsigned char flags)           // param_8: Flags stored at +0x88 (bitmask)
{
    // Allocate memory for a new scene node (size 0x8c = 140 bytes)
    int* newNode = (int*)allocateMemory(0x8c);
    if (newNode) {
        newNode = (int*)constructSpatialNode(); // FUN_006e8950 - constructor
    } else {
        newNode = 0;
    }

    // Initialize local quaternion storage to identity (from global constant)
    unsigned int localQuat[4];
    unsigned int identityQuat = _DAT_00d5780c; // Identity quaternion constant
    // local_9c = 0; local_98 = identityQuat; local_94 = 0; (first three components?)
    // Actually it sets up a struct for copyQuaternion call.
    unsigned int quatData[4] = {0, identityQuat, 0, 0}; // Simplified; actual layout unknown

    // Copy the given quaternion (param_4) into local storage with zero stride?
    copyQuaternion((unsigned int*)&localTemp, quatData, (unsigned int)quaternion, 0); // FUN_0046cf70

    // Add position offset (param_3) to the existing local position (likely accumulated)
    // local_60, fStack_5c, fStack_58 are floats for position (note: they are after quaternion)
    float posX = position[0] + localPositionX; // local_60 initially zero
    float posY = position[1] + localPositionY; // fStack_5c
    float posZ = position[2] + localPositionZ; // fStack_58

    // Set transform to identity (world matrix setup)
    setIdentityTransform(); // FUN_00471610

    // Build a matrix from position and quaternion using a helper
    buildTransformMatrix(&transformMatrix); // FUN_00874740 — writes to local_50 area

    localTemp = transformMatrix; // copy matrix blocks into final storage local_90..uStack_54 = position floats reinterpreted as ints? Actually this copies uint32 representation of position floats into uint fields… This is messy, likely due to decompiler limitations. We'll treat as assigning matrix fields then extracting position floats from uint values (casting is unsafe but exists in original engine code due to alignment tricks? Not exactly portable C++ style; we<｜begin▁of▁file｜>
somehow reconstruct naturally: assign transformMatrix to local_90 array and then copy position floats into final spots local_60, fStack_5c, fStack_58 by casting from int fields (local_20, uStack_1c, uStack_18). //end comment
    // This is a non-portable optimization; for simplicity we assume the engine's matrix layout is row-major with position in last row, and positions are extracted via reinterpret_cast.
    // Since we don't have exact structs, we skip the detailed bit copying and just use the already stored posX, posY, posZ.

    // Attach the new node to scene graph using parent handles
    attachToParent(parentHandle1, parentHandle2); // FUN_006e5d90
    updateChildList(&localTemp);                  // FUN_006e5b40
    setParentNodeId(parentNode);                  // FUN_006e5d30
    setParentNodeNew(parentNode);                 // FUN_006e5d60

    // Store the flags byte at offset +0x88
    *(unsigned char*)(newNode + 0x88) = flags;

    // Register with the scene manager (global DAT_00d5f540)
    unsigned int sceneManager = _DAT_00d5f540; // global scene manager
    registerWithScene(sceneManager); // FUN_006e8760

    // Set a flag at offset +0x8a (bit 3 set)
    *(unsigned char*)(newNode + 0x8a) |= 8;

    // Finalize the node (internal registration)
    finalizeNode(newNode); // FUN_006e7260

    // Now add the new node into the slot-specific linked list at this+0xdc4 + index*8
    int* slotHead = (int*)((unsigned int)this + 0xdc4 + index * 8);
    int oldNode = *slotHead; // first pointer in slot
    if (oldNode != (int)newNode) {
        if (oldNode != 0) {
            removeFromSlotList(slotHead); // FUN_004daf90 — remove old entry? Why? Actually this removes the node if already in list? The logic: if slotHead[0] != newNode, and slotHead[0] != 0, then call FUN_004daf90(slotHead) which likely removes the node from the linked list (update neighbors). Then insert newNode as head.
        }
        // Insert newNode at head of the slot's list
        *slotHead = (int)newNode;
        slotHead[1] = *(int*)(newNode + 4); // next pointer of newNode (originally stored at +4)
        *(int**)(newNode + 4) = slotHead; // set newNode->next to slotHead (back link)
    }
}