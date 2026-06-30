// FUNC_NAME: Entity::delegateToComponent
void __thiscall Entity::delegateToComponent(undefined4 param2, undefined4 param3, undefined4 param4)
{
    // Pre-delegation hook (likely debugging or preparation)
    FUN_009f2000();
    // Call through delegate object at this+0xD0
    // The delegate's vtable entry at offset 0x54 is a method taking three additional parameters
    (**(code **)(*(int *)((char *)this + 0xD0) + 0x54))(param2, param3, param4);
}