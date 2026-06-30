// FUNC_NAME: GUIDObject::GUIDObject
// Address: 0x004dae00
// Constructor for a GUID object that initializes a token string and manages different initialization modes
// The object stores a GUID string (39 bytes) and additional fields for flags, data pointer, etc.

typedef unsigned int uint32;
typedef unsigned char byte;
typedef unsigned short uint16;

class GUIDObject {
public:
    // Offset 0x00: GUID string buffer (39 bytes + null terminator)
    char guidString[40]; // +0x00

    // Offset 0x0B: Flag byte (set to 1 during init)
    byte flag0B; // +0x0B

    // Offset 0x4C: Some counter or mode (set to 0 during init)
    uint32 mode; // +0x4C

    // Offset 0x50: Pointer to something (DAT_00e36e5c or param_2)
    void* dataPtr; // +0x50

    // Constructor
    GUIDObject(int param_2);
};

extern uint32 DAT_00e36e5c; // global data

// External functions (likely engine internals)
extern bool __cdecl CheckLicense(); // FUN_004da120
extern void __cdecl InitSpecialMode(int param); // FUN_004da330
extern void __cdecl InitSystem(int param); // FUN_004d9500
extern void __cdecl InitSystemPart2(); // FUN_004da910
extern bool __cdecl SomeConditionCheck(); // FUN_00445250
extern void __cdecl CopyGUIDData(GUIDObject* dst, uint32 data1, uint32 data2); // FUN_004d9080
extern void __cdecl ProcessBuffer(char* buf); // FUN_004d9d60
extern void __cdecl ProcessBuffer2(); // FUN_004d9ff0
extern void __cdecl InitSubsystem(); // FUN_004da530
extern void __cdecl FreeMemory(int ptr); // FUN_009c8eb0
extern void __cdecl Cleanup(); // FUN_004d8be0

// The function
GUIDObject::GUIDObject(int param_2) {
    // Step 1: Initialize the GUID string with a debug token
    // The string is "{BADBADBA-BEEF-BEEF-555A-C1EA11091091}" (38 chars + null)
    const char* src = "{BADBADBA-BEEF-BEEF-555A-C1EA11091091}";
    char* dst = this->guidString;
    // Copy 36 bytes (9 dwords) using dword copy
    for (int i = 0; i < 9; i++) {
        *(uint32*)dst = *(uint32*)src;
        src += 4;
        dst += 4;
    }
    // Copy remaining 2 bytes
    *(uint16*)dst = *(uint16*)src;
    src += 2;
    dst += 2;
    // Copy last byte
    *dst = *src;

    // Step 2: Set flag at offset 0x0B to 1
    this->flag0B = 1;

    // Step 3: Set mode field at offset 0x4C to 0
    this->mode = 0;

    // Step 4: Branch based on param_2
    if (param_2 == 0) {
        // Default initialization: set type to 2 and dataPtr to global
        *(uint32*)this->guidString = 2; // Overwrites first 4 bytes of GUID string?
        this->dataPtr = &DAT_00e36e5c;
    }
    else {
        // Non-default: check license or something
        if (CheckLicense()) {
            // License check passed: set type to 1 and call special init
            *(uint32*)this->guidString = 1;
            InitSpecialMode(param_2);
            return; // Early return
        }

        // License check failed: do system initialization
        InitSystem(param_2);
        InitSystemPart2();

        // Check local buffer flag (local_40[0] was set by previous calls)
        // Note: local_40 is a 20-byte array on stack, but in decompile it's used to store a flag.
        char bufferFlag; // local_40[0] (simplified)
        // The actual locals are:
        uint32 local_50, local_4c; // used for GUID copy
        char local_40[20];
        int local_2c; // allocation pointer?
        uint32 local_28; // GUID data1
        int local_8; // allocation pointer?

        // To keep clarity, we'll just model the essential logic.
        // Assume local_40[0] was set by previous calls (maybe a flag).
        // In decompiled code, it's checked with local_40[0] == '\x01'.
        // That suggests it's a byte flag.

        // We'll declare local variables as in original (but with meaningful names)
        // Actually, the decompile shows local_40[0] is directly tested.
        // We'll just use a local char flag.

        char flag; // = local_40[0]
        // The original code didn't initialize local_40, so it's probably set by functions called.
        // Since we are reconstructing, we assume the calls above did that.
        // We'll treat it as a magic flag.

        if (flag == 1) {
            // Some condition: check another condition via SomeConditionCheck
            bool cond = SomeConditionCheck();
            if (cond) {
                // Set type to 2 and dataPtr to param_2
                *(uint32*)this->guidString = 2;
                this->dataPtr = (void*)param_2;
            }
            else {
                // Set type to 0 and copy GUID data from stack
                *(uint32*)this->guidString = 0;
                // Call to copy GUID data into local_28
                CopyGUIDData((GUIDObject*)&local_28, local_50, local_4c);
                // Copy from local_28 to this+4 (i.e., offset 4 = second dword)
                // This copies the GUID structure (9 dwords + 2 bytes + 1 byte)
                // effectively overwriting the rest of the GUID string
                char* src2 = (char*)&local_28;
                char* dst2 = (char*)(this + 1); // offset of 4 bytes (since this is pointer to start)
                // Actually param_1 + 1 in pointer arithmetic means add sizeof(undefined4) = 4 bytes
                // So we copy 9 dwords = 36 bytes, then 2 bytes, then 1 byte = 39 bytes
                for (int i = 0; i < 9; i++) {
                    *(uint32*)dst2 = *(uint32*)src2;
                    src2 += 4;
                    dst2 += 4;
                }
                *(uint16*)dst2 = *(uint16*)src2;
                src2 += 2;
                dst2 += 2;
                *dst2 = *src2;
            }
        }
        else {
            // flag != 1: set type to 1 and process buffer
            *(uint32*)this->guidString = 1;
            ProcessBuffer(local_40);
            ProcessBuffer2();

            // Check local_8 (some allocation pointer)
            if (local_8 != 0) {
                InitSubsystem();
                FreeMemory(local_8);
            }
        }

        // After the if-else, check if local_2c is non-zero (allocation pointer)
        if (local_2c != 0) {
            Cleanup();
            FreeMemory(local_2c);
            return;
        }
    }

    return;
}