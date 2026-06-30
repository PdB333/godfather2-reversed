// FUNC_NAME: SpatialTree::processNodeRecursive
int SpatialTree::processNodeRecursive(void* context1, void* context2, void* context3, int* node)
{
    int result = 0;

    if (node != nullptr)
    {
        // Check if the node should be processed directly: no children, or flagged as "processed"
        // Structure fields: +0x18 (node[6]) likely child count; +0x20 (node[8]) first child pointer
        // +0x14 (node[5] byte) flags (bit 2 = 0x04 = disabled/processed)
        if ((node[6] == 0) || (node[8] == 0) || ((*(uint8_t*)(node + 5) & 0x4) != 0))
        {
            // Call virtual function at vtable+0x14 to process/replace the node
            // Returns a new node pointer (possibly the same or a modified one)
            node = (int*)((void (*)(void*, void*, void*, int*, int))(*(void***)node)[5])(
                context1, context2, context3, &result, 0);
        }

        // result now holds the output from the virtual function (initially 0 if not called)
        if ((node != nullptr) && (node[8] != 0))
        {
            int child = node[8];               // First child at +0x20
            while (child != 0)
            {
                int nextChild = *(int*)(child + 0x28); // Next sibling at +0x28
                int childResult = SpatialTree::processNodeRecursive(context1, context2, context3, child);
                if (childResult != 0)
                {
                    result = childResult - 1;
                    break;
                }
                child = nextChild;
            }
        }
    }
    return result;
}