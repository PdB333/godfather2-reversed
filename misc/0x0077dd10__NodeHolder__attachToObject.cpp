// FUNC_NAME: NodeHolder::attachToObject
// Address: 0x0077dd10
// Role: Attaches this object to a target object via an intrusive link node.
// The target object must have a Node structure at offset 0x48 containing a back-pointer at +4.
// Copies 16 bytes of data from the target's offsets 0x60 and 0x68 into this object's offsets 4 and 0xC.

void __thiscall NodeHolder::attachToObject(void* param_2) {
    // this+0x14: pointer to the attached Node (inside the target object)
    int* pAttachedNode = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x14);
    
    // Compute the new node pointer: if param_2 is non-null, node is at param_2+0x48
    int* newAttachedNode = nullptr;
    if (param_2 != nullptr) {
        newAttachedNode = reinterpret_cast<int*>(reinterpret_cast<char*>(param_2) + 0x48);
    }
    
    // If the new node is different from the current one, update the link
    if (*pAttachedNode != reinterpret_cast<int>(newAttachedNode)) {
        // Detach old node if present
        if (*pAttachedNode != 0) {
            FUN_004daf90(pAttachedNode); // presumably removes/cleans old node link
        }
        *pAttachedNode = reinterpret_cast<int>(newAttachedNode);
        
        // If we have a new node, insert it into the linked list
        if (newAttachedNode != nullptr) {
            // Save the previous back-link stored in the node into this+0x18
            *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x18) = *reinterpret_cast<int*>(reinterpret_cast<char*>(newAttachedNode) + 4);
            // Set the node's back-link to point to our pAttachedNode field
            *reinterpret_cast<int**>(reinterpret_cast<char*>(newAttachedNode) + 4) = pAttachedNode;
        }
    }
    
    // Retrieve the base of the owning object (subtract 0x48 from node address)
    int* owningObjectBase = nullptr;
    if (*pAttachedNode == 0) {
        owningObjectBase = nullptr;
    } else {
        owningObjectBase = reinterpret_cast<int*>(*pAttachedNode - 0x48);
    }
    
    // Copy 8-byte values from the owning object's offsets 0x60 and 0x68
    // into this object's offsets 0x4 and 0xC (likely position/velocity data)
    *reinterpret_cast<unsigned long long*>(reinterpret_cast<char*>(this) + 4) =
        *reinterpret_cast<unsigned long long*>(reinterpret_cast<char*>(owningObjectBase) + 0x60);
    *reinterpret_cast<unsigned long long*>(reinterpret_cast<char*>(this) + 0xC) =
        *reinterpret_cast<unsigned long long*>(reinterpret_cast<char*>(owningObjectBase) + 0x68);
}