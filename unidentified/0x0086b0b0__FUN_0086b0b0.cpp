// FUNC_NAME: SomeComponent::SomeComponent
// Address: 0x0086b0b0
// Constructor for a derived component. Sets vtable to global table at 0x00d75d0c,
// calls base constructor, and conditionally handles destruction/allocation cleanup.
// The byte parameter likely indicates whether the object was dynamically allocated
// and should be freed on failure (common EA pattern).

class SomeComponent : public BaseObject {
public:
    // __thiscall: this=ecx, param2=dl (byte on stack)
    SomeComponent(byte allocationFlag) : BaseObject() {
        // Set vtable pointer to derived class vtable
        this->vtable = &gVtableSomeComponent;

        // Call base class constructor (address 0x004ac1e0)
        BaseObject::BaseObject();

        // If allocationFlag & 1, call destructor/cleanup (address 0x00624da0)
        // This likely means: if dynamically allocated, free memory on construction failure
        if (allocationFlag & 1) {
            this->destroy(); // Or operator delete? Probably cleanup function
        }
    }

    virtual ~SomeComponent() {} // Placeholder for vtable

private:
    // Function at 0x00624da0, likely a destructor or deallocation routine
    void destroy(); // Not implemented here
};