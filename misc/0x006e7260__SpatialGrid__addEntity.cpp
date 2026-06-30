// FUNC_NAME: SpatialGrid::addEntity
void __thiscall SpatialGrid::addEntity(SpatialGrid *this, Entity *entity)
{
    // Check if entity is already in grid (bit 4 of flags at offset 0x8a)
    if ((entity->flags & 0x10) == 0) {
        // Calculate 32x32 grid cell index from entity's x and z positions
        // Positions are floats at offsets 0x44 (x) and 0x4c (z)
        int cellX = (int)(entity->positionX * 0.125f) & 0x1F;  // >>3 & 0x1f
        int cellZ = (int)(entity->positionZ * 0.125f) & 0x1F;  // >>3 & 0x1f
        int cellIndex = cellZ * 32 + cellX;  // 32x32 grid

        // Grid cell storage starts at offset 0x20, each cell is 8 bytes (head, tail)
        Cell *cell = &this->gridCells[cellIndex];

        // Insert entity at front of cell's linked list
        entity->next = cell->head;  // New entity points to old head
        entity->prev = nullptr;     // New entity has no previous

        if (cell->head != nullptr) {
            // Link old head's prev to new entity
            cell->head->prev = entity;
            // Set head to new entity
            cell->head = entity;
        } else {
            // Cell was empty: both head and tail point to new entity
            cell->head = entity;
            cell->tail = entity;
        }

        // Mark as in grid (set bit 4 of flags)
        entity->flags |= 0x10;

        // Increment total entity count in grid (offset 0x2020)
        this->totalEntities++;
    }
}