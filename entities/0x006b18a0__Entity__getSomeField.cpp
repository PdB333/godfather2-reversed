// FUNC_NAME: Entity::getSomeField
uint32_t __fastcall Entity::getSomeField(Entity* thisPtr)
{
    // Return the value at offset 0x5C from the entity object
    // This is likely a field storing some entity state or identifier
    return *(uint32_t*)((uint8_t*)thisPtr + 0x5C);
}