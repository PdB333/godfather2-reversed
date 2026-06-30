// FUNC_NAME: InputManager::initialize
// Function address: 0x00427400
// Role: Initialize the input system: allocate controller state pool, load calibration data, set up controller plugs, and reset tables.

#include <cstdint>

// Forward declarations (assumed from external sources)
void FUN_00427200(); // Constructor for a 0x60-byte controller state object
void FUN_00427360(); // Secondary initialization
void FUN_00429dd0(); // Initialize a 0x18-byte allocation
void FUN_00609bf0(); // Handle controller plug error (reset?)
void FUN_0060be40(); // Probably release/disable calibration resource
void* FUN_009c8e50(uint32_t size); // Allocate 0x18 bytes (or 24)
void* FUN_009c8ef0(uint32_t size, void* param); // Allocate 0x3010 bytes with header
void* FUN_0060b620(uint32_t size, int a, void* b, int c); // Initialize calibration object (0x60)
void* FUN_0060c080(uint32_t size, int a, void* b, void* d); // Initialize calibration object (0x24)

// Global data (renamed for readability)
extern uint32_t* gSystemManager; // DAT_01205750 - base pointer to system manager vtable
extern uint32_t gSomeConstantStr; // DAT_0110ac5c
extern void* gInputObjectPool; // DAT_012053cc - pointer to array of controller states (0x80 * 0x60)
extern void* gAllocation18Ptr; // DAT_012053d4 - pointer to 0x18-byte allocation
extern uint8_t gInitializedFlag; // DAT_0120537d
extern uint32_t gInitializedFlag2; // DAT_012053c4

// Calibration objects (size 0x60)
extern uint32_t* gCalibObject1; // DAT_01163c80
extern uint32_t gCalib1Flags; // DAT_01163c8c
extern uint8_t gCalib1Bool; // DAT_01163c9c
extern uint8_t gCalib1Bool2; // DAT_01163c9d
extern uint32_t* gCalib1Buffer; // DAT_01163c90
extern uint32_t gDefaultCalib1Data[]; // DAT_00e2e648 - 24 DWORDs (0x60 bytes)

// Calibration objects (size 0x24)
extern uint32_t* gCalibObject2; // DAT_0116258c
extern uint32_t gCalib2Flags; // DAT_01162594
extern uint8_t gCalib2Bool; // DAT_011625b4
extern uint8_t gCalib2Bool2; // DAT_011625b5
extern uint32_t* gCalib2Buffer; // DAT_011625a8
extern uint32_t gDefaultCalib2Data[]; // DAT_00e2e6a8 - 18 DWORDs (0x48 bytes)

// Controller plug system (max 32 entries, each 0xC bytes)
extern uint32_t gControllerPlugArray[]; // DAT_01222330 (array of 0xC-byte structures)
extern uint32_t gControllerPlugCount; // DAT_012224a8 (max 32)
extern uint32_t gControllerPlugArrayStart; // DAT_01222328 (base for pointer arithmetic)

// Global array of 16-byte structures (initialized to zero)
extern uint32_t gGlobalTable[]; // DAT_012083e8 (size up to 0x120a3e8 - address)

// External error handler function pointer
extern void (*gErrorHandler)(int); // PTR_FUN_00f15a3c

// Saved EDI (from calling context)
extern uint32_t gSavedEdi; // DAT_01163cc8

// Vector constructor iterator function (STL-like or custom)
extern void _vector_constructor_iterator_(void* begin, uint32_t elementSize, uint32_t count, void (*constructor)());

