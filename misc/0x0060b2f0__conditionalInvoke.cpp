// FUNC_NAME: conditionalInvoke
// Address: 0x0060b2f0
// Role: Conditional call – invokes the function at 0x006063b0 only when param2 is non-zero. param1 is unused (likely a placeholder or this-pointer that is ignored by the implementation).
void __cdecl conditionalInvoke(int param1, int param2)
{
    if (param2 != 0)
    {
        FUN_006063b0(); // actual handler (address 0x006063b0)
    }
}