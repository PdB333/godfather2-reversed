// FUNC_NAME: MissionNode::MissionNode
// Function at 0x004a8bd0: Constructor for MissionNode, initializes fields and adds node to global linked list.

class MissionNode {
public:
    // vtable pointer at +0x00
    void *vtable; // +0x00

    // +0x04: some flags/count (initialized to 1)
    int field_04; // +0x04

    // +0x08 through +0x1C: mostly zeros, reserved
    int field_08;
    int field_0C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;

    // +0x20: name buffer (63 chars max + null)
    char name[0x40]; // +0x20

    // +0x60: 
    int field_60; // +0x60 (offset 0x60 = 24*4)

    // +0x64:
    int field_64; // +0x64 (25*4)

    // +0x68:
    int field_68; // +0x68 (26*4)

    // +0x6C:
    int field_6C; // +0x6C (27*4)

    // +0x70: pointer to previous node in global list
    MissionNode *prevNode; // +0x70 (28*4)

    // +0x74: parameter 3 (some ID or state)
    int param3; // +0x74 (29*4)

    // +0x78: parameter 4 (some ID or state)
    int param4; // +0x78 (30*4)

    // --- Methods ---
    MissionNode(char *name, int param3, int param4) {
        // Set vtable pointer
        this->vtable = &PTR_LAB_00e32a84; // external vtable symbol

        // Initialize fields
        this->field_04 = 1;
        this->field_08 = 0;
        this->field_0C = 0;
        this->field_10 = 0;
        this->field_14 = 0;
        this->field_18 = 0;
        this->field_1C = 0;
        this->field_60 = 0;
        this->field_64 = 0;
        this->field_68 = 0;
        this->field_6C = 0;

        // Copy name (safely)
        _strncpy(this->name, name, 0x3F);
        this->name[0x3F] = '\0'; // ensure null termination

        // Store parameters
        this->param3 = param3;
        this->param4 = param4;

        // Link node into global list
        this->prevNode = DAT_012059ec; // global head pointer
        DAT_012059ec = this; // new head is this node
    }
};

// Global linked list head for MissionNode instances
extern MissionNode *DAT_012059ec; // 0x012059ec