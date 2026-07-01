// FUNC_NAME: ObjectLink::getOwner
int __thiscall ObjectLink::getOwner() {
    // this+0x4: pointer to a node structure (e.g., NodeLink)
    // node+0x4: pointer to the containing object's member at offset 0x48
    // Subtract 0x48 to get the base of the containing object
    if (*(int*)(this + 4) != 0) {
        int* node = *(int**)(this + 4);
        if (node[1] != 0) {  // node+4
            return node[1] - 0x48;
        }
    }
    return 0;
}