// FUNC_NAME: ConditionSet::evaluateAllAndExecute
void __fastcall ConditionSet::evaluateAllAndExecute(void* thisPtr) {
    // thisPtr + 0x58: m_pCallback (function pointer or object)
    // Each condition pair at offsets: +0x60/+0x70, +0x80/+0x90, ..., +0x140/+0x150
    // Pairs are 0x20 apart (each condition occupies 0x20 bytes, but we check the start and start+0x10)
    bool allPassed = true;

    allPassed = allPassed && conditionCheck(thisPtr + 0x60, thisPtr + 0x70);
    allPassed = allPassed && conditionCheck(thisPtr + 0x80, thisPtr + 0x90);
    allPassed = allPassed && conditionCheck(thisPtr + 0xa0, thisPtr + 0xb0);
    allPassed = allPassed && conditionCheck(thisPtr + 0xc0, thisPtr + 0xd0);
    allPassed = allPassed && conditionCheck(thisPtr + 0xe0, thisPtr + 0xf0);
    allPassed = allPassed && conditionCheck(thisPtr + 0x100, thisPtr + 0x110);
    allPassed = allPassed && conditionCheck(thisPtr + 0x120, thisPtr + 0x130);
    allPassed = allPassed && conditionCheck(thisPtr + 0x140, thisPtr + 0x150);

    if (allPassed) {
        int* callbackPtr = *(int**)((char*)thisPtr + 0x58);  // Dereference m_pCallback
        if (callbackPtr != 0) {
            int args[2];
            args[0] = (int)callbackPtr;  // function pointer or object
            args[1] = 0;                 // second argument (0)
            char local_4 = 0;            // unused or padding
            callDelegate(args, 0);       // FUN_00408a00 -> invokes callback
        }
    }
}
```