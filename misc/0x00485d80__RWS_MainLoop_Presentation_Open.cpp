// Xbox PDB: RWS::MainLoop::Presentation::Open
// FUNC_NAME: ApplicationEngine::initializeEngine

#include <windows.h> // for HANDLE, DWORD_PTR, SetThreadAffinityMask, etc.

// Globals (defined elsewhere)
extern int* DAT_0120542c;          // +0x54  (vtable pointer?)
extern int DAT_01205424;          // +0x54  (some config value)
extern int _DAT_01205420;         // global uint
extern char DAT_01206870[];       // array of structs, each 0x68 bytes (0x1a * 4?)
extern int DAT_012053cb;          // bool flag
extern int DAT_010c3693;          // bool flag
extern int DAT_0110a620;          // CPU mask for thread affinity
extern int DAT_01205428;          // some global
extern int DAT_00e2e294;          // some resource handle

// Forward declarations of called functions
void FUN_004858f0();                           // engine pre-init
void FUN_0040ca80(void* pEventStruct);          // process event struct
void* FUN_009c8e50(int size);                  // memory allocator
void FUN_004cfb60(void* obj, void* params);     // construct object
void FUN_004861e0();                           // construct object #2
void FUN_00ab5450();                            // input system init
void FUN_00ab5070(int unk1, int unk2, const char* name); // presentation event start
void FUN_00ab50c0(char* buffer);                // presentation event end?
void FUN_00ab51e0(int unk);                     // finalize presentation
void* FUN_00485a00(int arg);                    // creates something (thread/callback)
int FUN_00ab5470();                             // get some value
void FUN_00ab7410(void* callback, void* param, char* buffer, int unk); // register callback
void FUN_00ab5130(int* handle);                 // release resource
void FUN_00ab4ac0(int cpuMask);                 // set thread affinity for current thread?
void FUN_00ab4a50(int global);                 // final init step

// Internal function equivalent to LAB_00485ae0
static void LAB_00485ae0(int* param1, int param2); // callback for thread/async

void ApplicationEngine::initializeEngine(int* pConfig) {
    // pConfig is a pointer to an array of ints; offsets are DWORD indices
    FUN_004858f0();

    int local_24 = pConfig[2];
    int local_28 = pConfig[0];
    int local_1c = pConfig[4];
    int local_14 = pConfig[3];
    int local_80 = pConfig[5];
    int local_78 = pConfig[6];
    int local_7c = pConfig[7];
    int local_74 = pConfig[8];

    // Setup some structs on stack
    struct StackStruct {
        int field_0;  // local_28
        int field_4;  // 0x40
        int field_8;  // local_24
        int field_C;  // local_1c
        int field_10; // local_14
        int field_14; // local_80
        int field_18; // 0x40
        int field_1C; // local_78
        int field_20; // local_7c
        int field_24; // local_74
    } stackData;

    stackData.field_0 = local_28;
    stackData.field_4 = 0x40;   // possible size/flag
    stackData.field_8 = local_24;
    stackData.field_C = local_1c;
    stackData.field_10 = local_14;
    stackData.field_14 = local_80;
    stackData.field_18 = 0x40;
    stackData.field_1C = local_78;
    stackData.field_20 = local_7c;
    stackData.field_24 = local_74;

    int iterations = 2; // local_84
    void* pGlobalArray = &DAT_01206870; // array of 0x68 byte structs? (0x1a * 4 = 0x68)
    do {
        FUN_0040ca80(pGlobalArray);
        pGlobalArray = (char*)pGlobalArray + 0x68; // 0x1a * 4 = 0x68? Actually 0x1a DWORDs = 0x68 bytes
        iterations--;
    } while (iterations != 0);

    // Allocate and construct objects
    int* obj1 = (int*)FUN_009c8e50(0xC); // size 12 bytes
    if (obj1) {
        FUN_004cfb60(obj1, &stackData);
    }

    int* obj2 = (int*)FUN_009c8e50(0x1C); // size 28 bytes
    if (obj2) {
        FUN_004861e0();
    }

    FUN_00ab5450(); // input init

    // Prepare some globals
    int local_68 = DAT_01205424;
    DAT_0120542c = (int*)pConfig[1]; // set global vtable pointer
    int local_64 = _DAT_01205420;
    char* local_5c = "Presentation";

    // Call virtual function on global instance (vtable offset +8)
    (**(code**)(*DAT_0120542c + 8))();

    if (pConfig[4] != 0) {
        // Presentation mode: enter/exit events
        FUN_00ab5070(0, 1, "PresEnter");
        char presBuffer1[24]; // auStack_58
        FUN_00ab50c0(presBuffer1);
        FUN_00ab5070(0, 1, "PresExit");
        char presBuffer2[24]; // auStack_40
        FUN_00ab50c0(presBuffer2);
        FUN_00ab51e0(1);

        int* piVar3 = (int*)FUN_00485a00(pConfig[9]); // likely creates a thread/callback context
        int uVar4 = FUN_00ab5470(); // some return value
        char local_70[8]; // used as buffer for callback registration
        FUN_00ab7410(&LAB_00485ae0, piVar3, local_70, uVar4);
        FUN_00ab5130(&DAT_00e2e294); // release resource

        int* refCountPtr = piVar3 + 2; // +8 bytes (2 ints)
        (*refCountPtr)--;
        if (*refCountPtr == 0) {
            if (*(int*)*piVar3 != 0) { // pointer to vtable
                (**(code**)(*(int*)*piVar3 + 0xC))(); // destructor?
            }
            int* vtable2 = (int*)piVar3[3]; // +12 bytes
            (**(code**)(*vtable2 + 4))(piVar3, 0); // call something
            (**(code**)(*vtable2 + 0xC))(); // destructor?
        }

        DAT_012053cb = 1;
        DAT_010c3693 = 1;
        FUN_00ab4ac0(DAT_0110a620); // set thread affinity? or record CPU mask

        DWORD_PTR dwThreadAffinityMask = 1 << (DAT_0110a620 & 0x1F);
        HANDLE hThread = GetCurrentThread();
        SetThreadAffinityMask(hThread, dwThreadAffinityMask);

        FUN_00ab4a50(DAT_01205428);
    }
    return;
}