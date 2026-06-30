// FUNC_NAME: Entity::initialize
int __thiscall Entity::initialize(byte flag)
{
    // Global system/engine initialization (e.g. memory system, object pools)
    ::globalSystemInit();

    // If bit 0 of flag is set, perform secondary initialization on this instance
    // (likely to set up derived class data or attach to managers)
    if (flag & 1)
    {
        this->initDerivedMembers();
    }

    return reinterpret_cast<int>(this);
}