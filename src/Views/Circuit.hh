#ifndef CIRCUIT_VIEW_HH
#define CIRCUIT_VIEW_HH

// wxWidgets library headers.
#include <wx/scrolwin.h>
#include <wx/event.h>

// Our own headers.
#include "Grid.hh"

/// Custom scrolled window class for displaying circuits.
class CircuitView: public wxScrolledWindow
{
 public:
 	CircuitView(wxWindow* parent);
 	virtual ~CircuitView();
 	void OnEraseBg(wxEraseEvent& evt);
 	
 private:
 	Grid *grids[3];  // We will store 3 grids of different levels here.
 	
 	DECLARE_EVENT_TABLE()
};

#endif