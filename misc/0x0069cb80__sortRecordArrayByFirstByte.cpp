// FUNC_NAME: sortRecordArrayByFirstByte
void __cdecl sortRecordArrayByFirstByte(byte* start, byte* end)
{
    // Sort 8-byte records by the least significant byte of the first 4-byte field.
    // Insertion sort (stable) in ascending order.
    struct Record {
        uint32_t field0; // +0x00: first int, low byte is sort key
        uint32_t field4; // +0x04: second int (not used for sorting)
    };

    if (start == end) return;

    // Start from the second element (index 1)
    for (byte* current = start + 8; current != end; current += 8)
    {
        Record temp;
        temp.field0 = *(uint32_t*)current;
        temp.field4 = *(uint32_t*)(current + 4);

        byte* insertPos = current;

        if ((byte)temp.field0 < *start)
        {
            // Insert before the first element: shift entire sorted portion right by one
            for (; start != insertPos; insertPos -= 8)
            {
                *(uint32_t*)insertPos = *(uint32_t*)(insertPos - 8);
                *(uint32_t*)(insertPos + 4) = *(uint32_t*)(insertPos - 4);
            }
            *(uint32_t*)start = temp.field0;
            *(uint32_t*)(start + 4) = temp.field4;
        }
        else
        {
            // Find insertion point within sorted region
            byte* prev = current - 8;
            byte key = *(byte*)prev; // low byte of element before current
            while ((byte)temp.field0 < key)
            {
                // Shift element at 'prev' right to 'insertPos'
                *(uint32_t*)insertPos = *(uint32_t*)prev;
                *(uint32_t*)(insertPos + 4) = *(uint32_t*)(prev + 4);
                insertPos = prev;
                prev -= 8;
                key = *(byte*)prev;
            }
            *(uint32_t*)insertPos = temp.field0;
            *(uint32_t*)(insertPos + 4) = temp.field4;
        }
    }
}