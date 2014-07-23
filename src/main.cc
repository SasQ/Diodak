// C++ Standard Library headers.
#include <iostream>

// wxWidgets library headers.
#include <wx/app.h>
#include <wx/frame.h>


/** Application class.
 ** We derive our application after the `wxApp` class from wxWidgets library and personalize it.
 ** For now we just override its `OnInit` method which is to be called when the application starts.
 **/
class DiodakApp: public wxApp
{
 public:
 	bool OnInit();
};


/** Main window (frame) class.
 ** We derive it after `wxFrame` class from wxWidgets library
 ** and personalize it through base class's constructor call.
 **/
class DiodakFrame: public wxFrame
{
 public:
 	DiodakFrame(): wxFrame(0, wxID_ANY, wxT("Diodak 0.1") ) {}
};


/// ========== Implementation ==========


// This macro implements a `main` function which creates an instance of our application class and runs it.
// TODO: In wxWidgets 3.0 this has to be changed into `wxIMPLEMENT_APP(DiodakApp);`.
IMPLEMENT_APP(DiodakApp)

/// Handle the application's initialization.
bool DiodakApp::OnInit()
{
	std::clog << "Diodak v0.1 (2014.07.19) by Mike 'SasQ' Studencki <sasq1@go2.pl>" << std::endl;
	
	// Create the main window and show it on the desktop.
	// We don't need to store the new object; we can use the temporary as well.
	(new DiodakFrame)->Show(true);
	
	return true;  // Successfully initialized. Continue running the app.
}