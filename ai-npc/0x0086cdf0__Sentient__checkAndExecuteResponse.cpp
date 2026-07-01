// FUNC_NAME: Sentient::checkAndExecuteResponse
void __thiscall Sentient::checkAndExecuteResponse(Sentient *this) {
    int result;
    
    // Virtual call at vtable offset 0x30 (index 12): likely isAlive() or isActive()
    result = ((int (__thiscall *)(Sentient *))((void **)*(int *)this)[0x30 / 4])(this);
    if (result != 0) {
        // Virtual call at vtable offset 0x24 (index 9): likely canAct() or isControllable()
        result = ((int (__thiscall *)(Sentient *))((void **)*(int *)this)[0x24 / 4])(this);
        // Check flag at offset 0x32, bit 5 (0x20) – possibly disabled/stunned?
        if ((result != 0) && ((((uint8_t *)this)[0x32] >> 5) & 1) == 0) {
            // Called when alive, active/controllable, and not incapacitated/stunned
            FUN_0086c0c0(); // global function – could be performResponse() or triggerAction()
        }
    }
}