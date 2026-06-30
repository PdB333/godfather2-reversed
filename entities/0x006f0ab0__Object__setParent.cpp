// FUNC_NAME: Object::setParent
int * __thiscall Object::setParent(int *thisObj, int *newParent) {
    if (*thisObj != newParent) {
        if (*thisObj != 0) {
            // Remove this object from its current parent's child list
            Object::removeFromSiblingList(thisObj);
        }
        // Set new parent pointer (offset 0)
        *thisObj = newParent;
        if (newParent != 0) {
            // Insert this object at head of new parent's child list (offset 4 = firstChild)
            thisObj[1] = *(int *)(newParent + 4); // this->nextSibling = parent->firstChild
            *(int **)(newParent + 4) = thisObj; // parent->firstChild = this
        }
    }
    return thisObj;
}