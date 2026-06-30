// FUNC_NAME: MovementController::update

int* __thiscall MovementController::update(int this, float deltaTime)
{
    // Thread-local storage handling (simplified)
    int* fsBase = *(int**)(__readgsdword(0x2c));
    int fsPrev = *fsBase;

    // Check if movement is disabled via flag at entity state offset 0x10 + entityOffset
    if ((*(byte*)(*(int*)(this + 0x10) + *(int*)(fsPrev + 8)) & 1) == 0)
    {
        // Pointer to movement parameters (acceleration, max speed, etc.)
        int* moveParams = *(int**)(this + 0x24);
        
        // Current velocity squared
        float currentSpeedSq = *(float*)(this + 0x28) * *(float*)(this + 0x28);
        
        // Handle acceleration
        if (*(float*)(moveParams + 0x20) == 0.0f) // acceleration is zero? 
        {
            *(undefined4*)(this + 0x30) = 0;
        }
        else
        {
            *(float*)(this + 0x30) = currentSpeedSq;
            // Apply acceleration: new velocity = old + accel * dt
            float newSpeed = deltaTime * *(float*)(moveParams + 0x20) + *(float*)(this + 0x28);
            *(float*)(this + 0x28) = newSpeed;
            currentSpeedSq = newSpeed * newSpeed;
        }
        
        // Store squared speed
        *(float*)(this + 0x34) = currentSpeedSq;
        
        // Clamp speed to maximum
        float maxSpeed = *(float*)(moveParams + 0x1c);
        if (maxSpeed <= *(float*)(this + 0x28))
        {
            *(float*)(this + 0x28) = maxSpeed;
            *(float*)(this + 0x34) = maxSpeed * maxSpeed;
            // If timer expired and acceleration exists, set flag to mark completion
            if (*(float*)(this + 0x2c) <= 0.0f && *(float*)(moveParams + 0x20) != 0.0f)
            {
                uint* flagPtr = (uint*)(*(int*)(fsPrev + 8) + *(int*)(this + 0x10));
                *flagPtr |= 1;
            }
        }
        
        // Get current position from entity state (offset 0x80 from start of entity data)
        float* positionPtr = (float*)(*(int*)(this + 0x10) + 0x80 + *(int*)(fsPrev + 8));
        float posX = *positionPtr;
        float posY = positionPtr[1];
        float posZ = positionPtr[2];
        float posW = positionPtr[3]; // unused in calculations?
        
        // Determine movement mode from moveParams flags
        int* modePtr = (int*)*(undefined4**)(this + 0x24);
        int mode = (int)modePtr;
        if ((mode & 0x20) == 0)
        {
            if ((mode & 0x10) == 0)
            {
                // Mode 0: Listen to global listener array (DAT_012234c4)
                undefined** listenerArray = DAT_012234c4; // singleton array
                int local_34 = this;
                if (DAT_012234c4[5] != nullptr)
                {
                    // Call listener function with position and speed
                    (**(code**)(*DAT_012234c4[5] + 8))(&posX, *(undefined4*)(this + 0x28), DAT_012234c4[4], &listenerArray, 0, 0, 1);
                }
            }
            else
            {
                // Mode 0x10: Process object list (DAT_012233a0) for collision
                int objectCount = DAT_012233a0[3];
                for (uint i = 0; i < (uint)objectCount; i++)
                {
                    if ((int)i >= 0 && i < (uint)DAT_012233a0[3])
                    {
                        int* object = ((int**)DAT_012233a0[1])[i];
                        if (object != nullptr)
                        {
                            // Call object's method to get its position? (offset 0xc in vtable)
                            int* objResult = (int*)(**(code**)(*object + 0xc))();
                            if (objResult != nullptr)
                            {
                                // Read object's position from offsets 0x40,0x41,0x42 (likely floats)
                                float objX = (float)objResult[0x40];
                                float objY = (float)objResult[0x41];
                                float objZ = (float)objResult[0x42];
                                
                                // Compare squared distance to our squared speed (radius)
                                float dx = objX - posX;
                                float dy = objY - posY;
                                float dz = objZ - posZ;
                                float distSq = dx*dx + dy*dy + dz*dz;
                                
                                if (distSq < *(float*)(this + 0x34))
                                {
                                    // If within range, call collision check and possibly trigger
                                    int* result2 = (int*)FUN_004f8a20(&objX);
                                    if (DAT_00e2e210 < *(float*)(this + 0x34)) // global threshold
                                    {
                                        FUN_004f8aa0(object, &objX, *(float*)(this + 0x34), 0, 0xffffffff);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        else
        {
            // Mode 0x20: Handle 'target' object from this+4+0xc4
            int* targetObject = *(int**)(*(int*)(this + 4) + 0xc4);
            if (targetObject != nullptr)
            {
                int* adjustedPtr = targetObject - 0x12;
                if (adjustedPtr != nullptr)
                {
                    // Get target's position (offsets 0x2e,0x2f,0x30? possibly float indices)
                    float targetX = (float)targetObject[0x2e];
                    float targetY = (float)targetObject[0x2f];
                    float targetZ = (float)targetObject[0x30];
                    // Call collision function with fixed radius (0x3f800000 = 1.0f)
                    FUN_004f8aa0(adjustedPtr, &targetX, 1.0f, 0, *(undefined4*)(*(int*)(this + 4) + 0xb8));
                }
            }
        }
        
        // Handle timer (delay before marking movement as complete)
        if (*(float*)(this + 0x2c) > 0.0f)
        {
            float remaining = *(float*)(this + 0x2c) - deltaTime;
            *(float*)(this + 0x2c) = remaining;
            if (remaining <= 0.0f)
            {
                int entityOffset = *(int*)(fsPrev + 8);
                int* entityBase = (int*)(*(int*)(this + 0x10) + entityOffset);
                *entityBase |= 1; // Set completion flag
            }
        }
        
        // Notify listener array[8] with movement data
        int* listener8 = (int*)DAT_012234c4[8];
        if (listener8 != nullptr)
        {
            (**(code**)(*listener8 + 4))(&posX, *(undefined4*)(*(int*)(this + 0x24) + 0x2c), 
                                         *(undefined4*)(this + 0x28), *(undefined4*)(*(int*)(this + 0x24) + 0x28));
        }
        
        // Optional debugging or additional effect
        if (DAT_012233c4 != 0)
        {
            int param = *(int*)(*(int*)(this + 0x24) + 0x28);
            if (param == 4)
            {
                param = 2;
            }
            else if (param == 5 || (int*)(param - 8) != nullptr)
            {
                // If not 4 or 5, just return pointer? Possibly a fallthrough
                return (int*)(param - 8);
            }
            else
            {
                param = 1;
            }
            float speed = *(float*)(this + 0x28);
            FUN_004f8980(listener8, param); // Some postprocess sound/effect
            FUN_00416340(&posX, speed, param);
        }
    }
    
    // Return pointer from earlier calculations (probably 'this' or a side result)
    return (int*)piVar5; // piVar5 often ends as some result pointer
}