// FUNC_NAME: GameLogic::evaluateCondition
int __thiscall evaluateCondition(int thisObj) {
    int* dataPtr;  // pointer to internal data (offset +0x08)
    int value1, value2;

    value1 = getTargetValue(1);  // FUN_0046ab80(1)
    value2 = getTargetValue(2);  // FUN_0046ab80(2)

    dataPtr = *(int**)(thisObj + 8);  // +0x08: pointer to current decision slot
    *dataPtr = 1;  // set first field to 1 (active?)

    if (value1 < value2) {
        dataPtr[1] = 1;  // second field indicates priority/choice
    } else {
        dataPtr[1] = 0;
    }

    // advance to next slot (8 bytes per slot)
    *(int**)(thisObj + 8) = dataPtr + 2;  // +0x08 updated
    return 1;
}