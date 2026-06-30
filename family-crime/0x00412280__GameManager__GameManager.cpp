// FUNC_NAME: GameManager::GameManager
class GameManager : public SomeBaseClass {
public:
    // Constructor at 0x00412280
    // param_2: bit 0 indicates heap-allocated (calls operator delete)
    GameManager(byte flag) {
        // Set vtable pointer
        vtable = &GameManager_vtable;  // PTR_FUN_00e2f504

        // Set secondary function table (offset +0x208)
        secondaryTable = &GameManager_secondaryTable1;  // PTR_LAB_00e2f52c

        // Base class constructor
        SomeBaseClass::init();  // FUN_00412130

        // Check if a stored pointer at offset +0x20C needs cleanup
        if (storedPointer != 0) {
            cleanupFunction(storedPointer);  // FUN_009c8f10
        }

        // Update secondary function table (offset +0x208)
        secondaryTable = &GameManager_secondaryTable2;  // PTR_LAB_00e2f530

        // Reset global singleton flag
        g_systemActive = 0;  // DAT_012233bc

        // Additional initialization
        systemInit();  // FUN_004c27f0

        // If heap-allocated, call operator delete on this
        if (flag & 1) {
            operatorDelete(this);  // FUN_009c8eb0
        }
    }

private:
    // Vtable pointer (offset +0x00)
    void* vtable;

    // Secondary table pointer (offset +0x208) – likely interface or function table
    void* secondaryTable;

    // Stored pointer (offset +0x20C) – possibly sub-object or resource
    void* storedPointer;

    // Other members...
};

// Global variable at 0x012233bc
static int g_systemActive;