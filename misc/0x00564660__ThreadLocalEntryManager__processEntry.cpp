// FUNC_NAME: ThreadLocalEntryManager::processEntry
#include <windows.h> // for TlsGetValue

// Represents an entry in a thread-local resource array.
struct ThreadLocalEntry {
    int handle;   // +0x00: Resource handle or ID
    int unknown;  // +0x04: Padding or additional data
    int index;    // +0x08: Index into a per-thread array (multiplied by 16 later)
};

// TLS index for per-thread data (likely a pointer to an array of 16-byte structures)
extern DWORD g_TlsIndex; // DAT_01139810

// Forward declaration of the internal processing function.
// It takes: some thread-local context, the handle, an offset (index<<4), and a constant (0x17).
void __fastcall processResourceEntry(void* tlsContext, int handle, int offset, int constant);

void __fastcall ThreadLocalEntryManager::processEntry(ThreadLocalEntry* pEntry) {
    int entryIndex = pEntry->index;
    if (entryIndex >= 0) {
        // Retrieve the per-thread data pointer (e.g., a buffer or object array).
        void* tlsData = TlsGetValue(g_TlsIndex);
        // Process the entry using the handle, offset into the TLS array, and a constant (type/priority?).
        processResourceEntry(tlsData, pEntry->handle, entryIndex << 4, 0x17);
    }
}