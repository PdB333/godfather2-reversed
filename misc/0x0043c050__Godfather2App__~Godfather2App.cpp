// FUNC_NAME: Godfather2App::~Godfather2App
void __thiscall Godfather2App::~Godfather2App(uint *this) {
    int *pSomeObject;

    pSomeObject = (int *)this[1];                    // +0x04: m_pSomeObject
    *this = &PTR_FUN_00e30fd4;                       // Set vtable to destructor-stage vtable
    if (pSomeObject != (int *)0x0) {
        FUN_0040cd70(pSomeObject, 0x1c, *(undefined4 *)((int)pSomeObject + -4), &LAB_0043c040);
        FUN_009c8f10((int)pSomeObject + -4);         // Free allocation header
    }
    FUN_009c8f10(*(int *)(this[2] + 4));             // +0x08: m_pSomeInterface, free its internal data at +4
    (**(code **)(*(int *)this[2] + 0xc))();          // Virtual call: m_pSomeInterface->shutdown()
    *this = &PTR_LAB_00e30fd8;                       // Set vtable to final destructor-stage vtable
    DAT_01223414 = 0;                                // g_bAppInitialized = false
    return;
}