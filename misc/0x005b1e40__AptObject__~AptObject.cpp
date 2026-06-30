// FUNC_NAME: AptObject::~AptObject

// AptObject is a base class in EA's APT memory management system.
// This destructor validates the internal header and frees a fixed-size block (0x70 bytes).
// Source: apt\_Apt.h (line 0x24e)
void __thiscall AptObject::~AptObject(void)
{
    int* pHead;         // this->m_pHead (offset +0x00)
    int* pAssertList;   // TLS assertion context
    int result;
    code* pcBreak;
    uint assertFlags;
    char* assertMsg;
    char* sourceFile;
    int lineNum;
    int severity;
    char* pAllowAssert;

    pHead = this->m_pHead;

    // Check if the header is in a defined state (bit 15 of *pHead)
    if (((*(uint*)pHead >> 0xF) & 1) == 0)
        goto cleanup;

    // Assertion fired: header is undefined
    assertMsg = "pHead->isUndefined()";
    sourceFile = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_Apt.h";
    lineNum = 0x24e;
    severity = 2;
    pAllowAssert = &DAT_01129009; // global boolean to enable/disable assertions

    if (*pAllowAssert == '\0')
        goto cleanup;

    // Retrieve assertion processing from TLS (FS:[0x2C])
    pAssertList = *(int**)(*(int*)(__readfsdword(0x2C) + 0x30) + 0x30);
    assertFlags = 1;
    if (pAssertList != (int*)0x0)
    {
        assertFlags = (**(code**)(*pAssertList + 8))(&assertMsg, "pHead->isUndefined()");
        if (pAllowAssert != (char*)0x0)
        {
            if ((assertFlags & 2) != 0)
                *pAllowAssert = 0;
        }
    }

    if ((pAssertList != (int*)0x0) || (severity != 4))
    {
        if (((assertFlags & 1) != 0) || (severity == 0) || (severity == 1))
        {
            // Debug break and return
            pcBreak = (code*)__debugbreak();
            (*pcBreak)();
            return;
        }
    }

cleanup:
    result = this->m_pHead;
    if (result != 0)
    {
        // Run pre-deallocation cleanup (likely virtual destructor call)
        FUN_005aa2a0();

        // Free memory block via APT fixed-size allocator (0x70 bytes)
        (*DAT_0119caf8)(result, 0x70);
    }
    return;
}