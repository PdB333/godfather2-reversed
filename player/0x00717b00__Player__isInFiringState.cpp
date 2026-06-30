// FUNC_NAME: Player::isInFiringState
int __thiscall Player::isInFiringState(void) // This is a member function; "this" is implicitly passed as ecx but Ghidra shows __fastcall with param_1 == this
{
    // param_1 is the "this" pointer
    // +0x338: pointer to some sub-object (e.g., state machine component)
    int* pComponent = *(int**)(this + 0x338); 
    if (pComponent != nullptr)
    {
        // The sub-object is embedded 0x48 bytes inside its parent
        // So subtracting 0x48 gives the parent object's base
        int* parentObj = (int*)((char*)pComponent - 0x48);
        if (parentObj != nullptr)
        {
            int result = 0;
            // Call virtual function at vtable+0x10 with an ID hash and output argument
            // This likely returns a pointer to a specific state object based on the hash (0x383225a1)
            char callResult = (*(char(__thiscall**)(int*, int*))(*(int*)parentObj + 0x10))(parentObj, (int*)&result);
            if (callResult != 0 && result != 0)
            {
                // +0x1b8c: large offset into a state object, probably a field storing current state
                // Values 1,2,3 represent firing sub-states (e.g., aiming, shooting, recoil)
                char stateByte = *(char*)(result + 0x1b8c);
                if (stateByte == 1 || stateByte == 2 || stateByte == 3)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}