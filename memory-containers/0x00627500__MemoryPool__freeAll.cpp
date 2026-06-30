// FUNC_NAME: MemoryPool::freeAll
// Function at 0x00627500, deallocates two buffer arrays and updates total allocated size counter in parent manager.

// External function pointer (likely free or operator delete)
extern void (*s_deallocFunc)(void*);

class MemoryPool {
public:
    // +0x1c: pointer to array of elements (size 8 each)
    void* m_buffer8; // offset 0x1c
    // +0x20: count of elements in m_buffer8
    int m_count8;    // offset 0x20
    // +0x28: pointer to array of elements (size 24 each)
    void* m_buffer24; // offset 0x28
    // +0x2c: count of elements in m_buffer24 (stored as ushort)
    ushort m_count24; // offset 0x2c

    // param_1: pointer to parent manager with size tracking.
    // Parent manager has at +0x10 a pointer to a structure containing total size at +0x24.
    void freeAll(void* parentManager) {
        ushort count24 = m_count24;
        if (m_buffer24 != nullptr) {
            s_deallocFunc(m_buffer24);
            if (parentManager != nullptr) {
                // Decrement total size by count24 * 24 bytes
                int* totalSize = (int*)(*(int*)((char*)parentManager + 0x10) + 0x24);
                *totalSize += (int)count24 * -0x18; // -24
            }
        }
        int count8 = m_count8;
        if (m_buffer8 != nullptr) {
            s_deallocFunc(m_buffer8);
            if (parentManager != nullptr) {
                // Decrement total size by count8 * 8 bytes
                int* totalSize = (int*)(*(int*)((char*)parentManager + 0x10) + 0x24);
                *totalSize += count8 * -8;
            }
        }
    }
};