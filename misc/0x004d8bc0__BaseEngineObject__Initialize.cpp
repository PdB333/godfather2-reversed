// FUNC_NAME: BaseEngineObject::Initialize
int __fastcall BaseEngineObject::Initialize(BaseEngineObject* this)
{
    // Check child pointer at offset +0x20 (likely a child/parent pointer)
    if (*(int*)((char*)this + 0x20) != 0) {
        // Recursive call – the constant 1 is likely a misinterpretation (could be the child pointer)
        // Ghidra shows literal 1; may be a decompilation artifact
        BaseEngineObject::Initialize((BaseEngineObject*)1);
    }
    // Call base initialization function (likely sets up object fields)
    sub_009c8eb0(this);
    return (int)this;
}