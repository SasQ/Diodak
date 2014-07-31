#include "Circuit.hh"

// wxWidgets library headers.
#include <wx/dcclient.h>
#include <wx/colour.h>
#include <wx/dcclient.h>
#include <wx/brush.h>
#include <wx/pen.h>


/// ----- Helper functions for drawing the grid -----


/// Low-level grid drawing function.
void DrawGrid(wxDC& canvas, wxColour color, wxSize gridCellSize, wxSize gridSize)
{
	unsigned gridStepX = gridCellSize.GetWidth(), gridStepY = gridCellSize.GetHeight(),
	         gridSizeX = gridSize.GetWidth(), gridSizeY = gridSize.GetHeight();
	
	canvas.SetPen( wxPen(color,1) );
	for (int x=0; x < gridSizeX; x += gridStepX) canvas.DrawLine(x,0, x,gridSizeY);
	for (int y=0; y < gridSizeY; y += gridStepY) canvas.DrawLine(0,y, gridSizeX,y);
}


// Circuit view's static event table.
BEGIN_EVENT_TABLE(CircuitView, wxScrolledWindow)
	EVT_ERASE_BACKGROUND(CircuitView::OnEraseBg)
END_EVENT_TABLE()


/// Constructor.
CircuitView::CircuitView(wxWindow* parent):
	wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxSize(200,100), wxSUNKEN_BORDER|wxVSCROLL|wxHSCROLL)
{
	// Nothing to see here, kid...
}


/// Erase the window's background.
void CircuitView::OnEraseBg(wxEraseEvent& evt)
{
	wxDC *dc = evt.GetDC();
	
	// Prepare the grid parameters.
	wxColour grid0Color(251,251,251), grid1Color(247,247,247), grid2Color(242,242,242); // Grid colors: FB, F7, F2.
	unsigned grid0StepX = 10, grid0StepY = grid0StepX;                                  // Grid 0 resolution is 10 pixels.
	unsigned grid1StepX = 10*grid0StepX, grid1StepY = 10*grid0StepY,                    // Grid 1 is 10 times more sparse.
	         grid2StepX = 10*grid1StepX, grid2StepY = 10*grid1StepY;                    // Grid 3 is 10 times more still sparse.
	unsigned gridSizeX = grid2StepX, gridSizeY = grid2StepY;                            // The size of one repetition of the grid.
	
	// Fill the background with white.
	dc->SetPen(wxNullPen);
	dc->SetBrush(*wxWHITE_BRUSH);
	dc->DrawRectangle(0,0, gridSizeX,gridSizeY);
	
	// Paint a grid on it and set it as window's background.
	DrawGrid(*dc, grid0Color, wxSize(grid0StepX,grid0StepY), wxSize(gridSizeX,gridSizeY) );
	DrawGrid(*dc, grid1Color, wxSize(grid1StepX,grid1StepY), wxSize(gridSizeX,gridSizeY) );
	DrawGrid(*dc, grid2Color, wxSize(grid2StepX,grid2StepY), wxSize(gridSizeX,gridSizeY) );
}