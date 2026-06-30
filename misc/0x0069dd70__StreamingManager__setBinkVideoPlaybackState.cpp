// FUNC_NAME: StreamingManager::setBinkVideoPlaybackState
void StreamingManager::setBinkVideoPlaybackState(int state)
{
    bool bBusy;
    
    if (state == 2) {
        bBusy = isBinkStreamBusy();
        if (!bBusy && !g_bBinkVideoActive) {
            g_bBinkVideoActive = startBinkMovie();
        }
    } else if (state == 0 || state == 1) {
        bBusy = isBinkStreamBusy();
        if (!bBusy && g_bBinkVideoActive) {
            stopBinkMovie();
            g_bBinkVideoActive = false;
        }
    }
}