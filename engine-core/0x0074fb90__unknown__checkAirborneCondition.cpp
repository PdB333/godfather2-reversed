// FUNC_NAME: unknown::checkAirborneCondition
bool __fastcall checkAirborneCondition(void* thisPtr)
{
    // Offset +0x5c: float speed (e.g., vertical or overall speed)
    // Offset +0x54: uint32_t some counter (e.g., number of wheels off ground, frame counter)
    // Global threshold DAT_01205228: e.g., airborne speed threshold
    
    float speed = *(float*)((int)thisPtr + 0x5c);
    uint32_t counter = *(uint32_t*)((int)thisPtr + 0x54);
    
    if (DAT_01205228 < speed && counter > 4)
        return true;
    else
        return false;
}