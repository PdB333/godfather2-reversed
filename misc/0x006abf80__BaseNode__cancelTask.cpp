// FUNC_NAME: BaseNode::cancelTask
void __fastcall BaseNode::cancelTask(void)
{
    // Set bit 1 (cancel flag) at offset +0x1c
    *(uint32_t *)(this + 0x1c) |= 2;
    
    // If there is a child at offset +0x20, propagate cancellation
    if (*(int32_t *)(this + 0x20) != 0)
    {
        // Internal cancellation helper at 0x006b0fb0
        ::cancelChild(*(int32_t *)(this + 0x20));
    }
}