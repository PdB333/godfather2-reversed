// Xbox PDB: AptObject::objectMemberLookup
// FUNC_NAME: checkRegisterClassName
// Function at 0x005bbd50 compares an input string against "registerClass" and returns a global flag if matched.
// Returns either 0 (no match) or DAT_0119cbac if exactly equal (including null terminator).

extern unsigned int DAT_0119cbac; // Global flag associated with registered class

unsigned int checkRegisterClassName(const char* className)
{
    bool isMatch = true;
    int i = 14; // 13 chars + null terminator
    const char* expected = "registerClass";
    do {
        if (i == 0) break;
        i--;
        isMatch = (*className == *expected);
        className++;
        expected++;
    } while (isMatch);

    // If isMatch remains true throughout the loop, the strings are identical.
    // Return the global flag if match, otherwise 0.
    return (!isMatch - 1) & DAT_0119cbac;
}