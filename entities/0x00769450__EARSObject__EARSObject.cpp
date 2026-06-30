// FUNC_NAME: EARSObject::EARSObject
// Role: Constructor for a game object that registers itself with a manager's linked list (observer/listener pattern)
// Offsets:
// +0x00: vtable pointer
// +0x48 (0x12*4): pointer to location inside manager object (used to compute manager base)
// +0x70 (0x1c*4): stored manager base (for quick access)
// +0x74 (0x1d*4): head of intrusive linked list (points to first node object)
// +0x78 (0x1e*4): pointer to previous node's next field (for list maintenance)
// +0x7c (0x1f*4): flags (bit field)
// +0x80 (0x20*4): extra field (unused in this function)

// Node object (in linked list):
// +0x00: vtable pointer
// +0x04: 'next' pointer (links to next node or null)
// Node objects are embedded into larger objects with a -0x48 header offset.

EARSObject* __thiscall EARSObject::EARSObject(EARSObject* this, int32_t arg2, int32_t arg3)
{
    int32_t resultCode;
    int32_t managerBase;
    int32_t** listNodePtr;
    int32_t* nodeBase;

    // Call base class constructor
    BaseClass::BaseClass(arg2, arg3);

    // Set vtable (this is a derived class)
    this->vtable = &VTABLE_EARSObject;

    // Clear linked list head and auxiliary fields
    this->listHead = nullptr;
    this->listPrev = nullptr;
    this->flags = 0;
    this->extraField = 0;

    // Global engine initialization
    EngineGlobals::init();

    // Compute manager base from stored pointer at +0x48
    if (this->managerField == nullptr) {
        managerBase = 0;
    } else {
        managerBase = reinterpret_cast<int32_t>(this->managerField) - 0x48;
    }
    this->managerBase = reinterpret_cast<void*>(managerBase);

    // Retrieve first node from manager's node list at offset 0x1c78
    if (managerBase != 0) {
        if (*(int32_t*)(managerBase + 0x1c78) == 0) {
            nodeBase = 0;
        } else {
            nodeBase = *(int32_t*)(managerBase + 0x1c78) - 0x48;
        }
    } else {
        nodeBase = 0;
    }

    // If nodeBase was non‑zero, add back the offset to get the pointer stored in the manager
    if (nodeBase == 0) {
        listNodePtr = nullptr;
    } else {
        listNodePtr = reinterpret_cast<int32_t**>(nodeBase + 0x48);
    }

    // Insert this object into the linked list (if the node has changed)
    if (this->listHead != listNodePtr) {
        if (this->listHead != nullptr) {
            intrusiveListRemove( &(this->listHead) );
        }
        this->listHead = listNodePtr;
        if (listNodePtr != nullptr) {
            // Update the 'next' pointer of the node to point back to our list head field
            this->listPrev = reinterpret_cast<int32_t*>(*reinterpret_cast<int32_t*>(reinterpret_cast<int32_t>(listNodePtr) + 4));
            *reinterpret_cast<int32_t**>(reinterpret_cast<int32_t>(listNodePtr) + 4) = &(this->listHead);
        }
    }

    // If there is a node in the list, query it for a specific capability (hash 0x55859efa)
    if ( (this->listHead != nullptr) && (this->listHead != reinterpret_cast<int32_t**>(0x48) ) ) {
        nodeBase = reinterpret_cast<int32_t*>(reinterpret_cast<int32_t>(this->listHead) - 0x48);
        resultCode = 0;
        bool8_t hasCapability = (*(int32_t(**)(int32_t, int32_t*))(*nodeBase + 0x10))(0x55859efa, &resultCode);
        if (hasCapability && resultCode != 0) {
            this->flags |= 0x10;
        }
    }

    // Perform engine‐wide state changes
    engineStateChange(0x51);
    engineStateChange(3);

    return this;
}