// FUNC_NAME: unknownClass::initializeAndCallVirtual
// Original address: 0x00541780
// Identified role: Calls a static initialization function (FUN_009f2000) and then performs an indirect call via a virtual method pointer.
// This may be part of a framework-level initialization or update step.

void __fastcall unknownClass::initializeAndCallVirtual(void* this)
{
    // Global initialization (likely engine-wide)
    FUN_009f2000();

    // Call virtual method at offset 0x50 from the interface pointer stored at offset 0xD0
    void* interfacePtr = *(void**)((int)this + 0xD0);
    void (*virtualMethod)() = *(void(**)())((int)interfacePtr + 0x50);
    virtualMethod();
}