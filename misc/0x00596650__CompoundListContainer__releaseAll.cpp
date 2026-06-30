// FUNC_NAME: CompoundListContainer::releaseAll

class ElementA;
class ElementB;
class ElementC;

// Global memory manager (DAT_01205590) with vtable; deallocate at vtable+0x1c
extern void* gMemoryManager;

class CompoundListContainer {
public:
    // Fields (offsets from this)
    // +0x04: bool m_bIsInitialized;
    // +0x08: int m_countA;
    // +0x0C: int m_countB;
    // +0x10: int m_countC;
    // +0x14: ElementA** m_ppElementsA;
    // +0x18: ElementA* m_pExtraA;
    // +0x1C: (unused gap)
    // +0x20: ElementB** m_ppElementsB;
    // +0x24: ElementB* m_pExtraB;
    // +0x28: (unused gap)
    // +0x2C: ElementC** m_ppElementsC;
    // +0x30: ElementC* m_pExtraC;

    bool m_bIsInitialized;
    int m_countA;
    int m_countB;
    int m_countC;
    ElementA** m_ppElementsA;
    ElementA* m_pExtraA;
    // gap at +0x1C
    ElementB** m_ppElementsB;
    ElementB* m_pExtraB;
    // gap at +0x28
    ElementC** m_ppElementsC;
    ElementC* m_pExtraC;

    // Virtual functions (called via vtable)
    virtual void releaseElementA(ElementA* pElem) = 0;  // vtable offset 0x1C
    virtual void releaseElementB(ElementB* pElem) = 0;  // vtable offset 0x20
    virtual void releaseElementC(ElementC* pElem) = 0;  // vtable offset 0x24

    // Deallocate through global memory manager (DAT_01205590 vtable+0x1C)
    void deallocateViaGlobal(void* pPtr) {
        // Equivalent to: (*(void (**)(void*))(*(uint32_t*)gMemoryManager + 0x1C))(pPtr);
        // Platform-specific indirect call
    }

    void releaseAll() {
        if (m_bIsInitialized) {
            m_bIsInitialized = false;

            // Release all ElementA objects
            for (int i = 0; i < m_countA; i++) {
                releaseElementA(m_ppElementsA[i]);
            }
            // Free arrays and extra pointers
            deallocateViaGlobal(m_ppElementsA);
            deallocateViaGlobal(m_pExtraA);

            // Release all ElementB objects
            for (int i = 0; i < m_countB; i++) {
                releaseElementB(m_ppElementsB[i]);
            }
            deallocateViaGlobal(m_ppElementsB);
            deallocateViaGlobal(m_pExtraB);

            // Release all ElementC objects
            for (int i = 0; i < m_countC; i++) {
                releaseElementC(m_ppElementsC[i]);
            }
            deallocateViaGlobal(m_ppElementsC);
            deallocateViaGlobal(m_pExtraC);
        }
    }
};