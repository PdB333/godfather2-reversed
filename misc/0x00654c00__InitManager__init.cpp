// FUNC_NAME: InitManager::init
void InitManager::init(int someInterface, int unused, int dataConfig)
{
    // Set vtable pointer (offset 0x00) - assumed from a pointer table
    this->vtable = &PTR_LAB_00e43130;
    this->field04 = 0;
    this->field08 = 0;
    this->field14 = 0;
    this->field0C = 0;
    this->field10 = 0;
    this->field20 = 0;
    this->field18 = 0;
    this->field1C = 0;
    int* arrayPtr = this->slotsArray; // +0x18?
    this->field2C = 0;
    this->field24 = 0;
    this->field28 = 0;
    this->field30 = 0;
    this->field34 = 0;

    // Initialize subsystems
    initSubsystemA();
    initSubsystemB();
    initSubsystemC();

    if (g_platform != 0) {
        g_platform->release(); // virtual call at offset 0x0C (likely Release)
    }
    g_platform = someInterface;
    if (someInterface != 0) {
        someInterface->addRef(); // virtual call at offset 0x08 (AddRef)
    }

    // Allocate a data configuration object (size 0x78 = 120 bytes)
    int* dataObj = allocObject(0x78); // FUN_009c8e50
    if (dataObj != 0) {
        constructDataConfig(dataObj, dataConfig); // FUN_0065ceb0
    }

    bool isFirstInit = (g_initFlag == '\0');
    this->field6C = 0;
    this->field7C = 1; // byte at offset 0x7C
    this->field68 = 0; // byte at offset 0x68

    if (isFirstInit) {
        g_initFlag = '\x01';
        initMutex(&g_mutex); // FUN_00662100
        initEvent(&g_event); // FUN_006622a0
    }

    // Attach event to this manager
    attachEvent(&this->eventSlot, 0xC, &g_event); // FUN_00662350

    // Register for callback with ID 0x81
    registerCallback(0x81); // FUN_00657bf0

    // Ensure maxSlots is at least 0x81 (129)
    if (this->maxSlots < 0x81 || this->maxSlots > 0x81) {
        this->maxSlots = 0x81;
    }

    // Clear the slot array (each slot is 4 bytes)
    int count = 0;
    if (0 < this->maxSlots) {
        do {
            *(this->slotDataArray + count) = 0;
            count++;
        } while (count < this->maxSlots);
    }

    this->field80 = 0;
    this->field64 = readHardwareConfig(); // FUN_0065c190
    return;
}