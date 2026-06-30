// FUNC_NAME: BaseObject::checkAndInitialize
void __thiscall BaseObject::checkAndInitialize(BaseObject* this)
{
    // +0x161: byte flag indicating whether initialization has been performed
    if (*(char*)((int)this + 0x161) == '\0') {
        // Run initialization logic if flag is not set
        FUN_00470460();
    }
    // If flag is already nonzero, do nothing
}