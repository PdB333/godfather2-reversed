// FUNC_NAME: PropertyCompare::compareValues
bool __thiscall PropertyCompare::compareValues(int* this, int extraParam) {
    int type = this[0]; // +0x00: type tag (0=byte, 1=int, 2=float)
    int* keyAParts = &this[1]; // +0x04, +0x08
    int* keyBParts = &this[3]; // +0x0C, +0x10

    if (type == 0) {
        uint8_t valA = fetchByteValue(keyAParts[0], keyAParts[1], extraParam);
        uint8_t valB = fetchByteValue(keyBParts[0], keyBParts[1], extraParam);
        return valB <= valA; // returns true if keyB <= keyA
    }
    else if (type == 1) {
        int valA = fetchIntValue(keyAParts[0], keyAParts[1], extraParam);
        int valB = fetchIntValue(keyBParts[0], keyBParts[1], extraParam);
        return valB <= valA;
    }
    else if (type == 2) {
        float valA = (float)fetchFloatValue(keyAParts[0], keyAParts[1], extraParam);
        float valB = (float)fetchFloatValue(keyBParts[0], keyBParts[1], extraParam);
        return valB <= valA;
    }
    return false; // unknown type
}