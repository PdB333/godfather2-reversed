// FUNC_NAME: GhostReplicationSlotArray::setSlotFlags
void __thiscall GhostReplicationSlotArray::setSlotFlags(int this, byte slotIndex, byte flags)
{
    // Structure size: 0x168 bytes per slot
    GhostReplicationSlot* slot = reinterpret_cast<GhostReplicationSlot*>(
        reinterpret_cast<uint>(this) + (uint)slotIndex * 0x168
    );

    // Set two flag/state fields to the same value
    slot->field_0x47 = flags; // +0x47 (likely a state/ack flag)
    slot->field_0x5f = flags; // +0x5f (likely a duplicate or related flag)
}