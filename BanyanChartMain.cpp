/***************************************************************
 * Name:      BanyanChartMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    lunanerdderg ()
 * Created:   2026-09-19
 * Copyright: lunanerdderg (https://github.com/lunanerdderg)
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "BanyanChartMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(BanyanChartFrame)
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format) {
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f ) {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(BanyanChartFrame)
const wxWindowID BanyanChartFrame::ID_CANVAS = wxNewId();
const wxWindowID BanyanChartFrame::idMenuNew = wxNewId();
const wxWindowID BanyanChartFrame::idMenuOpen = wxNewId();
const wxWindowID BanyanChartFrame::idMenuSave = wxNewId();
const wxWindowID BanyanChartFrame::idMenuSaveAs = wxNewId();
const wxWindowID BanyanChartFrame::idMenuQuit = wxNewId();
const wxWindowID BanyanChartFrame::idMenuEditText = wxNewId();
const wxWindowID BanyanChartFrame::idMenuAddBlock = wxNewId();
const wxWindowID BanyanChartFrame::idMenuAddNode = wxNewId();
const wxWindowID BanyanChartFrame::idMenuDelete = wxNewId();
const wxWindowID BanyanChartFrame::idMenuZoomIn = wxNewId();
const wxWindowID BanyanChartFrame::idMenuZoomOut = wxNewId();
const wxWindowID BanyanChartFrame::idMenuAbout = wxNewId();
const wxWindowID BanyanChartFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(BanyanChartFrame,wxFrame)
    //(*EventTable(BanyanChartFrame)
    //*)
    EVT_PAINT(BanyanChartFrame::paintEvent)
    EVT_LEFT_DOWN(BanyanChartFrame::mouseDown)
    EVT_LEFT_UP(BanyanChartFrame::mouseReleased)
    EVT_RIGHT_DOWN(BanyanChartFrame::rightClick)
    EVT_MOTION(BanyanChartFrame::mouseMoved)
    EVT_LEAVE_WINDOW(BanyanChartFrame::mouseLeftWindow)
    EVT_MOUSEWHEEL(BanyanChartFrame::mouseWheelMoved)
    EVT_LEFT_DCLICK(BanyanChartFrame::doubleClick)
END_EVENT_TABLE()

BanyanChartFrame::BanyanChartFrame(wxWindow* parent,wxWindowID id) {
    File = FileParser();
    this->Canvas_initializeBoxes();
    this->font = this->GetFont();

    //(*Initialize(BanyanChartFrame)
    wxBoxSizer* BoxSizer1;
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, wxID_ANY, _("BanyanChart"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(800,600));
    Move(wxPoint(50,50));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Canvas = new wxPanel(this, ID_CANVAS, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_CANVAS"));
    BoxSizer1->Add(Canvas, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, idMenuNew, _("New\tCtrl-N"), _("Create a new file"), wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem4 = new wxMenuItem(Menu1, idMenuOpen, _("Open\tCtrl-O"), _("Open a file"), wxITEM_NORMAL);
    Menu1->Append(MenuItem4);
    MenuItem5 = new wxMenuItem(Menu1, idMenuSave, _("Save\tCtrl-S"), _("Save your file"), wxITEM_NORMAL);
    Menu1->Append(MenuItem5);
    MenuItem6 = new wxMenuItem(Menu1, idMenuSaveAs, _("Save as\tCtrl-Shift-S"), _("Save your file as"), wxITEM_NORMAL);
    Menu1->Append(MenuItem6);
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tCtrl-Q"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    MenuItem12 = new wxMenuItem(Menu3, idMenuEditText, _("Edit text"), _("Edit the text of a block or node"), wxITEM_NORMAL);
    Menu3->Append(MenuItem12);
    MenuItem7 = new wxMenuItem(Menu3, idMenuAddBlock, _("Add block"), _("Add a block"), wxITEM_NORMAL);
    Menu3->Append(MenuItem7);
    MenuItem11 = new wxMenuItem(Menu3, idMenuAddNode, _("Add node"), _("Add a node to a block"), wxITEM_NORMAL);
    Menu3->Append(MenuItem11);
    MenuItem8 = new wxMenuItem(Menu3, idMenuDelete, _("Delete\tDelete"), _("Delete a block"), wxITEM_NORMAL);
    Menu3->Append(MenuItem8);
    MenuBar1->Append(Menu3, _("Edit"));
    Menu5 = new wxMenu();
    MenuItem9 = new wxMenuItem(Menu5, idMenuZoomIn, _("Zoom in\tCtrl-="), _("Zoom into the canvas"), wxITEM_NORMAL);
    Menu5->Append(MenuItem9);
    MenuItem10 = new wxMenuItem(Menu5, idMenuZoomOut, _("Zoom out\tCtrl--"), _("Zoom out of the canvas"), wxITEM_NORMAL);
    Menu5->Append(MenuItem10);
    MenuBar1->Append(Menu5, _("View"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    Layout();
    //*)

    Connect(idMenuNew, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnNew);
    Connect(idMenuOpen, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnOpen);
    Connect(idMenuSave, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnSave);
    Connect(idMenuSaveAs, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnSaveAs);
    Connect(idMenuQuit, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnQuit);

    Connect(idMenuZoomIn, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnZoomIn);
    Connect(idMenuZoomOut, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnZoomOut);

    Connect(idMenuAddBlock, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnAddBlock);
    Connect(idMenuAddNode, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnAddNode);
    Connect(idMenuEditText, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnEditText);
    Connect(idMenuDelete, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnDelete);

    Connect(idMenuAbout, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnAbout);
}
/*
    Canvas->Connect(wxEVT_PAINT, (wxObjectEventFunction)&BanyanChartFrame::paintEvent);
    Canvas->Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&BanyanChartFrame::mouseDown);
    Canvas->Connect(wxEVT_LEFT_UP, (wxObjectEventFunction)&BanyanChartFrame::mouseReleased);
    Canvas->Connect(wxEVT_RIGHT_DOWN, (wxObjectEventFunction)&BanyanChartFrame::rightClick);
    Canvas->Connect(wxEVT_MOTION, (wxObjectEventFunction)&BanyanChartFrame::mouseMoved);
    Canvas->Connect(wxEVT_LEAVE_WINDOW, (wxObjectEventFunction)&BanyanChartFrame::mouseLeftWindow);
    Canvas->Connect(wxEVT_MOUSEWHEEL, (wxObjectEventFunction)&BanyanChartFrame::mouseWheelMoved);
*/
BanyanChartFrame::~BanyanChartFrame() {
    //(*Destroy(BanyanChartFrame)
    //*)
}




