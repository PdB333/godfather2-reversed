// FUNC_NAME: ControllerState::selectAxisOutputPair
// Address: 0x005dd8a0
// Role: Selects between two 2D axis value pairs (raw vs processed) based on button state masks and a per-object filter.
// Input: mask (bitfield of buttons), out1 (output pointer), out2 (output pointer in EDI)
// Global masks used:
//   gAxisCombineMask (0x00f15b80) - mask to combine with input
//   gAxisDeadZoneMask (0x00f15b78 | 0x00f15b7c) - dead zone indicators
//   gButtonOverrideMask (0x012056c0) - override condition
// Member fields:
//   +0x28c (mAxisRawX), +0x290 (mAxisRawY)
//   +0x284 (mAxisProcessedX), +0x288 (mAxisProcessedY)
//   +0x2BC (mButtonMask) - per-object allowed button mask

void __thiscall ControllerState::selectAxisOutputPair(uint this, uint mask, uint32_t* out1, uint32_t* out2) // out2 passed in EDI
{
    uint uVar1;
    
    mask = gAxisCombineMask & mask;  // DAT_00f15b80
    uVar1 = (gAxisDeadZoneMask) & mask;  // DAT_00f15b78 | DAT_00f15b7c
    
    if ((uVar1 != gAxisDeadZoneMask) &&
        ((gButtonOverrideMask & mask) != 0 ||
         (uVar1 != 0 && ((*(uint*)(this + 0x2BC) & mask) == 0))))
    {
        *out1 = *(uint32_t*)(this + 0x28c);  // mAxisRawX
        *out2 = *(uint32_t*)(this + 0x290);  // mAxisRawY
        return;
    }
    
    *out1 = *(uint32_t*)(this + 0x284);  // mAxisProcessedX
    *out2 = *(uint32_t*)(this + 0x288);  // mAxisProcessedY
}