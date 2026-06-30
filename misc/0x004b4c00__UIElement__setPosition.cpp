// FUNC_NAME: UIElement::setPosition
class UIElement {
public:
    // +0x40: pointer to a layout/position structure (e.g., UIRect)
    void* m_layoutData;

    // Sets two consecutive integer values (likely x, y) in the layout structure
    void setPosition(int x, int y) {
        int* layout = *(int**)((char*)this + 0x40);
        layout[0x12B] = x;   // +0x4ac (0x4ac / 4 = 0x12B)
        layout[0x12C] = y;   // +0x4b0 (0x4b0 / 4 = 0x12C)
    }
};