#include "Circuit.hh"
#include <iostream>

// wxWidgets library headers.
#include <wx/dcclient.h>
#include <wx/gdicmn.h>    // wxSize, wxRect, wxPoint
#include <wx/region.h>
#include <wx/colour.h>
#include <wx/brush.h>
#include <wx/pen.h>


// Circuit view's static event table.
BEGIN_EVENT_TABLE(CircuitView, wxScrolledWindow)
	EVT_ERASE_BACKGROUND(CircuitView::OnEraseBg)
	EVT_PAINT(CircuitView::OnPaint)
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
	// Do nothing. The background is being updated along with everything else in the Paint event.
}

/// Update the window's client area.
void CircuitView::OnPaint(wxPaintEvent& evt)
{
	wxPaintDC dc(this);
	DoPrepareDC(dc);     // Remap the DC's coordinates to the virtual view's coordinates.
	
	// Update all damaged regions, one at a time.
	wxRegionIterator regions( GetUpdateRegion() );
	while (regions) {
		wxRect region( regions.GetRect() );
		wxPoint from( CalcUnscrolledPosition( region.GetTopLeft()     ) ),
		        to(   CalcUnscrolledPosition( region.GetBottomRight() ) );
		UpdateRegion(dc, wxRect(from,to) );
		++regions;
	}
}

void CircuitView::UpdateRegion(wxDC& dc, const wxRect& region)
{
	// Fill the background with white.
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.SetPen(wxNullPen);
	dc.DrawRectangle(region);
	
	// Paint all three levels of the grid over it.
	grids[0]->DrawOn(dc,region);
	grids[1]->DrawOn(dc,region);
	grids[2]->DrawOn(dc,region);
}