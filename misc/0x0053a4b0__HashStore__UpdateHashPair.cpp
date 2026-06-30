// FUNC_NAME: HashStore::UpdateHashPair
void __fastcall HashStore::UpdateHashPair(byte (*hashPair)[16]) // in_EAX: pointer to two 16-byte arrays (32 bytes total)
{
    static byte s_hashLo[16];   // _DAT_0121b930
    static byte s_hashHi[16];   // _DAT_0121b940

    // Write null or copy the 32-byte block
    if (hashPair == nullptr) {
        memset(s_hashLo, 0, sizeof(s_hashLo));
        memset(s_hashHi, 0, sizeof(s_hashHi));
    } else {
        memcpy(s_hashLo, hashPair[0], sizeof(s_hashLo));
        memcpy(s_hashHi, hashPair[1], sizeof(s_hashHi));
    }

    // Conditionally register the first half hash with the active hash system
    // DAT_012058e8: pointer to current hash system structure
    // DAT_0121b740: default hash system template
    // DAT_0121b754 = field at offset 0x14 in the template
    // DAT_0121bbcc = expected ID for the registration
    // DAT_0121bb8c = additional data for registration
    if (g_pActiveHashSystem == &g_hashSystemTemplate && g_hashSystemTemplate.field_0x14 == g_expectedHashId) {
        // FUN_0060ab00: registers 8 bytes from the low part of the hash into the system
        RegisterHashForSystem(g_expectedHashId, g_hashSystemData, s_hashLo, 8);
    }
}