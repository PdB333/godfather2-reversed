// FUNC_NAME: Condition::evaluate
// Address: 0x008ff7e0
// Role: Evaluates a comparison condition against a runtime value and returns result, then triggers an action with the selected target (true/false branch).

bool __thiscall Condition::evaluate(Condition *this) {
    uint runtimeValue;
    bool conditionMet;
    // local_c holds either the true or false target pointer (+0x60 or +0x68)
    // local_8 and local_4 are unused stack padding from compiler
    undefined4 targetPtr;
    undefined4 unused_1;
    undefined1 unused_2;

    runtimeValue = getCurrentValue();  // FUN_008fc6e0 - fetches a runtime uint (e.g., health, distance, money)

    // +0x50: comparison type enum (0: LT, 1: LE, 2: EQ, 3: GE, 4: GT)
    // +0x54: threshold value to compare against
    switch (*(int *)(this + 0x50)) {
        case 0:
            conditionMet = *(uint *)(this + 0x54) < runtimeValue;
            break;
        case 1:
            conditionMet = *(uint *)(this + 0x54) <= runtimeValue;
            break;
        case 2:
            conditionMet = runtimeValue == *(uint *)(this + 0x54);
            break;
        case 3:
            conditionMet = runtimeValue <= *(uint *)(this + 0x54);
            break;
        case 4:
            conditionMet = runtimeValue < *(uint *)(this + 0x54);
            break;
        default:
            conditionMet = false;
            goto afterCondition;
    }

    if (!conditionMet) {
afterCondition:
        targetPtr = *(undefined4 *)(this + 0x68);  // +0x68: target for false branch
    } else {
        targetPtr = *(undefined4 *)(this + 0x60);  // +0x60: target for true branch
    }

    unused_1 = 0;
    unused_2 = 0;

    // FUN_00408a00: likely triggers an event or stores the target handle (e.g., setResult, fireAction)
    setActionTarget(&targetPtr, 0);  // second param 0 = immediate/override flag?

    return conditionMet;
}