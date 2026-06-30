// FUNC_NAME: ListNode::replaceWith
void ListNode::replaceWith(ListNode* newElement)
{
    // If this is the same element, nothing to do.
    if (this == newElement)
        return;

    int* newObject = (int*)newElement->object; // +0x00: pointer to object (or head node)

    // Only update if the object pointer differs.
    if (this->object != newObject)
    {
        // Clean up the current object if it exists.
        if (this->object != nullptr)
            releaseObject(this); // FUN_004daf90 – probably decrements refcount or frees

        this->object = newObject; // +0x00

        if (newObject != nullptr)
        {
            // Update next pointer: this->next = newObject->next
            this->next = (ListNode*)(*(int*)((int)newObject + 4)); // +0x04
            // newObject->next = this
            *(int**)((int)newObject + 4) = this; // +0x04
        }
    }
}