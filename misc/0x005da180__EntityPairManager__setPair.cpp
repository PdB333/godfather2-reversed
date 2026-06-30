// FUNC_NAME: EntityPairManager::setPair
void __thiscall EntityPairManager::setPair(EntityPairManager* this, int param1, int newId1, int newId2, int oldId1, int oldId2) {
    // Verify that newId1 is valid and matches the expected old value
    if (newId1 == 0 || newId1 != oldId1) {
        // Assertion or error handling for invalid state
        FUN_00b97aea();
    }
    // If the second ID changed, compute a derived value and store it at param1+0x0C
    if (newId2 != oldId2) {
        int derived = FUN_005da650(oldId2);  // likely a hash or ID transformation
        *(int*)(param1 + 0x0C) = derived;
    }
    // Update the pair values stored in this object (offsets 0 and 4)
    this->id1 = newId1;   // this[0]
    this->id2 = newId2;   // this[1]
}