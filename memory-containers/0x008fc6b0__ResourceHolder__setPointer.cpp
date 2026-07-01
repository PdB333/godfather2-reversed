// FUNC_NAME: ResourceHolder::setPointer
void __thiscall ResourceHolder::setPointer(int this, int newValue)
{
    // +0x1c: pointer to a resource (e.g., handle, object)
    if (*(int *)(this + 0x1c) != 0) {
        // Release the old resource before reassigning
        FUN_008fbcf0(); // cleanup/release function
        *(int *)(this + 0x1c) = newValue;
        return;
    }
    *(int *)(this + 0x1c) = newValue;
}