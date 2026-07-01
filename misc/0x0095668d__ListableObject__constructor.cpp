// FUNC_NAME: ListableObject::constructor

// Structure offsets:
// +0x00: vtable (PTR_FUN_00d8c120)
// +0x04: next (pointer to another ListableObject)
// +0x08: char (some flag)
// +0x0C: int (initialized to 0xFF)
// +0x14: prev (pointer to previous node's 'next' field? or similar link)
// +0x18: char (another flag)
// +0x1C: float (from XMM0)

class ListableObject {
public:
    void* vtable;            // +0x00
    ListableObject* next;    // +0x04
    char flags1;             // +0x08
    int unknownID;           // +0x0C (always 0xFF)
    ListableObject* prev;    // +0x14  (link used during insertion)
    char flags2;             // +0x18
    float someFloat;         // +0x1C
};

// __fastcall: ECX = this; undocumented register parameters:
//   unaff_EBX  = nullValue (likely 0 used to clear fields)
//   in_EAX     = base address for list head (if ZF clear)
//   in_ZF      = flag indicating whether in_EAX is valid (ZF set means invalid/zero)
//   in_XMM0_Da = floating point value stored at +0x1C
void __fastcall ListableObject::constructor(ListableObject* this) {
    // Register values reinterpreted as local variables
    int nullVal = 0;                // unaff_EBX (clears fields)
    int listBase = 0;               // in_EAX (used if ZF clear)
    bool listValid = true;          // inverted from ZF; assume ZF cleared means valid
    float floatVal = 0.0f;          // in_XMM0_Da

    // Fields initialization
    this->vtable = (void*)&PTR_FUN_00d8c120;
    this->next = (ListableObject*)nullVal;
    this->flags1 = (char)nullVal;
    this->unknownID = 0xFF;
    this->prev = (ListableObject*)nullVal;   // will be overwritten later if insertion happens
    this->flags2 = (char)nullVal;
    this->someFloat = floatVal;

    // Determine target list node (head + offset 0x48)
    ListableObject* targetNode = nullptr;
    if (listValid) {
        targetNode = (ListableObject*)(listBase + 0x48);
    }

    // If the current next pointer differs from target, update the linkage
    if (this->next != targetNode) {
        // If currently linked to something, detach from it
        if (this->next != (ListableObject*)nullVal) {
            FUN_004daf90(&this->next);   // likely removes this node from its current list
        }
        this->next = targetNode;
        if (targetNode != nullptr) {
            // Insert this node into the list after targetNode:
            //   - Save the old next pointer of targetNode into this->prev
            this->prev = targetNode->next;
            //   - Update targetNode's next to point to this node's 'next' field address
            targetNode->next = (ListableObject*)&this->next;
        }
    }

    return this;
}