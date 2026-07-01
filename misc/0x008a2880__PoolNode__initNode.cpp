// FUNC_NAME: PoolNode::initNode
void __thiscall PoolNode::initNode(void* param_2)
{
    // Call base initialization (likely placement new or memory setup)
    FUN_00b22400(param_2);
    // Initialize the "next" pointer at +0x344 to point to the node's data area at +0x34c
    // This creates a self-referential link, typical for pool allocator free lists
    *(int**)(this + 0x344) = reinterpret_cast<int*>(this + 0x34c);
}