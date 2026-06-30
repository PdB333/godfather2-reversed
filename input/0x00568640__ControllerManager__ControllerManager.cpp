// FUNC_NAME: ControllerManager::ControllerManager
// 0x00568640 - ControllerManager constructor (singleton pattern, registers global pointer)
// __thiscall
// Initializes vtable, members, and calls internal allocation/init function.

class ControllerManager
{
public:
    void **vtable;          // +0x00
    void *allocationResult; // +0x04 (result from FUN_00c79560)
    uint32_t field_0x08;    // +0x08
    uint32_t field_0x0C;    // +0x0C
    // size 0x10
};

// Global singleton pointer
ControllerManager *g_pControllerManager;

// External allocation/init function (likely factory or resource loader)
void *FUN_00c79560(uint32_t param1, uint32_t param2);

ControllerManager *__thiscall ControllerManager::ControllerManager(ControllerManager *this, uint32_t initData)
{
    g_pControllerManager = this;                           // Store singleton reference
    this->vtable = (void**)0x00e3aa80;                     // Set virtual function table
    this->field_0x08 = 0;                                  // Clear member
    this->field_0x0C = 0;                                  // Clear member
    this->allocationResult = FUN_00c79560(initData, 0);    // Initialize internal data (e.g., allocate buffer, load config)
    return this;
}