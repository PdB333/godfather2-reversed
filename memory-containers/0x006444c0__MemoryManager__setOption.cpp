// FUNC_NAME: MemoryManager::setOption

#include <windows.h>

class MemoryManager {
public:
    // offsets relative to this (size unknown)
    // +0x04: m_flags (uint)
    // +0x46d: m_bool1 (bool)
    // +0x46e: m_bool2 (bool)
    // +0x490: m_opt10 (uint)
    // +0x494: m_opt9 (uint)
    // +0x498: m_bool3 (bool)
    // +0x4b4: m_opt13 (uint)
    // +0x4c8: m_opt7 (uint)
    // +0x4cc: m_opt8 (uint)
    // +0x4d4: m_alignment (uint, power of two)
    // +0x4dc: m_poolSize (uint)
    // +0x4e0: m_maxAllocSize (uint)
    // +0x4e4: m_bool4 (bool)
    // +0x4e8: m_pCriticalSection (CriticalSectionPair*)
    
    void setOption(int opcode, uint value);
};

void MemoryManager::setOption(int opcode, uint value) {
    // opcode enum:
    // 1: create/destroy critical section
    // 2: no-op
    // 3: set m_bool1
    // 4: set m_poolSize (rounded to alignment)
    // 5: set m_maxAllocSize (capped by m_poolSize)
    // 6: process internal and then flag reset/init
    // 7: set m_opt7
    // 8: set m_opt8
    // 9: set m_opt9
    // 10: set m_opt10
    // 11: set m_bool3
    // 12: set m_bool4
    // 13: set m_opt13
    // 14: set m_bool2

    CriticalSectionPair* csPair;

    switch (opcode) {
        case 1: {
            // critical section management
            if (value == 0) {
                csPair = m_pCriticalSection;
                if (csPair != nullptr) {
                    EnterCriticalSection(&csPair->cs);
                    // increment reference count stored in the second CRITICAL_SECTION's DebugInfo
                    csPair[1].debugInfo = reinterpret_cast<PRTL_CRITICAL_SECTION_DEBUG>(
                        reinterpret_cast<int>(&csPair[1].debugInfo->Type) + 1);
                    m_pCriticalSection = nullptr;
                    destroyCriticalSection(); // FUN_00643ee0
                    DeleteCriticalSection(&csPair->cs);
                    // note: the pair pointer is no longer valid after deletion
                }
            } else if (m_pCriticalSection == nullptr) {
                m_pCriticalSection = createCriticalSection(); // FUN_00643e90
            }
            break;
        }
        case 2:
            // no operation
            break;
        case 3:
            m_bool1 = (value != 0);
            break;
        case 4:
            if (value != 0) {
                uint align = m_alignment;
                if (value <= align) {
                    value = align;
                }
                m_poolSize = (value - 1 + align) & ~(align - 1);
            } else {
                m_poolSize = 0x1000000; // default 16MB
            }
            break;
        case 5:
            if (value == 0) {
                m_maxAllocSize = 0x400000; // 4MB default
            } else {
                uint align = m_alignment;
                if (value <= align) {
                    value = align;
                }
                uint rounded = (value - 1 + align) & ~(align - 1);
                if (rounded > m_poolSize) {
                    m_maxAllocSize = m_poolSize;
                } else {
                    m_maxAllocSize = rounded;
                }
            }
            break;
        case 6: {
            csPair = m_pCriticalSection;
            if (csPair != nullptr) {
                EnterCriticalSection(&csPair->cs);
                csPair[1].debugInfo = reinterpret_cast<PRTL_CRITICAL_SECTION_DEBUG>(
                    reinterpret_cast<int>(&csPair[1].debugInfo->Type) + 1);
            }
            processInternal(); // FUN_00647b20 (this)
            if (value == 0) {
                m_flags &= 1; // keep only bit 0
            } else {
                initializeInternals(); // FUN_00643e00
            }
            if (csPair != nullptr) {
                csPair[1].debugInfo = reinterpret_cast<PRTL_CRITICAL_SECTION_DEBUG>(
                    reinterpret_cast<int>(&csPair[1].debugInfo[-1].SpareWORD) + 1);
                LeaveCriticalSection(&csPair->cs);
            }
            break;
        }
        case 7:
            m_opt7 = value;
            break;
        case 8:
            m_opt8 = value;
            break;
        case 9:
            m_opt9 = value;
            break;
        case 10:
            m_opt10 = value;
            break;
        case 11:
            m_bool3 = (value != 0);
            break;
        case 12:
            m_bool4 = (value != 0);
            break;
        case 13:
            m_opt13 = value;
            break;
        case 14:
            m_bool2 = (value != 0);
            break;
        default:
            break;
    }
}