// FUNC_NAME: EARSObject::~EARSObject
// Function address: 0x004cb490
// Role: Base class destructor for EARS engine objects. Sets vtable to derived class, conditionally calls cleanup, then sets vtable to base class and clears a linked list of child nodes.

void __thiscall EARSObject::~EARSObject(EARSObject *this) {
    EARSObject *nextNode;
    EARSObject *currentNode;

    // Set vtable to derived class (to ensure correct virtual dispatch during destruction)
    this->vtable = &PTR_FUN_00e3663c;

    // Check if the object has been fully constructed (flag at offset +0x18)
    if (*(char *)((uint8_t *)this + 0x18) != '\0') {
        // Call derived class cleanup (likely destructor of derived class)
        FUN_004cb550();
    }

    // Switch vtable to base class
    this->vtable = &PTR_FUN_00e32808;

    // Clear linked list of child nodes (head at offset +0x04)
    currentNode = (EARSObject *)this->field_0x04;
    while (currentNode != nullptr) {
        nextNode = (EARSObject *)currentNode->field_0x04; // next pointer at offset +0x04 of node
        currentNode->field_0x04 = nullptr;                // clear next
        currentNode->vtable = nullptr;                    // clear vtable (or data)
        currentNode = nextNode;
    }
}