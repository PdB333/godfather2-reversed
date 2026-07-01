// FUNC_NAME: MultiTrackStream::releaseTracks
void __thiscall MultiTrackStream::releaseTracks()
{
    // Release first track object (offset +0x7C)
    FUN_0042c190(*(int*)((char*)this + 0x7C));
    // Release second track object (offset +0x80)
    FUN_0042c1a0(*(int*)((char*)this + 0x80));
}