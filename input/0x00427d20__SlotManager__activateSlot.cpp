// FUNC_NAME: SlotManager::activateSlot
// Address: 0x00427d20
// Slot activation function: checks global limits, increments counter, calls virtual methods and setup routines.

// Global variables (assumed extern)
extern int gActiveSlotCount; // DAT_01163cb0
extern int gMaxActiveSlots; // DAT_0110b76c (0 means unlimited)
extern void* gSlotObjectArray[]; // DAT_012083f4 // array of SlotObject pointers
extern int gSlotActiveFlag[]; // DAT_012083e8
extern int gSlotReadyFlag[]; // DAT_012083ec
extern int gGlobalFlags; // DAT_011f7430 (bit 0 = allow activation sound)
extern int gSomeBuffer; // DAT_0116258c (used as allocation parameter)

// Forward declarations of called functions
void slotPreActivate(); // FUN_00427c10
bool isGameStateReady(); // FUN_004166b0
void playActivationSound(); // FUN_00614a50
void* allocateSlotMemory(int arg1, void* arg2, int arg3, int arg4, int arg5, int arg6); // FUN_0060cb70

// Base class for slot objects (vtable at +0x18 has handleActivation method)
class SlotObject {
public:
    virtual void handleActivation(int action) = 0; // vtable+0x18
};

int __thiscall SlotManager::activateSlot(int thisPtr) // param_1 = this
{
    int slotIndex = *(int*)(thisPtr + 0x28); // offset +0x28 stores the slot index to activate
    bool canActivate = (gActiveSlotCount > 0x7f); // if current count > 127, false
    if (gMaxActiveSlots != 0) {
        canActivate = (gActiveSlotCount <= gMaxActiveSlots);
    }
    if (canActivate) {
        return 0; // activation rejected
    }

    gActiveSlotCount++; // increment global slot count

    SlotObject* slotObj = (SlotObject*)gSlotObjectArray[slotIndex];
    slotObj->handleActivation(2); // begin activation (action=2)

    slotPreActivate(); // perform generic slot setup

    if (isGameStateReady()) {
        if (gGlobalFlags & 1) {
            playActivationSound(); // play sound if allowed by flag
        }
    }

    allocateSlotMemory(4, &gSomeBuffer, 0, 0x24, 0, 0x23); // allocate 0x24-byte structure

    slotObj->handleActivation(1); // finish activation (action=1)

    gSlotActiveFlag[slotIndex] = 1; // mark slot as active
    gSlotReadyFlag[slotIndex] = 0; // mark slot as not ready (or idle)
    return 1; // success
}