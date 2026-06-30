// FUNC_NAME: sha256_process
// Address: 0x00659640
// Role: SHA-256 hash update function (libtomcrypt)
// Processes input data in 64-byte blocks, maintaining internal state
// Returns 0 on success, 0x10 (CRYPT_INVALID_ARG) on error

int sha256_process(uint *md, void *buf, uint len)
{
    uint uVar1;
    int iVar2;
    uint _Size;
    char *pcVar3;
    
    // Argument validation
    if (md == (uint *)0x0) {
        pcVar3 = "_ARGCHK '%s' failure on line %d of file %s\n";
        iVar2 = FUN_00b995f7("_ARGCHK '%s' failure on line %d of file %s\n", "md != NULL", 0xc5,
                             "..\\src\\libtomcrypt\\sha256.c");
        _fprintf((FILE *)(iVar2 + 0x40), pcVar3);
    }
    if (buf == (void *)0x0) {
        pcVar3 = "_ARGCHK '%s' failure on line %d of file %s\n";
        iVar2 = FUN_00b995f7("_ARGCHK '%s' failure on line %d of file %s\n", "buf != NULL", 0xc5,
                             "..\\src\\libtomcrypt\\sha256.c");
        _fprintf((FILE *)(iVar2 + 0x40), pcVar3);
    }
    
    // Check if state is valid (curlen < 0x41 = 65, meaning not finalized)
    if (md[10] < 0x41) {
        if (len != 0) {
            do {
                uVar1 = md[10]; // current length in buffer
                if ((uVar1 == 0) && (0x3f < len)) {
                    // Buffer empty and we have at least 64 bytes - process directly
                    FUN_00658fe0(md, buf); // compress block
                    uVar1 = *md;
                    *md = *md + 0x200; // update bit count low
                    md[1] = md[1] + (uint)(0xfffffdff < uVar1); // update bit count high
                    buf = (void *)((int)buf + 0x40);
                    len = len - 0x40;
                }
                else {
                    // Copy data into buffer
                    _Size = 0x40 - uVar1;
                    if (len < 0x40 - uVar1) {
                        _Size = len;
                    }
                    _memcpy((void *)((int)md + uVar1 + 0x2c), buf, _Size); // copy to md->buf
                    md[10] = md[10] + _Size; // update curlen
                    buf = (void *)((int)buf + _Size);
                    len = len - _Size;
                    if (md[10] == 0x40) {
                        // Buffer full - compress it
                        FUN_00658fe0(md, md + 0xb); // compress from buffer
                        uVar1 = *md;
                        *md = *md + 0x200;
                        md[10] = 0; // reset curlen
                        md[1] = md[1] + (uint)(0xfffffdff < uVar1);
                    }
                }
            } while (len != 0);
        }
        return 0; // CRYPT_OK
    }
    return 0x10; // CRYPT_INVALID_ARG (state already finalized)
}