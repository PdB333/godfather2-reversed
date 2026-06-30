// FUNC_NAME: GameObject::~GameObject
void __fastcall GameObject::destructor(GameObject *this)
{
    this->m_vtable = (void **)&PTR_LAB_00d64e80;  // set vtable to base class after our destructor runs
    baseClassDestructor();                        // FUN_007ffa80
    releaseResource(0);                           // FUN_0072cf00

    if (this->m_flags & 0x02) {
        freeGlobalResource(0, 0, g_globalPointer); // FUN_007f4490
    }

    if (this->m_flags & 0x04) {
        // m_pInternalObject (offset +0x50) has its own vtable; call cleanup method at offset 0x290
        this->m_pInternalObject->cleanup(1, 1);   // vtable index (0x290 / 4) = 0xA4
    }

    if (this->m_pSubObject != 0) {
        deleteAndNullifyPtr(&this->m_pSubObject); // FUN_004daf90, frees the pointed object and nulls the pointer
    }

    globalCleanup();                              // FUN_004ac1e0
}