// FUNC_NAME: UnknownClass::conditionalAction
void UnknownClass::conditionalAction(void* arg)
{
    int isReady = someCheck(arg);
    if (isReady != 0) {
        executeAction(this);
    }
    return;
}