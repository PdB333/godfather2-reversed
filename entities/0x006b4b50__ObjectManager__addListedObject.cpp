// FUNC_NAME: ObjectManager::addListedObject
void __thiscall ObjectManager::addListedObject(ObjectManager* thisPtr)
{
    int* newObj;
    int* listPtr;
    int newCapacity;

    // Attempt to obtain an object from two possible sources (e.g., free pool or creation)
    newObj = (int*)getAvailableObject();          // FUN_006b4080 – returns object or null
    if (newObj == nullptr) {
        newObj = (int*)createNewObject();         // FUN_006b2c70 – create if none free
        if (newObj == nullptr) {
            return;                               // no object to add
        }
    }

    // Mark object as "active" (bit23 set) and clear "pending" flag (bit26 cleared)
    newObj->flags |= 0x800000;                    // +0x5c flags
    newObj->flags &= 0xfbffffff;                  // clear bit 26

    // Release a reference or decrement a counter associated with this list
    releaseReference(thisPtr->somethingRef);      // FUN_00790d30; +0x38

    // Ensure capacity for new entry
    if (thisPtr->numEntries == thisPtr->currentCapacity) { // +0xac vs +0xb0
        newCapacity = (thisPtr->currentCapacity != 0)
                      ? thisPtr->currentCapacity * 2
                      : 1;
        reallocateEntryArray(newCapacity);        // FUN_006b1e10
    }

    // Store object pointer in the growing array
    listPtr = thisPtr->entryArray + thisPtr->numEntries; // +0xa8 base, index by +0xac
    thisPtr->numEntries += 1;
    if (listPtr != nullptr) {
        *listPtr = newObj;
    }

    // Toggle a global active flag based on list emptiness and other conditions
    if ((thisPtr->field_0x88 == 0) &&
        (thisPtr->field_0xa0 == 0) &&
        (thisPtr->numEntries == 0) &&
        (thisPtr->field_0xb8 == 0)) {
        disableGlobalActiveFlag();               // FUN_004086d0(&DAT_0112a640)
    } else {
        enableGlobalActiveFlag();                // FUN_00408680(&DAT_0112a640)
    }
}