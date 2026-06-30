// FUNC_NAME: EntityManager::spawnEntityObjects
void __fastcall EntityManager::spawnEntityObjects(
    int unusedParam,                    // param_1: ECX, unused
    DynamicArray& outArray,             // param_2: EDX, dynamic pointer array for created objects
    EntityDefinition* def,              // param_3: stack, parent entity definition
    bool isImportant,                   // param_4: stack, flag to mark object as important
    int gameTick,                       // param_5: stack, current game tick for logging
)
{
    CreateList* createList = *(CreateList**)(def + 0x08); // parent's creation list structure
    if (*(int*)(gameState + 0x24) == 0)                   // global game state check (DAT_01223480+0x24)
        return;

    // Process primary entity list (e.g., NPC definitions)
    for (int i = 0; i < createList->numPrimary; i++)
    {
        EntityBase* source = createList->primaryItems[i]; // original item (e.g., template)
        AllocationRequest req = { 2, 0x10, 0 };           // type=2, subtype=0x10, flags=0
        SimObject* obj = (SimObject*)AllocateMemory(0x70, &req); // allocate 0x70-byte SimObject

        if (obj != nullptr)
        {
            // Zero-initialize critical fields (offsets 0x40 to 0x68)
            obj->field_48 = 0;
            obj->field_4C = 0;
            obj->field_50 = 0;
            obj->field_54 = 0;
            obj->field_58 = 0;
            obj->field_5C = 0;
            obj->field_40 = 0;
            obj->field_44 = 0;
            obj->field_60 = 0;
            obj->field_64 = 0;
            obj->field_68 = 0;
        }

        // Resize dynamic array if full (check capacity at +0x14 vs size at +0x10)
        if (outArray.size == outArray.capacity)
        {
            int newCapacity = (outArray.capacity == 0) ? 1 : outArray.capacity * 2;
            ResizeArray(newCapacity); // FUN_0054aee0
        }

        // Append new SimObject pointer to output array
        uint* slot = (uint*)(outArray.data + outArray.size * 4);
        outArray.size++;
        if (slot != nullptr)
            *slot = (uint)obj;

        // Process the source entity (e.g., assign transform, component data)
        ProcessEntity(source, def, 0, 1, 0xFFFFFFFF); // FUN_00556ab0

        // Log spawn event (event ID 0x2003)
        LogEvent(0x2003, gameTick, gameTick >> 31);   // FUN_009f01f0

        // Mark object as important (e.g., for mission-critical NPC)
        if (isImportant)
            obj->field_4C = 0x3E1; // 1009, likely "isImportant" flag

        // Store reference handle in source: pack object pointer >> 2 | 0xC0000000
        source->objectHandle = ((uint)obj >> 2) | 0xC0000000;

        // Finalize object initialization
        InitializeObject(source, 1); // FUN_009e6ff0
    }

    // Post-processing: clean up or initialize related arrays from the definition
    for (int i = 0; i < createList->numLights; i++)
        ReleaseLight(createList->lights[i]); // FUN_009e7450

    for (int i = 0; i < createList->numEffects; i++)
        ReleaseEffect(createList->effects[i]); // FUN_009ebe70

    for (int i = 0; i < createList->numTriggers; i++)
        ReleaseTrigger(createList->triggers[i]); // FUN_009eace0
}