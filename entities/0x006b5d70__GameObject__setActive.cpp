// FUNC_NAME: GameObject::setActive
#include <cstdint>

extern uint32_t DAT_0112a660;            // global context identifier
extern void* PTR_LAB_00d5dbb0;          // pointer to some global symbol

void __thiscall GameObject::setActive(bool active)
{
    // +0x34: flags field (bit 28 = 0x10000000)
    uint32_t& flags = *(uint32_t*)((char*)this + 0x34);
    // +0x16C: state field (1 = special state)
    int32_t& state = *(int32_t*)((char*)this + 0x16C);

    if (active)
    {
        flags |= 0x10000000;                      // set flag

        if (state == 1)
            FUN_006b4e30(0, 0);                   // special state action
        else
            FUN_006b5a30();                       // default action

        // Prepare a small stack frame for a callback (FUN_00408a00)
        void** local_14;           // temporary pointer to global symbol
        int local_10;              // stores this pointer
        int local_c;               // context value
        void*** local_8;           // pointer to local_14
        char local_4;              // flag byte (always 0)

        local_8  = &local_14;                     // store address of local_14
        local_14 = (void**)&PTR_LAB_00d5dbb0;     // point to global symbol
        local_c  = DAT_0112a660;                  // global context
        local_4  = 0;                             // zero flag
        local_10 = (int)this;                     // pass this as an int

        FUN_00408a00(&local_c, 0);                // invoke callback
    }
    else
    {
        flags &= 0xEFFFFFFF;                      // clear flag
    }
}