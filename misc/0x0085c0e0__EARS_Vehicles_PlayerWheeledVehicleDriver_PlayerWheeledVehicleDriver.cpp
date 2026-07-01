// Xbox PDB: EARS_Vehicles_PlayerWheeledVehicleDriver_PlayerWheeledVehicleDriver
// FUNC_NAME: RadioController::RadioController
// Address: 0x0085c0e0
// Role: Constructor for the RadioController class. Initializes fields and registers radio message names.

// External global string pointers used for message registration
extern char* DAT_0112df84;
extern char* DAT_0112df90;
extern char* DAT_0112df64;

// Vtable pointer from external symbol
extern void* PTR_FUN_00d75650;

class RadioController {
public:
    RadioController(int radioId) {
        // Set vtable (+0x00)
        *(void**)this = PTR_FUN_00d75650;

        // Store radio ID at +0x04
        *(int*)((char*)this + 0x04) = radioId;

        // Initialize fields at +0x08 and +0x0C to zero
        *(int*)((char*)this + 0x08) = 0;
        *(int*)((char*)this + 0x0C) = 0;

        // The field at +0x08 was just set to 0, so the conditional call to
        // FUN_004daf90 (likely a cleanup/deinitialization) never executes.

        // Register message strings for radio control (via global pointers)
        registerMessageString(&DAT_0112df84, "iMsgRadioPowerController");
        registerMessageString(&DAT_0112df90, "iMsgRadioIncrementController");
        registerMessageString(&DAT_0112df64, "iMsgRadioDecrementController");
    }

private:
    // Helper: stores a message name string into a global char* pointer
    void registerMessageString(char** dest, const char* src) {
        *dest = src; // or might perform string duplication
    }
};