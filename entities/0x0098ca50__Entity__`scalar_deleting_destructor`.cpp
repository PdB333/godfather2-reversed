// FUNC_NAME: Entity::`scalar deleting destructor`
int __thiscall Entity::`scalar deleting destructor`(byte deletingFlag)
{
    // FUN_0098c4a0 likely performs the complete object destruction (calls destructors of base and members).
    // The decompiled shows a call with no arguments; this may be a static cleanup function or the result of
    // the decompiler simplifying a member function call. In practice, it is called on 'this'.
    baseCleanupFunction();

    if (deletingFlag & 1) {
        // If the flag's LSB is set, free the memory backing this object.
        operatorDelete(this); // FUN_005c4480
    }

    return (int)this;
}