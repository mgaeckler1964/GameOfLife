/*
	this file was created from C:\CRESD\Source\GameOfLife\gameOfLife.gui with MG Gui Builder
	+++++++++++++++++++++++
	!!!!! Do not Edit !!!!!
	+++++++++++++++++++++++
*/
#ifndef C__CRESD_SOURCE_GAMEOFLIFE_GAMEOFLIFE_GUI_H
#define C__CRESD_SOURCE_GAMEOFLIFE_GAMEOFLIFE_GUI_H
#include <winlib/popup.h>
#include <winlib/frame.h>
#include <winlib/scrollFrame.h>
#include <winlib/ControlWindow.h>
#include <winlib/xmlEditorChild.h>
#include <winlib/chartWin.h>
#include <winlib/gridView.h>

#include <winlib/winApp.h>

namespace winlibGUI {

	const int CountLABEL_id=135;
	const int HeightEDIT_id=130;
	const int LifeArea_id=136;
	const int LifeGameFORM_id=128;
	const int StartBUTTON_id=131;
	const int StopBUTTON_id=132;
	const int Time2LABEL_id=134;
	const int TimeLABEL_id=133;
	const int WidthEDIT_id=129;

	class GuiApplication : public winlib::Application {
		public:
		virtual gak::xml::Document *getGuiDoc();
		GuiApplication(int iconID=-1) : winlib::Application(iconID) {}
	};

	class LifeGameFORM_form : public winlib::OverlappedWindow {
		public:
		LifeGameFORM_form(winlib::BasicWindow *owner) : OverlappedWindow(owner) {}
		winlib::SuccessCode create(winlib::BasicWindow*parent) {
			return OverlappedWindow::create(parent,"LifeGameFORM");
		}

		winlib::EditControl *WidthEDIT;
		winlib::EditControl *HeightEDIT;
		winlib::PushButton *StartBUTTON;
		winlib::PushButton *StopBUTTON;
		winlib::Label *TimeLABEL;
		winlib::Label *Time2LABEL;
		winlib::Label *CountLABEL;
		winlib::FrameChild *LifeArea;
		private:
		virtual void getControls();
	};	// end of LifeGameFORM
}	// namespace winlibGUI

#endif // C__CRESD_SOURCE_GAMEOFLIFE_GAMEOFLIFE_GUI_H
