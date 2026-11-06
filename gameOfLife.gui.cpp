/*
	this file was created from C:\CRESD\Source\GameOfLife\gameOfLife.gui with MG Gui Builder
	+++++++++++++++++++++++
	!!!!! Do not Edit !!!!!
	+++++++++++++++++++++++
*/

#include "C:\CRESD\Source\GameOfLife\gameOfLife.gui.h"

namespace winlibGUI {

	gak::xml::Document *GuiApplication::getGuiDoc() {
		gak::xml::Document *doc = winlib::Application::getGuiDoc();
		if(!doc) {
			gak::STRING xmlSrc = "<?xml version=\"1.0\" encoding=\"iso-8859-1\" ?>\n"
"<gui>\n"
"<forms>\n"
"<form name=\"LifeGameFORM\" style=\"277807104\" width=\"640\" height=\"462\" caption=\"Conway\'s Game of Life\" id=\"128\" baseClass=\"OverlappedWindow\">\n"
"<child type=\"FrameChild\" name=\"\" caption=\"\" x=\"0\" y=\"0\" width=\"640\" height=\"40\" style=\"1342308352\" bgColor=\"COLOR_BTNFACE\" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\">\n"
"<layout attachment=\"1\" growWidth=\"5\" />\n"
"<child type=\"Label\" name=\"\" caption=\"Size (w*h)\" x=\"8\" y=\"16\" width=\"0\" height=\"0\" style=\"1342242827\" />\n"
"<child type=\"EditControl\" name=\"WidthEDIT\" caption=\"128\" x=\"80\" y=\"8\" width=\"80\" height=\"24\" style=\"1350631808\" id=\"129\" />\n"
"<child type=\"EditControl\" name=\"HeightEDIT\" caption=\"128\" x=\"168\" y=\"8\" width=\"80\" height=\"24\" style=\"1350631808\" id=\"130\" />\n"
"<child type=\"PushButton\" name=\"StartBUTTON\" caption=\"Start\" x=\"256\" y=\"8\" width=\"80\" height=\"24\" style=\"1342242816\" id=\"131\" />\n"
"<child type=\"PushButton\" name=\"StopBUTTON\" caption=\"Stop\" x=\"336\" y=\"8\" width=\"80\" height=\"24\" style=\"1342242816\" id=\"132\" />\n"
"<child type=\"Label\" name=\"TimeLABEL\" caption=\"\" x=\"424\" y=\"8\" width=\"72\" height=\"16\" style=\"1342242827\" id=\"133\" />\n"
"<child type=\"Label\" name=\"Time2LABEL\" caption=\"\" x=\"464\" y=\"8\" width=\"80\" height=\"16\" style=\"1342242827\" id=\"134\" />\n"
"<child type=\"Label\" name=\"CountLABEL\" caption=\"\" x=\"504\" y=\"8\" width=\"72\" height=\"16\" style=\"1342242827\" id=\"135\" />\n"
"</child>\n"
"<child type=\"FrameChild\" name=\"LifeArea\" caption=\"\" x=\"0\" y=\"40\" width=\"640\" height=\"424\" style=\"1342308352\" id=\"136\">\n"
"<layout attachment=\"4\" growWidth=\"5\" growHeight=\"5\" />\n"
"</child>\n"
"<layoutManager type=\"AttachmentManager\" />\n"
"</form>\n"
"</forms>\n"
"</gui>";
			return Application::getGuiDoc( xmlSrc );
		}
		return doc;
	}


	void LifeGameFORM_form::getControls() {
		WidthEDIT=static_cast<winlib::EditControl*>(findChild(WidthEDIT_id));
		HeightEDIT=static_cast<winlib::EditControl*>(findChild(HeightEDIT_id));
		StartBUTTON=static_cast<winlib::PushButton*>(findChild(StartBUTTON_id));
		StopBUTTON=static_cast<winlib::PushButton*>(findChild(StopBUTTON_id));
		TimeLABEL=static_cast<winlib::Label*>(findChild(TimeLABEL_id));
		Time2LABEL=static_cast<winlib::Label*>(findChild(Time2LABEL_id));
		CountLABEL=static_cast<winlib::Label*>(findChild(CountLABEL_id));
		LifeArea=static_cast<winlib::FrameChild*>(findChild(LifeArea_id));
	}	// LifeGameFORM
}	// namespace winlibGUI
