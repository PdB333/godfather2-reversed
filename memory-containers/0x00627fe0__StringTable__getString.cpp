// FUNC_NAME: StringTable::getString
// Function address: 0x00627fe0
// Role: Retrieves a localized string by index from a string table stored in memory.
// The object (this) has two pointers: m_pStart (start address of entries) at +0x8, m_pEnd (end address) at +0xC? Actually, the array grows upward from m_pEnd? We infer:
//   struct Entry { int32_t count; char* str; }; // size 8
//   Entries are stored contiguously from m_pBase (low address) to m_pLimit (high address).
//   m_pBase = *(int*)(this+0xC) - 8? Actually, the computation suggests base = *(int*)(this+0xC) - 8 for index 1.
//   m_pLimit = *(int*)(this+0x8). Valid entries: m_pBase <= piVar2 < m_pLimit.
// When index == 0, a special fallback string is used.
// The function also supports retrieving the string length.

// Assumed helper functions (not reconstructed here):
//   char* getDefaultString();   // FUN_00625430
//   char* getStringFromEntry(Entry*); // FUN_00625a70
//   int getStringLength(const char*); // FUN_00625ae0
//   void logError(const char*);       // FUN_00627ac0

extern char* getDefaultString();                 // 0x00625430
extern char* getStringFromEntry(void* entry);    // 0x00625a70
extern int getStringLength(const char* str);     // 0x00625ae0
extern void logError(const char* msg);           // 0x00627ac0

// External string constant for error logging
extern const char* const g_errorString; // PTR_s_string_00e2a8ac

// Note: The calling convention is __thiscall. The index is passed in EAX, defaultStr in param_1, outLen in param_2.
// We represent it as: char* getString(int index, const char* defaultStr, int* outLen)
char* __thiscall StringTable::getString(int index, const char* defaultStr, int* outLen)
{
    void* entryPtr;
    char* str;
    int length;

    // Use different lookup for index < 1 (including 0 and negative)
    if (index < 1)
    {
        entryPtr = (void*)getDefaultString();
    }
    else
    {
        // Compute entry address: base = *(int*)(this + 0xC) - 8, then add index*8
        entryPtr = (void*)(*(int*)(this + 0xC) + -8 + index * 8);
        // Bounds check: must be less than limit at +0x8
        if (*(void**)(this + 0x8) <= entryPtr)
            goto fallback;
    }

    // Validate entry: first int must be positive
    if (entryPtr != nullptr && *(int*)entryPtr > 0)
    {
        str = getStringFromEntry(entryPtr);
        if (str == nullptr)
        {
            logError(g_errorString);
        }
        if (outLen == nullptr)
        {
            return str;
        }
        length = getStringLength(str);
        *outLen = length;
        return str;
    }

fallback:
    if (outLen == nullptr)
    {
        return (char*)defaultStr;
    }
    if (defaultStr != nullptr)
    {
        // Compute length of default string
        const char* p = defaultStr;
        while (*p != '\0')
            p++;
        *outLen = p - (defaultStr + 1); // Equivalent to strlen
        return (char*)defaultStr;
    }
    *outLen = 0;
    return nullptr;
}