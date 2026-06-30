// FUNC_NAME: ThreadSlot::setValue
// Address: 0x004aaf60
// Role: Stores an integer into per-thread data array indexed by this->mIndex (offset 0x18).
// Uses Windows TIB (Thread Information Block) via fs:[0x2C] to locate the thread-local data block.
// The data block contains a pointer at offset 8 which acts as base for an array at offset 0x68.

void __thiscall ThreadSlot::setValue(int this, int value)
{
    // Fetch the thread-local storage base pointer from the TIB.
    // In Windows x86, fs:[0x2C] points to the TLS array. Dereferencing twice with offset +8 yields the base address.
    int tlsBaseAddress = *(int*)(*(int**)(((int)&__readfsdword(0x2C)) + 0) + 8); // Equivalent to *(int*)(**(int**)fs:[0x2C] + 8)
    // Calculate the target address: base + 0x68 (array start) + this->mIndex (offset 0x18)
    int* target = (int*)(tlsBaseAddress + 0x68 + *(int*)(this + 0x18));
    *target = value;
}