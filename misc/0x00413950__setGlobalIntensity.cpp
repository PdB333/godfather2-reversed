// FUNC_NAME: setGlobalIntensity
void setGlobalIntensity(char enable)
{
    if (enable != '\0') {
        g_globalIntensity = g_defaultIntensity; // +0x??: stored intensity value from global
    } else {
        g_globalIntensity = 0;
    }
}