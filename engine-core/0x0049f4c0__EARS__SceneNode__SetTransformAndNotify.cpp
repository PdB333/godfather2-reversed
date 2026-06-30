// FUNC_NAME: EARS::SceneNode::SetTransformAndNotify
void __thiscall EARS::SceneNode::SetTransformAndNotify(const void* data)
{
    // Offset +0xac: flags (bit0 = transform dirty, bit1 = propagate enabled)
    this->flags |= 1;

    // Offsets +0x70 and +0x78: store 16-byte transform (e.g., matrix or quaternion+translation)
    *(const __int64*)((int)this + 0x70) = *(const __int64*)data;
    *(const __int64*)((int)this + 0x78) = *(const __int64*)((int)data + 8);

    // Check if propagation is enabled (bit1)
    if ((this->flags & 2) != 0)
    {
        // Offset +0x8c: pointer to array of child object pointers
        int** childArray = *(int***)((int)this + 0x8c);
        // Offset +0x90: number of children
        int childCount = *(int*)((int)this + 0x90);
        int** end = childArray + childCount;

        for (int** it = childArray; it != end; ++it)
        {
            int* child = *it;
            // Offset +0xb2: child flags (bit0 = needs update)
            if (((*(byte*)(child + 0xb2)) & 1) != 0)
            {
                // Call external update function:
                // arg1 = global context (DAT_012233a8+4)
                // arg2 = child->someID (offset +0xa0)
                // arg3 = child->transform (offset +0x10)
                // arg4 = pointer to this node's new transform (offset +0x70)
                FUN_0042d380(*(int*)(DAT_012233a8 + 4),
                             *(int*)(child + 0xa0),
                             child + 0x10,
                             (const __int64*)((int)this + 0x70));
            }
        }
    }
}