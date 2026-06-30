// FUNC_NAME: Physics::computeDragForce
float computeDragForce(float param_1, float param_2, float param_3, float param_4)
{
    float fVar3;
    double dVar4;
    double dVar5;
    double dVar6;

    param_2 = param_2 * 0.017453292f; // DAT_00e445c8 = degrees to radians
    param_3 = param_3 * 0.017453292f; // DAT_00e445c8 = degrees to radians
    dVar4 = (double)param_2;
    FUN_00b99e20(); // likely sin/cos lookup or math helper
    fVar3 = (float)((uint)((float)dVar4 * param_1) & 0x7FFFFFFF); // DAT_00e44680 = 0x7FFFFFFF (abs mask)
    if ((float)((uint)fVar3 & 0x7FFFFFFF) <= 0.001f) { // DAT_00d5ef84 = 0.001f (epsilon)
        fVar3 = 0.0f;
    }
    else {
        dVar5 = (double)param_2;
        FUN_00b99fcb(); // likely another math helper
        dVar6 = (double)(param_3 * 0.017453292f); // _DAT_00d5c458 = degrees to radians
        FUN_00b9c041(); // likely another math helper
        fVar3 = fVar3 / (((float)dVar5 * param_1 * param_4) / ((float)dVar6 * 0.5f) + // DAT_00d5eee4 = 0.5f
                         fVar3 * 0.017453292f + fVar3); // _DAT_00d5c458 = degrees to radians
    }
    dVar5 = (double)param_2;
    FUN_00b99fcb();
    float fVar1 = (float)((0.785398163f - fVar3 * 0.017453292f) * (float)dVar5 * param_1); // _DAT_00d5780c = 0.785398163f (PI/4)
    float fVar2 = (float)tan((float)param_3 * 0.017453292f); // fptan = tan
    return ABS((float)(float)dVar4 * fVar1) * 1.0f + // DAT_00d5ef70 = 1.0f
           ((float)(float)dVar5 * fVar1 * (float)param_4) / (fVar2 + fVar2);
}