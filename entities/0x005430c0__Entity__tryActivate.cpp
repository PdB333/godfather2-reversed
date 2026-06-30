// FUNC_NAME: Entity::tryActivate
// Function address: 0x005430c0
// Role: Attempts to activate or transition state, returns 1 on success, 0 on failure.

int __thiscall Entity::tryActivate(int param_2)
{
    // Virtual function at vtable+0x1f8 (index 126) - likely isReady()
    bool isReady = (this->*reinterpret_cast<bool (__thiscall Entity::*)(void)>(*(int*)this + 0x1f8))();
    if (isReady)
    {
        // Virtual function at vtable+0x1f4 (index 125) - likely canActivate()
        int canActivate = (this->*reinterpret_cast<int (__thiscall Entity::*)(int)>(*(int*)this + 0x1f4))(param_2);
        if (canActivate == 0)
        {
            // Call vtable[126] again with two arguments
            (this->*reinterpret_cast<void (__thiscall Entity::*)(int, int*)>(*(int*)this + 0x1f8))(param_2, &localVar);
            // Call vtable[132] (0x210) twice
            (this->*reinterpret_cast<void (__thiscall Entity::*)(int, int*)>(*(int*)this + 0x210))(0, &param2Copy);
            (this->*reinterpret_cast<void (__thiscall Entity::*)(int, int)>(*(int*)this + 0x210))(param_2, unaff_retaddr);
            return 1;
        }
    }
    return 0;
}