// FUNC_NAME: SomeClass::shutdown
void __thiscall SomeClass::shutdown(void* pResource1, void* pResource2)
{
    // release two resources (likely pointers to allocated memory)
    releaseResource(pResource1); // FUN_004d3d90
    releaseResource(pResource2); // FUN_004d3d90

    // mark object as shutdown/disabled; offset +0x09 is a boolean flag
    *(uint8_t*)(this + 9) = 1;
}