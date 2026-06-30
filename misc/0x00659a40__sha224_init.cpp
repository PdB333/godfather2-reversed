// FUNC_NAME: sha224_init
// Address: 0x00659a40
// Purpose: Initializes a SHA-224 hash context with standard initial hash values.
// The structure is assumed to be a libtomcrypt hash_state with fields for count (2 words) and state (8 words).
// This matches the SHA-224 algorithm defined in RFC 3874.
void sha224_init(sha224_state *md) {
    // Debug assertion: if md is NULL, print error and file/line info (libtomcrypt _ARGCHK macro)
    if (md == nullptr) {
        int ret = debug_printf_format("_ARGCHK '%s' failure on line %d of file %s\n",
                                      "md != NULL", 0x11,
                                      "c:\\packages001_pc\\tnl\\dev\\src\\libtomcrypt\\sha224.c");
        // ret likely contains a FILE* offset; use it for fprintf
        _fprintf(reinterpret_cast<FILE*>(static_cast<uintptr_t>(static_cast<int>(ret) + 0x40)),
                 "_ARGCHK '%s' failure on line %d of file %s\n");
    }
    // Initialize bit count to 0 (two 32-bit words)
    md->count[0] = 0;
    md->count[1] = 0;
    // Initialize state with SHA-224 initial hash values
    md->state[0] = 0xc1059ed8;
    md->state[1] = 0x367cd507;
    md->state[2] = 0x3070dd17;
    md->state[3] = 0xf70e5939;
    md->state[4] = 0xffc00b31;
    md->state[5] = 0x68581511;
    md->state[6] = 0x64f98fa7;
    md->state[7] = 0xbefa4fa4;
    // Additional field (likely the length of processed data modulo block?) set to 0
    md->curlen = 0;
}