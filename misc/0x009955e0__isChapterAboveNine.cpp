// FUNC_NAME: isChapterAboveNine
extern int g_currentChapter; // 0x0113097c

bool isChapterAboveNine(void) {
    return g_currentChapter > 9;
}