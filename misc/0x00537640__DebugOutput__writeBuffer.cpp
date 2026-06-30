// FUNC_NAME: DebugOutput::writeBuffer
void __fastcall DebugOutput::writeBuffer(DebugOutput* this)
{
    // Write 4-byte block from global buffer to log (flags: 0x40000000)
    FUN_0060c8d0(0, &gLogBuffer, 4, 0, 0x40000000, this);
}