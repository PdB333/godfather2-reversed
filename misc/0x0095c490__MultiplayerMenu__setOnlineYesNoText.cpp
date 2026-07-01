// FUNC_NAME: MultiplayerMenu::setOnlineYesNoText
void __thiscall MultiplayerMenu::setOnlineYesNoText(void* this, int textControlId) {
    char* text;

    if (*(char*)((int)this + 5) == '\0') {
        text = "$mp_online_menu_no";
    } else {
        text = "$mp_online_menu_yes";
    }
    FUN_005c4660(textControlId, text, 0x80, 0); // sets UI text, 0x80 = max length?
}