void BanyanChartFrame::Canvas_initializeBoxes(bool reset) {
    size_t startNum = this->Canvas_boxDraggingList.size();
    size_t numBlocks = this->File.getNumBlocks();
    if (reset) {
        this->Canvas_dragging = false;
        this->Canvas_frameX = 0;
        this->Canvas_frameY = 0;
        this->Canvas_selectedBlock = {};
        this->Canvas_boxDraggingList = {};
        this->Canvas_boxXList = {};
        this->Canvas_boxYList = {};
        this->Canvas_boxWList = {};
        this->Canvas_boxHList = {};

        startNum = 0;
    }
    if (numBlocks > this->Canvas_boxDraggingList.size()) {
        for (size_t i = startNum; i != -1 && i < numBlocks; ++i) { // - this->Canvas_boxDraggingList.size()));
            this->Canvas_selectedBlock.push_back(false);
            this->Canvas_boxDraggingList.push_back(false);
            this->Canvas_boxXList.push_back(100);
            this->Canvas_boxYList.push_back(i*boxHeight*4/2+boxHeight/8);
            this->Canvas_boxWList.push_back(boxWidth);
            this->Canvas_boxHList.push_back(boxHeight);
        }
    }
}

double BanyanChartFrame::Canvas_getXPosition(double location) {
    return (location + this->Canvas_frameX) * this->Canvas_zoom / 100.0;
}
double BanyanChartFrame::Canvas_getYPosition(double location) {
    return (location + this->Canvas_frameY) * this->Canvas_zoom / 100.0;
}
double BanyanChartFrame::Canvas_getProportions(double widthHeightThickness, bool invert) {
    if (invert) {
        return widthHeightThickness * 100.0 / this->Canvas_zoom;
    }
    return widthHeightThickness * this->Canvas_zoom / 100.0;
}



