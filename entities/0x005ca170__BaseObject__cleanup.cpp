// FUNC_NAME: BaseObject::cleanup

void __thiscall BaseObject::cleanup(void) {
    // Fields: [0] = vtable, [1] = m_ptr1, [2] = m_field2, [3] = m_field3,
    //         [4] = m_ptr2, [5] = m_field5, [6] = m_field6
    int** allocManager = *(int***)(DAT_012234ec + 4); // +0x4: pointer to allocator vtable

    m_field6 = 0;       // offset +0x18
    m_field5 = 0;       // offset +0x14
    if (m_ptr2 != 0) {  // offset +0x10
        // Release through allocator (likely operator delete or object release)
        (*(void(__thiscall**)(void*, int))(*allocManager + 4))(m_ptr2, 0);
    }
    m_ptr2 = 0;         // offset +0x10

    m_vtable = &vtable1; // +0x00: set to base vtable

    // Initialize sub-object (calls another cleanup or reset)
    subObjectCleanup(); // FUN_005c0360

    m_field3 = 0;       // offset +0x0C
    m_field2 = 0;       // offset +0x08
    if (m_ptr1 != 0) {  // offset +0x04
        (*(void(__thiscall**)(void*, int))(*allocManager + 4))(m_ptr1, 0);
    }
    m_ptr1 = 0;         // offset +0x04

    m_vtable = &vtable2; // +0x00: final vtable (likely base class)
}