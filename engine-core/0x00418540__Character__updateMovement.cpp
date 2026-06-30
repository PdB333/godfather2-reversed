// FUNC_NAME: Character::updateMovement
void __thiscall Character::updateMovement(void* this, void* context) {
    // Get the SimManager singleton from Thread Local Storage (FS:0x2C)
    SimManager* simManager = **reinterpret_cast<SimManager***>(__readfsdword(0x2C));
    
    // Offset +0x04: pointer to internal data (mData)
    char* data = *(char**)(reinterpret_cast<int>(this) + 0x04);
    
    // Context structure: +0x18 is pointer to a type-specific lookup table
    // simManager->typeId (offset +0x08) indexes into that table
    float speedFactor = *(float*)(*(int*)(*(int*)context + 0x18) + 0x68 + *(int*)(simManager + 0x08));
    
    // Get input vector (direction/force from controls/AI)
    float* inputVector = getInputVector();
    
    // Compute new acceleration at offset +0xDC
    // Uses current speed (+0xD8), desired speed (+0xD4), and input
    *(float*)(data + 0xDC) = (*(float*)(data + 0xD8) + *(float*)(data + 0xD4) + *inputVector) * speedFactor * DAT_00e44728;
    
    // If this character is the player, call debug/diagnostic function with input
    if (DAT_012058e8 == data) {
        FUN_0060add0(*(void**)(reinterpret_cast<int>(this) + 0x14), *(void**)(data + 0xC0), inputVector);
    }
    
    // Re-fetch data pointer (could change? but usually same)
    data = *(char**)(reinterpret_cast<int>(this) + 0x04);
    
    // Update target heading/orientation from context table (offset 100 = 0x64)
    unsigned int targetHeading = *(unsigned int*)(*(int*)(*(int*)context + 0x18) + 100 + *(int*)(simManager + 0x08));
    *(unsigned int*)(data + 0x1B0) = targetHeading;
    
    // If player, call another debug function with heading data
    if (DAT_012058e8 == data) {
        FUN_0060aa90(*(void**)(reinterpret_cast<int>(this) + 0x14), *(void**)(data + 0x1AC), targetHeading);
    }
}