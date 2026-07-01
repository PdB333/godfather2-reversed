// FUNC_NAME: ConditionGroup::evaluateAllConditions
void __thiscall ConditionGroup::evaluateAllConditions(int thisObj, int unusedParam, int conditionList)
{
    uint count = listGetCount(conditionList);
    uint i = 0;
    char* conditionName = nullptr;

    // Enter scope for batch evaluation (e.g., beginChangeBatch)
    beginBatch(thisObj + 0x10);

    while (i < count)
    {
        uint* conditionEntry = (uint*)listGetItem(conditionList, i);
        stringFromHash(conditionEntry[0], &conditionName);

        char* name = conditionName;
        if (name == nullptr)
        {
            name = "UnknownCondition"; // DAT_0120546e
        }

        uint argA = conditionEntry[1];
        uint argB = conditionEntry[2];

        byte result = evaluateSingleCondition(argA, argB, name);
        *(byte*)(thisObj + 0xc) &= result;

        i++;
    }

    // Leave the evaluation scope
    endBatch();

    // Note: The original binary calls (*local_4)(conditionName) after the loop,
    // but local_4 is uninitialized (null). This likely corresponds to a free of
    // the allocated string (via a global destructor table or similar). Since the
    // pointer is null, it might indicate that stringFromHash does not allocate
    // memory, or the decompiler misidentified the call. We omit the call as it
    // would cause a crash in the reconstructed logic.
    // See the Ghidra decompilation for the attempted call.
}