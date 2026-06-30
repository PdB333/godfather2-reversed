// FUNC_NAME: Task::Task
// Reconstructed constructor for a Task/Job object at 0x006c0560.
// Sets type to 2, initializes fields from parameters and globals.

#include <cstdint>

class Task {
public:
    int32_t m_type;                 // +0x00
    uint8_t  m_padding_04;          // +0x04
    int32_t field_05;               // +0x14 (index 5)
    int32_t field_06;               // +0x18 (index 6)
    int32_t field_0x10;             // +0x40 (index 0x10)
    int32_t field_0x11;             // +0x44 (index 0x11)
    int32_t field_0x12;             // +0x48 (index 0x12)
    int32_t field_0x13;             // +0x4C (index 0x13)
    int32_t field_0x14;             // +0x50 (index 0x14)
    int32_t field_0x15;             // +0x54 (index 0x15)

    // Global data pointers used by the constructor
    static int32_t& g_taskData1;    // DAT_00e50dfc
    static int32_t& g_taskData2;    // DAT_00e50e00

    // External init function (FUN_006da9d0)
    void baseInit();

    // __thiscall constructor
    Task* __thiscall Task(int32_t param2, int32_t param3, int32_t param4, int32_t param5) {
        this->m_type = 2;                        // Set type to 2
        this->baseInit();                        // Call global initializer
        this->field_0x10 = 0;                    // Clear field at +0x40
        this->field_0x12 = 0;                    // Clear field at +0x48
        this->field_0x13 = param3;               // Store param3 at +0x4C
        this->field_0x14 = param4;               // Store param4 at +0x50
        this->field_0x11 = param2;               // Store param2 at +0x44
        this->field_0x15 = param5;               // Store param5 at +0x54
        this->field_05 = g_taskData1;            // Set from global
        this->field_06 = g_taskData2;            // Set from global
        this->m_padding_04 = 0;                  // Zero out byte at +0x04
        return this;
    }
};