// FUNC_NAME: GodfatherGameManager::getMissionFactor
float __fastcall GodfatherGameManager::getMissionFactor(GodfatherGameManager* this)
{
    // +0x2004: mission state (0 = inactive, 0x48 = completed, other = active)
    if (this->field_2004 != 0 && this->field_2004 != 0x48)
    {
        return FUN_007234c0(8);  // returns a factor based on current mission status
    }
    return 0.0f;
}