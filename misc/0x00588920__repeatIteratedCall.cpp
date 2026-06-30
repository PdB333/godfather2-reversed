// FUNC_NAME: repeatIteratedCall
void repeatIteratedCall(int param1)
{
    // param1 is likely a value used to compute iteration count
    // unaff_EDI is a register variable that holds a global or member value
    int diff = param1 - unaff_EDI; // unaff_EDI is not a local variable; it comes from calling context
    // Compute number of iterations: (diff/8) with proper rounding for signed division
    int count = ((diff >> 2) - (diff >> 31)) >> 1;
    while (count > 0)
    {
        FUN_00588b80(); // Called repeatedly; likely processes something
        count--;
    }
}