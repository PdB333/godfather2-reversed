// FUNC_NAME: DLink::GetContainer
// Function address: 0x005f6280
// Returns pointer to the containing object from a link. Offset +0x24 holds a pointer to a node structure,
// and the container is at offset -0x48 from that node. Returns null if the link is not attached.
void* __thiscall DLink::GetContainer(void* this) {
    void* nodePtr = *(void**)((char*)this + 0x24);
    if (nodePtr != 0) {
        return (char*)nodePtr - 0x48;
    }
    return 0;
}