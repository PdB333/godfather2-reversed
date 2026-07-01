// FUNC_NAME: MyClass::~MyClass
// Address: 0x007c3b10
// Destructor with cleanup of sub-object and possible memory deallocation.
// Derived class with vtable at 0x00d6e610, base vtable at 0x00d6b95c.

#include <cstdint>

// Forward declaration for MemoryManager singleton
class MemoryManager {
public:
    static MemoryManager* getInstance(); // FUN_007ab130
    void free(void* ptr); // vtable+4
};

// Base class declaration (vtable referenced)
class BaseClass {
public:
    virtual ~BaseClass(); // FUN_0080ea60
};

// Derived class
class MyClass : public BaseClass {
public:
    // The destructor itself. Hidden parameter __deleting indicates if memory should be freed.
    void* __thiscall ~MyClass(bool __deleting); // scalar deleting destructor

    // Fields (offset from this)
    // +0x00: vtable pointer (set to derived vtable at start, base vtable later)
    // +0x1d: byte flag (m_bFlag)
    // +0x58: pointer to a sub-object with its own vtable (m_pSubObject)
    // +0x78: pointer to be freed via memory manager (m_pData)
private:
    // Layout inferred from offsets
    uint32_t* _vtable;                         // +0x00
    uint8_t  m_bFlag;                          // +0x1d (byte)
    uint32_t __pad[0x1e - 0x1d/4];            // padding to align next
    void*    m_pSubObject;                     // +0x58 (offset 0x58 from this)
    void*    m_pData;                          // +0x78 (offset 0x78 from this)
};

// MemoryManager implementation stub (assuming singleton)
MemoryManager* MemoryManager::getInstance() {
    // via FUN_007ab130
    extern int* __fastcall getMemoryManagerSingleton();
    return reinterpret_cast<MemoryManager*>(getMemoryManagerSingleton());
}

void MemoryManager::free(void* ptr) {
    // via vtable+4 call on MemoryManager object
    // Implementation not shown, but invokes actual deallocation
}

// BaseClass destructor stub
BaseClass::~BaseClass() {
    // via FUN_0080ea60
}

// Operator delete stub (for scalar delete)
void __fastcall operatorDelete(void* pMem) {
    // via FUN_00624da0
    extern void __cdecl operator delete(void*);
    operator delete(pMem);
}

// The actual destructor implementation
void* MyClass::__thiscall ~MyClass(bool __deleting) {
    MyClass* thisPtr = this;

    // Set vtable to derived class'
    thisPtr->_vtable = reinterpret_cast<uint32_t*>(&PTR_LAB_00d6e610); // Derived vtable

    // Check flag at offset 0x1d; if set, perform additional cleanup
    if (thisPtr->m_bFlag != 0) {
        // Call virtual function at vtable offset 0x25c on sub-object
        // The sub-object is at offset 0x58
        void* subObj = thisPtr->m_pSubObject;
        if (subObj != nullptr) {
            uint32_t* subVtable = *reinterpret_cast<uint32_t**>(subObj);
            typedef void (*VirtualFunc)(void*);
            VirtualFunc func = reinterpret_cast<VirtualFunc>(subVtable[0x25c / 4]);
            func(subObj);
        }
    }

    // Get memory manager and free the data pointer at offset 0x78
    MemoryManager* memMgr = MemoryManager::getInstance();
    if (memMgr != nullptr) {
        memMgr->free(thisPtr->m_pData);
    }

    // Set vtable to base class before calling base destructor
    thisPtr->_vtable = reinterpret_cast<uint32_t*>(&PTR_LAB_00d6b95c); // Base vtable

    // Call base destructor
    thisPtr->BaseClass::~BaseClass();

    // If deleting flag is set (unaff_retaddr & 1), deallocate the memory
    if (__deleting) {
        operatorDelete(thisPtr);
    }

    return thisPtr;
}