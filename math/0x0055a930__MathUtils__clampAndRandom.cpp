// FUNC_NAME: MathUtils::clampAndRandom
float MathUtils::clampAndRandom(float param_1)
{
    float fVar1;
    float fVar2;
    
    fVar1 = (float)FUN_0040f220(param_1); // likely fabsf or similar
    if ((float)1.0 <= fVar1) {
        fVar2 = 0.0;
        if (param_1 <= 0.0) {
            fVar2 = DAT_00e2afac; // some global constant
        }
        return (float)fVar2;
    }
    fVar1 = (float)FUN_00b9a660(); // likely random() or rand()
    return fVar1;
}