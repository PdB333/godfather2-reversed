// FUNC_NAME: EARSObject::EARSObject
// Function address: 0x004a7340
// Role: Constructor for EARSObject, initializes vtable, creates a linked child node, and sets up transform matrix.

EARSObject* __thiscall EARSObject::EARSObject(EARSObject* parent)
{
    EARSObject* newNode;        // iVar2
    float localMatrix[16];            // uStack_50..uStack_14 (16 floats)

    // Set vtable pointer (offset +0x00)
    this->vtable = &PTR_FUN_00e35538;

    // Call base class constructor (likely EObject or similar)
    FUN_0060ffd0();

    // Store an internal pointer (extraout_EDX) at offset +0xA0 (this[0x28])
    this->field_0xA0 = extraout_EDX;

    // Allocate a new child node (?)
    newNode = (EARSObject*)(*(code**)(extraout_EDX + 0x60))();

    // If newNode->next (offset +0x80) is not null, remove it from its previous list
    if (newNode->next != NULL)
    {
        FUN_00610100(newNode);
    }

    // Link newNode into this object's child list (this->child at offset +0x94)
    newNode->prev = this->child;     // offset +0x8C
    newNode->childOf = this;         // offset +0x88 (parent)
    if (this->child != NULL)
    {
        this->child->next = newNode; // offset +0x8C (same as prev), but used as next in the list?
    }
    this->child = newNode;           // offset +0x94

    // Set newNode's other sibling pointer to this+4 (offset +0x80)
    newNode->sibling = (EARSObject*)((char*)this + 4);

    // Debug/check call
    FUN_006101b0();

    // Initialize local transform matrix (identity matrix)
    FUN_004a36a0(localMatrix);

    // Copy the matrix to this object (offsets +0x50 to +0x8C)
    this->transform[0]  = localMatrix[0];
    this->transform[1]  = localMatrix[1];
    this->transform[2]  = localMatrix[2];
    this->transform[3]  = localMatrix[3];
    this->transform[4]  = localMatrix[4];
    this->transform[5]  = localMatrix[5];
    this->transform[6]  = localMatrix[6];
    this->transform[7]  = localMatrix[7];
    this->transform[8]  = localMatrix[8];
    this->transform[9]  = localMatrix[9];
    this->transform[10] = localMatrix[10];
    this->transform[11] = localMatrix[11];
    this->transform[12] = localMatrix[12];
    this->transform[13] = localMatrix[13];
    this->transform[14] = localMatrix[14];
    this->transform[15] = localMatrix[15];

    // Zero out specific matrix elements (indices 3,7,11,15 are set to 0? Actually indices 0x17,0x1b,0x1f,0x23 correspond to matrix positions)
    // This seems to set the last row or column to zero except the last element which comes from global.
    this->transform[3]  = 0.0f;   // index 0x17 = 3
    this->transform[7]  = 0.0f;   // index 0x1b = 7
    this->transform[11] = 0.0f;   // index 0x1f = 11
    this->transform[15] = DAT_00e2b1a4; // global constant, likely 1.0f for identity

    // Another debug call
    FUN_006101b0();

    // If parent is provided, link this object into parent's sibling list (using fields at +0x98, +0x9C)
    if (parent != NULL)
    {
        this->parentSiblingNext = parent->siblingHead;      // offset +0x98, parent->siblingHead at parent+0x84
        this->parentSiblingPrev = NULL;                     // offset +0x9C
        if (parent->siblingHead != NULL)
        {
            parent->siblingHead->parentSiblingPrev = this;  // offset +0x9C
        }
        parent->siblingHead = this;                         // offset +0x84
        this->parentRef = parent;                           // offset +0x90 (this[0x24])
        FUN_006101b0();
    }

    return this;
}