// FUNC_NAME: Apt::createObject
// Address: 0x0059ee00
// Role: Allocates and initializes an Apt object (8-byte header with flags and type).
// Note: Uses debug assertion macros from Apt.cpp line 0x245 (581).

void Apt::createObject(void* aptManager, uint typeId)
{
    // Debug assertion: Apt must be initialized
    if (g_bAptInitialized == 0)
    {
        const char* condition = "bAptIsInitialized";
        const char* file = "..\\source\\Apt\\Apt.cpp";
        int line = 0x245; // 581
        int severity = 2;
        char* g_bDontBreak = &DAT_01128f43; // global break flag

        if (*g_bDontBreak != '\0')
        {
            int* piVar1 = *(int**)(*(int**)(__readfsdword(0x2c) + 0x30)); // TLS or debug data
            uint uVar3 = 1;
            if (piVar1 != nullptr)
            {
                uVar3 = (**(code**)(*piVar1 + 8))(&condition, "bAptIsInitialized");
            }
            if ((uVar3 & 2) != 0)
            {
                *g_bDontBreak = 0;
            }
            if ((piVar1 != nullptr) || (severity != 4))
            {
                if ((uVar3 & 1) != 0 || (severity == 0) || (severity == 1))
                {
                    // Trigger debug breakpoint
                    (*(code*)swi(3))();
                    return;
                }
            }
        }
    }

    // Allocate 8-byte Apt object header
    uint* pHeader = (uint*)(*g_pAptAllocator)(8, 0); // custom allocator
    if (pHeader != nullptr)
    {
        // Initialize flags: set type bits (low 15 bits) to 7, clear certain bits, set high bit (0x8000)
        *pHeader = (*pHeader & 0xFFFF8007) | 7;
        *(uint16*)((uint)pHeader + 2) = 0; // clear half of flags?
        *pHeader |= 0x8000; // set bit 15 (refcount or persistent flag)
        pHeader[1] = typeId; // store type ID
    }
    else
    {
        pHeader = nullptr;
    }

    // If the object is not the global sentinel, perform type-specific initialization
    if (pHeader != g_pAptObjectList)
    {
        uint type = *pHeader & 0x7FFF;
        if (type != 0x19 && ((~(*pHeader >> 0xF) & 1) != 0 || 
            (type != 0xB && type != 0x18 && type != 0x17)))
        {
            AptObject::init(pHeader); // internal init (insert into list, etc.)
        }
    }

    // Register object with the system
    uint v1 = 1, v2 = 1;
    uint uVar5 = FUN_0059e2f0(0, aptManager, pHeader, 1, 1); // likely register or attach
    FUN_005ad5b0(uVar5, 0, aptManager, pHeader, v1, v2); // likely additional setup

    // Dispatch via vtable based on type
    (*(code*)(DAT_0103aee0 + (*pHeader & 0x7FFF) * 4))(pHeader);
    return;
}