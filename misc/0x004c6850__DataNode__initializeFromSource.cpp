// FUNC_NAME: DataNode::initializeFromSource
// Function address: 0x004c6850
// Initializes a data node from a source node, setting type to 1 and copying data block.

void __thiscall DataNode::initializeFromSource(DataNode* this, DataNode* source, int param2)
{
    // +0x00: type flag (set to 1)
    this->type = 1;
    // +0x04: short field (set to 0)
    this->field_04 = 0;
    // +0x06: short field (set to 0)
    this->field_06 = 0;
    // +0x08 to +0x14: zero out 5 ints (likely pointers or counters)
    this->field_08 = 0;
    this->field_0C = 0;
    this->field_10 = 0;
    this->field_14 = 0;
    // +0x18: store the second parameter (e.g., ID or index)
    this->param2 = param2;
    // +0x1C to +0x28: copy 4 ints from source (e.g., data array or child pointers)
    this->data[0] = source->data[0];
    this->data[1] = source->data[1];
    this->data[2] = source->data[2];
    this->data[3] = source->data[3];
    // +0x2C: set to 0 (e.g., next pointer or flags)
    this->field_2C = 0;
}