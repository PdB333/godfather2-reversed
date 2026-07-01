// FUNC_NAME: safeReleaseObject
void safeReleaseObject(void* pObject)
{
    if (pObject != nullptr) {
        doPreReleaseCleanup();
        destroyObject(pObject);
    }
}