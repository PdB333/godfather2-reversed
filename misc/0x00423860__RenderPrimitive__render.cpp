// FUNC_NAME: RenderPrimitive::render
void __thiscall RenderPrimitive::render(RenderPrimitive *this)
{
  int type = *(int *)((char *)this + 0x140); // +0x140: type enum (1=rect, 2=line?)

  if (type == 1) {
    // Render rectangle
    // Parameters: color? x1,y1, x2,y2? 
    // Offsets: +0x14c, +0x150, +0x144, +0x148
    FUN_00614440(*(undefined4 *)((char *)this + 0x14c),
                 *(undefined4 *)((char *)this + 0x150),
                 *(undefined4 *)((char *)this + 0x144),
                 *(undefined4 *)((char *)this + 0x148));
  } else if (type == 2) {
    // Render line
    // Parameters: x1,y1, x2,y2, color? 
    // Offsets: +0x150, +0x154, +0x158, +0x144
    FUN_006145f0(*(undefined4 *)((char *)this + 0x150),
                 *(undefined4 *)((char *)this + 0x154),
                 *(undefined4 *)((char *)this + 0x158),
                 *(undefined4 *)((char *)this + 0x144));
  }
  // If type is neither, do nothing
}