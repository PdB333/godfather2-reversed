// FUNC_NAME: ConsumeQuantity
// 0x006b3b10: Decrements a quantity value (offset +0x74) by the given amount,
// capped to the current value. Calls a notification function afterwards.

void __thiscall ConsumeQuantity(int this, uint amount)
{
    uint current = *(uint *)(this + 0x74);  // +0x74: quantity field
    if (current < amount) {
        amount = current;
    }
    *(uint *)(this + 0x74) = current - amount;
    NotifyQuantityChanged();  // 0x006b2f70: likely updates UI or triggers depletion
}