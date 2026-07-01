//FUNC_NAME: DataNode::DataNode
void __thiscall DataNode::DataNode(DataNode *this)
{
    // +0x04: first field (likely a pointer or integer)
    // +0x08: second field (likely a pointer or integer)
    // +0x0c: third field (set to 0, possibly a flag or counter)
    initNode(*(int *)((char *)this + 4), *(int *)((char *)this + 8));
    *(int *)((char *)this + 0xc) = 0;
}