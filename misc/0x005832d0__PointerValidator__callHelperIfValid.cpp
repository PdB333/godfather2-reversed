// FUNC_NAME: PointerValidator::callHelperIfValid
int __fastcall PointerValidator::callHelperIfValid(void* thisPtr, void* otherPtr)
{
    if ((thisPtr != 0) && (otherPtr != 0)) {
        return helperFunction(); // Calls FUN_005848f0
    }
    return 0;
}