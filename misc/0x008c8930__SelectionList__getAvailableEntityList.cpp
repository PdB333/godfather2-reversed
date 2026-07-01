// FUNC_NAME: SelectionList::getAvailableEntityList
// Address: 0x008c8930
// Purpose: Fills an output array with all entity IDs from the global entity database,
// but zeroes out those that are already in the selection list. Returns total byte size written.
// This is used to build a list of entities that are not already selected (e.g., for UI listing).

// Assumptions:
// - this+0x08: pointer to a global entity manager (or null if unavailable)
// - this+0x0c: pointer to a SelectionList structure (has array at +0x124, count at +0x128)
// - Manager (entityDB) has array of all entity IDs at +0x18 and count at +0x1c
// - FUN_0043b870 is EntityDatabase::getInstance()

int __thiscall SelectionList::getAvailableEntityList(int* outList) {
    int* pManager;
    int iVar3;
    uint dbCount;
    uint selectionCount;

    // If the global manager pointer is null, mark manager as invalid (will result in empty output)
    if (*(int*)(this + 0x08) == 0) {
        pManager = 0; // no manager available
    } else {
        pManager = EntityDatabase::getInstance(); // get the global entity database
    }

    // Pointer to the selection list structure (contains array of selected IDs)
    SelectionList* pSelectionList = *(SelectionList**)(this + 0x0c);
    // This holds the array of all entity IDs from the database
    int* allEntityIds = pManager ? *(int**)(pManager + 0x18) : (int*)0;
    uint dbCount = pManager ? *(uint*)(pManager + 0x1c) : 0;

    // Iterate over all entities in the database
    for (uint i = 0; i < dbCount; i++) {
        int entityId = allEntityIds[i]; // current entity ID from the full list
        selectionCount = *(uint*)(pSelectionList + 0x128); // number of selected IDs
        uint selIdx = 0;

        // Search in the selected list for a match
        if (selectionCount != 0) {
            int* pSelectionIds = *(int**)(pSelectionList + 0x124); // array of selected IDs
            do {
                if (pSelectionIds[selIdx] == entityId) {
                    // Entity is selected – mark it as 0 in output
                    if (-1 < (int)selIdx) { // always true for uint cast to int, but kept as original logic
                        entityId = 0;
                    }
                    break;
                }
                selIdx++;
            } while (selIdx < selectionCount);
        }

        // Write the (possibly zeroed) ID to the output array
        outList[i] = entityId;
    }

    // Return total byte size of the written data
    return dbCount * 4;
}