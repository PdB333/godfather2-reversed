// FUNC_NAME: BaseManager::BaseManager
// Constructor for a manager class. Initializes base, vtable, and fields.
// Address: 0x007c2f90
// Callees: baseConstructor(0x007ab5e0), getGlobalObject1(0x007ab150),
//          getGlobalInt(0x007ab130), debugFunction(0x0045f2a0),
//          deallocatePointer(0x004daf90)

// Forward declarations (stubs)
void BaseConstructor(int param2, int param3);                 // 0x007ab5e0
void* GetGlobalObject1();                                      // 0x007ab150
int   GetGlobalInt();                                          // 0x007ab130
void  DebugFunction(int arg);                                  // 0x0045f2a0
void  DeallocatePointer(int* ptr);                            // 0x004daf90

// External vtable symbol (from PTR_LAB_00d6e510)
extern void* g_vtable_BaseManager;

class BaseManager {
public:
    BaseManager(int param2, int param3);
    // ... class fields assumed to be contiguous ints.
    // Offsets noted in comments.
};

BaseManager::BaseManager(int param2, int param3) {
    // Base class initialization
    BaseConstructor(param2, param3);

    // Set vtable
    *reinterpret_cast<void**>(this) = &g_vtable_BaseManager;

    // Field at +0x7C (int*) – pointer to be freed later
    int* pField7C = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x7C);
    *pField7C = 0;

    // Fields at +0x80, +0x84
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x80) = 0;
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x84) = 0;

    // Fetch global object and call its vfunc(1)
    void* pObj1 = GetGlobalObject1();
    void (*vfunc1)(void*, int) = *reinterpret_cast<void (**)(void*, int)>(pObj1);
    vfunc1(pObj1, 1);

    // Fetch global integer and copy value at offset +4 into field at +0x74
    int globalVal = GetGlobalInt();
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x74) =
        *reinterpret_cast<int*>(globalVal + 4);

    // Fetch another global object (via GetGlobalInt) and call its vfunc(0x3F)
    void* pObj2 = reinterpret_cast<void*>(GetGlobalInt());
    void (*vfunc2)(void*, int) = *reinterpret_cast<void (**)(void*, int)>(pObj2);
    vfunc2(pObj2, 0x3F);

    // Debug call
    DebugFunction(0);

    // Field at +0x78
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x78) = 0;

    // Field at +0x58 is a pointer. Access its target at +0x249c and set a flag.
    int* ptrAt58 = *reinterpret_cast<int**>(reinterpret_cast<char*>(this) + 0x58);
    *reinterpret_cast<int*>(reinterpret_cast<char*>(ptrAt58) + 0x249c) |= 0x40000000;

    // Field at +0x84 set again (redundant, but present)
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x84) = 0;

    // If field at +0x7C is non-zero, deallocate it and clear
    if (*pField7C != 0) {
        DeallocatePointer(pField7C);
        *pField7C = 0;
    }
}