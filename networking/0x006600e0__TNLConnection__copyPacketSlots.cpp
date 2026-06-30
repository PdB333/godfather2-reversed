// FUNC_NAME: TNLConnection::copyPacketSlots
// Address: 0x006600e0
// Copies an array of uint32 values from src into the internal slot array (offset +0x8),
// but only for slots that already contain a non-zero value.
// Parameters: this in EDI, count in ESI, src as stack param (param_1).
void __thiscall TNLConnection::copyPacketSlots(TNLConnection* this, uint count, const int* src)
{
    // +0x8: pointer to an array of ints (slot array)
    int* slotArray = *(int**)((char*)this + 8);
    if (slotArray == nullptr) {
        return;
    }
    for (uint i = 0; i < count; ++i) {
        if (slotArray[i] != 0) {
            slotArray[i] = src[i];
        }
    }
}