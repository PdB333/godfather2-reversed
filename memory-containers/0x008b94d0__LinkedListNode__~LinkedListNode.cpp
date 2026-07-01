// FUNC_NAME: LinkedListNode::~LinkedListNode
class LinkedListNode {
public:
    // Offset +0x18: pointer to previous node
    LinkedListNode* prevNode;
    // Offset +0x1c: pointer to next node
    LinkedListNode* nextNode;
    // Offset +0x20: pointer to owned data (or another node)
    void* dataPtr;
    // Offset +0x28: vtable pointer (immortal)
    void* vtablePtr;

    // Constructor and other members omitted

    // Destructor (flag param_2 indicates whether to deallocate via operator delete)
    __thiscall ~LinkedListNode(char deleteFlag) {
        // Set vtable to a base class vtable (often done in destructors)
        *(void***)(this + 0x28) = &PTR_LAB_00e317cc;

        // Unlink this node from the linked list
        // The list uses a non‑standard linking scheme:
        // - If only prev exists (next is null), update prev->field+0x4 with dataPtr
        // - Else if both exist, update next->field+0x8 with dataPtr
        // - Also, if dataPtr is non-null, update dataPtr->field+0x4 with nextNode
        if (prevNode != nullptr) {
            if (nextNode == nullptr) {
                *(int*)((char*)prevNode + 4) = (int)dataPtr;
            } else {
                *(int*)((char*)nextNode + 8) = (int)dataPtr;
            }
            if (dataPtr != nullptr) {
                *(int*)((char*)dataPtr + 4) = (int)nextNode;
            }
        }

        // Call base class cleanup (likely a virtual destructor)
        FUN_0064d150();

        // If delete flag is set, perform object deallocation
        if (deleteFlag & 1) {
            FUN_009c8eb0(this);
        }
    }
};