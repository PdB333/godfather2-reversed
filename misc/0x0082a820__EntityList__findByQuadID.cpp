// FUNC_NAME: EntityList::findByQuadID
// Function at 0x0082a820 searches a container of entities by a 16-byte quad ID (4 ints).
// Container layout: +0x08 = array of pointers to entity objects, +0x0C = count.
// Each entity object has ID fields at offsets +0x1C, +0x20, +0x24, +0x28 (4 consecutive ints).
// Returns pointer to entity (as int) or 0 if not found.
__thiscall int EntityList::findByQuadID(const int* quadID)
{
    uint32_t count = *(uint32_t*)((char*)this + 0xC);
    if (count != 0)
    {
        int** entityArray = *(int***)((char*)this + 0x8);
        for (uint32_t i = 0; i < count; ++i)
        {
            int* entity = entityArray[i];
            // Compare quad ID fields at offsets 0x1C, 0x20, 0x24, 0x28
            if (entity[7] == quadID[0] &&   // +0x1C
                entity[8] == quadID[1] &&   // +0x20
                entity[9] == quadID[2] &&   // +0x24
                entity[10] == quadID[3])    // +0x28
            {
                return (int)entity;
            }
        }
    }
    return 0;
}