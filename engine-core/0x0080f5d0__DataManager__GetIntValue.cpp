// FUNC_NAME: DataManager::GetIntValue
// Function at 0x0080f5d0: Retrieve an integer attribute by key. Returns 1 if found, 0 if not.
int DataManager::GetIntValue(int key, int& outValue) {
    int value = 0;
    bool found = getAttributeInt(this, key, &value); // calls internal at 0x004480d0
    if (found) {
        outValue = value;
        return 1;
    }
    outValue = 0;
    return 0;
}