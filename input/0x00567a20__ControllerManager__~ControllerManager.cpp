// FUNC_NAME: ControllerManager::~ControllerManager
// Address: 0x00567a20
// Role: Destructor for ControllerManager class. Cleans up dynamically allocated members and resets global count.

void __thiscall ControllerManager::~ControllerManager(ControllerManager* this)
{
    // Set vtable to derived class (likely ControllerManager vtable)
    this->vtable = &PTR_FUN_00e3a8d8;               // +0x00: vtable pointer
    this->field_4 = &PTR_LAB_00e3a920;              // +0x04: second vtable or offset

    // Clean up member at offset +0x24 (9th element)
    if (this->m_pControllerList != nullptr) {
        // Call virtual function at vtable+8 on the object (likely destructor or release)
        (*(void (__thiscall**)(void*))(*this->m_pControllerList + 8))(this->m_pControllerList);
    }
    this->m_pControllerList = nullptr;

    // Clean up member at offset +0x08 (2nd element)
    if (this->m_pSomeOther != nullptr) {
        // Call virtual function at vtable+0x2c (44) on that object
        (*(void (__thiscall**)(void*))(*this->m_pSomeOther + 0x2c))(this->m_pSomeOther);
    }
    this->m_pSomeOther = nullptr;

    // Clean up member at offset +0x0C (3rd element)
    if (this->m_pThirdPointer != nullptr) {
        // Call virtual function at vtable+0x5c (92) on that object
        (*(void (__thiscall**)(void*))(*this->m_pThirdPointer + 0x5c))(this->m_pThirdPointer);
    }
    this->m_pThirdPointer = nullptr;

    // Clean up raw pointer at offset +0x10 (4th element) using a function pointer at +0x1C (7th element)
    if (this->m_pRawData != 0) {
        (*(void (__cdecl*)(void*))this->m_pDeleterFunc)(this->m_pRawData);  // +0x1C: deleter function
    }

    // Switch vtable to base class (likely a parent destructor section)
    this->field_4 = &PTR_LAB_00e3a924;              // +0x04
    s_controllerCount = 0;                          // Global count reset
    this->vtable = &PTR_LAB_00e3a890;               // +0x00: final base vtable
}