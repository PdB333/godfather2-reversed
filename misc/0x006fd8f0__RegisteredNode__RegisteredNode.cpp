// FUNC_NAME: RegisteredNode::RegisteredNode

// Constructor for a node in a global doubly-linked list (inserts at head)
// Offset layout:
// +0x00: field_0 (uint32)
// +0x04: field_4 (uint32)
// +0x08: next (RegisteredNode*)
// +0x0C: prev (RegisteredNode*)
// +0x10: field_10 (uint32)
// +0x14: field_14 (uint32)
// +0x30: field_30 (uint32)
// +0x34: byte_34 (uint8)
// The global head pointer is stored at DAT_0112aaa8

extern RegisteredNode* g_pRegisteredHead; // DAT_0112aaa8

__fastcall RegisteredNode::RegisteredNode()
{
    this->field_0 = 0;
    this->field_4 = 0;
    this->next = nullptr; // offset +0x08, set by link step
    this->prev = g_pRegisteredHead; // offset +0x0C
    if (g_pRegisteredHead != nullptr)
    {
        g_pRegisteredHead->next = this; // link old head's next to new node
    }
    g_pRegisteredHead = this; // new node becomes head

    this->field_10 = 0; // offset +0x10
    this->field_14 = 0; // offset +0x14
    this->field_30 = 0; // offset +0x30
    *reinterpret_cast<uint8_t*>(&this->field_30 + 4) = 0; // zero byte at offset +0x34

    // additional initialization (likely base constructor or private init)
    sub_006fd030();

    return;
}