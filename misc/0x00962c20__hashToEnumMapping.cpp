// FUNC_NAME: hashToEnumMapping
unsigned int hashToEnumMapping(unsigned int hash) 
{
    // Mapping table for 32-bit hashes to enum values (0-4)
    if (hash < 0x45c2f637) {
        if (hash == 0x45c2f636) return 4;
        if (hash == 0) return 0;
        if (hash == 0x2efecf8d) return 1;
        if (hash == 0x3d26cff9) return 3;
    } 
    else {
        if (hash == 0x7116917a) return 2;
        if (hash == 0xdaaa5987) return 0;
    }
    return 0;
}