// FUNC_NAME: WaitForResource
void WaitForResource(void* context, int param) {
    int status;
    status = TestResourceReady(context, param);
    while (status < 0) {
        status = TestResourceReady(context, param);
    }
}