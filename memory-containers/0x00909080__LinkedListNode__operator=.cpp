// FUNC_NAME: LinkedListNode::operator=
// Address: 0x00909080
// Role: Assigns a new value to this linked list node, releasing the old value, and relinking the node into the list after the new value's node.
// Node layout: offset 0 = stored pointer (value), offset 4 = next pointer.
// The function inserts this node after the node pointed to by the new value (if non-null) by updating next pointers.

int* __thiscall LinkedListNode::operator=(int* param_1, int* param_2)
{
    if (param_1 == param_2) {
        return param_1; // Self-assignment guard
    }

    int newValue = *param_2;

    if (*param_1 != newValue) {
        if (*param_1 != 0) {
            // Release the old value (e.g., decrement refcount or remove from list)
            FUN_004daf90(param_1); // releaseNode(this)
        }

        *param_1 = newValue;

        if (newValue != 0) {
            // Relink: store newValue's original next pointer into this->next
            param_1[1] = *(int*)(newValue + 4);
            // Make newValue's next point to this node
            *(int**)(newValue + 4) = param_1;
        }
    }

    return param_1;
}