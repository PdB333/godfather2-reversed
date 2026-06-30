// FUNC_NAME: CharacterManager::updateCharacters
void __thiscall CharacterManager::updateCharacters(void)
{
    int iVar2;
    uint uVar3;
    double dVar5;
    float fVar6;
    int index;
    float speed;
    // Structure at this+0x10 is array of CharacterData of size 0x1d0
    // Number of characters at this+0x154
    CharacterData* pChar;
    
    // First phase: set physics update flag, call start/end physics
    uVar3 = 0;
    if (*(int*)(this + 0x154) != 0) {
        index = 0;
        do {
            pChar = *(CharacterData**)(this + 0x10) + index;
            pChar->updateFlag = 1;            // +0x1c0
            FUN_004a23c0();                    // physicsBegin
            FUN_004a25c0(pChar);               // updatePhysics
            pChar->updateFlag = 0;             // +0x1c0
            FUN_004a2e20();                    // physicsEnd
            FUN_004a2f10(pChar);               // finalizePhysics
            index++;                           // incremented by 1 (but pChar advances by 0x1d0 bytes)
            uVar3++;
        } while (uVar3 < *(uint*)(this + 0x154));
    }
    
    // Second phase: handle speed and network update
    uVar3 = 0;
    if (*(int*)(this + 0x154) != 0) {
        index = 0;
        if (*(int*)(this + 0x154) == 0) goto LAB_004253f1;
        do {
            pChar = *(CharacterData**)(this + 0x10) + index;
            // Copy first 32 bytes of structure (position + orientation?)
            localTransform.set(pChar->transform); // +0x00
            // Copy next 16 bytes at +0x20 (velocity?)
            localVelocity.set(pChar->velocity);   // +0x20
            // float at +0x30 (current speed magnitude?)
            speed = pChar->speed;                 // +0x30
            
            // If character state is 2 (e.g., moving/running?)
            if (*(int*)(pChar + 0x38) == 2) {
                fVar6 = DAT_00e447a8;             // default multiplier
                if (*(int*)(pChar + 0x34) == 1) {
                    fVar6 = DAT_00e447ac;         // alternative multiplier for movement type 1
                }
                // Apply game speed scale
                dVar5 = (double)(speed * DAT_00e2cd54);
                FUN_00b9c041();                   // math::sin? or vector op
                dVar5 = (double)(((float)dVar5 / fVar6) * DAT_01205878);
                FUN_00b9d99d();                   // math::cos? or other operation
                speed = (float)dVar5 * DAT_00e2b04c; // clamp/multiply
            }
            // Send update to network/system
            FUN_00425ea0(uVar3, &localTransform, speed);
LAB_004253f1:
            uVar3++;
            index++;
        } while (uVar3 < *(uint*)(this + 0x154));
    }
    return;
}