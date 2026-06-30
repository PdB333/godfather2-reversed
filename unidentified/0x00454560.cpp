// FUN_00454560: SomeClass::releaseMember
void __thiscall SomeClass::releaseMember()
{
    // Call cleanup function on the sub-object stored at offset +0x14
    subObjectRelease(*(void**)(this + 0x14));
}