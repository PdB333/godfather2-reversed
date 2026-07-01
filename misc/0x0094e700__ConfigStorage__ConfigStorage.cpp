// FUNC_NAME: ConfigStorage::ConfigStorage
// Function constructor for ConfigStorage class (address 0x0094e700)
// Stores config strings and flags, likely singletone (gConfigStorage)
ConfigStorage* __fastcall ConfigStorage::ConfigStorage(ConfigStorage* thisPtr)
{
    // Call base class constructor
    BaseClass::BaseClass();

    // Set vtable and other function pointer tables
    thisPtr->vtablePtr = (void*)0x00d8b9a8;                     // +0x00: vtable
    thisPtr->field4_ptr = (void*)0x00d8b984;                    // +0x10: some table
    thisPtr->field13_ptr = (void*)0x00d8b980;                   // +0x4C: another table

    // Initialize flags and counters
    thisPtr->field14 = 0;                                       // +0x50
    thisPtr->field15 = 0;                                       // +0x54
    thisPtr->field17_color = 0xFFFFFF;                          // +0x5C: default color (RGB)
    thisPtr->field19_color = 0xFFFFFF;                          // +0x64: another color
    thisPtr->field1b = 0;                                       // +0x6C
    thisPtr->field20 = 0;                                       // +0x80
    thisPtr->field21 = 1;                                       // +0x84: active flag
    thisPtr->field22 = 0;                                       // +0x88
    thisPtr->field23 = 0;                                       // +0x8C
    thisPtr->field24 = 0;                                       // +0x90
    thisPtr->field25 = 0;                                       // +0x94

    // Initialize critical section (or similar)
    InitializeCriticalSection(&gConfigStorageCS);               // DAT_00e2f044
    InitializeCriticalSection(&gConfigStorageCS);               // called twice (likely both read/write)

    // Set byte flags
    thisPtr->byteFlags[0] = 1;                                  // +0xB8
    thisPtr->byteFlags[1] = 0;                                  // +0xB9
    thisPtr->byteFlags[2] = 0;                                  // +0xBA

    // Allocate string buffers (0x80 = 128 bytes)
    thisPtr->stringA = (char*)AllocateMemory(0x80);             // +0x58: name/path buffer
    thisPtr->stringA[0] = '\0';

    thisPtr->stringB = (char*)AllocateMemory(0x80);             // +0x60
    thisPtr->stringB[0] = '\0';

    thisPtr->stringC = (char*)AllocateMemory(0x80);             // +0x68
    thisPtr->stringC[0] = '\0';

    thisPtr->stringD = (char*)AllocateMemory(0x80);             // +0x70
    thisPtr->stringD[0] = '\0';

    // Allocate smaller buffers (0x20 = 32 bytes)
    thisPtr->stringE = (char*)AllocateMemory(0x20);             // +0x74
    thisPtr->stringE[0] = '\0';

    thisPtr->stringF = (char*)AllocateMemory(0x20);             // +0x78
    thisPtr->stringF[0] = '\0';

    thisPtr->stringG = (char*)AllocateMemory(0x20);             // +0x7C
    thisPtr->stringG[0] = '\0';

    // Register global singleton
    gConfigStorage = thisPtr;                                   // DAT_0112b9b8

    return thisPtr;
}