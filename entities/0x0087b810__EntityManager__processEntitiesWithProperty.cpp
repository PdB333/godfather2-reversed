// FUNC_NAME: EntityManager::processEntitiesWithProperty
bool __fastcall EntityManager::processEntitiesWithProperty(int* this)
{
    char matchCount = '\0'; // +0x0 (local)
    byte loopIndex = 0; // +0x1 (local)
    int someStruct[4]; // +0x14 (local stack)

    int numEntities = entityCount(); // FUN_00543330
    if (numEntities != 0) {
        unsigned int index = 0;
        do {
            someStruct[2] = 0;
            someStruct[1] = 0;
            // vtable+0x218: getEntityAtIndex(index, &someStruct[1])
            (**(code**)(*this + 0x218))(index, &someStruct[1]);

            // vtable+500 (0x1F4): getEntityPropertyPointer()
            int* propertyPtr = (int*)(**(code**)(*this + 500))(someStruct);
            if (propertyPtr != nullptr) {
                someStruct[0] = 0;
                // vtable+0x10: hasPropertyHash(0x369ac561, &someStruct[0])
                char hasHash = (**(code**)(*propertyPtr + 0x10))(0x369ac561, someStruct);
                if (hasHash != '\0' && someStruct[0] != 0) {
                    processEntity(someStruct[0], &someStruct[1]); // FUN_00878250
                    matchCount = matchCount + '\x01';
                }
            }
            loopIndex = loopIndex + 1;
            index = (uint)loopIndex;
            unsigned int newEntityCount = entityCount(); // FUN_00543330
        } while (index < newEntityCount);

        if (matchCount != '\0') {
            // notifyManager(g_pEntityList, this + 0x3C, 0)
            FUN_00408c70(&DAT_0112e134, this + 0xf, 0);
        }
    }

    int someFlag = someOtherFunction(); // FUN_00542d70
    if (someFlag != 0 && matchCount != '\0') {
        updateAfterProcessing(0); // FUN_0086cac0
    }

    return matchCount != '\0';
}