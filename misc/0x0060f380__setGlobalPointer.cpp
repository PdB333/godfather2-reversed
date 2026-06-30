// FUNC_NAME: setGlobalPointer
// Address: 0x0060f380
// Role: Sets a global pointer (likely engine instance or manager reference).

// Global variable at 0x00f15a18
static void* g_globalPointer = nullptr;

void setGlobalPointer(void* ptr) {
    g_globalPointer = ptr;
}