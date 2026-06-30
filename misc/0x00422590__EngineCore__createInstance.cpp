// FUNC_NAME: EngineCore::createInstance
// Address: 0x00422590
// Role: Allocates and initializes an EngineCore singleton; uses TLS to distinguish primary (0) and secondary (1) instances.
// First few fields (0x00–0x7C) are cleared and set to a constant value (DAT_00e2b1a4) in blocks of 5, likely an array.
// High fields (0x140+) hold function pointers/constants. If primary, instance is added to a global linked list.

EngineCore* EngineCore::createInstance() {
    // Allocate raw memory (sizeof(EngineCore) ~0x180)
    EngineCore* instance = (EngineCore*)allocateEngineCore();
    
    // Read instance type from thread-local storage (FS:[0x2C] + 0x34)
    // In Windows, this likely returns a process/thread ID or a global flag.
    int instanceType = *(int*)(*(int**)(__readfsdword(0x2C) + 0x34));
    
    instance->instanceType = instanceType; // offset 0x17C
    
    // Vtable/constant pointer for all array-like slots
    int vtableConst = DAT_00e2b1a4; // likely a vtable or magic number
    
    // Initialize array of 8 slots (indices 0,5,10,15,16,21,26,31) with vtableConst,
    // and clear the four slots following each (unless at index 16 where two consecutive are set).
    instance->slot[0] = vtableConst;   // offset 0x00
    instance->slot[1] = 0;             // offset 0x04
    instance->slot[2] = 0;             // offset 0x08
    instance->slot[3] = 0;             // offset 0x0C
    instance->slot[4] = 0;             // offset 0x10
    instance->slot[5] = vtableConst;   // offset 0x14
    instance->slot[6] = 0;             // offset 0x18
    instance->slot[7] = 0;             // offset 0x1C
    instance->slot[8] = 0;             // offset 0x20
    instance->slot[9] = 0;             // offset 0x24
    instance->slot[10] = vtableConst;  // offset 0x28
    instance->slot[11] = 0;            // offset 0x2C
    instance->slot[12] = 0;            // offset 0x30
    instance->slot[13] = 0;            // offset 0x34
    instance->slot[14] = 0;            // offset 0x38
    instance->slot[15] = vtableConst;  // offset 0x3C
    instance->slot[16] = vtableConst;  // offset 0x40  (double assignment at 0x0F and 0x10)
    instance->slot[17] = 0;            // offset 0x44
    instance->slot[18] = 0;            // offset 0x48
    instance->slot[19] = 0;            // offset 0x4C
    instance->slot[20] = 0;            // offset 0x50
    instance->slot[21] = vtableConst;  // offset 0x54
    instance->slot[22] = 0;            // offset 0x58
    instance->slot[23] = 0;            // offset 0x5C
    instance->slot[24] = 0;            // offset 0x60
    instance->slot[25] = 0;            // offset 0x64
    instance->slot[26] = vtableConst;  // offset 0x68
    instance->slot[27] = 0;            // offset 0x6C
    instance->slot[28] = 0;            // offset 0x70
    instance->slot[29] = 0;            // offset 0x74
    instance->slot[30] = 0;            // offset 0x78
    instance->slot[31] = vtableConst;  // offset 0x7C

    // Fields at offsets 0x140–0x17C
    instance->flags = 1;                          // +0x140 (index 0x50)
    instance->someConstant = vtableConst;         // +0x144 (index 0x51)
    instance->callback1 = (void*)DAT_00e2e700;    // +0x148 (index 0x52)
    instance->callback2 = (void*)DAT_00e2e704;    // +0x14C (index 0x53)
    instance->callback3 = (void*)DAT_01205878;    // +0x150 (index 0x54)
    instance->field87 = 0;                        // +0x15C (index 0x57)
    instance->field88 = 0;                        // +0x160 (index 0x58)
    instance->field89 = vtableConst;              // +0x164 (index 0x59)
    instance->field90 = vtableConst;              // +0x168 (index 0x5A)
    instance->field91 = 0;                        // +0x16C (index 0x5B)
    instance->field92 = 0;                        // +0x170 (index 0x5C)

    // Second-stage initialization (likely sets up internal subsystems)
    initializeEngineCore();

    if (instanceType == 1) {
        // Secondary instance: acquire a subsystem handle and store it
        instance->subsystemHandle = (int)getSubsystemHandle(); // +0x178 (index 0x5E)
    } else if (instanceType == 0) {
        // Primary instance: insert into a global linked list
        // DAT_01206880 is a global pointer; +0x14 holds the tail of a dynamic list.
        int** tail = (int**)(DAT_01206880 + 0x14);
        *tail = (int*)&PTR_LAB_0110b618;  // Reset list end marker
        (*tail)++;                              // Move to next slot
        *(*tail) = (int)instance;               // Store this instance
        (*tail)++;                              // Advance for next insertion
        instance->subsystemHandle = 0;           // +0x178 clear
    }

    return instance;
}