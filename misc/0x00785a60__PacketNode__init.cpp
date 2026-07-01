// FUNC_NAME: PacketNode::init
void __thiscall PacketNode::init(PacketNode* this, uint32_t param1, uint32_t param2, const uint32_t param3[3], PacketNode* insertAfter)
{
    // this->field_04 = param1
    this->field_04 = param1;
    // this->field_00 = 0
    this->field_00 = 0;
    // this->field_08 = param2
    this->field_08 = param2;
    // Copy 12 bytes from param3 into this+0x0C, this+0x10, this+0x14
    // (interpret as 8 bytes and 4 bytes separate)
    *(uint64_t*)(&this->field_0C) = *(uint64_t*)param3;
    this->field_14 = *(uint32_t*)((uint8_t*)param3 + 8);
    // Handle insertion after a node (if insertAfter != nullptr)
    if (insertAfter == 0) {
        insertAfter = 0;
    } else {
        // Offset by 0x48? This is unusual; maybe insertAfter is a base pointer to a pool chunk
        insertAfter = (PacketNode*)((uint8_t*)insertAfter + 0x48);
    }
    // this->next = insertAfter
    this->next = insertAfter;
    // this->prev = 0
    this->prev = 0;
    if (insertAfter != 0) {
        // Save the old next pointer of insertAfter into this->prev
        this->prev = insertAfter->next;
        // Link insertAfter->next to this's next field (singly linked list insertion)
        insertAfter->next = &this->next;
    }
    // this->field_20 = 0
    this->field_20 = 0;
    return;
}