// FUNC_NAME: Entity::getDataId
int __thiscall Entity::getDataId(void) {
    int result = -1;
    if (this != 0) {
        int** ppData = (int**)(this + 0x2c); // +0x2c: pointer to data block
        if (*ppData != 0) {
            int* pInner = **ppData; // first field of data block is another pointer
            if (pInner != 0) {
                result = *(int*)(pInner + 0x18); // +0x18: value (likely an ID)
            }
        }
    }
    return result;
}