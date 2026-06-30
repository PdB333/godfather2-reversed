// FUNC_NAME: Entity::tick
void __fastcall Entity::tick(int thisPtr)
{
    // Static cleanup / reference management (e.g., recycle deferred allocations)
    FUN_009f2000();

    // +0xd0: pointer to an embedded behavior/state machine object
    // vtable +0x48: virtual update/tick method for that sub-object
    int* behaviorPtr = reinterpret_cast<int*>(thisPtr + 0xd0);
    int vtable = *behaviorPtr;
    typedef void (__thiscall* BehaviorTickFunc)(int);
    BehaviorTickFunc tickFunc = reinterpret_cast<BehaviorTickFunc>(vtable + 0x48);
    tickFunc(*behaviorPtr);
}