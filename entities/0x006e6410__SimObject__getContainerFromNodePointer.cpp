// FUNC_NAME: SimObject::getContainerFromNodePointer
int __fastcall SimObject::getContainerFromNodePointer(int thisPtr)
{
    // Pointer at +0x330 is a node pointer (likely an intrusive list node).
    // The node is embedded at offset 0x48 in the containing object.
    void* nodePtr = *(void**)(thisPtr + 0x330);
    if (nodePtr != 0) {
        // Reverse the embedding to get the container's base address.
        return (int)((char*)nodePtr - 0x48);
    }
    return 0;
}