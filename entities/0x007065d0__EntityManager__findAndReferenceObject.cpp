// FUNC_NAME: EntityManager::findAndReferenceObject
int EntityManager::findAndReferenceObject(int primaryKey, int secondaryKey, int** referenceOut)
{
    int* foundObject = findObjectByKey(primaryKey, *referenceOut);
    if (foundObject == 0) {
        foundObject = findObjectByKey(secondaryKey, *referenceOut);
        if (foundObject == 0) {
            return 0;
        }
    }

    // Extract low bit from object flags at offset 0x1d0
    uint flags = *(uint*)((char*)foundObject + 0x1d0);
    uint8_t slotFlag = (uint8_t)(flags >> 6); // bit 6 of flags becomes low byte
    // Modify reference pointer: keep high 3 bytes, set low byte to slotFlag masked to bit0 only
    uintptr_t refVal = reinterpret_cast<uintptr_t>(referenceOut);
    refVal = (refVal & 0xFFFFFF00) | (slotFlag & 0x01);
    int* modifiedRef = reinterpret_cast<int*>(refVal);

    lockMutex(0);
    attachReference(foundObject, 0);
    unlockMutex(modifiedRef);
    return reinterpret_cast<int>(foundObject);
}