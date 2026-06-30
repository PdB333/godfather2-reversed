// FUNC_NAME: VariableDictionary::VariableDictionary
class VariableDictionary {
public:
    // Vtable at offset 0, but we use a base pointer (likely inherited)
    void** m_vtable; // +0x00
    int m_flags; // +0x04
    void* m_staticDataA; // +0x08
    void* m_staticDataB; // +0x0C
    int m_dictionaryId; // +0x10
    Allocator* m_pAllocator; // +0x14
    void* m_pKeyBuffer; // +0x18
    void* m_pKeyIndex; // +0x1C (result of constructArray)
    int m_maxEntries; // +0x20
    VariableEntry* m_pEntries; // +0x24
    int m_entryCount; // +0x28
};

// Global pointer to the singleton dictionary instance
VariableDictionary* g_pVarDict = nullptr; // DAT_01223428

// Global hash table for class‑based lookup (entries of 12 bytes: key, value, retaddr)
extern int* g_pClassRegistry; // DAT_0122341c

VariableDictionary* __thiscall VariableDictionary::VariableDictionary(
    Allocator* pAlloc,          // param_2
    int keyBufferSize,          // param_4 (size in bytes, multiple of 8)
    int maxEntries,             // param_3
    int unused1,                // param_5 (unused)
    int dictionaryId             // param_6
) {
    this->m_flags = 0;
    this->m_staticDataA = &PTR_LAB_00e30fe0;
    this->m_staticDataB = &PTR_LAB_00e31124;
    this->m_dictionaryId = dictionaryId;
    this->m_maxEntries = maxEntries;

    // Store global singleton reference
    g_pVarDict = this;

    // Set vtable pointer (base class? then later overwritten)
    this->m_vtable = &PTR_FUN_00e31104;
    this->m_staticDataA = &PTR_LAB_00e31110; // reassign
    this->m_staticDataB = &PTR_LAB_00e31120;

    this->m_pAllocator = pAlloc;
    this->m_entryCount = 0;

    // Call allocator’s init method (offset 8)
    pAlloc->init();

    // Register debug name
    FUN_0049c6e0("VariableDictionary", 1);

    // Allocate key buffer (size = keyBufferSize * 8)
    void* keyBuf = pAlloc->allocate(keyBufferSize * 8);
    this->m_pKeyBuffer = keyBuf;

    // Allocate a temporary 0x20‑byte buffer for index construction
    void* tempBuf = pAlloc->allocate(0x20);
    if (tempBuf != nullptr) {
        // Construct an indexed array inside m_pKeyBuffer (8‑byte elements, 4‑byte alignment)
        this->m_pKeyIndex = FUN_004abe90(this->m_pKeyBuffer, keyBufferSize * 8, 8, 4);
    } else {
        this->m_pKeyIndex = 0;
    }

    // Allocate and zero‑fill the variable entry array
    if (this->m_maxEntries > 0) {
        VariableEntry* entries = (VariableEntry*)pAlloc->allocate(this->m_maxEntries * 0x14);
        this->m_pEntries = entries;
        for (int i = 0; i < this->m_maxEntries; i++) {
            // Zero out each 0x14‑byte entry
            memset(&entries[i], 0, 0x14);
        }
    } else {
        this->m_pEntries = nullptr;
    }

    // Insert a reference to this dictionary into the global class registry
    // The key is 0xE60B027D (hash for "VariableDictionary")
    const uint registryKey = 0xE60B027D;
    int* regBase = g_pClassRegistry;
    int regCount = *(int*)(regBase + 0x10); // +0x10
    int regCapacity = *(int*)(regBase + 0x14); // +0x14
    int* entryPtr = (int*)(*(int*)(regBase + 0x0C)); // base of entries (12 bytes each)
    int foundIndex = 0;

    for (uint i = 0; i < regCount; i++) {
        int* currentEntry = entryPtr + i * 3; // 3 ints per entry
        if (currentEntry[0] == registryKey) {
            foundIndex = currentEntry[1]; // value found
            break;
        }
    }

    if (foundIndex == 0) {
        // Insert new entry
        if (regCount >= regCapacity) {
            // Double capacity
            int newCap = (regCapacity == 0) ? 1 : regCapacity * 2;
            FUN_00463b90(newCap);
            // Re-read pointers after resize
            regBase = g_pClassRegistry;
            regCount = *(int*)(regBase + 0x10);
            entryPtr = (int*)(*(int*)(regBase + 0x0C));
        }
        int insertIndex = regCount;
        *(int*)(regBase + 0x10) = regCount + 1;
        int* newEntry = &entryPtr[insertIndex * 3];
        newEntry[0] = registryKey;
        newEntry[1] = (int)(&this->m_staticDataA); // pointer to the data block
        newEntry[2] = (int)__builtin_return_address(0); // return address for debugging
    }

    return this;
}