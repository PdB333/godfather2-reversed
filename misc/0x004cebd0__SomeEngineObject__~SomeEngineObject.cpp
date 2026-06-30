// FUNC_NAME: SomeEngineObject::~SomeEngineObject
// Destructor for an EA engine object with two dynamically allocated members and a sub-object.
// Offset map:
// +0x00: vtable (this)
// +0x10: m_pBaseSubObject (pointer to a base-like object with its own vtable)
// +0x14: m_pMember1 (pointer to a dynamically allocated block, freed with size=0)
// +0x18: m_pMember2 (pointer to a dynamically allocated block of 12 bytes)

void __thiscall SomeEngineObject::~SomeEngineObject(void)
{
    // Base class destructor / pre-cleanup
    FUN_004cecd0();

    // Delete m_pMember2 (12-byte allocation) using vtable slot[1] (sized deallocation)
    (*(void (__stdcall *)(void *, unsigned int))(*(int *)this + 4))(this->m_pMember2, 0xc);
    this->m_pMember2 = 0;

    // Delete m_pMember1 (size 0, likely flag or special) via base sub-object's vtable slot[1]
    if (this->m_pMember1 != 0) {
        (*(void (__stdcall *)(void *, unsigned int))(*(int *)this->m_pBaseSubObject + 4))(this->m_pMember1, 0);
        this->m_pMember1 = 0;
    }

    // Call cleanup/destructor on base sub-object (vtable slot[3])
    (*(void (__stdcall *)(void))(*(int *)this->m_pBaseSubObject + 0xc))();

    // Post-destructor cleanup
    FUN_004cee30();
}