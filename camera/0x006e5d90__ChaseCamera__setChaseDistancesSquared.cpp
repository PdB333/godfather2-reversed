// FUNC_NAME: ChaseCamera::setChaseDistancesSquared
void __thiscall ChaseCamera::setChaseDistancesSquared(ChaseCamera *this, float nearDist, float farDist)
{
    // +0x58: squared near distance
    // +0x5c: squared far distance
    *(float *)((int)this + 0x58) = nearDist * nearDist;
    *(float *)((int)this + 0x5c) = farDist * farDist;
    return;
}