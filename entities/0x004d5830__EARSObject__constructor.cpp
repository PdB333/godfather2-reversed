// FUNC_NAME: EARSObject::constructor

// Original address: 0x004d5830
// In-game function: Constructs an EARSObject, performs static init then instance init.

class EARSObject {
public:
    // Offset 0x00: vtable pointer (likely)
    // ... other members

    // Constructor
    __thiscall EARSObject();
};

// Static class initialization (address 0x004d57e0)
extern void __cdecl EARSObject_staticInit();

// Instance initialization helper (address 0x004d4300)
extern void __cdecl EARSObject_init(EARSObject* obj);

__thiscall EARSObject::EARSObject() {
    // Perform static initialization (e.g., vtable setup, global state)
    EARSObject_staticInit();
    // Perform instance-specific initialization (sets up object data)
    EARSObject_init(this);
}