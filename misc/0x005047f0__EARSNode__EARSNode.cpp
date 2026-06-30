// FUNC_NAME: EARSNode::EARSNode
void __thiscall EARSNode::EARSNode(EARSNode *this, void *param1, int param2, short param3, byte param4, void *param5, void *param6, void *param7)
{
    EARSNode *prevNode;
    int iVar2;
    void *eaxVal;
    EARSNode *nodePtr;

    // Store constructor arguments into member fields
    this->field_04 = eaxVal;               // +0x04: stored from in_EAX (likely return value)
    this->field_08 = param6;               // +0x08
    this->field_0C = param7;               // +0x0C
    this->field_18 = param2;               // +0x18 (offset 0x18 = 6*4)
    this->field_1C = param3;               // +0x1C (short)
    this->field_1E = param4;               // +0x1E (byte)
    this->field_20 = param1;               // +0x20 (offset 0x20 = 8*4)
    this->field_24 = param5;               // +0x24 (offset 0x24 = 9*4)

    // Initialize vtable pointer
    this->vtable = &PTR_FUN_00e37f3c;      // +0x00

    // Initialize list pointers (next, prev, etc.)
    this->field_30 = nodePtr;              // +0x30 (offset 0x30 = 0xc*4)
    this->field_34 = nodePtr;              // +0x34 (offset 0x34 = 0xd*4)
    this->field_38 = nodePtr;              // +0x38 (offset 0x38 = 0xe*4)

    // Clear a large block (48 bytes) starting at offset 0x3C
    _memset(&this->field_3C, 0, 0x30);     // +0x3C to +0x6B

    // Set a flag at offset 0x3D
    this->field_3D = 1;                    // +0x3D (byte)

    // Insert this node into the global doubly linked list
    // Global structure at DAT_012191b0 contains head and tail pointers
    // The list is managed by a global manager (likely ObjectManager)
    iVar2 = *(int *)(DAT_012191b0 + 0x2C); // Get previous node (tail->prev or head->prev)
    this->field_28 = DAT_012191b0;         // +0x28: store head pointer
    this->field_2C = iVar2;                // +0x2C: store previous node

    // Update head to point to this node
    *(EARSNode **)(DAT_012191b0 + 0x2C) = this; // head->prev = this (or head = this)
    // Update previous node's next to point to this node
    *(EARSNode **)(iVar2 + 0x28) = this;   // prev->next = this

    // Check a flag in param1 (offset 0x14, bit 0)
    if ((*(byte *)((int)param1 + 0x14) & 1) != 0) {
        // If flag is set, call another function and store result
        this->field_98 = FUN_00505da0();   // +0x98 (offset 0x98 = 0x26*4)
    } else {
        this->field_98 = 0;
    }
    return;
}