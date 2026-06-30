// FUNC_NAME: GameObject::setTargetLink
struct Vector3 { float x, y, z; };
struct Quaternion { float w, x, y, z; };

struct LinkedNode {
    int* ownerPtr;    // +0x00: pointer to owner's node pointer (m_pLinkNode)
    LinkedNode* next; // +0x04: pointer to next node in list
    int* prev;        // +0x08: (if needed) 
};

struct GameObject {
    // offsets based on decompiled code
    // +0x54: vtable? or some method table
    // +0x68: m_pLinkNode (LinkedNode*)
    // +0x6c: m_pLinkNodePrev (LinkedNode*)
    // +0x70: m_targetPosition (Vector3)
    // +0x74: m_targetRotation (Quaternion)
    // +0x78: m_targetData (uint)
    // +0x15e: m_flags (ushort) - bit 0 is used for attachment state
    // +0x164: m_isActive (int) - bool for active state
};

// External function declarations from callees
void LinkedNode_detach(LinkedNode* node); // FUN_004daf90
bool EventRecorder_beginEvent();          // FUN_004709e0

// Global event buffer pointer (DAT_01206880 + 0x14)
extern uint8* g_eventBufferPtr;

void __thiscall GameObject::setTargetLink(GameObject* thisPtr, GameObject* pTargetObject,
                                          Vector3* position, Quaternion* rotation,
                                          int param_flags, uint param_data) {
    // Bitfield handling for m_flags at +0x15e
    ushort* flags = (ushort*)((uint8*)thisPtr + 0x15e);
    if (param_flags == 0) {
        *flags &= 0xfffe; // Clear bit 0 (attachment flag)
    } else {
        *flags |= (ushort)param_flags; // Set specified bits
    }

    // Linked node at +0x68
    LinkedNode** nodePtr = (LinkedNode**)((uint8*)thisPtr + 0x68);
    LinkedNode* targetNode = nullptr;
    if (pTargetObject != nullptr) {
        // Target object's node is at offset +0x48
        targetNode = (LinkedNode*)((uint8*)pTargetObject + 0x48);
    }

    if (*nodePtr != targetNode) {
        if (*nodePtr != nullptr) {
            LinkedNode_detach(*nodePtr);
        }
        *nodePtr = targetNode;
        if (targetNode != nullptr) {
            // Save the previous next pointer of targetNode into our node's back pointer (+0x6c)
            *(LinkedNode**)((uint8*)thisPtr + 0x6c) = targetNode->next;
            // Insert our node before targetNode by updating targetNode's next
            targetNode->next = (LinkedNode*)((uint8*)thisPtr + 0x68);
        }
    }

    // Store position, rotation, and data
    *(Vector3*)((uint8*)thisPtr + 0x70) = *position;
    *(Quaternion*)((uint8*)thisPtr + 0x74) = *rotation;
    *(uint*)((uint8*)thisPtr + 0x78) = param_data;

    // If the object is active (+0x164), record an event into the global buffer
    if (*(int*)((uint8*)thisPtr + 0x164) != 0) {
        // Determine effective target object from the node (if any)
        int effectiveTarget = 0;
        if (*nodePtr != nullptr) {
            effectiveTarget = (int)((uint8*)*nodePtr - 0x48); // Recover object pointer
        }

        // Call a virtual method on the target (offset 0x50 from its vtable at +0x54)
        if (effectiveTarget != 0) {
            int vtable = *(int*)(effectiveTarget + 0x54);
            (*(void (__thiscall**)(int))vtable[0x50])(effectiveTarget);
        }

        // Push event data into a global serialization/event buffer
        uint8** bufferPtr = (uint8**)(*(uint8**)g_eventBufferPtr + 0x14);
        *(void**)*bufferPtr = (void*)&PTR_LAB_0110baa8; // Some event type marker
        *bufferPtr += 4;

        *(int*)*bufferPtr = (int)((uint8*)thisPtr + 0x54); // Address of thisPtr's field
        *bufferPtr += 4;

        int targetField = 0;
        if (pTargetObject != nullptr) {
            targetField = (int)((uint8*)pTargetObject + 0x54);
        }
        *(int*)*bufferPtr = targetField;
        *bufferPtr += 4;

        bool eventResult = EventRecorder_beginEvent();
        *(void**)*bufferPtr = (void*)&PTR_LAB_0110bad0; // Another marker
        *bufferPtr += 4;
        *(int*)*bufferPtr = (int)extraout_EDX; // Possibly a state flag from the call
        *bufferPtr += 4;
        *(bool*)*bufferPtr = eventResult;
        *bufferPtr += 4;
        // Align to next 4-byte boundary
        *bufferPtr = (uint8*)(((uint32)*bufferPtr) & 0xfffffffc);
    }
}