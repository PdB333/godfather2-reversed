// FUNC_NAME: CommandQueue::enqueueAction
void __thiscall CommandQueue::enqueueAction(bool flag)
{
    // Check if this queue is enabled (offset 0x164)
    if (this->m_enabled != 0)
    {
        // Global write pointer for the command buffer (stored at DAT_01206880 + 0x14)
        uint32_t*& writePtr = *(uint32_t**)(DAT_01206880 + 0x14);

        // Write the vtable/type descriptor for the command
        *writePtr = (uint32_t)&PTR_LAB_0110ba94;
        writePtr++;

        // Write a pointer to the data at this + 0x54 (e.g., an object or payload)
        *writePtr = (uint32_t)(this + 0x54);
        writePtr++;

        // Write the boolean flag
        *(bool*)writePtr = flag;
        writePtr++;

        // Align the write pointer to the next 4-byte boundary
        writePtr = (uint32_t*)((uint32_t)writePtr & 0xFFFFFFFC);
    }
}