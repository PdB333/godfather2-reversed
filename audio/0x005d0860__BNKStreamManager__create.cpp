// FUNC_NAME: BNKStreamManager::create
// Function address: 0x005d0860
// Role: Creates the singleton BNKStreamManager instance and initializes its streaming buffer (0x400 bytes at offset 0x10).
#include <cstring> // memset
extern BNKStreamManager* g_pBNKStreamManager; // DAT_01205668

// Memory allocation helper (likely EARS::Memory::Alloc with flags)
void* allocate(size_t size, int flags);

void BNKStreamManager::create()
{
    void* mem = allocate(0x54, 0);
    if (mem == 0) {
        g_pBNKStreamManager = 0;
    } else {
        // placement new calls the underlying constructor (original FUN_005cf150)
        g_pBNKStreamManager = new (mem) BNKStreamManager();
    }
    // Clear the stream buffer at object+0x10, which is 0x400 bytes.
    // NOTE: If g_pBNKStreamManager is null, this will fault. The original may have had
    // a conditional not captured in decompilation, but we reproduce the exact logic.
    std::memset(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(g_pBNKStreamManager) + 0x10), 0, 0x400);
}