// FUNC_NAME: Presentation::handleEnterTab
void __thiscall Presentation::handleEnterTab(void *this) {
    int servicePtr;
    
    debugPrint("EnterTab", 0, &someStaticString, 0); // FUN_005a04a0
    if (*(int *)((char *)this + 0x54) == 0) { // m_state == 0
        servicePtr = getSomeService(); // FUN_0079f9d0
        if (servicePtr != 0) {
            registerService(servicePtr); // FUN_009bcb30
            setSomething(0xffffffff); // FUN_009bbc50
            // Jump to vtable entry +0x28 on global object A
            (**(code **)(*DAT_011304fc + 0x28))();
            return;
        }
    }
    else if (*(int *)((char *)this + 0x54) == 1) { // m_state == 1
        servicePtr = getSomeService();
        if (servicePtr != 0) {
            registerService(servicePtr);
            setSomething(0xffffffff);
            // Jump to vtable entry +0x28 on global object B
            (**(code **)(*DAT_01130000 + 0x28))();
            return;
        }
    }
    return;
}