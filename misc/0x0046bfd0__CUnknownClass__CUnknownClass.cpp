// FUNC_NAME: CUnknownClass::CUnknownClass
// Address: 0x0046bfd0
// Constructor: sets vtable pointer and chains to base class constructor

typedef void (__thiscall *VFunc)(void);

class CUnknownClass
{
public:
    VFunc* vtable; // +0x00

    CUnknownClass* __thiscall CUnknownClass(void);
};

CUnknownClass* __thiscall CUnknownClass::CUnknownClass()
{
    // Set vtable to class-specific table
    this->vtable = (VFunc*)&PTR_FUN_00e327cc;

    // Call base class constructor (FUN_0043e2e0)
    FUN_0043e2e0(this);

    return this;
}