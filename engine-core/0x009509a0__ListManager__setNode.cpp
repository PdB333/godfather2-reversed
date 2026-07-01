// FUNC_NAME: ListManager::setNode

void __thiscall ListManager::setNode(int this, int* newObject, int userData) {
    int** ppNode = (int**)(this + 0x168); // +0x168: pointer to current list node
    if ((*ppNode != 0) && (*ppNode != 0x48)) {
        int refCountObj;
        if (this == 0) {
            refCountObj = 0;
        } else {
            refCountObj = this + 0x50; // +0x50: reference count object
        }
        releaseRefCount(refCountObj);
    }
    int* newNode;
    if (newObject == 0) {
        newNode = 0;
    } else {
        newNode = (int*)((int)newObject + 0x48); // each object has an embedded node at offset 0x48
    }
    if (*ppNode != newNode) {
        if (*ppNode != 0) {
            decrementRefCount(ppNode);
        }
        *ppNode = newNode;
        if (newNode != 0) {
            *(int*)(this + 0x16c) = *(int*)(newNode + 4); // +0x16c: previous link pointer
            *(int**)(newNode + 4) = ppNode; // update new node's prev to point to our pointer
        }
    }
    *(int*)(this + 0x164) = userData; // +0x164: user data
    if ((*ppNode != 0) && (*ppNode != 0x48)) {
        if (*ppNode != 0) {
            addRefCount(this + 0x50);
            return;
        }
        addRefCount(this + 0x50);
    }
}