void INPUT_MANAGER_Initialize()
{
    uint32_t* puVar1;
    uint32_t* puVar6;
    uint32_t uVar5;
    uint8_t* pbVar4;
    int iVar2;
    uint32_t local_10 = 0;
    uint32_t local_c = 2;       // allocation flags?
    uint32_t local_8 = 0x10;
    uint32_t local_4 = 0;

    // Allocate the controller state pool: header (4 bytes) + 0x80 elements of 0x60 bytes
    puVar1 = (uint32_t*)FUN_009c8ef0(0x3010, &local_c);
    if (puVar1 == nullptr)
    {
        gInputObjectPool = nullptr;
    }
    else
    {
        *puVar1 = 0x80;  // store count of elements
        // Construct 0x80 elements of size 0x60 starting at puVar1+4 using constructor FUN_00427200
        _vector_constructor_iterator_(puVar1 + 4, 0x60, 0x80, FUN_00427200);
        gInputObjectPool = puVar1 + 4;
    }

    local_10 = 0;
    // Call system manager function at vtable offset 0x158 (e.g., QueryInterface or GetSomething)
    iVar2 = (*(int (__thiscall**)(void*, void*, uint32_t*))(*(uint32_t*)gSystemManager + 0x158))
                 (gSystemManager, &gSomeConstantStr, &local_10);
    if (iVar2 == -0x7789fe84)  // 0x8876017C ? Possibly an error code
    {
        gErrorHandler(2);
    }

    // Save EDI from caller? (unaff_EDI)
    gSavedEdi = /*unaff_EDI*/ 0;  // The original value came from register, we don't know it here.

    // Initialize calibration object 1 (size 0x60)
    FUN_0060b620(0x60, 0, &gCalibObject1, 0);
    if (gCalib1Bool == '\0')
    {
        gCalib1Bool2 = 1;
        puVar1 = gCalib1Buffer;
    }
    else
    {
        uint32_t uVar3 = 0;
        if (gCalib1Flags != '\0')
        {
            uVar3 = 0x3000;
        }
        // Call vtable function at offset 0x2c on gCalibObject1 (e.g., init with parameters)
        (*(void (__thiscall**)(void*, int, int, void*, uint32_t))(*(uint32_t*)gCalibObject1 + 0x2c))
            (gCalibObject1, 0, 0, &/*stack0xffffffe4*/, uVar3);
        puVar1 = nullptr;
    }

    // Copy default calibration data (24 DWORDs) to the buffer
    puVar6 = &gDefaultCalib1Data[0];
    iVar2 = 0x18;
    do {
        *puVar1 = *puVar6;
        puVar6++;
        puVar1++;
        iVar2--;
    } while (iVar2 != 0);

    if (gCalib1Bool == '\0')
    {
        gCalib1Bool2 = 0;
    }
    else
    {
        // Call vtable function at offset 0x30 on gCalibObject1 (e.g., finalize/apply)
        (*(void (__thiscall**)(void*))(*(uint32_t*)gCalibObject1 + 0x30))(gCalibObject1);
    }

    // Initialize calibration object 2 (size 0x24)
    FUN_0060c080(0x24, 0, &gCalibObject2, 0x12);
    if (gCalib2Bool == '\0')
    {
        gCalib2Bool2 = 1;
        puVar1 = gCalib2Buffer;
    }
    else
    {
        uint32_t uVar3 = 0;
        if (gCalib2Flags != '\0')
        {
            uVar3 = 0x3000;
        }
        (*(void (__thiscall**)(void*, int, int, void*, uint32_t))(*(uint32_t*)gCalibObject2 + 0x2c))
            (gCalibObject2, 0, 0, &/*gCalib2DataPtr*/, uVar3);
        puVar1 = /*gCalib2DataPtr*/;  // The original used DAT_011625a0
    }

    // Copy default calibration data (18 DWORDs)
    puVar6 = &gDefaultCalib2Data[0];
    iVar2 = 0x12;
    do {
        *puVar1 = *puVar6;
        puVar6++;
        puVar1++;
        iVar2--;
    } while (iVar2 != 0);

    if (gCalib2Bool == '\0')
    {
        gCalib2Bool2 = 0;
    }
    else
    {
        FUN_0060be40();
        (*(void (__thiscall**)(void*))(*(uint32_t*)gCalibObject2 + 0x30))(gCalibObject2);
    }

    // Validate controller plug array entries (each 0xC bytes, first byte is ID)
    uVar5 = 0;
    local_10 = 0x80;  // default plug ID? The original code did CONCAT31(local_10._1_3_,0x80) which set lower byte to 0x80
    if (gControllerPlugCount != 0)
    {
        pbVar4 = (uint8_t*)&gControllerPlugArray; // &DAT_01222330
        do {
            if (0x80 < *pbVar4)  // if plug ID > 0x80, error
            {
                FUN_00609bf0();
                goto LAB_004275f6;
            }
            uVar5++;
            pbVar4 += 0xC;
        } while (uVar5 < gControllerPlugCount);
    }

    // Add a new plug entry if room (max 32)
    if (gControllerPlugCount < 0x20)
    {
        iVar2 = gControllerPlugCount * 0xC;
        // Write two float values at the base + offset? The original wrote 8 bytes as a double? Actually it wrote 0x4273f0004273e0 as two floats.
        *(uint64_t*)(&gControllerPlugArrayStart + gControllerPlugCount * 3) = 0x4273f0004273e0ULL; // floats: 60.96875 and 60.9375
        *(uint32_t*)(&gControllerPlugArray + iVar2) = local_10;  // store the ID (0x80) in first DWORD of new entry
        gControllerPlugCount++;
    }

LAB_004275f6:
    // Allocate a 0x18-byte object (24 bytes)
    iVar2 = FUN_009c8e50(0x18);
    if (iVar2 == 0)
    {
        gAllocation18Ptr = nullptr;
    }
    else
    {
        // Dummy loop that shifts 0x20 right by 2 until zero (seems like a delay or size calculation)
        uVar5 = 0x20;
        do {
            uVar5 >>= 2;
        } while (uVar5 != 0);

        FUN_00429dd0();  // initialize the 24-byte object
        gAllocation18Ptr = (void*)iVar2;
    }

    gInitializedFlag = 1;
    gInitializedFlag2 = 0;

    FUN_00427360();  // secondary init

    // Zero-initialize a global table of 16-byte structures (each 4 DWORDs)
    puVar1 = &gGlobalTable[0];
    do {
        local_10 = 0;
        // Call system manager function at vtable offset 0x1d8 (e.g., SomeSystemCall)
        (*(void (__thiscall**)(void*, int))(*(uint32_t*)gSystemManager + 0x1d8))(gSystemManager, 9);
        puVar1[3] = local_10;
        *puVar1 = 0;
        puVar1[2] = 0;
        puVar1 += 4;  // advance by 16 bytes (4 DWORDs)
    } while ((int)puVar1 < (int)(&gGlobalTable[0] + 0x120a3e8));  // upper bound of the table
}