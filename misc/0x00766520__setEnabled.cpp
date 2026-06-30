// FUNC_NAME: setEnabled
void setEnabled(void* object)
{
    // Calls internal function to set the object's enabled state to true (1)
    setEnabledInternal(object, 1);
}