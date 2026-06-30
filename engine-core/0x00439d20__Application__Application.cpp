// FUNC_NAME: Application::Application
void* __thiscall Application::Application(Application* this, void* parentObj, int param_3) {
    this->field_4 = 1;          // +0x04: unknown flag, initialized to 1
    this->field_8 = 0;          // +0x08: counter or handle
    this->field_C = (int*)&PTR_LAB_00e30ed8; // +0x0C: pointer to a label or string table
    gpApplication = this;       // +0x00: vtable pointer set earlier? Actually set after global assign
    this->vtable = (void**)&PTR_FUN_00e30ec4; // +0x00: vtable pointer (overwrites previous assignment)
    this->field_C = (int*)&PTR_LAB_00e30ed4; // +0x0C: overwritten with different pointer
    this->field_10 = 0;         // +0x10: some null field
    this->field_14 = parentObj; // +0x14: pointer to parent/owner object

    if (parentObj != nullptr) {
        // Call virtual method at vtable+8 (index 2) on parent
        (*(void(__thiscall**)(void*))(*((int*)parentObj) + 8))(parentObj);

        // Allocate first subsystem object (size 0x10)
        void* subsys1 = (void*)new(0x10);
        if (subsys1 != nullptr) {
            gpSubsys1 = subsys1;
            *(void**)subsys1 = &PTR_FUN_00e3f50c; // vtable
            *(int*)((int)subsys1 + 4) = 0;         // field_4
            *(int*)((int)subsys1 + 8) = 0;         // field_8
            *(int*)((int)subsys1 + 12) = 0;        // field_C
        }

        // Call setup on parent with param_3
        FUN_005e33e0(parentObj, param_3);

        // Allocate second subsystem object (size 0x1c)
        void* subsys2 = (void*)new(0x1c);
        if (subsys2 != nullptr) {
            *(void**)subsys2 = &PTR_FUN_00e36614; // vtable
            *(void**)((int)subsys2 + 4) = &PTR_LAB_00e36618; // field_4 (another label)
            *(int*)((int)subsys2 + 8) = 1;        // field_8
            *(int*)((int)subsys2 + 12) = 0;       // field_C
            gpSubsys2 = subsys2;
            *(int*)((int)subsys2 + 16) = 0;       // field_10
            *(int*)((int)subsys2 + 20) = 0;       // field_14
            *(int*)((int)subsys2 + 24) = 0;       // field_18
        }

        FUN_004c9250(gpSubsys2); // Initialize second subsystem
    }

    // Optionally register this object as a listener/callback for two global events
    if (DAT_01206940 != 0) {
        FUN_00407e60(this, &DAT_01206940); // Register hook for event 1
    }
    if (DAT_012069dc != 0) {
        FUN_00407e60(this, &DAT_012069dc); // Register hook for event 2
    }

    return this;
}