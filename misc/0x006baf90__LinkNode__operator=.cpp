// FUNC_NAME: LinkNode::operator=
// Function at 0x006baf90: Assignment operator for a linked list node.
// The node structure:
// +0x00: value (int) - used as identifier or pointer to a target node
// +0x04: next (LinkNode*)
// +0x08 through +0x14: data fields (int)
// When the value changes, the node is removed from its old list (via an external function)
// and inserted after the node pointed to by the new value (i.e., value becomes a pointer to a target node).
int* __thiscall LinkNode::operator=(LinkNode* other) {
    if (this != other) {
        int newValue = other->value; // +0x00
        if (this->value != newValue) {
            if (this->value != 0) {
                // Remove this node from the current list (external function at 0x004daf90)
                FUN_004daf90(this);
            }
            this->value = newValue;
            if (newValue != 0) {
                // Insert this node after the target node (newValue is a pointer to a LinkNode)
                LinkNode* target = (LinkNode*)(int)newValue; // treat newValue as pointer
                this->next = target->next;                    // +0x04
                target->next = this;
            }
        }
        // Copy remaining data fields
        this->field_08 = other->field_08; // +0x08
        this->field_0C = other->field_0C; // +0x0C
        this->field_10 = other->field_10; // +0x10
        this->field_14 = other->field_14; // +0x14
    }
    return (int*)this;
}