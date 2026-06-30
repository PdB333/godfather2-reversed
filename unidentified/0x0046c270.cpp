// FUN_NAME: EAObject::constructor
// Address: 0x0046c270
// This is a constructor for a base EA engine object, likely in the EARS hierarchy.
// It sets up initial vtables, calls base initialization functions, then updates the vtable after all base parts are initialized.
// A global flag is reset to zero at the end.

extern void* g_vtableInitial;    // +0x00: PTR_FUN_00e327f0 (initial vtable)
extern void* g_vtableSecondary;  // +0x04: PTR_LAB_00e327f4 (second vtable or interface)
extern void* g_vtableFinal;      // +0x00: PTR_LAB_00e32804 (final vtable after init)
extern int g_initializedFlag;    // _DAT_0122347c - set to 0 at end of constructor

void baseInit(void* data);       // FUN_004086d0 - initializes some base with global data
void secondaryInit(void);        // FUN_004083d0 - additional initialization step

void __thiscall EAObject::constructor(void* thisPtr)
{
    // Set up initial vtable pointers (before base class construction)
    *(void**)thisPtr = &g_vtableInitial;            // +0x00: primary vtable
    *((void**)thisPtr + 1) = &g_vtableSecondary;    // +0x04: secondary vtable/interface

    // Call base class initializer with global data (DAT_012069d4)
    baseInit(&DAT_012069d4);

    // Additional initialization
    secondaryInit();

    // After all base parts are constructed, update to the final vtable
    *(void**)thisPtr = &g_vtableFinal;

    // Reset a global flag (e.g., an already-initialized guard)
    g_initializedFlag = 0;

    return;
}