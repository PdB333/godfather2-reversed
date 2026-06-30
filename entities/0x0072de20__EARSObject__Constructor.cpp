// FUNC_NAME: EARSObject::Constructor

struct EARSObject {
    void **vtable;           // +0x00
    int field_04;            // +0x04
    void *parentNodePtr;     // +0x08 (points to parent's child list head)
    void *nextSibling;       // +0x0C (next in parent's child list)
    uint8_t flags[4];        // +0x10..0x13 (byte flags, initialized to 0)
    int globalRef;           // +0x14 (set from DAT_00d5ccf8)
    const char *debugName;   // +0x18 (set to &DAT_0112daec)
    int field_1C;            // +0x1C (initialized to 0)
    int field_20;            // +0x20 (initialized to 0)
};

// Global references (assumed int/pointer)
extern int DAT_00d5ccf8;
extern const char DAT_0112daec[];

void __thiscall EARSObject::Constructor(EARSObject *this, void *parent)
{
    // Set vtable pointer
    this->vtable = (void**)0x00d62bd8;

    // Zero field at +0x04
    this->field_04 = 0;

    // Adjust parent: if non-null, treat parent+0x48 as the list head node
    void *parentNode = parent;
    if (parent != 0) {
        parentNode = (char*)parent + 0x48; // +0x48 is offset to child list head in parent object
    }

    // Store the parent node pointer
    this->parentNodePtr = parentNode;

    // Initialize next sibling (will be overwritten if parentNode exists)
    this->nextSibling = 0;

    if (parentNode != 0) {
        // Save old next sibling from parent node (parentNode+4 is the "next" field of the head node)
        this->nextSibling = *(void**)((char*)parentNode + 4);
        // Insert this object after the parent node:
        // Update parent's next to point to our parentNodePtr field (acting as the node's link)
        *(void**)((char*)parentNode + 4) = &this->parentNodePtr;
    }

    // Zero byte flags at offsets 0x10..0x13
    ((uint8_t*)this)[0x10] = 0;
    ((uint8_t*)this)[0x11] = 0;
    ((uint8_t*)this)[0x12] = 0;
    ((uint8_t*)this)[0x13] = 0;

    // Set global reference (likely a manager pointer)
    this->globalRef = DAT_00d5ccf8;

    // Set debug name pointer (points to a static string)
    this->debugName = &DAT_0112daec;

    // Zero out remaining fields
    this->field_1C = 0;
    this->field_20 = 0;
}