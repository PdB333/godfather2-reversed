// FUNC_NAME: Entity::getFlaggedProperty
uint __thiscall Entity::getFlaggedProperty(void *this, int object) {
    uint result;
    uint dataValue;
    int dataSize;
    uint *dataPtr;

    dataSize = 0;
    dataPtr = (uint *)0x0;
    result = FUN_005fd340(*(undefined2 *)(object + 8), 0xee654334, &dataSize);
    if ((char)result != '\0') {
        dataValue = 0;
        if (((dataPtr != (uint *)0x0) && (dataSize != 0)) && (*(char *)(dataSize + 6) == '\x02')) {
            dataValue = *dataPtr;
        }
        // Construct return: upper 3 bytes of dataValue, low byte = 1 if bit 2 set, else 0
        result = CONCAT31((int3)(dataValue >> 8), 1);
        if ((dataValue & 4) != 0) {
            return result;
        }
    }
    // Clear low byte on failure or flag not set
    return result & 0xffffff00;
}