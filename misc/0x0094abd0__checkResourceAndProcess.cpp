// FUNC_NAME: checkResourceAndProcess
void checkResourceAndProcess(ResourceHandle* resourceHandle, void* additionalData)
{
    int validationResult = validateResource(resourceHandle);
    if (validationResult >= 0) {
        processResource(additionalData);
    }
}