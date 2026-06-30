// FUNC_NAME: TimerCallback::setCallbackAndStartTimer
void __thiscall TimerCallback::setCallbackAndStartTimer(void* this, void* callbackNode) 
{
    // this offsets:
    // +0x0c : callback ID (used for enable/disable calls)
    // +0x10 : pointer to callback node (intrusive list node, offset +0x04 is "prev pointer" to pointer that points to this node)
    // +0x14 : saved previous "prev pointer" of the node at +0x10
    // +0x3c : flags (bit0 = active?)
    // +0x50 : current timer value (float)

    int** nodePtrPtr = (int**)((char*)this + 0x10); // pointer to the stored node pointer
    int* existingNode = *nodePtrPtr;

    // Remove old callback node if present
    if (existingNode != 0) {
        g_callbacks_setActive(0, 0); // disable? first arg 0 = disable, second unused here
        if (*nodePtrPtr != 0) {
            g_list_unlinkNode(nodePtrPtr); // unlink and free? or just unlink
            *nodePtrPtr = 0;
        }
    }

    // Clear active flag
    *(uint32_t*)((char*)this + 0x3c) &= 0xFFFFFFFE;

    // Replace node pointer if different
    if (*nodePtrPtr != callbackNode) {
        if (*nodePtrPtr != 0) {
            g_list_unlinkNode(nodePtrPtr); // unlink old node again? (redundant here but safe)
        }
        *nodePtrPtr = (int*)callbackNode; // store new node

        if (callbackNode != 0) {
            // Save the node's current "prev pointer" (offset +0x04) into container's +0x14
            *(int*)((char*)this + 0x14) = *(int*)((char*)callbackNode + 4);
            // Set the node's "prev pointer" to point to the container's pointer storage (+0x10)
            *(int**)((char*)callbackNode + 4) = nodePtrPtr;
        }
    }

    // If a node is set, randomize timer and enable callback
    if (*nodePtrPtr != 0) {
        bool isActive = g_callbacks_isActive(*(uint32_t*)((char*)this + 0x0c));
        if (!isActive) {
            int randVal = _rand();
            float f = (float)randVal * DAT_00e44590 * _DAT_00d61b30 - _DAT_00d5780c;
            f += DAT_01205228; // base timer
            *(float*)((char*)this + 0x50) = f;
        }
        g_callbacks_setActive(1, *(uint32_t*)((char*)this + 0x0c)); // enable with ID
    }
}