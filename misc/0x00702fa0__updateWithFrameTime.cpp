// FUNC_NAME: updateWithFrameTime
void updateWithFrameTime(void)
{
    float fVar1;
    
    fVar1 = getFrameTime();
    updateFromTime(fVar1);
    return;
}