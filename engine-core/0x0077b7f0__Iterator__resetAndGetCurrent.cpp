//FUNC_NAME: Iterator::resetAndGetCurrent
int __fastcall Iterator::resetAndGetCurrent(Iterator* this)
{
    int* piVar1;
    int iVar2;

    // If version mismatch, current node is null, or current node is the sentinel (0x48), reset iterator
    if ((this->version != g_listVersion) || (this->currentNode == nullptr) || (this->currentNode == (int*)0x48)) {
        this->version = g_listVersion;
        piVar1 = &this->currentNode;
        // Compute the user data pointer of the head node (head node + 0x48)
        if (*this->headPtr == nullptr) {
            iVar2 = 0;
        } else {
            iVar2 = (int)*this->headPtr + 0x48;
        }
        // If current node differs from the new target, release old and set new
        if (this->currentNode != (int*)iVar2) {
            if (this->currentNode != nullptr) {
                releaseNode(&this->currentNode); // FUN_004daf90 – likely decrements refcount
            }
            this->currentNode = (int*)iVar2;
            if (iVar2 != 0) {
                // Update the previous pointer in the node to point back to this iterator
                this->prevNode = *(int**)(iVar2 + 4); // +0x4 in node: previous iterator link
                *(int**)(iVar2 + 4) = &this->currentNode; // link node back to iterator
            }
        }
    }
    // Return user data pointer (node - 0x48) or null if no current node
    if (this->currentNode == nullptr) {
        return 0;
    }
    return (int)this->currentNode - 0x48;
}