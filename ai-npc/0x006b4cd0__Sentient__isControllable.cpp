// FUNC_NAME: Sentient::isControllable
bool __fastcall Sentient::isControllable(Sentient* this)
{
    void* controllingEntity; // eax, from this+0x16c
    void* damageStatus; // eax, from call to damage component
    bool result;

    result = false;
    controllingEntity = *(void**)(this + 0x16c); // pointer to entity currently controlling this

    // Check: not in special states, not dead, and has a damage component
    if ((((*(uint32_t*)(this + 0x34) & 0x120000) == 0) &&      // bit 17 and 20 clear
         ((*(uint8_t*)(this + 0x34) & 1) == 0)) &&             // bit0 clear
        (*(void**)(this + 0x40) != nullptr))                     // damage component exists
    {
        damageStatus = FUN_008c74d0(*(void**)(this + 0x40));  // Get status pointer from damage component
        if ((damageStatus != nullptr) &&
            ((~(uint8_t)(*(uint32_t*)((uint8_t*)damageStatus + 0x84) >> 5) & 1) != 0) && // bit5 of damage status = 0 (alive)
            (controllingEntity == nullptr) &&                                             // no one else controlling
            ((*(uint32_t*)(this + 0x34) >> 0x1c & 1) == 0))                              // bit28 clear
        {
            if ((*(int32_t*)(this + 0xc4) == 1) ||          // control state is 1 (active)
                (*(int32_t*)(this + 0xc4) == 0) ||          // or control state is 0 (idle)
                ((*(uint32_t*)(this + 0x34) >> 10 & 1) != 0)) // or bit10 set (force controllable)
            {
                result = true;
            }
        }
    }
    return result;
}