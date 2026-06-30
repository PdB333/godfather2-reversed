// FUNC_NAME: SimObject::operator=
// Address: 0x006bfa70
// Role: Deep copy assignment for a core EARS SimObject, with intrusive linked-list pointer management.

SimObject& SimObject::operator=(const SimObject& other)
{
    // Copy first five 8-byte fields (e.g., GUID, name hash, timestamps)
    // Offsets 0x00–0x27
    this->field00 = other.field00; // 8 bytes
    this->field08 = other.field08; // 8 bytes
    this->field10 = other.field10; // 8 bytes
    this->field18 = other.field18; // 8 bytes
    this->field20 = other.field20; // 8 bytes

    // Intrusive pointer at offset 0x28 (node1)
    int*& thisNode1 = this->node1Ptr;
    int* otherNode1 = other.node1Ptr;
    if (thisNode1 != otherNode1)
    {
        if (thisNode1 != nullptr)
            nodeRelease(thisNode1); // FUN_004daf90 – deallocate if needed
        thisNode1 = otherNode1;
        if (otherNode1 != nullptr)
        {
            // Maintain intrusive list: next/prev pointers are stored at node+4
            this->node1Prev = otherNode1[1]; // save old prev
            otherNode1[1] = reinterpret_cast<int>(&thisNode1); // update node's prev
        }
    }

    // Intrusive pointer at offset 0x30 (node2)
    int*& thisNode2 = this->node2Ptr;
    int* otherNode2 = other.node2Ptr;
    if (thisNode2 != otherNode2)
    {
        if (thisNode2 != nullptr)
            nodeRelease(thisNode2);
        thisNode2 = otherNode2;
        if (otherNode2 != nullptr)
        {
            this->node2Prev = otherNode2[1];
            otherNode2[1] = reinterpret_cast<int>(&thisNode2);
        }
    }

    // Copy remaining 4-byte fields (offsets 0x38–0x78)
    this->field38 = other.field38;
    this->field3C = other.field3C;
    this->field40 = other.field40;
    this->field44 = other.field44;
    this->field48 = other.field48;
    this->field4C = other.field4C;
    this->field50 = other.field50;
    this->field54 = other.field54;
    this->field58 = other.field58;
    this->field5C = other.field5C;
    this->field60 = other.field60;
    this->field64 = other.field64;
    this->field68 = other.field68;
    this->field6C = other.field6C;
    this->field70 = other.field70;
    this->field74 = other.field74;
    this->field78 = other.field78;

    // 8-byte field at offset 0x7C (e.g., double or pointer+int)
    this->field7C = other.field7C;

    // 4-byte fields at offsets 0x84 and 0x88
    this->field84 = other.field84;
    this->field88 = other.field88;

    return *this;
}