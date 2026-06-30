// FUNC_NAME: GameObject::GameObject

// Reconstructed constructor for a game object at 0x0047c3c0.
// Base class initialization at FUN_0046c590 (likely ObjectBase ctor).
// Offsets relative to this pointer:
// +0x00: vtable pointer
// +0x3C: callback pointer 1 (virtual table or function pointer)
// +0x48: callback pointer 2
// +0x50: flags (int32)
// +0x54: short value 1
// +0x56: short value 2
// +0x58: counter/int32

class ObjectBase {
public:
    virtual ~ObjectBase() {}
    // Base constructor called with an int param
    // FUN_0046c590 is assumed to be ObjectBase::ObjectBase(int)
    ObjectBase(int param);
};

class GameObject : public ObjectBase {
public:
    // Derived constructor
    void* m_callback1;        // +0x3C
    void* m_callback2;        // +0x48
    int32 m_flags;            // +0x50
    int16 m_short1;           // +0x54
    int16 m_short2;           // +0x56
    int32 m_counter;          // +0x58

    GameObject(int param);
};

GameObject::GameObject(int param) : ObjectBase(param) {
    // The decompiler shows explicit vtable assignment; in actual MSVC code
    // this is done by the compiler, but preserved here for accuracy.
    *(void**)this = (void*)0x00e3317c;

    // Initialize derived members
    m_callback1 = (void*)0x00e33198;  // +0x3C
    m_callback2 = (void*)0x00e331a8;  // +0x48
    m_flags = 0;                      // +0x50
    m_short1 = 0;                     // +0x54
    m_short2 = 0;                     // +0x56
    m_counter = 0;                    // +0x58

    // Return this (implicit in constructor)
}