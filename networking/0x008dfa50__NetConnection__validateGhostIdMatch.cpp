// FUNC_NAME: NetConnection::validateGhostIdMatch
char __thiscall NetConnection::validateGhostIdMatch(NetConnection* this, void* other)
{
    // Compare local ghost ID (offset +0x230) with remote ghost ID (offset +0x1ef4)
    if (*(int*)((char*)other + 0x1ef4) != *(int*)((char*)this + 0x230))
    {
        // IDs do not match – invoke mismatch handler
        return handleIdMismatch();
    }
    return 0;
}