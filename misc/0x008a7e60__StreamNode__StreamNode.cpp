// FUNC_NAME: StreamNode::StreamNode
// Address: 0x008a7e60
// Constructor for a node in a singly-linked list used by the audio stream manager
// The node stores a name (up to 63 chars), three unknown integer/pointer fields, and a linked-list next pointer at +0x70
// After construction, the node is inserted at the head of a global list (DAT_012059ec)

class StreamNode {
public:
    // vtable pointer (offset 0x00)
    void *vtable;

    // Offsets 0x04, 0x08, 0x0C – likely identifiers, sizes, or handles
    int field_04;   // param_3
    int field_08;   // param_5
    int field_0C;   // param_4

    // Offsets 0x10 to 0x1C – zeroed out (4 ints)
    int field_10;
    int field_14;
    int field_18;
    int field_1C;

    // Name buffer at offset 0x20, 64 bytes (0x40)
    char name[0x40];

    // Next pointer in the linked list at offset 0x70 (index 0x1c * 4)
    StreamNode *next;

    // Constructor – performs base initialization, copies name, sets fields, zeroes intermediate fields, links into global list
    __thiscall StreamNode(char *name, int id1, int id2, int id3) {
        // Call base class constructor (e.g., Object::Object)
        FUN_0064cc90(); // assumed base initialization

        // Set vtable
        this->vtable = &PTR_LAB_00d79c10;

        // Copy the name with truncation to 63 characters
        _strncpy(this->name, name, 0x3f);

        // Store the passed parameters
        this->field_04 = id1;   // param_3
        this->field_08 = id3;   // param_5
        this->field_0C = id2;   // param_4

        // Clear fields at offsets 0x10, 0x14, 0x18, 0x1C
        this->field_10 = 0;
        this->field_14 = 0;
        this->field_18 = 0;
        this->field_1C = 0;

        // Insert this node at the head of the global node list
        // DAT_012059ec is the static head pointer of the list
        this->next = DAT_012059ec; // offset 0x70
        DAT_012059ec = this;

        // Return this
    }
};

// Global head pointer for the linked list of StreamNode instances
extern StreamNode *DAT_012059ec;