// C++ Standard Library headers.
#include <iostream>

// wxWidgets library headers.
#include <wx/app.h>

/** Application class.
 ** We derive our application after the `wxApp` class from wxWidgets library and personalize it.
 ** For now we just override its `OnInit` method which is to be called when the application starts.
 **/
class DiodakApp : public wxApp
{
 public:
 	bool OnInit();
};

// This macro implements a `main` function which creates an instance of our application class and runs it.
// TODO: In wxWidgets 3.0 this has to be changed into `wxIMPLEMENT_APP(DiodakApp);`.
IMPLEMENT_APP(DiodakApp)

bool DiodakApp::OnInit()
{
	std::clog << "Diodak v.0.1 (2014.07.19) by Mike 'SasQ' Studencki <sasq1@go2.pl>" << std::endl;
	return false;  // Nothing more to be done. Just end the program.
}