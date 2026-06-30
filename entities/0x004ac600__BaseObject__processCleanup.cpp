// FUNC_NAME: BaseObject::processCleanup
// Function address: 0x004ac600
// Role: Wrapper that always calls internal cleanup function.
// The field at +0x48 is checked but does not alter the logic; may be a debug/hook leftover.

void __thiscall BaseObject::processCleanup()
{
    if (this->m_someFlag) { // +0x48
        internalCleanup(); // Calls FUN_0045f2a0
        return;
    }
    internalCleanup();
    return;
}