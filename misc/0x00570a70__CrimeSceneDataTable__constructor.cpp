// FUNC_NAME: CrimeSceneDataTable::constructor
void CrimeSceneDataTable::constructor(void* thisPtr) {
    // Call base initialization (likely allocates memory or sets up base class)
    FUN_00581960();

    // Set vtable pointer to virtual function table
    *reinterpret_cast<int**>(thisPtr) = &PTR_FUN_00e3abe4;

    // Default sentinel value (likely -1 or 0xFFFFFFFF)
    int defaultValue = DAT_00e2b1a4; // global sentinel value

    // Initialize first header/special entry at offset 0x70
    *reinterpret_cast<int*>(reinterpret_cast<char*>(thisPtr) + 0x70) = 0; // +0x70
    *reinterpret_cast<short*>(reinterpret_cast<char*>(thisPtr) + 0x74) = 0xffff; // +0x74
    *reinterpret_cast<short*>(reinterpret_cast<char*>(thisPtr) + 0x76) = 0xffff; // +0x76

    // Initialize main data array: each group of 4 ints (3 zeros, 1 defaultValue)
    // Offsets are given as int* indices (each int = 4 bytes)
    // Group starting at offset 0x80
    reinterpret_cast<int*>(thisPtr)[0x20] = 0;
    reinterpret_cast<int*>(thisPtr)[0x21] = 0;
    reinterpret_cast<int*>(thisPtr)[0x22] = 0;
    reinterpret_cast<int*>(thisPtr)[0x23] = defaultValue;

    // Group starting at offset 0x90
    reinterpret_cast<int*>(thisPtr)[0x24] = 0;
    reinterpret_cast<int*>(thisPtr)[0x25] = 0;
    reinterpret_cast<int*>(thisPtr)[0x26] = 0;
    reinterpret_cast<int*>(thisPtr)[0x27] = defaultValue;

    // Group at offset 0x100
    reinterpret_cast<int*>(thisPtr)[0x40] = 0;
    reinterpret_cast<int*>(thisPtr)[0x43] = 0; // note: indices not contiguous, but follows pattern
    reinterpret_cast<int*>(thisPtr)[0x4c] = defaultValue;
    reinterpret_cast<int*>(thisPtr)[0x54] = 0;

    // Group at offset 0x150? Actually indices 0x55,0x56,0x57
    reinterpret_cast<int*>(thisPtr)[0x56] = 0;
    reinterpret_cast<int*>(thisPtr)[0x55] = 0;
    reinterpret_cast<int*>(thisPtr)[0x57] = defaultValue;

    // Next group at 0x58-0x5b
    reinterpret_cast<int*>(thisPtr)[0x58] = 0;
    reinterpret_cast<int*>(thisPtr)[0x5a] = 0;
    reinterpret_cast<int*>(thisPtr)[0x59] = 0;
    reinterpret_cast<int*>(thisPtr)[0x5b] = defaultValue;

    // Group at 0x60-0x63
    reinterpret_cast<int*>(thisPtr)[0x62] = 0;
    reinterpret_cast<int*>(thisPtr)[0x61] = 0;
    reinterpret_cast<int*>(thisPtr)[0x60] = 0;
    reinterpret_cast<int*>(thisPtr)[0x63] = defaultValue;

    // Group at 0x64-0x67
    reinterpret_cast<int*>(thisPtr)[0x66] = 0;
    reinterpret_cast<int*>(thisPtr)[0x65] = 0;
    reinterpret_cast<int*>(thisPtr)[0x64] = 0;
    reinterpret_cast<int*>(thisPtr)[0x67] = defaultValue;

    // Group at 0x6c-0x6f
    reinterpret_cast<int*>(thisPtr)[0x6e] = 0;
    reinterpret_cast<int*>(thisPtr)[0x6d] = 0;
    reinterpret_cast<int*>(thisPtr)[0x6c] = 0;
    reinterpret_cast<int*>(thisPtr)[0x6f] = defaultValue;

    // Group at 0x70-0x73
    reinterpret_cast<int*>(thisPtr)[0x72] = 0;
    reinterpret_cast<int*>(thisPtr)[0x71] = 0;
    reinterpret_cast<int*>(thisPtr)[0x70] = 0;
    reinterpret_cast<int*>(thisPtr)[0x73] = defaultValue;

    // Group at 0x78-0x7b
    reinterpret_cast<int*>(thisPtr)[0x7a] = 0;
    reinterpret_cast<int*>(thisPtr)[0x79] = 0;
    reinterpret_cast<int*>(thisPtr)[0x78] = 0;
    reinterpret_cast<int*>(thisPtr)[0x7b] = defaultValue;

    // Group at 0x7c-0x7f
    reinterpret_cast<int*>(thisPtr)[0x7e] = 0;
    reinterpret_cast<int*>(thisPtr)[0x7d] = 0;
    reinterpret_cast<int*>(thisPtr)[0x7c] = 0;
    reinterpret_cast<int*>(thisPtr)[0x7f] = defaultValue;

    // Group at 0x84-0x87
    reinterpret_cast<int*>(thisPtr)[0x86] = 0;
    reinterpret_cast<int*>(thisPtr)[0x85] = 0;
    reinterpret_cast<int*>(thisPtr)[0x84] = 0;
    reinterpret_cast<int*>(thisPtr)[0x87] = defaultValue;

    // Group at 0x88-0x8b
    reinterpret_cast<int*>(thisPtr)[0x8a] = 0;
    reinterpret_cast<int*>(thisPtr)[0x89] = 0;
    reinterpret_cast<int*>(thisPtr)[0x88] = 0;
    reinterpret_cast<int*>(thisPtr)[0x8b] = defaultValue;

    // Group at 0x90-0x93
    reinterpret_cast<int*>(thisPtr)[0x92] = 0;
    reinterpret_cast<int*>(thisPtr)[0x91] = 0;
    reinterpret_cast<int*>(thisPtr)[0x90] = 0;
    reinterpret_cast<int*>(thisPtr)[0x93] = defaultValue;

    // Group at 0x94-0x97
    reinterpret_cast<int*>(thisPtr)[0x96] = 0;
    reinterpret_cast<int*>(thisPtr)[0x95] = 0;
    reinterpret_cast<int*>(thisPtr)[0x94] = 0;
    reinterpret_cast<int*>(thisPtr)[0x97] = defaultValue;

    // Group at 0x9c-0x9f
    reinterpret_cast<int*>(thisPtr)[0x9e] = 0;
    reinterpret_cast<int*>(thisPtr)[0x9d] = 0;
    reinterpret_cast<int*>(thisPtr)[0x9c] = 0;
    reinterpret_cast<int*>(thisPtr)[0x9f] = defaultValue;

    // Group at 0xa0-0xa3
    reinterpret_cast<int*>(thisPtr)[0xa2] = 0;
    reinterpret_cast<int*>(thisPtr)[0xa1] = 0;
    reinterpret_cast<int*>(thisPtr)[0xa0] = 0;
    reinterpret_cast<int*>(thisPtr)[0xa3] = defaultValue;

    // Group at 0xa8-0xab
    reinterpret_cast<int*>(thisPtr)[0xaa] = 0;
    reinterpret_cast<int*>(thisPtr)[0xa9] = 0;
    reinterpret_cast<int*>(thisPtr)[0xa8] = 0;
    reinterpret_cast<int*>(thisPtr)[0xab] = defaultValue;

    // Group at 0xac-0xaf
    reinterpret_cast<int*>(thisPtr)[0xae] = 0;
    reinterpret_cast<int*>(thisPtr)[0xad] = 0;
    reinterpret_cast<int*>(thisPtr)[0xac] = 0;
    reinterpret_cast<int*>(thisPtr)[0xaf] = defaultValue;
}