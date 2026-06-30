// FUNC_NAME: writeCollisionEventData
// Address: 0x004697a0
// This function serializes collision event data (velocity, angle, position, materials, masses) into a stream buffer.
// It reads from an input event list within the stream context and writes to the output buffer.

int writeCollisionEventData(int stream) // stream is a pointer to a writable context with internal pointers
{
    char* materialA = "collision_default";
    char* materialB = "collision_default";
    
    // Read input pointer from stream+0x0C
    int* inputPtr = *(int**)(stream + 0x0C);
    int eventObjectPointer = 0;
    
    float velocity = 0.0f;
    float angle = DAT_00e2b1a4; // constant default angle
    float massA = 0.0f;
    float massB = 0.0f;
    
    // If there is input data and it is a type 2 event
    if ((inputPtr < *(int**)(stream + 8)) && 
        (inputPtr != (int*)0x0) && 
        (*inputPtr == 2) &&
        (inputPtr < *(int**)(stream + 8)) && 
        (inputPtr != (int*)0x0))
    {
        if (*inputPtr == 2)
        {
            inputPtr = (int*)inputPtr[1]; // advance to data block
        }
        else
        {
            if (*inputPtr != 7) goto LAB_004698db;
            inputPtr = (int*)(inputPtr[1] + 0x10); // for type 7, skip header
        }
        
        if (inputPtr != (int*)0x0)
        {
            if ((*inputPtr != 0) && 
                (eventObjectPointer = *(int*)(*inputPtr + 0x20), eventObjectPointer != 0))
            {
                // Increment reference count on the object (event +4)
                *(int*)(eventObjectPointer + 4) = *(int*)(eventObjectPointer + 4) + 1;
                
                // Get collision info object
                int* collisionInfo = (int*)FUN_00469ad0(eventObjectPointer);
                if (collisionInfo != (int*)0x0)
                {
                    // Call virtual getters at vtable offsets +0x10, +0x14, +0x1c, +0x24, +0x18, +0x20
                    // Offsets +0x10 and +0x14: get floats
                    // Offsets +0x1c and +0x24: get strings (material names)
                    // Offsets +0x18 and +0x20: get floats (masses)
                    velocity = (float)((code*)collisionInfo[0x10 / 4])(); // +0x10
                    angle    = (float)((code*)collisionInfo[0x14 / 4])(); // +0x14
                    materialA = (char*)((code*)collisionInfo[0x1c / 4])(); // +0x1c
                    materialB = (char*)((code*)collisionInfo[0x24 / 4])(); // +0x24
                    massA    = (float)((code*)collisionInfo[0x18 / 4])(); // +0x18
                    massB    = (float)((code*)collisionInfo[0x20 / 4])(); // +0x20
                    
                    if (materialA == 0x0) materialA = "collision_default";
                    if (materialB == 0x0) materialB = "collision_default";
                }
            }
            eventObjectPointer = inputPtr[1]; // store next event pointer? Actually used for position
        }
    }
    
LAB_004698db:
    // Check if output buffer has enough space (stream+0x10 is a size struct)
    if (*(uint*)(*(int*)(stream + 0x10) + 0x20) <= *(uint*)(*(int*)(stream + 0x10) + 0x24))
    {
        FUN_00627360(); // probably a flush or error handler
    }
    
    // Write a type 5 entry (object reference?)
    int* writePtr = *(int**)(stream + 8); // current write position
    *writePtr = 5; // type code 5
    writePtr[1] = FUN_00637c50(0, 0); // some object handle
    *(int*)(stream + 8) = *(int*)(stream + 8) + 8; // advance write pointer
    
    // Adjust stream position (rewind? Maybe align/validate)
    FUN_00633d60(*(int*)(stream + 8) - 0x18, *(int*)(stream + 8) - 0x10, *(int*)(stream + 8) - 8);
    *(int*)(stream + 8) = *(int*)(stream + 8) - 0x10;
    
    // Write "velocity" field
    FUN_00625ca0(stream, "velocity");
    writePtr = *(int**)(stream + 8);
    *writePtr = 3; // type 3 = float
    writePtr[1] = velocity;
    *(int*)(stream + 8) = *(int*)(stream + 8) + 8;
    FUN_00633d60(*(int*)(stream + 8) - 0x18, *(int*)(stream + 8) - 0x10, *(int*)(stream + 8) - 8);
    *(int*)(stream + 8) = *(int*)(stream + 8) - 0x10;
    
    // Write "angle" field
    FUN_00625ca0(stream, "angle");
    writePtr = *(int**)(stream + 8);
    *writePtr = 3;
    writePtr[1] = angle;
    *(int*)(stream + 8) = *(int*)(stream + 8) + 8;
    FUN_00633d60(*(int*)(stream + 8) - 0x18, *(int*)(stream + 8) - 0x10, *(int*)(stream + 8) - 8);
    *(int*)(stream + 8) = *(int*)(stream + 8) - 0x10;
    
    // Write "position" field (eventObjectPointer is an object handle)
    FUN_00625ca0(stream, "position");
    writePtr = *(int**)(stream + 8);
    *writePtr = 2; // type 2 = int (object handle)
    writePtr[1] = eventObjectPointer;
    *(int*)(stream + 8) = *(int*)(stream + 8) + 8;
    FUN_00633d60(*(int*)(stream + 8) - 0x18, *(int*)(stream + 8) - 0x10, *(int*)(stream + 8) - 8);
    *(int*)(stream + 8) = *(int*)(stream + 8) - 0x10;
    
    // Write "materialA" field (string)
    FUN_00625ca0(stream, "materialA");
    FUN_00625ca0(stream, materialA); // writes the string value
    FUN_00633d60(*(int*)(stream + 8) - 0x18, *(int*)(stream + 8) - 0x10, *(int*)(stream + 8) - 8);
    *(int*)(stream + 8) = *(int*)(stream + 8) - 0x10;
    
    // Write "materialB" field
    FUN_00625ca0(stream, "materialB");
    FUN_00625ca0(stream, materialB);
    FUN_00633d60(*(int*)(stream + 8) - 0x18, *(int*)(stream + 8) - 0x10, *(int*)(stream + 8) - 8);
    *(int*)(stream + 8) = *(int*)(stream + 8) - 0x10;
    
    // Write "massA" field (float)
    FUN_00625ca0(stream, "massA");
    writePtr = *(int**)(stream + 8);
    *writePtr = 3;
    writePtr[1] = massA;
    *(int*)(stream + 8) = *(int*)(stream + 8) + 8;
    FUN_00633d60(*(int*)(stream + 8) - 0x18, *(int*)(stream + 8) - 0x10, *(int*)(stream + 8) - 8);
    *(int*)(stream + 8) = *(int*)(stream + 8) - 0x10;
    
    // Write "massB" field (float)
    FUN_00625ca0(stream, "massB");
    writePtr = *(int**)(stream + 8);
    *writePtr = 3;
    writePtr[1] = massB;
    *(int*)(stream + 8) = *(int*)(stream + 8) + 8;
    FUN_00633d60(*(int*)(stream + 8) - 0x18, *(int*)(stream + 8) - 0x10, *(int*)(stream + 8) - 8);
    *(int*)(stream + 8) = *(int*)(stream + 8) - 0x10;
    
    return 1; // success
}