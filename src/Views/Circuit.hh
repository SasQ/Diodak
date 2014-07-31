#ifndef CIRCUIT_VIEW_HH
#define CIRCUIT_VIEW_HH

#include <wx/scrolwin.h>
#include <wx/event.h>

/// Custom scrolled window class for displaying circuits.
class CircuitView: public wxScrolledWindow
{
 public:
 	CircuitView(wxWindow* parent);
 	void OnEraseBg(wxEraseEvent& evt);
 	
 private:
 	DECLARE_EVENT_TABLE()
};

#endif