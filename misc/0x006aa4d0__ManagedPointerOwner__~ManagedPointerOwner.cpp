// FUNC_NAME: ManagedPointerOwner::~ManagedPointerOwner
// Address: 0x006aa4d0
// Destructor: frees up to four owned pointer objects, each with its own destructor function pointer.
// Layout: 
//   +0x00: vtable pointer
//   +0x04: m_pObject1 (pointer to first owned object)
//   +0x10: m_pDestructor1 (function pointer to destroy object1)
//   +0x14: m_pObject2
//   +0x20: m_pDestructor2
//   +0x24: m_pObject3
//   +0x30: m_pDestructor3
//   +0x34: m_pObject4
//   +0x40: m_pDestructor4
void __thiscall ManagedPointerOwner::destructor(ManagedPointerOwner* this) {
    // Set vtable pointer (likely marks object as destroyed or switches to base vtable)
    this->vtable = &PTR_FUN_00d5d9b0;

    // Destroy each owned object using its pre-stored destructor function
    if (this->m_pObject4 != nullptr) {
        this->m_pDestructor4(this->m_pObject4);
    }
    if (this->m_pObject3 != nullptr) {
        this->m_pDestructor3(this->m_pObject3);
    }
    if (this->m_pObject2 != nullptr) {
        this->m_pDestructor2(this->m_pObject2);
    }
    if (this->m_pObject1 != nullptr) {
        this->m_pDestructor1(this->m_pObject1);
    }
}