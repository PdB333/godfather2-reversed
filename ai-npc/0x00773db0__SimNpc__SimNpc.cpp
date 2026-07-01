// FUNC_NAME: SimNpc::SimNpc
// Address: 0x00773db0
// Constructs a SimNpc object (base class for NPCs/Player). 
// Takes a data block pointer (param_2) and an ID (param_3).
// Initializes vtable pointers, zeros out fields, inserts into GameManager's NPC list,
// and configures a component based on the data block's flags.

int* __thiscall SimNpc::SimNpc(SimNpc* this, int dataBlock, int someId) {
    int* baseGameManager = this->gameManagerPtr; // param_1[0x17] = +0x5C
    FUN_0073e160(dataBlock, someId); // Base class constructor (Sentient/Entity)

    this->field_0x1d = 0;                     // +0x74
    this->someVtablePtr1 = &PTR_LAB_00d61acc; // +0x70 (first vtable)
    this->field_0x1e = 0xffffffff;            // +0x78
    this->vtbl = &PTR_LAB_00d67ea8;           // +0x00 (primary vtable)
    this->someVtablePtr2 = &PTR_LAB_00d67ea0; // +0x70 (second vtable, overwritten)
    this->listNodePtr = 0;                    // +0x7c (used for linked list)
    this->listPrevPtr = 0;                    // +0x80
    this->flags1 = 1;                        // +0x84 (bit0)
    this->field_0x29 = 0;                    // +0xa4
    int* nodePtrPtr = &this->listNodePtr;     // piVar1 = param_1+0x1f
    this->field_0x2b = 0;                    // +0xac
    this->field_0x2a = 0;                    // +0xa8
    this->field_0x2e = 0;                    // +0xb8
    this->field_0x2d = 0;                    // +0xb4
    this->field_0x2c = 0;                    // +0xb0
    this->field_0x31 = 0;                    // +0xc4
    this->field_0x30 = 0;                    // +0xc0
    this->field_0x23 = 0;                    // +0x8c
    this->field_0x24 = 0;                    // +0x90
    this->field_0x25 = 0;                    // +0x94
    this->field_0x26 = 0;                    // +0x98
    this->field_0x27 = 0;                    // +0x9c
    this->field_0x28 = 0;                    // +0xa0
    this->field_0x2f = 0;                    // +0xbc

    FUN_005512c0(2); // Possibly Logging/Message
    FUN_007f63e0(5); // Unknown

    if (baseGameManager != 0) {
        int isMultiplayer = FUN_0043b870(DAT_0112af58); // Check multiplayer state
        if (isMultiplayer != 0) {
            char isHost = FUN_007829d0(); // Is this session host?
            if (isHost != 0) {
                this->flags1 |= 2;          // Set bit1 (host flag)
                FUN_00782d10(0);           // Start host specific logic
            }
        }
    }

    // Resolve link target: either from data block's linked NPC or 0
    int linkTarget = 0;
    if (baseGameManager[0x9a2] != 0) { // offset +0x2688 (NPC link list head)
        linkTarget = baseGameManager[0x9a2] - 0x48; // Subtract offset of "this" in the node?
    }
    if (linkTarget == 0) {
        linkTarget = 0;
    } else {
        linkTarget = linkTarget + 0x48; // Restore
    }

    // Insert this node into the linked list (if not empty and not the sentinel)
    if (this->listNodePtr != linkTarget) {
        if (this->listNodePtr != 0) {
            FUN_004daf90(nodePtrPtr); // Remove old node from list
        }
        this->listNodePtr = linkTarget;
        if (linkTarget != 0) {
            this->listPrevPtr = *(int*)(linkTarget + 4); // Save previous node
            *(int**)(linkTarget + 4) = nodePtrPtr;      // Link back to this node
        }
    }

    // If successfully linked and not a placeholder (0x48 = 72 bytes offset)
    if ((this->listNodePtr != 0) && (this->listNodePtr != 0x48)) {
        // Detach from baseGameManager's list if already there
        if (baseGameManager[0x9a2] != 0) {
            FUN_004daf90(baseGameManager + 0x9a2);
            baseGameManager[0x9a2] = 0;
        }

        // Call vtable function to initialize substructure at +0xb0
        int substructBase = (this->listNodePtr == 0) ? 0 : (this->listNodePtr - 0x48);
        (this->vtbl->someInit)(substructBase + 0xb0);

        // Clear something at +0x90
        substructBase = (this->listNodePtr == 0) ? 0 : (this->listNodePtr - 0x48);
        FUN_0046fe50(substructBase + 0x90, 0);

        // Set a byte flag to 1 at +0xbc
        substructBase = (this->listNodePtr == 0) ? 0 : (this->listNodePtr - 0x48);
        *(unsigned char*)(substructBase + 0xbc) = 1;

        // Determine component type from flags at +0xf4
        substructBase = (this->listNodePtr == 0) ? 0 : (this->listNodePtr - 0x48);
        if ((*(unsigned int*)(substructBase + 0xf4) >> 2 & 1) != 0) {
            this->componentType = 0; // +0x88
            return this;
        }
        if ((*(unsigned int*)(substructBase + 0xf4) >> 3 & 1) != 0) {
            this->componentType = 1;
            return this;
        }
        int temp = (this->listNodePtr != 0) ? (this->listNodePtr - 0x48) : 0;
        this->componentType = (-(unsigned int)((*(unsigned int*)(temp + 0xf4) >> 4 & 1) != 0) & 3) - 1;
    }
    return this;
}