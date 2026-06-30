// FUNC_NAME: Timer::constructor (0x004cb610)
void __thiscall Timer::constructor(Timer *this, int param_2, int param_3)
{
    // Call base class constructor at vtable+0xC
    (*(void (**)(void))(*reinterpret_cast<int*>(this) + 0xC))();

    // Global constructor lock count
    g_lockCount++;

    // Build a temporary timer structure (20 bytes) on stack
    struct TimerTemp {
        uint16_t field0;  // +0x00
        uint16_t field2;  // +0x02
        uint32_t field4;  // +0x04
        uint32_t field8;  // +0x08
        uint32_t fieldC;  // +0x0C
        uint32_t field10; // +0x10
    } temp;
    // Initialize all fields to 0
    temp.field0 = 0;
    temp.field2 = 0;
    temp.field4 = 0;
    temp.field8 = 0;
    temp.fieldC = 0;
    temp.field10 = 0;

    // Call initialization function (likely sets up timer with params)
    Timer::initialize(param_2, &temp, param_3);

    g_lockCount--;

    // Set vtable (object becomes fully constructed)
    *reinterpret_cast<void**>(this) = &Timer::vtable;

    // Set timer interval (60000 ms = 60 sec) at offset 0x84
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x84) = 60000;

    // Set initial delay (30 ms) at offset 0x88
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x88) = 30;
}