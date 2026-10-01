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
const wxWindowID BanyanChartFrame::idMenuAdd = wxNewId();
const wxWindowID BanyanChartFrame::idMenuDelete = wxNewId();
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
END_EVENT_TABLE()

BanyanChartFrame::BanyanChartFrame(wxWindow* parent,wxWindowID id) { // BOOKMARK
    File = new FileParser( { {"Block1" , "1Node1","1Node2","1Node3"}, {"Block2" , "2Node1","2Node2","2Node3"} }, { {0 , 0,1,0}, {0 , 1,1,0} } );
    this->Canvas_initializeBoxes();

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
    MenuItem7 = new wxMenuItem(Menu3, idMenuAdd, _("Add"), _("Add a block"), wxITEM_NORMAL);
    Menu3->Append(MenuItem7);
    MenuItem8 = new wxMenuItem(Menu3, idMenuDelete, _("Delete\tDelete"), _("Delete a block"), wxITEM_NORMAL);
    Menu3->Append(MenuItem8);
    MenuBar1->Append(Menu3, _("Blocks"));
    Menu4 = new wxMenu();
    MenuBar1->Append(Menu4, _("Nodes"));
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
    Connect(idMenuAdd, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnAdd);
    Connect(idMenuDelete, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnDelete);

    Connect(idMenuQuit, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnQuit);
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



void BanyanChartFrame::Canvas_initializeBoxes() {
    this->Canvas_boxDraggingList = {};
    this->Canvas_boxXList = {};
    this->Canvas_boxYList = {};
    this->Canvas_boxWList = {};
    this->Canvas_boxHList = {};

    size_t numBlocks = this->File.getNumBlocks();

    for (size_t i = 0; i != -1 && i < numBlocks; ++i) {
        this->Canvas_boxDraggingList.push_back(false);
        this->Canvas_boxXList.push_back(100*numBlocks/(numBlocks - i));
        this->Canvas_boxYList.push_back(100);
        this->Canvas_boxWList.push_back(50);
        this->Canvas_boxHList.push_back(50);
    }
}



void BanyanChartFrame::OnNew(wxCommandEvent& event) {
    this->File.newInstance();
    this->Canvas_initializeBoxes();
    Refresh();
}

void BanyanChartFrame::OnOpen(wxCommandEvent& WXUNUSED(event)) {
    if (false) { // Remember to replace "false" with a function that tests if the file has been saved (BOOKMARK)
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
}

void BanyanChartFrame::OnSave(wxCommandEvent& WXUNUSED(event)) {
    if (File.getPath() == fs::path()) {
        wxFileDialog saveFileDialog(this, _("Save BanyanChart file"), "", "", "BanyanChart files (*.byfc)|*.byfc", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
        if (saveFileDialog.ShowModal() == wxID_CANCEL) {
            return;
        }

        this->File.setPath(saveFileDialog.GetPath());
        this->File.save();
    }
    else {
        this->File.save();
    }
}

void BanyanChartFrame::OnSaveAs(wxCommandEvent& WXUNUSED(event)) {
    wxFileDialog saveFileDialog(this, _("Save BanyanChart file"), "", "", "BanyanChart files (*.byfc)|*.byfc", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    this->File.save(saveFileDialog.GetPath());
}

void BanyanChartFrame::OnAdd(wxCommandEvent& WXUNUSED(event)) {
    this->File.addBlock("");
    this->Canvas_initializeBoxes();
    Refresh();
}
void BanyanChartFrame::OnDelete(wxCommandEvent& WXUNUSED(event)) {
    if (this->selectedBlock != -1) {
        this->File.removeBlock(this->selectedBlock);
        this->Canvas_boxDraggingList.erase(this->Canvas_boxDraggingList.begin() + this->selectedBlock);
        this->Canvas_boxXList.erase(this->Canvas_boxXList.begin() + this->selectedBlock);
        this->Canvas_boxYList.erase(this->Canvas_boxYList.begin() + this->selectedBlock);
        this->Canvas_boxWList.erase(this->Canvas_boxWList.begin() + this->selectedBlock);
        this->Canvas_boxHList.erase(this->Canvas_boxHList.begin() + this->selectedBlock);
        selectedBlock = -1;
        Refresh();
    }
}

void BanyanChartFrame::OnQuit(wxCommandEvent& event) {
    Close();
}

void BanyanChartFrame::OnAbout(wxCommandEvent& event) {
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void BanyanChartFrame::OnClose(wxCloseEvent& event) {
    event.Skip(TRUE);
}



void BanyanChartFrame::mouseMoved(wxMouseEvent& event) {
    for (size_t index = 0; index != -1 && index < this->Canvas_boxDraggingList.size(); ++index) {
        if (this->Canvas_boxDraggingList.at(index) && event.Dragging()) {
            int delta_x = event.GetPosition().x - this->Canvas_mousePrevX;
            int delta_y = event.GetPosition().y - this->Canvas_mousePrevY;

            this->Canvas_boxXList.at(index) += delta_x;
            this->Canvas_boxYList.at(index) += delta_y;

            this->Canvas_mousePrevX = event.GetPosition().x;
            this->Canvas_mousePrevY = event.GetPosition().y;
            Refresh(); // trigger paint event
        }
    }
}

void BanyanChartFrame::mouseDown(wxMouseEvent& event) {
    bool selectionMade = false;
    for (size_t index = 0; index != -1 && index < this->Canvas_boxDraggingList.size(); ++index) {
        if (event.GetPosition().x >= this->Canvas_boxXList.at(index) && event.GetPosition().x <= this->Canvas_boxXList.at(index) + this->Canvas_boxWList.at(index) &&
            event.GetPosition().y >= this->Canvas_boxYList.at(index) && event.GetPosition().y <= this->Canvas_boxYList.at(index) + this->Canvas_boxHList.at(index))
        {
            this->Canvas_boxDraggingList.at(index) = true;
            this->Canvas_mousePrevX = event.GetPosition().x;
            this->Canvas_mousePrevY = event.GetPosition().y;
            this->selectedBlock = index;
            selectionMade = true;
        }
    }
    if (!selectionMade) {
        selectedBlock = -1;
    }
    Refresh();
}

void BanyanChartFrame::mouseReleased(wxMouseEvent& event) {
    for (size_t index = 0; index != -1 && index < this->Canvas_boxDraggingList.size(); ++index) {
        this->Canvas_boxDraggingList.at(index) = false;
    }
}

void BanyanChartFrame::rightClick(wxMouseEvent& event) {
}

void BanyanChartFrame::mouseLeftWindow(wxMouseEvent& event) {
    for (size_t index = 0; index != -1 && index < this->Canvas_boxDraggingList.size(); ++index) {
        this->Canvas_boxDraggingList.at(index) = false;
    }
}

void BanyanChartFrame::mouseWheelMoved(wxMouseEvent& event) {
}

void BanyanChartFrame::paintEvent(wxPaintEvent& event) {
    wxPaintDC dc(this);
    this->Canvas_render(dc);
}



void BanyanChartFrame::Canvas_render(wxDC&  dc) {
    dc.SetBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    dc.SetPen( wxPen( wxColor(255,175,175), 2 ) );
    for (size_t index = 0; index != -1 && index < this->Canvas_boxDraggingList.size() && index < this->File.getNumBlocks(); ++index) {
        if (index == this->selectedBlock) {
            dc.SetPen( wxPen( wxColor(255,75,75), 3 ) );
        }
        dc.DrawRectangle(this->Canvas_boxXList.at(index), this->Canvas_boxYList.at(index), this->Canvas_boxWList.at(index), this->Canvas_boxHList.at(index));
        if (index == this->selectedBlock) {
            dc.SetPen( wxPen( wxColor(255,175,175), 2 ) );
        }
        dc.DrawText(this->File.getBlockBody(index).c_str(), this->Canvas_boxXList.at(index), this->Canvas_boxYList.at(index));
    }
}
