// FUNC_NAME: FlagSet::getFlagMask
uint __thiscall FlagSet::getFlagMask(int *this, uint flagMask)
{
    bool isSet;
    uint output;

    output = 0;
    isSet = (**(code (__thiscall **)(int *, uint, uint *))(*(int *)this + 0x10))(this, flagMask, &output);
    return -(uint)isSet & flagMask;
}