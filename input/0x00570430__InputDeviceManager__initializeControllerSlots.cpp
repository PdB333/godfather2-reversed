// FUNC_NAME: InputDeviceManager::initializeControllerSlots
void __thiscall InputDeviceManager::initializeControllerSlots(InputDeviceManager* this, void* config, int slotCount)
{
    // +0xB8: m_pControllerData - pointer to array of controller state structures (0x40 bytes each)
    // +0xB4: m_pSlotBuffer - buffer allocated per slot (filled with 0xFF initially)
    // +0xB0: m_numSlots - maximum number of slots (short)
    this->m_pControllerData = (ControllerState*)in_EAX; // in_EAX is a pre-allocated pointer or returned value

    if (this->m_pSlotBuffer == 0) {
        uint local_1c[3] = {0,0,0}; // temp for allocation
        this->m_pSlotBuffer = (uint*)(*(code**)(DAT_0120556c))(this->m_numSlots, &local_1c); // call allocation function
    }

    // Fill slot buffer with 0xFF
    for (int i = 0; i < this->m_numSlots; i++) {
        ((char*)this->m_pSlotBuffer)[i] = 0xFF;
    }

    // Initialize controller state structures
    for (int i = 0; i < slotCount; i++) {
        ControllerState* state = &this->m_pControllerData[i];
        state->field_0 = kDefaultControllerValue;
        state->field_4 = 0;
        state->field_8 = 0;
        state->field_C = 0;
        state->field_10 = 0;
        state->field_14 = kDefaultControllerValue;
        state->field_18 = 0;
        state->field_1C = 0;
        state->field_20 = 0;
        state->field_24 = 0;
        state->field_28 = kDefaultControllerValue;
        state->field_2C = 0;
        state->field_30 = 0;
        state->field_34 = 0;
        state->field_38 = 0;
        state->field_3C = kDefaultControllerValue;
    }

    // If config indicates a special mode and slotCount matches max, assign sequential indices
    if (*(int*)(config + 0x38) == 1 && slotCount == this->m_numSlots) {
        for (int i = 0; i < slotCount; i++) {
            ((char*)this->m_pSlotBuffer)[i] = (char)i;
        }
    } else {
        FUN_005703d0(config); // build controller data from config
    }
}