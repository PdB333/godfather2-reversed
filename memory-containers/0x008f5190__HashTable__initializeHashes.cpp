// FUNC_NAME: HashTable::initializeHashes
// Function address: 0x008f5190
// Role: Initializes a hash table with a fixed set of 27 hash values, called once per instance.
// Checks bit 1 at offset +0x10 to avoid reinitialization.

void __fastcall HashTable::initializeHashes(int this)
{
    // Check if already initialized (bit 1 at offset +0x10)
    if (((*(uint32_t *)(this + 0x10) >> 1) & 1) == 0)
    {
        // Register each hash at its slot index (0..26)
        addHash(this, 0, 0xceca2ffd);
        addHash(this, 1, 0x21db6f49);
        addHash(this, 2, 0xd9126947);
        addHash(this, 3, 0xf6fedafe);
        addHash(this, 4, 0xc1683e52);
        addHash(this, 5, 0x9df0dde0);
        addHash(this, 6, 0x946e3ed0);
        addHash(this, 7, 0xf8c057b8);
        addHash(this, 8, 0xe32b0a31);
        addHash(this, 9, 0xceca2ffd);          // duplicate hash? intentional or data error
        addHash(this, 10, 0x3bca5d1a);
        addHash(this, 11, 0xe3245a9f);
        addHash(this, 12, 0x3763e1d1);
        addHash(this, 13, 0xc79e3a56);
        addHash(this, 14, 0x286de749);
        addHash(this, 15, 0x5a67d071);
        addHash(this, 16, 0xf2c1a188);
        addHash(this, 17, 0xc64a3028);
        addHash(this, 18, 0x82a3550d);
        addHash(this, 19, 0x1629c93f);
        addHash(this, 20, 0xf5ee953a);
        addHash(this, 21, 0xd0ab7ef6);
        addHash(this, 22, 0xec16a395);
        addHash(this, 23, 0xbfa57805);
        addHash(this, 24, 0xc467ec09);
        addHash(this, 25, 0x5710ced7);
        addHash(this, 26, 0x573edd47);

        // Mark as initialized by setting bit 1 at offset +0x10
        *(uint32_t *)(this + 0x10) |= 2;
    }
}