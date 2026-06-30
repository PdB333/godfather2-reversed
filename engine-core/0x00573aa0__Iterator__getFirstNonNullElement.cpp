// FUNC_NAME: Iterator::getFirstNonNullElement
// Reconstructed from Ghidra decompile of FUN_00573aa0
// Role: Iterates over a sparse int array (int*) stored in a container, finds the first non-zero element,
// resets internal cursor to start each call, and updates current value and index.
// The caller is expected to check this->m_currentValue after call.

void __thiscall Iterator::getFirstNonNullElement(void)
{
    Container* container = this->m_container;    // this+0x00: pointer to container
    this->m_index = 0;                           // this+0x04: current index in array
    this->m_currentValue = 0;                    // this+0x08: value found (0 if none)

    if (container != nullptr)
    {
        do
        {
            int idx = this->m_index;
            if (idx >= container->count)         // container+0x04: number of elements
            {
                return;
            }
            int value = container->data[idx];    // container+0x00: pointer to int array
            this->m_currentValue = value;
            this->m_index = idx + 1;
        } while (this->m_currentValue == 0);
    }
}