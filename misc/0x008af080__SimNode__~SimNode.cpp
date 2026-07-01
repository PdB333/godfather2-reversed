// FUNC_NAME: SimNode::~SimNode
// Address: 0x008af080

int __thiscall SimNode::~SimNode(SimNode* this, byte deleteFlag)
{
    // Call base class destructor
    BaseSimNode::~BaseSimNode();

    // Restore vtable pointer (likely to this class' vtable after base destruction)
    *(void***)(this + 0x28) = &PTR_LAB_00e317cc; // vtable for SimNode

    // Remove this node from doubly linked list
    // Offsets: +0x18 = prev, +0x1c = next, +0x20 = data pointer (or another node?)
    SimNode* prev = *(SimNode**)((uint)this + 0x18);
    SimNode* next = *(SimNode**)((uint)this + 0x1C);
    void* data = *(void**)((uint)this + 0x20);

    if (prev != 0) {
        if (next == 0) {
            // If this is last node, update previous node's forward pointer
            *(void**)((uint)prev + 4) = data;
        } else {
            // Otherwise update next node's backward pointer
            *(void**)((uint)next + 8) = data;
        }
    }

    if (data != 0) {
        // Update data's backward pointer
        *(void**)((uint)data + 4) = next;
    }

    // Additional cleanup
    DestructorPart2(&this->field_0x?); // FUN_0064d150()

    // If deleteFlag & 1, free memory
    if ((deleteFlag & 1) != 0) {
        OperatorDelete(this); // FUN_009c8eb0()
    }

    return (int)this;
}