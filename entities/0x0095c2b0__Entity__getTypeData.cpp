//FUNC_NAME: Entity::getTypeData
uint32_t __fastcall Entity::getTypeData(Entity* thisPtr)
{
    // Offset +0x24: typeIndex (index into global type data table)
    // Global array at 0x00d8ccd4: gTypeDataTable
    return gTypeDataTable[*(int*)((uint8_t*)thisPtr + 0x24)];
}