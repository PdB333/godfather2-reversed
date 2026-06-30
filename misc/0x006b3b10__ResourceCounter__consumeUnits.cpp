// FUNC_NAME: ResourceCounter::consumeUnits
void __thiscall ResourceCounter::consumeUnits(int thisPtr, unsigned int amount)
{
    // +0x74 holds the current available count
    unsigned int current = *(unsigned int *)(thisPtr + 0x74);
    if (current < amount) {
        amount = current; // clamp to available amount
    }
    *(unsigned int *)(thisPtr + 0x74) = current - amount;
    // Notify or update after consumption
    FUN_006b2f70(); // likely triggers a state update or callback
    return;
}