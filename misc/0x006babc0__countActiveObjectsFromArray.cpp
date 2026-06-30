// FUNC_NAME: countActiveObjectsFromArray
int countActiveObjectsFromArray(int *param_1) {
    uint index = 0;
    int count = 0;
    int object;          // iVar3
    int globalResult;    // iVar2

    if (param_1[1] != 0) { // array size
        do {
            object = *(int *)(*param_1 + index * 4);
            globalResult = isGameActive(); // FUN_007912e0
            if ((((globalResult != 0) || 
                 (uint flags5c = *(uint *)(object + 0x5c), (flags5c & 0x60000) != 0)) ||
                 ((flags5c >> 0x14 & 1) != 0)) ||
                ((((flags5c >> 0x1a & 1) != 0 || 
                   (object = getPerceptionManager(), object == 0)) ||
                 ((~(byte)(*(uint *)(object + 0x84) >> 5) & 1) == 0)))) {
                count++;
            }
            index++;
        } while (index < (uint)param_1[1]);
    }
    return count;
}