// FUNC_NAME: EntityManager::extractBitMaskFromEntityList
void __fastcall EntityManager::extractBitMaskFromEntityList(EntityManager* this)
{
    // Counter indicating number of bits written; if non-zero, mask already built
    int* pCounter = reinterpret_cast<int*>((uint8*)this + 0x100);
    if (*pCounter != 0)
        return;

    // Linked list of entities (head at +0x1c)
    EntityNode* node = *reinterpret_cast<EntityNode**>((uint8*)this + 0x1c);
    while (node)
    {
        // Extract bit 2 from node's flags field at offset +0x14
        uint32 flags = *reinterpret_cast<uint32*>((uint8*)node + 0x14);
        uint8 bit = (uint8)((flags >> 2) & 1);

        // Store the bit in a byte array at +0x104
        *reinterpret_cast<uint8*>((uint8*)this + 0x104 + *pCounter) = bit;
        (*pCounter)++;

        // Advance to next node (next pointer at +0x1c within node)
        node = *reinterpret_cast<EntityNode**>((uint8*)node + 0x1c);

        // Yield to scheduler / thread
        yieldExecution(0); // FUN_00624ca0
    }
}