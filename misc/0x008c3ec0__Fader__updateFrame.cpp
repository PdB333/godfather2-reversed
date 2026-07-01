// FUNC_NAME: Fader::updateFrame
void __thiscall Fader::updateFrame(Fader *this, FadeState *fadeState)
{
    uint paramType;
    int deltaValue;
    float newValue;

    paramType = 0xffffffff;
    deltaValue = 0;
    if (fadeState->state == 1) {
        deltaValue = fadeState->speedOut;
        paramType = 0;
        getFadeOutDelta();
    }
    else if (fadeState->state == 0) {
        getFadeInDelta();
        deltaValue = fadeState->speedIn + fadeState->speedOut;
        paramType = 2;
    }
    if (this->callback != (void *)0x0) {
        FUN_00892490((float)deltaValue, paramType); // likely a virtual callback or signal
    }
    newValue = this->currentValue + (float)deltaValue;
    if (newValue <= g_minFadeValue) {
        this->currentValue = g_minFadeValue;
        return;
    }
    if (g_maxFadeValue <= newValue) {
        newValue = g_maxFadeValue;
    }
    this->currentValue = newValue;
}