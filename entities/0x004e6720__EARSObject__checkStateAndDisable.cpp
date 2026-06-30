// FUNC_NAME: EARSObject::checkStateAndDisable
void __thiscall EARSObject::checkStateAndDisable()
{
    // Check if state at +0x44 is 1 and +0x48 is 0 (active/idle).
    // If not, disable the object via its handle.
    if ((*(int *)(this + 0x44) != 1) || (*(int *)(this + 0x48) != 0))
    {
        // +0x4 is the object handle or pointer; second param 0 = disable/deactivate.
        setObjectEnabled(*(int *)(this + 4), false);
    }
}