// FUNC_NAME: EntityFactory::createEntity
void __thiscall EntityFactory::createEntity(int typeId, void* data1, void* data2, byte flag)
{
    // Check if game is in valid state to create entities
    if (!FUN_00481660()) {
        return;
    }

    // Allocate memory for the entity (size 0x48 = 72 bytes)
    Entity* newEntity = (Entity*)FUN_009c8e50(0x48);
    if (newEntity != nullptr) {
        // Call entity constructor with the type identifier
        newEntity = FUN_007a0de0(typeId);

        // Set custom data fields
        // +0x38: first data pointer
        newEntity->field_0x38 = data1;
        // +0x3c: second data pointer
        newEntity->field_0x3c = data2;
        // +0x40: flag byte (e.g., boolean or state)
        newEntity->field_0x40 = flag;

        // Register the entity (add to world, list, etc.)
        FUN_00481690(newEntity);
    }
}