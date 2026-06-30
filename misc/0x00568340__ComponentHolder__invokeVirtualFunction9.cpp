// FUNC_NAME: ComponentHolder::invokeVirtualFunction9
// Function at 0x00568340: calls virtual function at vtable offset 0x24 (index 9) on object pointed to by this+0x0C.
// If the pointer is null, returns 0.

class IComponentInterface {
public:
    virtual void dummy1();  // vtable+0x00
    virtual void dummy2();  // vtable+0x04
    virtual void dummy3();  // vtable+0x08
    virtual void dummy4();  // vtable+0x0C
    virtual void dummy5();  // vtable+0x10
    virtual void dummy6();  // vtable+0x14
    virtual void dummy7();  // vtable+0x18
    virtual void dummy8();  // vtable+0x1C
    virtual void dummy9();  // vtable+0x20
    virtual int someFunction(); // vtable+0x24 (the one being called)
};

class ComponentHolder {
public:
    // +0x00: vtable pointer (for ComponentHolder)
    // +0x04: unknown (maybe size or ID)
    // +0x08: unknown
    // +0x0C: pointer to an IComponentInterface object
    IComponentInterface* m_pComponent; 

    // +0x10: ...

public:
    // __thiscall: this in ECX
    int __fastcall invokeVirtualFunction9(); // returns the result from the virtual call
};

int __fastcall ComponentHolder::invokeVirtualFunction9() {
    if (m_pComponent != nullptr) {
        // Call virtual function at vtable offset 0x24 (someFunction)
        return m_pComponent->someFunction(); 
    }
    return 0;
}