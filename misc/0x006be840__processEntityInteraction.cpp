// FUNC_NAME: processEntityInteraction
void processEntityInteraction(Entity* entityA, Entity* entityB, uint32_t extraParam)
{
    // Check entity type at offset +0x54
    if (entityA->typeId == 0x637b907)
    {
        char result = FUN_006b34a0();
        if (result == '\0')
        {
            // Entity A is of special type (e.g. player) and condition not met
            FUN_008c3660(0x661cde1, extraParam, 0);
        }
        return;
    }

    if (entityB->typeId == 0x637b907)
    {
        // Entity B is of the same special type
        FUN_008c3660(0x789a9424, extraParam, 0);
        return;
    }

    // Neither entity is of the special type (e.g. generic interaction)
    FUN_008c36b0(0xe522174b, extraParam, 0);
}