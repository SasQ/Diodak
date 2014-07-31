// C++ Standard Library headers.
#include <iostream>
#include <string>

// wxWidgets library headers.
#include <wx/app.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/icon.h>
#include <wx/toolbar.h>
#include <wx/combobox.h>
#include <wx/msgdlg.h>
#include <wx/string.h>

// Own headers.
#include "Views/Circuit.hh"

// Icons (in XPM format).
#include "assets/icons/NewCircuit.xpm"

// Strings.
const std::string
	appName         = "Diodak",
	appVersion      = "0.1",
	appBuildDate    = "2014.07.19",
	appAuthor       = "Mike 'SasQ' Studencki",
	appAuthorEmail  = "sasq1@go2.pl",
	appNameVer      = appName + ' ' + appVersion,
	appNameVerBuild = appNameVer + " (build " + appBuildDate + ")",
	appAuthorFull   = appAuthor + " <" + appAuthorEmail + ">";


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
 	void OnCmdAbout(wxCommandEvent& evt);
 	void OnCmdExit(wxCommandEvent& evt);
 	
 private:
 	void InitMenus();
 	void InitToolbars();
 	
 	DECLARE_EVENT_TABLE()
};


/// ========== Implementation ==========


// This macro implements a `main` function which creates an instance of our application class and runs it.
// TODO: In wxWidgets 3.0 this has to be changed into `wxIMPLEMENT_APP(DiodakApp);`.
IMPLEMENT_APP(DiodakApp)

/// Handle the application's initialization.
bool DiodakApp::OnInit()
{
	std::clog << appNameVerBuild + " by " + appAuthorFull << std::endl;
	
	(new DiodakFrame)->Show(true);  // Create the main window and show it on the desktop.
	return true;                    // Successfully initialized. Continue running the app.
}


// Main window's static event table.
BEGIN_EVENT_TABLE(DiodakFrame, wxFrame)
	EVT_MENU(wxID_EXIT,  DiodakFrame::OnCmdExit)
	EVT_MENU(wxID_ABOUT, DiodakFrame::OnCmdAbout)
END_EVENT_TABLE()


/// The main frame's default constructor.
DiodakFrame::DiodakFrame():
	wxFrame(0, wxID_ANY, wxString::FromAscii( appNameVer.c_str() ) )
{
	// Set the main window's icon.
	SetIcon( wxIcon(NewCircuit_xpm) );
	
	// Initialize menu bars and toolbars.
	InitMenus();  InitToolbars();
	
	// Create a scrolled window for the circuit area, with a grid in its background.
	CircuitView *circuitView = new CircuitView(this);
	
	// Set the scrolling parameters.
	circuitView->SetVirtualSize(400,400);  // The size of its "virtual" (potential, offscreen) area.
	circuitView->SetScrollRate(10,10);     // Jump by 10 pixels as the "scroll unit" (must be positive to see the scrollbars).
	
	// All's ready to roll. Create the status bar.
	CreateStatusBar();  SetStatusText( wxT("Command, my Master!") );
}

/// Initialize the menus with menu items.
void DiodakFrame::InitMenus()
{
	// Create some basic menus with menu items.
	// Since we use the default system menus, we don't need to specify any additional params.
	
	// "File" menu.
	wxMenu *menuFile = new wxMenu;
	menuFile->Append(wxID_NEW);
	menuFile->Append(wxID_OPEN);
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);
	
	// "Edit" menu.
	wxMenu *menuEdit = new wxMenu;
	menuEdit->Append(wxID_UNDO);
	menuEdit->Append(wxID_REDO);
	menuEdit->AppendSeparator();
	menuEdit->Append(wxID_CUT);
	menuEdit->Append(wxID_COPY);
	menuEdit->Append(wxID_PASTE);
	
	// "Help" menu.
	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	
	// Create a menu bar and attach the menus to it.
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, wxT("&File") );
	menuBar->Append(menuEdit, wxT("&Edit") );
	menuBar->Append(menuHelp, wxT("&Help") );
	SetMenuBar(menuBar);
}

/// Initialize the toolbars.
void DiodakFrame::InitToolbars()
{
	// Create a toolbar.
	wxToolBar *toolBar = CreateToolBar();
	
	// Add some tool icons into it.
	toolBar->AddTool(wxID_NEW,  wxT("New"),  wxIcon(NewCircuit_xpm), wxT("New circuit")  );
	toolBar->AddTool(wxID_OPEN, wxT("Open"), wxIcon(NewCircuit_xpm), wxT("Open circuit") );
	toolBar->AddSeparator();
	
	// Add a combo box (because we can!).
	wxComboBox *combo = new wxComboBox(toolBar,wxID_ANY);
	toolBar->AddControl(combo);
	
	// Update the toolbar and attach it to the window.
	toolBar->Realize();
	SetToolBar(toolBar);
}

/// ----- Menu commands handlers -----

/// Handle File -> Exit.
void DiodakFrame::OnCmdExit(wxCommandEvent& evt)
{
	// We don't store any user data yet,
	// so we just quit without asking by closing the main window.
	Close(true);
}

/// Handle Help -> About.
void DiodakFrame::OnCmdAbout(wxCommandEvent& evt)
{
	// Display a simple message box with some information about the program and its author.
	wxMessageBox(
		wxString::FromAscii( (appNameVerBuild + "\nby " + appAuthorFull).c_str() ),
		wxT("About Diodak"), wxOK | wxICON_INFORMATION
	);
}