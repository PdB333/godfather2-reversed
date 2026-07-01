// FUNC_NAME: PointerArray::removeNulls
void __thiscall PointerArray::removeNulls()
{
    // this+0xac: pointer to array descriptor struct { int** data; int count; }
    ArrayDescriptor* desc = *(ArrayDescriptor**)(this + 0xac);
    if (!desc) return;

    int count = desc->count;
    int** data = desc->data;

    // Iterate backwards from count-1 to 0
    for (int i = count - 1; i >= 0; i--)
    {
        if (data[i] == nullptr)
        {
            // If this null is not the last element, replace it with the last element
            if (i != count - 1)
            {
                data[i] = data[count - 1];
            }
            // Decrement count (effectively removing the last element)
            count--;
        }
    }

    desc->count = count;

    // If all elements were null, free the array and the descriptor
    if (count == 0)
    {
        if (desc)
        {
            if (desc->data)
            {
                DeallocateArray(desc->data); // FUN_009c8f10
            }
            DeallocateStruct(desc);          // FUN_009c8eb0
        }
        *(int**)(this + 0xac) = nullptr;
    }

    // Clear the "needs compaction" flag (bit 0x02000000) at offset 0x5c
    *(uint32_t*)(this + 0x5c) &= ~0x02000000;
}