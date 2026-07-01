// FUNC_NAME: deinitGlobalState
// Address: 0x0084d400
// Releases two global resources (DAT_0112dd8c, DAT_0112dd94) by passing their addresses to a deallocation function.
void releaseGlobalResource(void* ptr);

extern int g_resourceA; // was DAT_0112dd8c
extern int g_resourceB; // was DAT_0112dd94

void deinitGlobalState(void)
{
    releaseGlobalResource(&g_resourceA);
    releaseGlobalResource(&g_resourceB);
}