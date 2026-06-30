// FUNC_NAME: EffectBase::update
// Function at 0x006db410: Main update/init for an effect (likely bullet/trail) with state machine (states: 1=active, 2=updating timer, 3=finished)

void __thiscall EffectBase::update(Vector4* inPos, int effectIndex)
{
    float currentTime = g_globalTime; // _DAT_00d5780c (global frame time)
    
    if (this->state == 2) // State 2: updating timer before finalization
    {
        float fScale = this->field_0x1ac; // Some scaling factor (duration?)
        float fElapsed = this->field_0x1b0; // Current elapsed (or accumulated value)
        float fNewRatio = currentTime - (fElapsed / fScale);
        
        this->state = 3; // Mark as finished
        this->field_0x1b0 = fNewRatio * fScale;
        return;
    }
    
    if (this->state != 3) // Not finished, so perform initialization
    {
        // Retrieve effect source from global manager array by index
        int* managerPtr = *(int**)(DAT_012233a0 + 4); // Base of object table
        int* srcObj = (int*)(managerPtr[effectIndex]); // Pointer to source object
        if (srcObj == (int*)0)
            srcObj = (int*)0;
        else
            srcObj = (int*)((char*)srcObj - 0x1F30); // Adjust pointer (handle to actual object)
        
        // Call some initialization helper (e.g., setup trajectory)
        FUN_006d68e0((int)srcObj);
        
        // Store the provided position (likely initial start point)
        this->startPos.x = inPos->x;
        this->startPos.y = inPos->y;
        this->startPos.z = inPos->z;
        this->startPos.w = inPos->w; // +0x11C
        
        // Store offset-based position (relative to some origin, maybe for trail)
        this->offsetPos.x = inPos->x + 0.0f;
        this->offsetPos.y = inPos->y + currentTime;
        this->offsetPos.z = inPos->z + 0.0f;
        this->offsetPos.w = 0.0f; // +0x17C
        
        // Another initialization call (e.g., set up visual or sound)
        FUN_006db310();
        
        // Set flags and state
        this->flag0x1a0 = 1; // Some active flag
        this->byte0x08 = 0; // Unknown field
        this->field_0x1a8 = 0; // Some counter or timer
        this->state = 1; // Set state to active
    }
}
