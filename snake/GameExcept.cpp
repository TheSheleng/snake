#include "GameExcept.h"

ge::GameExcept::GameExcept(string ex)
{
	this->ex = ex;
}

void ge::GameExcept::errPrint()
{
	const char* DECOR_ERR = "----====<(|*|***|*|)>====----";
	const char* SEC_MESS = "(Press Enter to continue)";
	short str_num = 10;

	wp::Img ErrorScren;
	ErrorScren.addStr(ex, { (short)(WIN::WIDTH - ex.size()) / 2, str_num });
	ErrorScren.addStr(DECOR_ERR, { (short)(WIN::WIDTH - strlen(DECOR_ERR)) / 2, str_num += 2 });
	ErrorScren.addStr(SEC_MESS, { (short)(WIN::WIDTH - strlen(SEC_MESS)) / 2, str_num += 2 });

	wp::Window.set_screen(ErrorScren);
	mbl::SAbility::enterPause();
}