// FUNC_NAME: compareValues (property equality check)
uint compareValues(int *valueEntry, uint context) {
    int type = *valueEntry;
    if (type == 0) {
        char val1 = getCharValue(valueEntry[1], valueEntry[2], context);
        char val2 = getCharValue(valueEntry[3], valueEntry[4], context);
        if (val1 == val2) {
            return 0;
        }
        if (val1 != '\0') {
            return 1;
        }
        bool bothZero = (val2 == '\0');
        if (!bothZero) {
            return 1;
        }
        return 0;
    }
    if (type == 1) {
        int val1 = getIntValue(valueEntry[1], valueEntry[2], context);
        int val2 = getIntValue(valueEntry[3], valueEntry[4], context);
        if (val1 == val2) {
            return 0;
        }
        if (val1 != 0) {
            return 1;
        }
        bool bothZero = (val2 == 0);
        if (!bothZero) {
            return 1;
        }
        return 0;
    }
    if (type == 2) {
        float val1 = (float)getFloatValue(valueEntry[1], valueEntry[2], context);
        float val2 = (float)getFloatValue(valueEntry[3], valueEntry[4], context);
        if (val1 == val2) {
            return 0;
        }
        if (val1 != 0.0f) {
            return 1;
        }
        if (val2 != 0.0f) {
            return 1;
        }
        return 0;
    }
    return 0;
}