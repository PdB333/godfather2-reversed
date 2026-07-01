// FUNC_NAME: UIElement::SetImageCheckOrCall
void UIElement::setImageCheck(undefined4 param_1)
{
  char cVar1;
  
  cVar1 = FUN_005bd670(param_1); // Unknown function, likely checks something
  if (cVar1 != '\0') {
    FUN_005a04a0("SetImage",0,&DAT_00d83810,1,param_1); // Call SetImage function
  }
  return;
}