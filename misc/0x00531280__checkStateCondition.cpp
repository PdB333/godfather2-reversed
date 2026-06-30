// FUNC_NAME: checkStateCondition
// Address: 0x00531280
// Checks if global state flags (likely a mode indicator and a pointer) are both set.
// DAT_01125294 is a byte, DAT_01125290 is an int/pointer (non-zero indicates active).

extern char DAT_01125294;
extern int DAT_01125290;

bool __cdecl checkStateCondition(void)
{
    if ((DAT_01125294 == 0x06) && (DAT_01125290 != 0))
    {
        return true;
    }
    return false;
}