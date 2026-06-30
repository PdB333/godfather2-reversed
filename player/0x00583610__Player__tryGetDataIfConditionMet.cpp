// FUNC_NAME: Player::tryGetDataIfConditionMet
// Function address: 0x00583610
// Role: Validates both the object pointer (this) and an external condition (passed via EAX register at call time) before calling an internal retrieval function.
//       The EAX value is not a formal parameter; it is provided by the caller and stored in the register.
//       This pattern is used for quick conditional access where the condition is preloaded into EAX.

int __fastcall Player::tryGetDataIfConditionMet(int thisPtr, int conditionInEAX) // second parameter added for clarity, originally register
{
    int result;
    if (thisPtr != 0 && conditionInEAX != 0) {
        result = FUN_00585a60(thisPtr);
    } else {
        result = 0;
    }
    return result;
}