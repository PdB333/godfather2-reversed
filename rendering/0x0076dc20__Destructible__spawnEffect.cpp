// FUNC_NAME: Destructible::spawnEffect
void __thiscall Destructible::spawnEffect() {
    // Get pointer to inner object at offset 0x5c
    InnerData* pData = *(InnerData**)((int)this + 0x5c);
    
    // Check if any of the four effect flags are set (offsets 0x82f-0x832)
    if (pData->effectFlags[0] || pData->effectFlags[1] || pData->effectFlags[2] || pData->effectFlags[3]) {
        // Get current game time or a unique identifier
        int handle = GetCurrentHandle(); // FUN_00471610
        
        char buffer[76]; // static buffer for formatting
        FormatString(buffer, handle); // FUN_0044b4e0
        
        // Virtual call on inner object: spawn something (vtable+0x58)
        // Parameters: (0, this, -1, 0) – likely type/count/source
        pData->vtable->spawnSomething(0, pData, 0xFFFFFFFF, 0);
        
        // Allocate an effect object using the effect flags and formatted string
        Effect* pEffect = AllocateEffect(&pEffect, &pData->effectFlags[0], buffer, handle); // FUN_004df330
        if (pEffect) {
            pEffect->field_8 = 0; // Clear a field (likely timer or state)
        }
    }
}