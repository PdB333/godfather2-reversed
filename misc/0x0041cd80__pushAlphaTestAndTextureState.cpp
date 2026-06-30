// FUNC_NAME: pushAlphaTestAndTextureState
void pushAlphaTestAndTextureState(void)
{
    float savedState2 = *(float *)0x011f38f4;
    float savedState1 = *(float *)0x011f38f0;

    *(float *)0x011f38f4 = 0.0f;
    float newState1 = (float)in_EAX; // in_EAX passed implicitly (likely a float)
    setRenderState(0, *(float *)0x011f38f0, savedState2); // save old, set blend? params: (?, oldValue, savedState2)
    *(float *)0x011f38f0 = newState1;

    // Set identity transform? (0,0,0,1,1)
    setTransform(0, 0, 0, 1.0f, 1.0f);

    // Bind globalTexture to three texture units (likely same texture for all)
    setTextureUnit(*(float *)0x00e2cd54, *(float *)0x00e2cd54, *(float *)0x00e2cd54, 0, 1.0f, 0);
    enableAlphaTest(1); // enable alpha test

    // Clear texture units and disable alpha test
    setTextureUnit(0, 0, 0, 0, 1.0f, 0);
    disableAlphaTest(1); // disable alpha test

    // Restore saved state
    float temp2 = *(float *)0x011f38f4;
    float temp1 = *(float *)0x011f38f0;
    *(float *)0x011f38f4 = 0.0f;
    *(float *)0x011f38f0 = savedState1;
    setRenderState(0, temp1, temp2);
    setTransform(0, 0, 0, 1.0f, 1.0f);
}