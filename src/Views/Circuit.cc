#include "Circuit.hh"

// wxWidgets library headers.
#include <wx/dcclient.h>
#include <wx/colour.h>
#include <wx/brush.h>
#include <wx/pen.h>


// Circuit view's static event table.
BEGIN_EVENT_TABLE(CircuitView, wxScrolledWindow)
	EVT_ERASE_BACKGROUND(CircuitView::OnEraseBg)
END_EVENT_TABLE()


/// Constructor.
CircuitView::CircuitView(wxWindow* parent):
	wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxSize(200,100), wxSUNKEN_BORDER|wxVSCROLL|wxHSCROLL)
{
	// Prepare the grids. 
	wxColour grid0Color(251,251,251), grid1Color(246,246,246), grid2Color(238,238,238); // Grid colors: FB, F6, EE.
	unsigned grid0StepX = 10, grid0StepY = grid0StepX;                                  // Grid 0 resolution is 10 pixels.
	unsigned grid1StepX = 10*grid0StepX, grid1StepY = 10*grid0StepY,                    // Grid 1 is 10 times more sparse.
	         grid2StepX = 10*grid1StepX, grid2StepY = 10*grid1StepY;                    // Grid 3 is 10 times more still sparse.
	
	// Create the grids on the heap.
	grids[0] = new Grid( grid0Color, wxSize(grid0StepX,grid0StepY) );
	grids[1] = new Grid( grid1Color, wxSize(grid1StepX,grid1StepY) );
	grids[2] = new Grid( grid2Color, wxSize(grid2StepX,grid2StepY) );
}

/// Destructor.
CircuitView::~CircuitView()
{
	// Delete the grids.
	delete grids[0];  delete grids[1];  delete grids[2];
}


/// Erase the window's background.
void CircuitView::OnEraseBg(wxEraseEvent& evt)
{
	wxDC *dc = evt.GetDC();
	DoPrepareDC(*dc);        // Map the DC's coordinates to the scrolled coordinates.
	
	// Get the dimensions of the virtual view.
	wxSize viewSize = GetVirtualSize();
	unsigned gridSizeX = viewSize.GetWidth(), gridSizeY = viewSize.GetHeight();
	
	// Fill the background with white.
	dc->SetPen(wxNullPen);
	dc->SetBrush(*wxWHITE_BRUSH);
	dc->DrawRectangle(0,0, gridSizeX,gridSizeY);
	
	// Paint all three levels of the grid over it.
	grids[0]->DrawOn(*dc, wxRect(0,0,gridSizeX,gridSizeY) );
	grids[1]->DrawOn(*dc, wxRect(0,0,gridSizeX,gridSizeY) );
	grids[2]->DrawOn(*dc, wxRect(0,0,gridSizeX,gridSizeY) );
}