void BanyanChartFrame::OnNew(wxCommandEvent& event) {
    if (this->unsaved) {
        if (wxMessageBox(_("Current content has not been saved! Proceed?"), _("Please confirm"), wxICON_QUESTION | wxYES_NO, this) == wxNO ) {
            return;
        }
    }
    this->File.newInstance();
    this->Canvas_initializeBoxes();
    Refresh();
    this->unsaved = false;
}
void BanyanChartFrame::OnOpen(wxCommandEvent& WXUNUSED(event)) {
    if (this->unsaved) {
        if (wxMessageBox(_("Current content has not been saved! Proceed?"), _("Please confirm"), wxICON_QUESTION | wxYES_NO, this) == wxNO ) {
            return;
        }
    }
    wxFileDialog openFileDialog(this, _("Open BanyanChart file"), "", "", "BanyanChart files (*.byfc)|*.byfc", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    this->File.newInstance(openFileDialog.GetPath());
    this->Canvas_initializeBoxes();
    Refresh();
    this->unsaved = false;
}
void BanyanChartFrame::OnSave(wxCommandEvent& WXUNUSED(event)) {
    if (File.getPath() == "") {
        wxFileDialog saveFileDialog(this, _("Save BanyanChart file"), "", "", "BanyanChart files (*.byfc)|*.byfc", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
        if (saveFileDialog.ShowModal() == wxID_CANCEL) {
            return;
        }

        this->File.setPath(saveFileDialog.GetPath());
        this->File.save();
        this->unsaved = false;
    }
    else {
        this->File.save();
        this->unsaved = false;
    }
}
void BanyanChartFrame::OnSaveAs(wxCommandEvent& WXUNUSED(event)) {
    wxFileDialog saveFileDialog(this, _("Save BanyanChart file"), "", "", "BanyanChart files (*.byfc)|*.byfc", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    this->File.save(saveFileDialog.GetPath());
    this->unsaved = false;
}

void BanyanChartFrame::changeText(std::string text, size_t blockIndex, size_t nodeIndex) {
    this->File.setText(text, blockIndex, nodeIndex);
    this->unsaved = true;
}
void BanyanChartFrame::changeText(const char text[], size_t blockIndex, size_t nodeIndex) {
    this->changeText(text, blockIndex, nodeIndex);
}
void BanyanChartFrame::changeText(wxString text, size_t blockIndex, size_t nodeIndex) {
    this->changeText(text.ToStdString(), blockIndex, nodeIndex);
}
void BanyanChartFrame::changeText(size_t blockIndex, size_t nodeIndex) {
    wxTextEntryDialog textDialog(this, _("Enter text"));
    if (textDialog.ShowModal() == wxID_CANCEL) {
        return;
    }
    this->changeText(textDialog.GetValue(), blockIndex, nodeIndex);
}
void BanyanChartFrame::doubleClick(wxMouseEvent& event) {
    size_t index = -1;
    for (size_t i = 0; i != -1 && i < this->Canvas_boxXList.size(); ++i) {
        const int xLocation = this->Canvas_getXPosition(this->Canvas_boxXList.at(i));
        const int yLocation = this->Canvas_getYPosition(this->Canvas_boxYList.at(i));
        if (event.GetPosition().x >= xLocation && event.GetPosition().x <= xLocation + this->Canvas_getProportions(this->Canvas_boxWList.at(i)) &&
                event.GetPosition().y >= yLocation && event.GetPosition().y <= yLocation + this->Canvas_getProportions(this->Canvas_boxHList.at(i))) {
            index = i;
        }
    }
    if (index != -1) {
        this->changeText(index);
        Refresh();
    }
}
void BanyanChartFrame::OnEditText(wxCommandEvent& WXUNUSED(event)) {
    if (this->Canvas_selectedBlock.size() > 0) {
        wxTextEntryDialog textDialog(this, _("Enter text"));
        if (textDialog.ShowModal() == wxID_CANCEL) {
            return;
        }
        for (size_t index = 0; index != -1 && index < this->Canvas_selectedBlock.size(); ++index) {
            if (this->Canvas_selectedBlock.at(index)) {
                this->changeText(textDialog.GetValue().ToStdString(), index);
            }
        }
        Refresh();
    }
}
void BanyanChartFrame::OnAddBlock(wxCommandEvent& WXUNUSED(event)) {
    this->File.addBlock("");
    this->Canvas_initializeBoxes(false);
    Refresh();
    this->unsaved = true;
}
void BanyanChartFrame::OnAddNode(wxCommandEvent& WXUNUSED(event)) {
}
void BanyanChartFrame::OnDelete(wxCommandEvent& WXUNUSED(event)) {
    for (size_t i = this->Canvas_selectedBlock.size(); i != -1 && i < this->File.getNumBlocks(); --i) {
        if (this->Canvas_selectedBlock.at(i)) {
            this->File.removeBlock(i);
            this->Canvas_boxDraggingList.erase(this->Canvas_boxDraggingList.begin() + i);
            this->Canvas_boxXList.erase(this->Canvas_boxXList.begin() + i);
            this->Canvas_boxYList.erase(this->Canvas_boxYList.begin() + i);
            this->Canvas_boxWList.erase(this->Canvas_boxWList.begin() + i);
            this->Canvas_boxHList.erase(this->Canvas_boxHList.begin() + i);
            this->Canvas_selectedBlock.erase(this->Canvas_selectedBlock.begin() + i);
            this->unsaved = true;
        }
    }
    Refresh();
}

void BanyanChartFrame::OnZoomIn(wxCommandEvent& WXUNUSED(event)) {
    if (this->Canvas_zoom + 25 <= 400) {
        this->Canvas_zoom += 25;
        Refresh();
    }
}
void BanyanChartFrame::OnZoomOut(wxCommandEvent& WXUNUSED(event)) {
    if (this->Canvas_zoom - 25 >= 1) {
        this->Canvas_zoom -= 25;
        Refresh();
    }
}

void BanyanChartFrame::OnAbout(wxCommandEvent& event) {
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}
void BanyanChartFrame::OnQuit(wxCommandEvent& event) {
    Close();
}
void BanyanChartFrame::OnClose(wxCloseEvent& event) {
    event.Skip(TRUE);
}




void BanyanChartFrame::mouseMoved(wxMouseEvent& event) {
    if (this->Canvas_dragging && event.Dragging()) {
        int delta_x = event.GetPosition().x - this->Canvas_mousePrevX;
        int delta_y = event.GetPosition().y - this->Canvas_mousePrevY;

        this->Canvas_frameX += Canvas_getProportions(delta_x, true);
        this->Canvas_frameY += Canvas_getProportions(delta_y, true);

        this->Canvas_boxMoved = true;
    }
    else if (!this->Canvas_dragging) {
        for (size_t index = 0; index != -1 && index < this->Canvas_boxDraggingList.size(); ++index) {
            if (this->Canvas_boxDraggingList.at(index) && event.Dragging()) {
                int delta_x = event.GetPosition().x - this->Canvas_mousePrevX;
                int delta_y = event.GetPosition().y - this->Canvas_mousePrevY;

                this->Canvas_boxXList.at(index) += Canvas_getProportions(delta_x, true);
                this->Canvas_boxYList.at(index) += Canvas_getProportions(delta_y, true);

                this->Canvas_boxMoved = true;
            }
        }
    }
    this->Canvas_mousePrevX = event.GetPosition().x;
    this->Canvas_mousePrevY = event.GetPosition().y;
    Refresh();
}

void BanyanChartFrame::mouseDown(wxMouseEvent& event) {
    bool selectionMade = false;
    this->Canvas_boxDraggingList = this->Canvas_selectedBlock;
    for (size_t index = 0; index != -1 && index < this->Canvas_boxDraggingList.size() && index < this->Canvas_boxDraggingList.size(); ++index) {
        const int xLocation = this->Canvas_getXPosition(this->Canvas_boxXList.at(index));
        const int yLocation = this->Canvas_getYPosition(this->Canvas_boxYList.at(index));
        if (event.GetPosition().x >= xLocation && event.GetPosition().x <= xLocation + this->Canvas_getProportions(this->Canvas_boxWList.at(index)) &&
                event.GetPosition().y >= yLocation && event.GetPosition().y <= yLocation + this->Canvas_getProportions(this->Canvas_boxHList.at(index))) {
            this->Canvas_dragging = false;
            this->Canvas_boxDraggingList.at(index) = true;
            selectionMade = true;
        }
    }
    if (!selectionMade) {
        this->Canvas_dragging = true;
    }
    this->Canvas_mousePrevX = event.GetPosition().x;
    this->Canvas_mousePrevY = event.GetPosition().y;
    Refresh();
}

void BanyanChartFrame::mouseReleased(wxMouseEvent& event) {
    bool ctrlPressed = event.ControlDown();
    bool shiftPressed = event.ShiftDown();
    for (size_t index = 0; index != -1 && index < this->Canvas_boxDraggingList.size(); ++index) {
        this->Canvas_boxDraggingList.at(index) = false;
        if (!this->Canvas_boxMoved) {
            const int xLocation = this->Canvas_getXPosition(this->Canvas_boxXList.at(index));
            const int yLocation = this->Canvas_getYPosition(this->Canvas_boxYList.at(index));
            if (event.GetPosition().x >= xLocation && event.GetPosition().x <= xLocation + this->Canvas_getProportions(this->Canvas_boxWList.at(index)) &&
                    event.GetPosition().y >= yLocation && event.GetPosition().y <= yLocation + this->Canvas_getProportions(this->Canvas_boxHList.at(index))) {
                if (ctrlPressed || shiftPressed) {
                    this->Canvas_selectedBlock.at(index) = !this->Canvas_selectedBlock.at(index);
                }
                else {
                    this->Canvas_selectedBlock.at(index) = true;
                }
            }
            else if (!ctrlPressed && !shiftPressed) {
                this->Canvas_selectedBlock.at(index) = false;
            }
        }
    }
    this->Canvas_dragging = false;
    this->Canvas_boxMoved = false;
    Refresh();
}

void BanyanChartFrame::rightClick(wxMouseEvent& event) {
}

void BanyanChartFrame::mouseLeftWindow(wxMouseEvent& event) {
    for (size_t index = 0; index != -1 && index < this->Canvas_boxDraggingList.size(); ++index) {
        this->Canvas_boxDraggingList.at(index) = false;
    }
}

void BanyanChartFrame::mouseWheelMoved(wxMouseEvent& event) {
    if (event.GetWheelAxis() == wxMOUSE_WHEEL_HORIZONTAL) {
//        if ( ( event.GetWheelRotation() >= 0 && !event.IsWheelInverted() ) || ( event.GetWheelRotation() < 0 && event.IsWheelInverted() ) ) {
        if (event.GetWheelRotation() < 0) {
            this->Canvas_frameX += -100 * event.GetWheelRotation() / (5 * this->Canvas_zoom);
        }
        else {
            this->Canvas_frameX -= 100 * event.GetWheelRotation() / (5 * this->Canvas_zoom);
        }
    }
    else if (event.GetWheelAxis() == wxMOUSE_WHEEL_VERTICAL) {
        if (event.ControlDown()) {
            wxCommandEvent commandEvent;
            if (event.GetWheelRotation() > 0) {
                this->OnZoomIn(commandEvent);
            }
            else if (event.GetWheelRotation() < 0) {
                this->OnZoomOut(commandEvent);
            }
        }
        else {
//            if ( ( event.GetWheelRotation() >= 0 && !event.IsWheelInverted() ) || ( event.GetWheelRotation() < 0 && event.IsWheelInverted() ) ) {
            if (event.GetWheelRotation() >= 0) {
                this->Canvas_frameY += 100 * event.GetWheelRotation() / (5 * this->Canvas_zoom);
            }
            else {
                this->Canvas_frameY -= -100 * event.GetWheelRotation() / (5 * this->Canvas_zoom);
            }
        }
    }
    Refresh();
}

void BanyanChartFrame::paintEvent(wxPaintEvent& event) {
    wxPaintDC dc(this);
    this->Canvas_render(dc);
}



void BanyanChartFrame::Canvas_render(wxDC&  dc) {
    dc.SetBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    dc.SetPen(wxPen(wxColor(255,175,175), this->Canvas_getProportions()));
    for (size_t index = 0; index != -1 && index < this->Canvas_boxDraggingList.size() && index < this->File.getNumBlocks(); ++index) {
        double xLocation = this->Canvas_getXPosition(this->Canvas_boxXList.at(index));
        double yLocation = this->Canvas_getYPosition(this->Canvas_boxYList.at(index));
        double width = this->Canvas_getProportions(this->Canvas_boxWList.at(index));
        double height = this->Canvas_getProportions(this->Canvas_boxHList.at(index));
        if (xLocation + width > 0 && xLocation < this->GetClientSize().GetWidth()) {
            if (this->Canvas_selectedBlock.at(index)) {
                dc.SetPen(wxPen(wxColor(255,75,75), this->Canvas_getProportions(2)));
            }
            dc.DrawRectangle(xLocation, yLocation, width, height);
            if (this->Canvas_selectedBlock.at(index)) {
                dc.SetPen(wxPen(wxColor(255,175,175), this->Canvas_getProportions()));
            }
            wxFont tempFont = font;
            this->SetFont(tempFont.Scale(this->Canvas_getProportions(1)));
            dc.DrawText(this->File.getBlockBody(index).c_str(), xLocation, yLocation);
        }
    }
}
