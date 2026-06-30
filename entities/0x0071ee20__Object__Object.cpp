// FUNC_NAME: Object::Object
undefined4 * __thiscall Object::Object(undefined4 *this, int param_2)
{
    // vtable pointer initialization - offset +0x00
    *this = &PTR_FUN_00d61fc4;  // virtual function table

    // Zero out fields at offsets 0x04, 0x08, 0x0C, 0x10, 0x14, 0x18, 0x1C, 0x20
    this[1] = 0;  // offset +0x04: pointer (next or link)
    this[2] = 0;  // offset +0x08: pointer (prev or backlink)
    this[3] = 0;  // offset +0x0C
    this[4] = 0;  // offset +0x10
    this[5] = _DAT_00d5780c;  // offset +0x14: global singleton or stamp
    this[6] = 0;  // offset +0x18
    this[7] = 0;  // offset +0x1C
    this[8] = 0;  // offset +0x20

    // Adjust param_2 if non-null: treat as pointer to a parent object with a linked list at +0x48
    int *parentLink;
    if (param_2 == 0) {
        parentLink = 0;
    } else {
        parentLink = (int *)(param_2 + 0x48);
    }

    // Update the link field (offset +0x04) with the new parentLink
    int **pLinkField = (int **)(this + 1);  // &this[1]
    if (*pLinkField != parentLink) {
        if (*pLinkField != 0) {
            FUN_004daf90(pLinkField);  // release or decrement reference
        }
        *pLinkField = parentLink;
        if (parentLink != 0) {
            // Insert this object into the linked list: copy old next pointer from parentLink to field at +0x08
            this[2] = *(parentLink + 1);  // parentLink->next => this->prev? (offset +0x08)
            // Update parentLink->next to point to this object's link field
            *(parentLink + 1) = pLinkField;  // parentLink->next = &this->link
        }
    }

    // Set a magic identifier at offset +0x24 (offset 9)
    this[9] = 0x2ca3cff6;

    // Call final initialization routine (maybe debug or register)
    FUN_007f63b0(1);

    return this;
}