// FUNC_NAME: SomeManager::CheckAndSetup
bool SomeManager::CheckAndSetup()
// Function at 0x006ab960, __thiscall, returns bool (actually char)
// Manages a one-time initialization of a pointer (+0x60) and a flag (+0x9a)
{
    char result;
    int buffer[2];   // local_c, padded for alignment
    // +0x9a: flag indicating whether setup is complete
    *(char*)(this + 0x9a) = 0;  // clear flag

    result = FUN_006f6eb0(this);  // external function, likely checks readiness

    if (result == 0) {
        // Check if flag is still 0 (it should be) and pointer at +0x60 is non-null
        if (*(char*)(this + 0x9a) == 0 && *(int*)(this + 0x60) != 0) {
            buffer[0] = *(int*)(this + 0x60);  // copy the pointer
            buffer[1] = 0;                     // second word zero
            // Note: local_4 (cVar1) is stored but seems unused; probably the cast result
            char local_4 = result;             // result is 0 here
            FUN_00408a00(buffer, 0);           // cleanup/free the pointer
        }
        *(char*)(this + 0x9a) = 1;  // mark setup as done
    }
    return result;
}