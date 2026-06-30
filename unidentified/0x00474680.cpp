// FUNC_00474680: BaseGameObject::verifyAction
bool __thiscall BaseGameObject::verifyAction(int this, char param_forceReset) {
    char ret;
    int containerPtr;
    bool bVar;
    // Structure used for query
    struct ActionQuery {
        int queryType; // +0x0, always 1
        int objectId;  // +0x4
        int padding;   // +0x8, always 0
        char flag;     // +0xC, param_forceReset
    } query;

    // Check if pointer at +0xE8 is valid
    if (*(int*)(this + 0xE8) != 0) {
        // Prepare query
        query.queryType = 1;
        query.padding = 0;
        query.flag = param_forceReset;

        // Get an object from the container at +0x6C (index 0, subindex 0)
        containerPtr = FUN_00455f50(this + 0x6C, 0, 0);
        if (containerPtr != 0) {
            query.objectId = *(int*)(containerPtr + 0x24); // Extract ID from object
        } else {
            query.objectId = 0;
        }

        // Execute the query
        ret = FUN_005e2040(&query);
        bVar = (ret != 0);
        if (bVar) {
            // Log or trigger event if query succeeded
            FUN_004086d0(&DAT_012069c4);
        }

        // If force reset flag is set, clear the pointer at +0xE8
        if (param_forceReset != 0) {
            *(int*)(this + 0xE8) = 0;
            return bVar;
        }
    } else {
        bVar = false;
    }
    return bVar;
}