// FUNC_NAME: Entity::addToAccumulator
void __thiscall Entity::addToAccumulator(int value)
{
    // +0x8c: accumulated value (e.g., score, time, count)
    *(int *)(this + 0x8c) = *(int *)(this + 0x8c) + value;
}