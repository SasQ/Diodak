// C++ Standard Library headers.
#include <iostream>

// wxWidgets library headers.
#include <wx/app.h>
#include <wx/frame.h>
#include <wx/menu.h>


/// Application class.
class DiodakApp: public wxApp
{
 public:
 	bool OnInit();
};


/// Main window (frame) class.
class DiodakFrame: public wxFrame
{
 public:
 	DiodakFrame();
};


/// ========== Implementation ==========


// This macro implements a `main` function which creates an instance of our application class and runs it.
// TODO: In wxWidgets 3.0 this has to be changed into `wxIMPLEMENT_APP(DiodakApp);`.
IMPLEMENT_APP(DiodakApp)

/// Handle the application's initialization.
bool DiodakApp::OnInit()
{
	std::clog << "Diodak v0.1 (2014.07.19) by Mike 'SasQ' Studencki <sasq1@go2.pl>" << std::endl;
	(new DiodakFrame)->Show(true);  // Create the main window and show it on the desktop.
	return true;                    // Successfully initialized. Continue running the app.
}


/// The main frame's default constructor.
DiodakFrame::DiodakFrame(): wxFrame(0, wxID_ANY, wxT("Diodak 0.1") )
{
	// Create some basic menus with menu items.
	// Since we use the default system menus, we don't need to specify any additional params.
	
	// "Help" menu.
	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	
	// "File" menu.
	wxMenu *menuFile = new wxMenu;
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);
	
	// Create the menu bar and attach the menus to it.
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, wxT("&File") );
	menuBar->Append(menuHelp, wxT("&Help") );
	SetMenuBar(menuBar);
	
	// Create the status bar.
	CreateStatusBar();
	SetStatusText( wxT("Command, my Master!") );
}