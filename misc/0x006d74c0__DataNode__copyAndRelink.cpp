// FUNC_NAME: DataNode::copyAndRelink
// Function at 0x006d74c0: Copies a DataNode's contents (0x8C bytes) and then relinks two intrusive doubly-linked lists
// (listA at offset +0x28/+0x2C, listB at offset +0x30/+0x34) so that the destination node inherits the list connections from the source node.

struct DataNode {
    // Total size 0x8C (140 bytes)
    // Offset +0x00: first 5 fields, 8 bytes each (40 bytes)
    uint64 field00;           // +0x00
    uint64 field08;           // +0x08
    uint64 field10;           // +0x10
    uint64 field18;           // +0x18
    uint64 field20;           // +0x20

    // Linked list A: next/prev pair using embedded link fields
    DataNode* nextListA;      // +0x28 (param_1[5])
    DataNode* prevListA;      // +0x2C (param_1+0x2C)

    // Linked list B: second next/prev pair
    DataNode* nextListB;      // +0x30 (param_1[6])
    DataNode* prevListB;      // +0x34 (param_1+0x34)

    // Remaining fields: 4-byte each for most, one 8-byte at +0x7C
    uint32 field38;           // +0x38
    uint32 field3C;           // +0x3C
    uint32 field40;           // +0x40
    uint32 field44;           // +0x44
    uint32 field48;           // +0x48
    uint32 field4C;           // +0x4C
    uint32 field50;           // +0x50
    uint32 field54;           // +0x54
    uint32 field58;           // +0x58
    uint32 field5C;           // +0x5C
    uint32 field60;           // +0x60
    uint32 field64;           // +0x64
    uint32 field68;           // +0x68
    uint32 field6C;           // +0x6C
    uint32 field70;           // +0x70
    uint32 field74;           // +0x74
    uint32 field78;           // +0x78
    uint64 field7C;           // +0x7C (8 bytes)
    uint32 field84;           // +0x84
    uint32 field88;           // +0x88
};

void __thiscall DataNode::copyAndRelink(DataNode* this, const DataNode* source) {
    // Copy the first 5 8-byte fields (40 bytes)
    this->field00 = source->field00;
    this->field08 = source->field08;
    this->field10 = source->field10;
    this->field18 = source->field18;
    this->field20 = source->field20;

    // --- Relink list A (next/prev at +0x28/+0x2C) ---
    this->nextListA = source->nextListA;          // copy source's next pointer
    this->prevListA = nullptr;                     // initialise prev to null

    if (this->nextListA != nullptr) {
        // Set this node's prev to the previous node of the target next node
        // (effectively inserting this node before the existing next node)
        this->prevListA = this->nextListA->prevListA;

        // Update the next node's prev to point to this node's next field
        // This relinks the list so that this node replaces the source's position
        this->nextListA->prevListA = &(this->nextListA);
    }

    // --- Relink list B (next/prev at +0x30/+0x34) ---
    this->nextListB = source->nextListB;
    this->prevListB = nullptr;

    if (this->nextListB != nullptr) {
        this->prevListB = this->nextListB->prevListB;
        this->nextListB->prevListB = &(this->nextListB);
    }

    // Copy remaining fields (32-bit and one 64-bit)
    this->field38 = source->field38;
    this->field3C = source->field3C;
    this->field40 = source->field40;
    this->field44 = source->field44;
    this->field48 = source->field48;
    this->field4C = source->field4C;
    this->field50 = source->field50;
    this->field54 = source->field54;
    this->field58 = source->field58;
    this->field5C = source->field5C;
    this->field60 = source->field60;
    this->field64 = source->field64;
    this->field68 = source->field68;
    this->field6C = source->field6C;
    this->field70 = source->field70;
    this->field74 = source->field74;
    this->field78 = source->field78;
    this->field7C = source->field7C;
    this->field84 = source->field84;
    this->field88 = source->field88;
}