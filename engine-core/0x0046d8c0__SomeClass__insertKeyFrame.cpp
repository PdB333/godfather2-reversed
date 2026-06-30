// FUNC_NAME: SomeClass::insertKeyFrame
void __thiscall SomeClass::insertKeyFrame(void* this, void* dataSource, uint key, uint value)
{
    uint currentKey;
    int slotOffset;
    uint slotIndex;

    // Get slot index based on current byte at +0x61 (m_nextSlotIndex)
    slotIndex = *(byte*)((int)this + 0x61);
    slotOffset = slotIndex * 0x30;

    // Read the key stored in the current slot at +0x24 (relative to this)
    currentKey = *(uint*)(slotOffset + 0x24 + (int)this);

    // If the buffer is empty (m_count == 0 at +0x60) or the new key is larger than the stored key
    if ((currentKey < key) || (*(char*)((int)this + 0x60) == '\0'))
    {
        // Increment the slot index (wrap-around with sign bit preservation)
        slotIndex = (*(byte*)((int)this + 0x61) + 1) & 0x80000001;
        *(char*)((int)this + 0x61) = (char)slotIndex;

        // Compute new slot offset with the updated index
        slotOffset = slotIndex * 0x30;

        // Initialize the new slot (calls internal function)
        SomeHelper::initSlot(dataSource, (void*)((int)this + slotOffset));

        // Copy 16 bytes from dataSource+0x30 into the slot's vector data at offsets +0x10 through +0x1c
        *(undefined4*)(slotOffset + 0x10 + (int)this) = *(undefined4*)((int)dataSource + 0x30);
        *(undefined4*)(slotOffset + 0x14 + (int)this) = *(undefined4*)((int)dataSource + 0x34);
        *(undefined4*)(slotOffset + 0x18 + (int)this) = *(undefined4*)((int)dataSource + 0x38);
        *(undefined4*)(slotOffset + 0x1c + (int)this) = *(undefined4*)((int)dataSource + 0x3c);

        // Overwrite the last component with 0 (vector/quaternion normalization)
        *(undefined4*)(slotOffset + 0x1c + (int)this) = 0;

        // Store the key and value in the slot
        *(uint*)(slotOffset + 0x24 + (int)this) = key;
        *(undefined4*)(slotOffset + 0x20 + (int)this) = value;

        // Increment count (m_count at +0x60) but cap at 2?
        uint newCount = *(byte*)((int)this + 0x60) + 1;
        if (1 < newCount) {
            newCount = 2;
        }
        *(char*)((int)this + 0x60) = (char)newCount;
    }
    else if (key == currentKey)
    {
        // If the key matches the last slot's key, update the value in that slot
        SomeHelper::updateSlot(dataSource, (void*)(slotOffset + (int)this));
        *(undefined4*)(slotOffset + 0x20 + (int)this) = value;
    }
    // If key is smaller than currentKey, do nothing (no insertion in middle)
}