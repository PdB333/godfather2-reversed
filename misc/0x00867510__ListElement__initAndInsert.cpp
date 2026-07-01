// FUNC_NAME: ListElement::initAndInsert
void __thiscall ListElement::initAndInsert(ListElement* this, ListElement* other)
{
    // Copy the "insertAfter" pointer for first list
    this->insertAfter1 = other->insertAfter1; // +0x00
    this->next1 = 0; // +0x04
    if (this->insertAfter1 != 0) {
        // Insert this node after insertAfter1 in list1
        this->next1 = this->insertAfter1->next1; // +0x04 of the node
        this->insertAfter1->next1 = this;
    }

    // Copy field2
    this->field2 = other->field2; // +0x08

    // Copy the "insertAfter" pointer for second list
    this->insertAfter2 = other->insertAfter2; // +0x0C
    this->next2 = 0; // +0x10
    if (this->insertAfter2 != 0) {
        // Insert a pointer to this->insertAfter2 after insertAfter2 in list2
        // This creates a chain of pointers to the insertAfter2 fields
        this->next2 = this->insertAfter2->next2; // +0x04 of the node
        this->insertAfter2->next2 = &this->insertAfter2; // store address of the pointer
    }

    // Copy field5
    this->field5 = other->field5; // +0x14

    // Copy field6
    this->field6 = other->field6; // +0x18

    // Initialize fields7 and field8 to 0
    this->field7 = 0; // +0x1C
    this->field8 = 0; // +0x20
}