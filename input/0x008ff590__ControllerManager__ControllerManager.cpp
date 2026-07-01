// FUNC_NAME: ControllerManager::ControllerManager

#include <cstdint>

// Vibration state for one controller slot
struct VibrationSlot {
    uint32_t mPacketNumber; // +0x00
    uint16_t mLeftMotor;    // +0x04
    uint16_t mRightMotor;   // +0x06
};

// Class with vtable at +0x00 and two additional function pointer tables
class ControllerManager {
public:
    void* m_vtable;               // +0x00 (&PTR_FUN_00d816e0)
    void* mTable1;                // +0x3C (&PTR_LAB_00d816d0)
    void* mTable2;                // +0x48 (&PTR_LAB_00d816cc)
    VibrationSlot mVibrationSlots[4]; // +0x50 (4 * 8 = 32 bytes)

    ControllerManager(void* param2);
};

// External base class constructor (FUN_0046c590)
void BaseClassConstructor(void* this_ptr, void* param2);

// Constructor at 0x008ff590
ControllerManager* __thiscall ControllerManager::ControllerManager(void* param2) {
    BaseClassConstructor(this, param2);

    // Set vtable and function pointer tables
    this->m_vtable = &PTR_FUN_00d816e0;
    this->mTable1 = &PTR_LAB_00d816d0;
    this->mTable2 = &PTR_LAB_00d816cc;

    // Zero all vibration slots (32 bytes starting at +0x50)
    for (int i = 0; i < 4; ++i) {
        this->mVibrationSlots[i].mPacketNumber = 0;
        this->mVibrationSlots[i].mLeftMotor = 0;
        this->mVibrationSlots[i].mRightMotor = 0;
    }

    return this;
}