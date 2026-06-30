// FUNC_NAME: UIElement::setRect
// Address: 0x006da5b0
// Role: Sets a rectangular region (position/size) for a UI element via the UIManager singleton.

struct UIRect {
    int x;      // +0x0
    int y;      // +0x4
    int flags;  // +0x8
};

class UIManager; // Forward declaration
UIManager* getUIManager(); // Defined elsewhere, returns singleton at 0x009c8f80

class UIElement {
public:
    void setRect();
};

void __thiscall UIElement::setRect() {
    UIManager* manager = getUIManager();
    UIRect rect;
    rect.x = 2;       // e.g., left/top coordinate
    rect.y = 0x10;    // e.g., right/bottom coordinate or size
    rect.flags = 0;   // flags or z-order

    // Call first virtual function on UIManager (e.g., SetElementRect)
    typedef void (__thiscall* SetRectFn)(UIManager*, UIElement*, UIRect*);
    SetRectFn setRectFn = *(SetRectFn*)(*reinterpret_cast<int*>(manager));
    setRectFn(manager, this, &rect);
}