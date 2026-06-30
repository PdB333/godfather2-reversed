// FUNC_NAME: GameManager::initialize
// Function address: 0x005e33e0
// Role: Main game engine initialization, allocates and initializes subsystems,
//       validates global manager chain, prints status.

typedef int (*VirtualFunction)(void*, ...);

// Forward declarations for subsystem initialization functions
void initSimManager();                 // 0x005ea280
void initSomeLargeSystem();            // 0x005e42a0
void initSubsystem1750();              // 0x005e1ca0
void initSubsystemFC();                // 0x005dbf30
void initSubsystem20();                // 0x005e7180
void initSubsystem25C();               // 0x005f0120

bool validateSubsystem1();             // 0x005e4450
bool validateSubsystem2(int*);         // 0x005e1d80
bool validateSubsystem3(int*);         // 0x005dc060
bool validateSubsystem4();             // 0x005e7270
bool validateSubsystem5();             // 0x005f2da0
bool validateSubsystem6();             // 0x005f1c60

void debugPrint(char* message);        // 0x005dbc10
void* allocateMemory(unsigned int size); // 0x009c8e50 (malloc equivalent)

// Global pointers
extern int* DAT_01223510;              // Global manager vtable pointer
extern int* DAT_0122350c;              // Pointer for validation
extern int* DAT_01223508;              // Pointer for validation
extern char DAT_011a0ec0[0x30];        // Global buffer cleared during init

struct ManagedObject; // Forward declaration for param_1 (interface)

// Alloc call with alignment/flag struct
struct AllocationParams {
    int field_0;   // 2
    int field_4;   // 0x10
    int field_8;   // 0
};

typedef struct _VTable {
    VirtualFunction alloc;        // index 0 (func at offset 0)
    VirtualFunction someFunc;     // index 1 (offset 4)
    VirtualFunction initVFunc;    // index 2 (offset 8) – called initially
} VTable;

unsigned char GameManager::initialize(ManagedObject* param_1, int param_2) {
    char cVar1;
    int* iVar2;
    char* statusStr;
    unsigned char result;

    // Store the interface pointer in the object
    *(int**)(this + 4) = param_1;

    // Call virtual function at offset 8 of param_1's vtable
    ((VTable*)(*param_1))->initVFunc();

    // Allocate and initialize large subsystems
    iVar2 = (int*)allocateMemory(0x90a8);
    if (iVar2 != 0) {
        initSimManager();
    }

    // Second allocation with flag structure
    AllocationParams params;
    params.field_0 = 2;
    params.field_4 = 0x10;
    params.field_8 = 0;
    iVar2 = (int*)((VTable*)(*param_1))->alloc(0x6050, &params);
    if (iVar2 != 0) {
        initSomeLargeSystem();
    }

    // Call global manager virtual function at offset 4
    cVar1 = (char)((VTable*)(*DAT_01223510))->someFunc(param_1, param_2);

    if (cVar1 == '\0') {
        // First branch: minimal initialization, then failure
        iVar2 = (int*)allocateMemory(0x1750);
        if (iVar2 != 0) {
            initSubsystem1750();
        }
        iVar2 = (int*)allocateMemory(0xfc);
        if (iVar2 != 0) {
            initSubsystemFC();
        }
        iVar2 = (int*)allocateMemory(0x20);
        if (iVar2 != 0) {
            initSubsystem20();
        }
        iVar2 = (int*)allocateMemory(0x25c);
        if (iVar2 != 0) {
            initSubsystem25C();
        }
        statusStr = "FAIL!";
        result = (unsigned char)params.field_4; // 0x10 -> failure indicator
    } else {
        // Second branch: same allocations + validation chain
        iVar2 = (int*)allocateMemory(0x1750);
        if (iVar2 != 0) {
            initSubsystem1750();
        }
        iVar2 = (int*)allocateMemory(0xfc);
        if (iVar2 != 0) {
            initSubsystemFC();
        }
        iVar2 = (int*)allocateMemory(0x20);
        if (iVar2 != 0) {
            initSubsystem20();
        }
        iVar2 = (int*)allocateMemory(0x25c);
        if (iVar2 != 0) {
            initSubsystem25C();
        }

        // Validation chain: all must succeed
        cVar1 = validateSubsystem1();
        if (cVar1 != '\0') {
            cVar1 = validateSubsystem2(DAT_0122350c);
            if (cVar1 != '\0') {
                cVar1 = validateSubsystem3(DAT_01223508);
                if (cVar1 != '\0') {
                    cVar1 = validateSubsystem4();
                    if (cVar1 != '\0') {
                        cVar1 = validateSubsystem5();
                        if (cVar1 != '\0') {
                            cVar1 = validateSubsystem6();
                            if (cVar1 != '\0') {
                                // Clear global buffer
                                debugPrint(0); // Possibly print nothing? Actually call with null? Decompiled: "FUN_005dbc10();" then memset. But original: FUN_005dbc10(); then memset. Might be a log.
                                // Actually the decompiled shows: FUN_005dbc10(); _memset(&DAT_011a0ec0,0,0x30);
                                // So two separate calls.
                                // We'll treat the first debugPrint with no args? Probably a separate call to clear log.
                                // Let's just follow the pattern:
                                _memset(DAT_011a0ec0, 0, 0x30);

                                cVar1 = FUN_005f01f0(); // Final validation, likely returns bool
                                if (cVar1 != '\0') {
                                    statusStr = "OK.";
                                    result = 1;
                                    goto printStatus;
                                }
                            }
                        }
                    }
                }
            }
        }
        // If any validation fails
        statusStr = "FAIL!";
        result = (unsigned char)params.field_4; // 0x10
    }

printStatus:
    debugPrint(statusStr);
    return result;
}