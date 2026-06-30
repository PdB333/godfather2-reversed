// FUNC_NAME: EventDispatch::processQueuedMessages
void __thiscall EventDispatch::processQueuedMessages(void* this_ptr, int** listHead)
{
    // listHead: pointer to pointer to first queue node
    int* current = *listHead ? **(int**)(*listHead + 8) : 0;

    while (current)
    {
        // Ring buffer descriptor at offset +4
        RingBufferDescriptor* desc = *(RingBufferDescriptor**)(current + 4);
        int remaining = desc->count; // piVar2[3]

        while (remaining)
        {
            // Current item location: buffer base + head * 8 (each item is 2 ints)
            int* item = (int*)(desc->buffer + desc->head * 2);
            // Call the registered handler with the two ints
            void (**handler)(int, int) = *(void (***)(int, int))(*(int**)(this_ptr + 8) + 4);
            (*handler)(item[0], item[1]);

            // Advance the head pointer (circular)
            int oldHead = desc->head; // iVar3
            int* base = desc->buffer; // iVar4
            // Overwrite current slot with itself (no-op in effect, but keeps code)
            item[0] = *(base + oldHead * 2);
            item[1] = *(base + oldHead * 2 + 1);
            desc->head++;
            if (desc->head >= desc->capacity)
                desc->head = 0;
            desc->count--;
            remaining = desc->count;
        }

        // Free the buffer and the node itself
        if (desc->buffer)
            freeBuffer(desc->buffer); // FUN_009c8f10
        freeNode(desc); // FUN_009c8eb0

        // Move to next node
        current = **(int**)(current + 8);
    }

    // Final flush/processing step
    finalizeFlush(); // FUN_0065dc00
}