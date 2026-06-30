// FUNC_NAME: getGlobalStateFlag
// Returns a global state flag byte at 0x0120587f.
// Used by various game systems to check a condition.
// Referenced by many functions in the 0x0069xxxx and 0x009xxxxx ranges.
byte getGlobalStateFlag(void)
{
    // DAT_0120587f is a single-byte global variable likely set elsewhere.
    return DAT_0120587f;
}