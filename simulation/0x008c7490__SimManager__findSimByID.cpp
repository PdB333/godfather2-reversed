// FUNC_NAME: SimManager::findSimByID
int __thiscall SimManager::findSimByID(int thisPtr, int id)
{
    int result = 0;
    uint count = *(uint *)(thisPtr + 0x28); // +0x28: number of sims in array
    if (count != 0) {
        int **array = *(int ***)(thisPtr + 0x24); // +0x24: pointer to array of sim pointers
        for (uint i = 0; i < count; i++) {
            if (*(int *)(array[i] + 0x54) == id) { // +0x54: sim's ID field
                result = array[i];
                break;
            }
        }
    }
    return result;
}