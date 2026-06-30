// FUNC_NAME: EntityBase::~EntityBase
void __fastcall EntityBase::~EntityBase(EntityBase* this)
{
    int* pMainObj; // piVar3: pointer to main associated object (offset +0x5C)
    uint* pFlags;  // puVar2: for clearing bits in main object
    int iBase;     // iVar4: computed base of subobject
    int* pBase;    // piVar5: base pointer for virtual call

    // Set vtable pointer to first base class vtable
    this->vtable = &PTR_LAB_00d63910;

    // Resource/component cleanup calls
    FUN_007ff050(0);          // likely release some global resource
    FUN_007f7e40();           // probably stop audio/effects
    FUN_007f6420(0x60);       // unload texture or resource ID 0x60
    FUN_007f6420(0x69);       // unload texture or resource ID 0x69

    // pMainObj = this->m_pMainObject (offset +0x5C)
    pMainObj = (int*)this->field_0x5C;

    // Process subobject if it exists and hasn't been destroyed (0x48 sentinel)
    if ((this->m_pSubObject != 0) && (this->m_pSubObject != 0x48)) {
        // If flag bit0 at offset +0x84 is clear
        if ((*(byte*)&this->field_0x84 & 1) == 0) {
            // Compute base of subobject by subtracting 0x48 offset
            if (this->m_pSubObject == 0) {
                iBase = 0;
            }
            else {
                iBase = (int)this->m_pSubObject - 0x48;
            }
            // Check if bit 20 of a uint at base+0x110 is 0 (means not yet cleaned)
            if ((~(byte)(*(uint*)(iBase + 0x110) >> 0x14) & 1) != 0) {
                // Call cleanup function on main object
                FUN_00726ec0(this->m_pMainObject);
            }
        }
        // Always call virtual function at offset 0x24 on subobject's base
        if (this->m_pSubObject == 0) {
            pBase = (int*)0x0;
        }
        else {
            pBase = (int*)((int)this->m_pSubObject - 0x48);
        }
        (**(code**)(*pBase + 0x24))(this->m_pMainObject);
    }

    // If flag bit2 at offset +0x84 is set, call virtual function 0x290 on main object
    if (((uint)this->field_0x84 >> 2 & 1) != 0) {
        (**(code**)(*pMainObj + 0x290))(1, 1);
    }

    // Additional cleanup
    FUN_0071e1d0(0);    // likely remove from registry/list
    FUN_004612a0();     // another cleanup

    // Clear bit1 (flag 0x2) at main object + 0x5C4 (offset 0x5C4)
    pFlags = (uint*)(pMainObj + 0x171);
    *pFlags &= ~2;

    // Delete the object at field +0x78 (m_pSomePointer) if non-null
    if (this->field_0x78 != 0) {
        FUN_004daf90(&this->field_0x78);
    }

    // Delete subobject pointer (m_pSubObject) if non-null
    if (this->m_pSubObject != 0) {
        FUN_004daf90(&this->m_pSubObject);
    }

    // Switch vtable to second base class
    this->vtable = &PTR_LAB_00d63090;

    // Delete another pointer at offset +0x68 if non-null
    if (this->field_0x68 != 0) {
        FUN_004daf90(&this->field_0x68);
    }

    // Final cleanup
    FUN_0080ea60();
    return;
}