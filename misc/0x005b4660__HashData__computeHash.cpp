// FUNC_NAME: HashData::computeHash
// Function address: 0x005b4660
// Role: Computes a hash of a small data structure using a lookup table.
// The data structure is pointed to by 'this' (ESI). The hash is accumulated
// from bytes at offsets +1, +5, +7 depending on the control value in EAX.
// The lookup table is at 0x00e2b638 (hashTable).

int __thiscall HashData::computeHash(int control) {
    int hash = control; // initial hash value passed in EAX
    unsigned char* data = (unsigned char*)this;

    // The switch on the control value determines which bytes are hashed.
    // Fall-through cases process additional bytes.
    switch (hash) {
        default:
            // Include byte at offset +7
            hash += hashTable[data[7]]; // +0x07
        case 6:
        case 7:
            // Include byte at offset +5
            hash += hashTable[data[5]]; // +0x05
        case 2:
        case 3:
        case 4:
        case 5:
            // Always include byte at offset +1
            hash += hashTable[data[1]]; // +0x01
            return hash;
    }
}