// FUNC_NAME: EARSObjectList::findObjectByType
int EARSObjectList::findObjectByType() {
    int result = 0;
    ushort count = *(ushort *)(this + 0x20); // Number of entries in the list
    if (count != 0) {
        for (ushort i = 0; i < count; i++) {
            int *node = *(int **)(*(int *)(this + 0x1c) + i * 4); // Pointer to each node
            if (node[5] == 0x10) { // Subtype 0x10 (e.g., mission objective)
                int *obj = (int *)*node; // First field of node is pointer to game object
                if (obj != nullptr && *(int *)(obj + 8) == 0x1961bed) { // Class ID check
                    result = *(int *)(obj + 0x1c); // Return component pointer at +0x1C
                }
                break; // Found the first matching node
            }
        }
    }
    return result;
}