// FUNC_NAME: isEnemyTarget
bool __fastcall isEnemyTarget(void* thisPtr)
{
    // +0x52c: whether this entity is currently active/engaged
    if (*(uint8_t*)((uint8_t*)thisPtr + 0x52c) != 0)
    {
        // Perform some context update (probably AI state refresh)
        updateAIState(); // FUN_00b92e50

        // +0x567: relationship/state byte (e.g., faction allegiance)
        uint8_t relationshipState = *(uint8_t*)((uint8_t*)thisPtr + 0x567);
        if (relationshipState != 0x12) // 0x12 = neutral/friendly? 
        {
            // Retrieve relationship data table based on the state byte
            int* relationshipTable = (int*)getRelationshipData(relationshipState); // FUN_00b94a20
            if ((relationshipTable != nullptr) && (relationshipTable[1] == 2)) // +4 = relationship type flag (2 = enemy)
            {
                return true;
            }
        }
    }
    return false;
}