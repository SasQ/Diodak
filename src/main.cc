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
#include <wx/scrolwin.h>
// FIXME: Uncomment this if you're compiling against wxWidgets < 3.1 (changeset 76947) where this bughas been corrected:
//#include <wx/wx.h>
#include <wx/custombgwin.h>
#include <wx/bitmap.h>
#include <wx/dcmemory.h>
#include <wx/brush.h>
#include <wx/pen.h>
#include <wx/colour.h>
#include <wx/msgdlg.h>
#include <wx/string.h>

// Icons (in XPM format).
#include "assets/icons/NewCircuit.xpm"

typedef wxCustomBackgroundWindow<wxScrolledWindow> CircuitView;

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
	
	// Create a scrolled window for the circuit area, with a custom bitmap as its background.
	CircuitView *circuitView = new CircuitView;
	circuitView->Create(this, wxID_ANY, wxDefaultPosition, wxSize(400,400), wxHSCROLL|wxVSCROLL);
	
	// --- Prepare the bitmap tile with a grid and set it as the custom background. ---
	
	// Prepare the grid parameters.
	wxColour grid0Color(251,251,251), grid1Color(247,247,247), grid2Color(242,242,242); // Grid colors: FB, F7, F2.
	unsigned grid0StepX = 10, grid0StepY = grid0StepX;                                  // Grid 0 resolution is 10 pixels.
	unsigned grid1StepX = 10*grid0StepX, grid1StepY = 10*grid0StepY,                    // Grid 1 is 10 times more sparse.
	         grid2StepX = 10*grid1StepX, grid2StepY = 10*grid1StepY;                    // Grid 3 is 10 times more still sparse.
	unsigned gridSizeX = grid2StepX, gridSizeY = grid2StepY;                            // The size of one repetition of the grid.
	
	// Create a bitmap for the grid tile, and its corresponding DC.
	wxBitmap bmpGrid(gridSizeX,gridSizeY);
	wxMemoryDC dcGrid(bmpGrid);
	
	// Fill the background with white.
	dcGrid.SetPen(wxNullPen);
	dcGrid.SetBrush(*wxWHITE_BRUSH);
	dcGrid.DrawRectangle(0,0, gridSizeX,gridSizeY);
	
	// Draw grid lines.
	dcGrid.SetPen( wxPen(grid0Color,1) );
	for (int x=0; x < gridSizeX; x += grid0StepX) dcGrid.DrawLine(x,0, x,gridSizeY);
	for (int y=0; y < gridSizeY; y += grid0StepY) dcGrid.DrawLine(0,y, gridSizeX,y);
	dcGrid.SetPen( wxPen(grid1Color,1) );
	for (int x=0; x < gridSizeX; x += grid1StepX) dcGrid.DrawLine(x,0, x,gridSizeY);
	for (int y=0; y < gridSizeY; y += grid1StepY) dcGrid.DrawLine(0,y, gridSizeX,y);
	dcGrid.SetPen( wxPen(grid2Color,1) );
	for (int x=0; x < gridSizeX; x += grid2StepX) dcGrid.DrawLine(x,0, x,gridSizeY);
	for (int y=0; y < gridSizeY; y += grid2StepY) dcGrid.DrawLine(0,y, gridSizeX,y);
	
	// Set the bitmap as the window's background.
	circuitView->SetBackgroundBitmap(bmpGrid);
	
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