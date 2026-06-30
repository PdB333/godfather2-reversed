// FUNC_NAME: InputManager::onControllerDisconnect
void __thiscall InputManager::onControllerDisconnect(int controllerId)
{
    // this+0x1a (offset 0x68): pointer to array of controller entries
    // this+0x1b (offset 0x6C): number of entries
    // each entry is 16 bytes: int id at +0x00, uint32_t flags at +0x04, two unused ints

    uint32_t i = 0;
    if (this->m_nControllerCount != 0)
    {
        int *entryBase = reinterpret_cast<int *>(this->m_pControllerArray);
        do
        {
            if (*entryBase == controllerId)
            {
                // Clear bits 8-11? (mask 0xF0C7 = 1111000011000111)
                // This likely removes connection/active flags
                *reinterpret_cast<uint16_t *>(entryBase + 1) &= 0xF0C7;
                FUN_004a62b0(); // internal update routine
                break;
            }
            i++;
            entryBase += 4; // stride of 16 bytes
        } while (i < static_cast<uint32_t>(this->m_nControllerCount));
    }

    // vtable at this[0], method at +0x18 (entry 6) checks overall controller state
    typedef bool (__thiscall *VirtFunc)(InputManager *);
    VirtFunc checkFunc = reinterpret_cast<VirtFunc>((*reinterpret_cast<unsigned int **>(this))[0x18 / 4]);

    // Clear global "any connected" flag (bit 0 at offset 0x80)
    this->m_nControllerStatusFlags &= ~1;

    bool connected = checkFunc(this);
    if (connected)
    {
        this->m_nControllerStatusFlags |= 1;
    }

    FUN_004a6710(); // notify subsystems
    FUN_004a6210(); // recount active controllers
}