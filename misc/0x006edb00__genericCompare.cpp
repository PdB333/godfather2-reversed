// FUNC_NAME: genericCompare
bool genericCompare(int* comparatorDesc, uint32_t extraData) {
    // comparatorDesc structure:
    // +0x00: type (0=byte, 1=int, 2=float)
    // +0x04: first item part1
    // +0x08: first item part2
    // +0x0C: second item part1
    // +0x10: second item part2

    int type = *comparatorDesc;
    if (type == 0) {
        uint8_t value1 = getByteAttr(comparatorDesc[1], comparatorDesc[2], extraData);
        uint8_t value2 = getByteAttr(comparatorDesc[3], comparatorDesc[4], extraData);
        return value2 < value1; // second < first?
    }
    else if (type == 1) {
        int value1 = getIntAttr(comparatorDesc[1], comparatorDesc[2], extraData);
        int value2 = getIntAttr(comparatorDesc[3], comparatorDesc[4], extraData);
        return value2 < value1;
    }
    else if (type == 2) {
        float value1 = getFloatAttr(comparatorDesc[1], comparatorDesc[2], extraData);
        float value2 = getFloatAttr(comparatorDesc[3], comparatorDesc[4], extraData);
        return value2 < value1;
    }
    return false;
}