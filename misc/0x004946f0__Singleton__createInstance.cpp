// FUNC_NAME: Singleton::createInstance

#include <cstring>

// Global state for the singleton system
extern void* g_pVTable;          // 0x012161c0
extern int g_field1;             // 0x01216490
extern int g_field2;             // 0x01216494
extern int g_field3;             // 0x012164e0
extern int g_field4;             // 0x01216500
extern char g_buffer[0x40];      // 0x012164a0
extern char g_array1[16];        // 0x012164f0
extern char g_array2[16];        // 0x01216510

// External symbol for the vtable
extern void* PTR_LAB_00e34e50;   // vtable placeholder

void* Singleton::createInstance()
{
    // Call sub‑initialization (likely sets up engine dependencies)
    FUN_00492030();

    // Initialize vtable pointer to class’s function table
    g_pVTable = &PTR_LAB_00e34e50;

    // Zero out integer fields
    g_field1 = 0;
    g_field2 = 0;
    g_field3 = 0;
    g_field4 = 0;

    // Clear 64‑byte buffer and two 16‑byte arrays
    memset(g_buffer, 0, sizeof(g_buffer));
    memset(g_array1, 0, sizeof(g_array1));
    memset(g_array2, 0, sizeof(g_array2));

    // Return pointer to the global vtable pointer (double indirection)
    return &g_pVTable;
}