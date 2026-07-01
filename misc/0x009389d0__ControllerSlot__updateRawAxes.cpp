// FUNC_NAME: ControllerSlot::updateRawAxes
void __fastcall ControllerSlot::updateRawAxes(ControllerSlot* this)
{
    // FUN_0060d850: returns current controller slot index (e.g., for player 1)
    int slotIdx = getCurrentSlotIndex();
    
    // FUN_00606370: retrieves raw controller state structure for that slot
    RawControllerState* rawState = getRawState(slotIdx);
    
    // Offset +0x08: X-axis float, +0x0C: Y-axis float
    // Raw state has unsigned short at +0x02 (X) and +0x04 (Y)
    this->axisX = (float)rawState->rawX;   // +0x02
    this->axisY = (float)rawState->rawY;   // +0x04
}

// Helper struct for raw controller state (assumed layout)
struct RawControllerState {
    /* +0x00 */ uint16_t padding;
    /* +0x02 */ uint16_t rawX;
    /* +0x04 */ uint16_t rawY;
    // ... potentially more fields
};