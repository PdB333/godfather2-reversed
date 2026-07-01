// FUNC_NAME: hashLookupFunction
// Returns a global value based on a hash code.
// Used to look up data (e.g., pointer or integer) for known string hashes.
// If the hash matches one of the first two constants, returns DAT_0112fdd4.
// If it matches the other two, returns DAT_0112fdd8.
// Otherwise returns 0.
undefined4 hashLookupFunction(int hash)
{
    if ((hash == 0x369ac561) || (hash == 0xA0D329D6)) { // -0x5f2cd62a unsigned
        return DAT_0112fdd4;
    }
    if ((hash != 0x10e5319e) && (hash != 0xA5976EB2)) { // -0x5a68a14e unsigned
        return 0;
    }
    return DAT_0112fdd8;
}