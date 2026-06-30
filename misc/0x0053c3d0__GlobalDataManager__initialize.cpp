// FUNC_NAME: GlobalDataManager::initialize
// Address: 0x0053c3d0
// Role: Initializes global data structures for the game manager singleton.
// Calls a system initialization function (FUN_006126d0), clears multiple global state variables,
// sets a static pointer to a data table, and returns the address of that pointer.
// The returned pointer is likely used as a singleton handle.

#include <cstdint>

// Forward declare the system initialization function (likely from engine core)
void systemInitialize(); // FUN_006126d0

// Global state variables (likely static members of GlobalDataManager)
static int32_t g_managerFlags0;       // DAT_01198e54
static int32_t g_managerFlags1;       // DAT_01198e4c
static int32_t g_managerFlags2;       // DAT_01198e48
static int32_t g_managerFlags3;       // DAT_01198e70
static int32_t g_managerFlags4;       // DAT_01194d04
static int32_t g_managerFlags5;       // DAT_01198e74
static int32_t g_managerFlags6;       // DAT_01198e64
static int32_t g_managerFlags7;       // DAT_01198e78
static int32_t g_managerFlags8;       // DAT_0121be7c
static int32_t g_managerFlags9;       // DAT_0121bcd8

// Pointer to the static data table (PTR_LAB_00e38de4)
static uint32_t* g_dataTable;         // DAT_0121bc10

// Initialization function
uint32_t** GlobalDataManager::initialize()
{
    // Call system-level initialization (likely memory/heap setup)
    systemInitialize();

    // Clear all manager flags to zero
    g_managerFlags0 = 0;
    g_managerFlags1 = 0;
    g_managerFlags2 = 0;
    g_managerFlags3 = 0;
    g_managerFlags4 = 0;
    g_managerFlags5 = 0;
    g_managerFlags6 = 0;
    g_managerFlags7 = 0;
    g_managerFlags8 = 0;
    g_managerFlags9 = 0;

    // Set the data table pointer to a static constant table (located at 0x00e38de4)
    g_dataTable = reinterpret_cast<uint32_t*>(0x00e38de4); // PTR_LAB_00e38de4

    // Return the address of the data table pointer (serves as singleton handle)
    return &g_dataTable;
}