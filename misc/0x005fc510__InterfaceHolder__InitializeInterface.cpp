// FUNC_NAME: InterfaceHolder::InitializeInterface
// Address: 0x005fc510
// Role: Initializes a wrapper object that holds an interface pointer and optionally creates a sub-object.
// This function is likely part of the EARS framework object initialization pattern.
// It takes an interface object (with virtual methods at offsets 8,4,0xC) and a parent parameter.
// The interface pointer is stored as the first member of this object.
// If parent is non-null, a sub-object is created via FUN_004265d0, the interface's SetParent is called,
// and then the interface's PostInit is called. If parent is null, only PostInit is called.

struct IInterfaceVTable {
    void (__thiscall *unk0)();       // vtable[0]
    void (__thiscall *SetParent)(void* parent, int unkZero); // vtable[1] offset 4
    void (__thiscall *PreInit)();    // vtable[2] offset 8
    void (__thiscall *PostInit)();   // vtable[3] offset 12
};

class InterfaceHolder {
public:
    IInterfaceVTable* m_interface; // +0x00
    int m_subObject;               // +0x04

    void __thiscall InitializeInterface(IInterfaceVTable* interfacePtr, void* parent) {
        this->m_interface = interfacePtr; // store interface pointer

        if (parent != nullptr) {
            // Create a sub-object using external function; result stored as second member
            this->m_subObject = FUN_004265d0(parent, this->m_interface);
            // Call SetParent on the interface
            interfacePtr->SetParent(parent, 0);
            // Finalize initialization
            interfacePtr->PostInit();
        } else {
            this->m_subObject = 0;
            // Even with no parent, finalize initialization
            interfacePtr->PostInit();
        }
    }
};