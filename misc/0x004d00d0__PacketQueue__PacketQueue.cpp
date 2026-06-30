// FUNC_NAME: PacketQueue::PacketQueue

#include <windows.h>

class PacketQueue {
public:
    void* m_pVtable;        // +0x00
    void* m_pOwner;         // +0x04
    int   m_nFlags1;        // +0x08
    int   m_nFlags2;        // +0x0C
    int   m_nFlags3;        // +0x10
    int   m_nFlags4;        // +0x14
    void* m_pDataBuffer;    // +0x18
    uint  m_nMaxSlots;      // +0x1C
    int   m_nUnknown1;      // +0x20
    int   m_nUnknown2;      // +0x24
    CRITICAL_SECTION m_csLock;       // +0x28
    byte  m_bLockByte;      // +0x64
    CRITICAL_SECTION m_csWriteLock;  // +0x68
    int   m_nCount;         // +0x88
    int   m_nHead;          // +0x8C
    int   m_nTail;          // +0x90
    int   m_nCapacity;      // +0x94
};

extern PacketQueue* g_pPacketQueue;  // DAT_012234a8

// 0x004d00d0
void __fastcall PacketQueue::PacketQueue(uint maxSlots, void* ownerPtr)
{
    // Initialize vtable and owner
    this->m_pOwner = ownerPtr;
    this->m_pVtable = reinterpret_cast<void**>(0x00e36cc0);  // vtable pointer
    this->m_nFlags1 = 0;
    this->m_nFlags2 = 0;
    g_pPacketQueue = this;
    this->m_nFlags3 = 0;
    this->m_nFlags4 = 0;

    // Allocate buffer for packet data (maxSlots * 4 bytes)
    this->m_pDataBuffer = reinterpret_cast<void*>(FUN_009c8e80(maxSlots * 4)); // allocation function
    this->m_nMaxSlots = maxSlots;
    this->m_nUnknown1 = 0;
    this->m_nUnknown2 = 0;

    // Initialize the main critical section
    InitializeCriticalSection(&this->m_csLock);
    this->m_bLockByte = 0;

    // Initialize the write critical section
    InitializeCriticalSection(&this->m_csWriteLock);

    // Initialize queue state
    this->m_nCount = 0;
    this->m_nHead = 0;
    this->m_nTail = 0;
    this->m_nCapacity = 0;
}