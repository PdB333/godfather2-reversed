// FUNC_NAME: MovementController::updateSteeringVector
void __thiscall MovementController::updateSteeringVector(int param_2, int param_3, int param_4, float* param_5, int param_6, char* param_7) {
    // param_1 is 'this' (implicit), param_2 == inputEnable, param_3 unused, param_4 == targetEntity, param_5 == inputVector, param_6 == forceUpdate, param_7 == outputHasLock
    *param_7 = 0;

    bool bVar5;
    if (param_2 == 0 || !checkInput()) { // checkInput returns true when active
        bVar5 = (param_2 != 0 && !checkInput()); // bVar5 = true only if param_2 != 0 AND checkInput false
    } else {
        bVar5 = (param_2 != 0 && checkInput()) ? false : true; // actually: if param_2 != 0 and checkInput true, then bVar5 false. else bVar5 true? The code: if (param_2==0 || checkInput()) then bVar5=false else bVar5=true. So bVar5 = !(param_2==0 || checkInput()) = (param_2 != 0 && !checkInput()). So it's the same.
    }

    if (param_6 == 0 || (float)this->field_0x20 > 0.0f || bVar5) {
        float fVar15 = param_5[0];
        float fVar10 = *(float*)(param_4 + 0x20) * g_scale1; // DAT_00e51178
        float fVar11 = param_5[1] + g_offset1; // _DAT_00e5112c
        float fVar12 = *(float*)(param_4 + 0x28) * g_scale1;
        float fVar1 = param_5[2];
        float fVar2 = *(float*)(param_4 + 0x30);
        float fVar3 = *(float*)(param_4 + 0x34);
        float fVar4 = *(float*)(param_4 + 0x38);
        float fVar9 = *(float*)(param_4 + 0x3c) - g_offset2; // _DAT_00d5780c

        float* pfVar7 = (float*)(this->vtable->getPosition)(); // vtable +0x10
        float fVar13 = *(float*)(param_4 + 0x30) - pfVar7[0]; // dx
        float fVar16 = *(float*)(param_4 + 0x38) - pfVar7[2]; // dz
        float fVar8 = SQRT(fVar16 * fVar16 + fVar13 * fVar13);
        float fVar14 = g_threshold1 * fVar8; // DAT_0112a864
        fVar8 = g_threshold2 * fVar8; // DAT_00e51184

        float fVar13_dot = (float)this->dirX * fVar13 + (float)this->dirZ * fVar16; // dirX at offset 0x14, dirZ at 0x16
        if (fVar13_dot > 0.0f) {
            *param_7 = 1;
        }

        if ((g_angleMax - fVar14 < fVar13_dot) && ((param_2 != 0) || (fVar13_dot < fVar8))) {
            float lerpFactor = (float)this->lerpFactor; // offset 0x23
            // Smoothly update movement vector components
            this->moveX = (int)(((fVar2 - (fVar15 - fVar10)) - (float)this->moveX) * lerpFactor + (float)this->moveX);
            this->moveY = (int)(((fVar3 - fVar11) - (float)this->moveY) * lerpFactor + (float)this->moveY);
            this->moveZ = (int)(((fVar4 - (fVar1 - fVar12)) - (float)this->moveZ) * lerpFactor + (float)this->moveZ);
            this->moveW = (int)((fVar9 - (float)this->moveW) * lerpFactor + (float)this->moveW);
        }
    }

    // Normalize movement vector if magnitude > 0 and speed factor is nonzero or input active
    float magnitude = SQRT((float)this->moveX * (float)this->moveX + 
                           (float)this->moveY * (float)this->moveY + 
                           (float)this->moveZ * (float)this->moveZ);
    if (magnitude > 0.0f && ((float)this->speedFactor == 0.0f || checkInput())) {
        float scale = (float)this->maxSpeed / magnitude; // maxSpeed at offset 0x22
        this->moveX = (int)(scale * (float)this->moveX);
        this->moveY = (int)(scale * (float)this->moveY);
        this->moveZ = (int)(scale * (float)this->moveZ);
        this->moveW = (int)(scale * (float)this->moveW);
    }
}