// FUNC_NAME: ResourceManager::findResourceIndex
// Function address: 0x005cc170
// This function looks up a resource index by name, using a hash.
// It first checks a cached hash; if that fails, it hashes a default string and searches a global table.
// The function signature is ambiguous; likely takes a resource name string (in ECX or EAX) and returns an index.

int ResourceManager::findResourceIndex(void) {
    int cachedHash;
    int hash;
    int i;
    unsigned int idx;
    int *hashArray;
    void *vtable;

    // Try to get a cached hash for the resource (maybe from this?)
    cachedHash = FUN_005cc120();
    if (cachedHash != -1) {
        // If cached hash exists, hash the corresponding string from a table of known resources
        // PTR_s_magnesium_mvb_std12b_00f1763c is a table of string pointers
        hash = FUN_004dafd0((&PTR_s_magnesium_mvb_std12b_00f1763c)[cachedHash]);
        return hash;
    }

    // No cached hash: initialize something (maybe the resource manager)
    FUN_004d3bc0(in_EAX); // in_EAX likely is a parameter (the resource name string?)
    // Set up a global table reference (maybe the string table)
    FUN_004d4c00(&DAT_00e337ec, &DAT_00e3ed40);

    // Determine the string to hash:
    // If this pointer (local_18) is non-null, use it as the string; otherwise use a default string
    void *resourceName = local_18;
    if (resourceName == 0) {
        resourceName = &DAT_0120546e; // Default resource name string (e.g., "magnesium_mvb_std12b")
    }

    // Hash the resource name
    hash = FUN_004dafd0(resourceName);

    // Search the global hash table (array of ints) for a matching hash
    // The global object at DAT_0122349c is likely a hash table manager
    // +0x10: pointer to array of hash values (ints)
    // +0x14: number of entries in the array
    idx = 0;
    i = 0;
    if (*(int *)(DAT_0122349c + 0x14) != 0) {
        hashArray = *(int **)(DAT_0122349c + 0x10);
        do {
            i = hash; // store current hash for comparison? Actually i is overwritten; might be a bug or compiler optimization
            if (*hashArray == hash) {
                goto found;
            }
            idx++;
            hashArray++;
        } while (idx < *(unsigned int *)(DAT_0122349c + 0x14));
        i = 0; // not found
    }
found:
    // If our resource name string was dynamically allocated, call its destructor (vtable call)
    if (local_18 != 0) {
        // local_c is likely a function pointer from the vtable (e.g., destructor)
        (*local_c)(local_18);
    }

    return i; // return the index found (0 if not found)
}