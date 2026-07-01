// FUNC_NAME: SomeManager::~SomeManager
// Function address: 0x0081e710
// Role: Destructor / cleanup for a manager class. Releases reference-counted objects (smart pointers) at offsets 0xFC, 0x100, 0xF4, 0xF8, 0x104,
//       nullifies raw pointers at offsets 0xE0-0x114, and performs global cleanup.

void __thiscall SomeManager::~SomeManager()
{
    int *piVar1;
    int *piVar2;

    // vtable setup (multi‑inheritance: two vtable pointers)
    *(void **)this = &PTR_FUN_00d732d8;           // +0x00: first vtable
    *(void **)((char *)this + 0x0C) = &PTR_LAB_00d732d4; // +0x0C: second vtable

    // Release smart pointers (reference counting)
    piVar2 = *(int **)((char *)this + 0xFC);       // +0xFC: smart pointer a
    piVar1 = piVar2 + 1;
    (*piVar1)--;
    if (*piVar1 == 0) {
        (**(code **)(*piVar2 + 4))();             // delete via vtable+4
    }

    piVar2 = *(int **)((char *)this + 0x100);      // +0x100: smart pointer b
    piVar1 = piVar2 + 1;
    (*piVar1)--;
    if (*piVar1 == 0) {
        (**(code **)(*piVar2 + 4))();
    }

    piVar2 = *(int **)((char *)this + 0xF4);       // +0xF4: smart pointer c
    piVar1 = piVar2 + 1;
    (*piVar1)--;
    if (*piVar1 == 0) {
        (**(code **)(*piVar2 + 4))();
    }

    piVar2 = *(int **)((char *)this + 0xF8);       // +0xF8: smart pointer d
    piVar1 = piVar2 + 1;
    (*piVar1)--;
    if (*piVar1 == 0) {
        (**(code **)(*piVar2 + 4))();
    }

    piVar2 = *(int **)((char *)this + 0x104);      // +0x104: smart pointer e
    piVar1 = piVar2 + 1;
    (*piVar1)--;
    if (*piVar1 == 0) {
        (**(code **)(*piVar2 + 4))();
    }

    // Global cleanup call
    FUN_004086d0(&DAT_01206970);                  // release a global singleton

    // Nullify and disconnect raw pointers
    if (*(int *)((char *)this + 0x114) != 0) {    // +0x114: raw pointer?
        FUN_004daf90((int *)((char *)this + 0x114)); // release or disconnect
    }

    if (*(int *)((char *)this + 0xF0) != 0) {     // +0xF0: m_pListener1
        *(int *)(*(int *)((char *)this + 0xF0) + 8) = 0; // clear back‑reference
        *(int *)((char *)this + 0xF0) = 0;
    }
    if (*(int *)((char *)this + 0xEC) != 0) {     // +0xEC: m_pListener2
        *(int *)(*(int *)((char *)this + 0xEC) + 8) = 0;
        *(int *)((char *)this + 0xEC) = 0;
    }
    if (*(int *)((char *)this + 0xE8) != 0) {     // +0xE8: m_pListener3
        *(int *)(*(int *)((char *)this + 0xE8) + 8) = 0;
        *(int *)((char *)this + 0xE8) = 0;
    }
    if (*(int *)((char *)this + 0xE4) != 0) {     // +0xE4: m_pListener4
        *(int *)(*(int *)((char *)this + 0xE4) + 8) = 0;
        *(int *)((char *)this + 0xE4) = 0;
    }
    if (*(int *)((char *)this + 0xE0) != 0) {     // +0xE0: m_pListener5
        *(int *)(*(int *)((char *)this + 0xE0) + 8) = 0;
        *(int *)((char *)this + 0xE0) = 0;
    }

    // Final vtable switch (destructor finalisation)
    *(void **)((char *)this + 0x0C) = &PTR_LAB_00d732d0;

    // Clear global flag
    DAT_01129944 = 0;

    // Final global cleanup
    FUN_004083d0();
}