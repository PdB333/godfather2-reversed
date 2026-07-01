// FUNC_NAME: UISprite::render

void __thiscall UISprite::render(UISprite* thisObj, int param2, int param3)
{
    int iVar1;
    int iVar2;
    float local_84[4]; // Actually a structure, likely a transform retrieval
    float matrix[16]; // 4x4 column-major, built from local_50 and others
    float* materialVtable; // points to PTR_LAB_00d8bff4
    float* matrixPtr; // points to matrix
    float local_68;
    float local_60;
    float local_58;
    float local_54;
    char local_5c; // byte, maybe a flag
    
    iVar1 = g_Renderer; // DAT_011298a0, global renderer singleton
    iVar2 = getRenderableManager(); // FUN_009bcb70, returns pointer to some manager
    
    // Check if renderable manager is valid and if a specific flag (maybe enabled) is set
    if ((iVar2 != 0) && (*(int*)(iVar2 + 0x130) != 0))
    {
        beginDraw2D(); // FUN_005c4bf0
        setDrawTransform(param2, param3); // FUN_005c5320, sets some viewport/transform
        
        // Initialize identity matrix (column-major)
        matrix[0]  = 1.0f;  matrix[4]  = 0.0f;  matrix[8]  = 0.0f;  matrix[12] = 0.0f;
        matrix[1]  = 0.0f;  matrix[5]  = 1.0f;  matrix[9]  = 0.0f;  matrix[13] = 0.0f;
        matrix[2]  = 0.0f;  matrix[6]  = 0.0f;  matrix[10] = 1.0f;  matrix[14] = 0.0f;
        matrix[3]  = 0.0f;  matrix[7]  = 0.0f;  matrix[11] = 0.0f;  matrix[15] = 1.0f;
        
        // Retrieve sprite transform data from global renderer
        getSpriteTransform(&local_84, iVar1 + 0x74); // FUN_00953bc0
        iVar2 = *(int*)(&local_84[1]); // local_84+4, some pointer within the structure
        
        // Fetch position parts from this pointer
        float posX = *(float*)(iVar2 + 100); // +0x64 offset? Actually +100 decimal = +0x64
        float posY = *(float*)(iVar2 + 0x68);
        float posZ = *(float*)(iVar2 + 0x6C);
        float posW = 1.0f;
        
        // Set rotation in matrix: angle = (iVar2+0x70) + (iVar1+0x78)
        float angle = *(float*)(iVar2 + 0x70) + *(float*)(iVar1 + 0x78);
        setRotationZ(angle, matrix); // FUN_0056b8a0, modifies matrix rotation part
        
        // Now set translation part of matrix (fourth column)
        matrix[12] = posX;
        matrix[13] = posY;
        matrix[14] = posZ;
        matrix[15] = posW;
        
        float objValue = *(float*)(iVar1 + 0x84); // some global value
        
        // Determine a parameter: if thisObj->field_0x14 is 0, use 0, else use thisObj->field_0x10
        if (*(int*)(thisObj + 0x14) == 0)
        {
            local_68 = 0.0f;
        }
        else
        {
            local_68 = *(float*)(thisObj + 0x10);
        }
        
        // Rectangle or UV coordinates from thisObj
        local_58 = *(float*)(thisObj + 8);   // x or u1
        local_54 = *(float*)(thisObj + 0xC); // y or v1
        
        // Set up the structure for the draw call
        matrixPtr = matrix;
        materialVtable = &PTR_LAB_00d8bff4; // some shader/material vtable pointer
        local_5c = 0; // blend mode? 0 = normal
        
        // Draw the quad
        drawQuad(&materialVtable); // FUN_004a4bd0
        
        endDraw2D(); // FUN_005c4ac0
    }
}