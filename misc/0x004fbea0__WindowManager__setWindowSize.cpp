// FUNC_NAME: WindowManager::setWindowSize
void WindowManager::setWindowSize(void *this, void *unused)
{
    int dimensions[2] = { 184, 168 }; // Width = 0xb8, Height = 0xa8
    FUN_004eba90(this, unused, dimensions, 2);
}