// FUNC_NAME: SpatialGrid::insertEntity
// Function address: 0x006e7260
// Inserts an entity into a 32x32 spatial hash grid based on its position.
// The grid stores entities in doubly-linked list per cell.
// entity+0x44: position.x (float)
// entity+0x4c: position.y (float)
// entity+0x8:  next pointer in cell list
// entity+0xc:  prev pointer in cell list
// entity+0x8a: flags byte (bit 4 = inserted flag)

void __thiscall SpatialGrid::insertEntity(int thisPtr, int entityPtr)
{
    int* cellBase;
    int index;
    int oldHead;

    // Check if entity is already inserted
    if ((*(byte*)(entityPtr + 0x8a) & 0x10) == 0)
    {
        // Compute cell index: 32x32 grid, each cell 8 bytes (head and tail)
        // x = *(float*)(entityPtr+0x44), y = *(float*)(entityPtr+0x4c)
        index = ((int)*(float*)(entityPtr + 0x4c) >> 3 & 0x1f) * 0x20 +
                ((int)*(float*)(entityPtr + 0x44) >> 3 & 0x1f);

        cellBase = (int*)(thisPtr + 0x20 + index * 8);

        // Link entity into cell's doubly-linked list (insert at front)
        *(int*)(entityPtr + 8) = *cellBase;           // entity->next = head
        *(int*)(entityPtr + 0xc) = 0;                  // entity->prev = nullptr

        if (*cellBase != 0)
        {
            // List not empty: update old head's prev
            oldHead = *cellBase;
            *(int*)(oldHead + 0xc) = entityPtr;       // oldHead->prev = entity
            *cellBase = entityPtr;                     // head = entity
            *(byte*)(entityPtr + 0x8a) |= 0x10;        // mark inserted
            *(int*)(thisPtr + 0x2020) += 1;            // increment entity count
            return;
        }

        // List was empty: set both head and tail
        cellBase[1] = entityPtr;                        // tail = entity
        *cellBase = entityPtr;                          // head = entity
        *(byte*)(entityPtr + 0x8a) |= 0x10;             // mark inserted
        *(int*)(thisPtr + 0x2020) += 1;                 // increment entity count
    }
}