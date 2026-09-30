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
const wxWindowID BanyanChartFrame::idMenuAbout = wxNewId();
const wxWindowID BanyanChartFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(BanyanChartFrame,wxFrame)
    //(*EventTable(BanyanChartFrame)
    //*)
END_EVENT_TABLE()

BanyanChartFrame::BanyanChartFrame(wxWindow* parent,wxWindowID id) {
    this->Canvas_dragging = false;
    this->Canvas_mouseX = 100;
    this->Canvas_mouseY = 100;

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
    MenuBar1->Append(Menu3, _("Object"));
    Menu4 = new wxMenu();
    MenuBar1->Append(Menu4, _("Node"));
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

    Canvas->Connect(wxEVT_PAINT, (wxObjectEventFunction)&BanyanChartFrame::paintEvent, NULL, this);
    Canvas->Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&BanyanChartFrame::mouseDown, NULL, this);
    Canvas->Connect(wxEVT_LEFT_UP, (wxObjectEventFunction)&BanyanChartFrame::mouseReleased, NULL, this);
    Canvas->Connect(wxEVT_RIGHT_DOWN, (wxObjectEventFunction)&BanyanChartFrame::rightClick, NULL, this);
    Canvas->Connect(wxEVT_MOTION, (wxObjectEventFunction)&BanyanChartFrame::mouseMoved, NULL, this);
    Canvas->Connect(wxEVT_LEAVE_WINDOW, (wxObjectEventFunction)&BanyanChartFrame::mouseLeftWindow, NULL, this);
    Canvas->Connect(wxEVT_MOUSEWHEEL, (wxObjectEventFunction)&BanyanChartFrame::mouseWheelMoved, NULL, this);
    Connect(idMenuQuit, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnQuit);
    Connect(idMenuAbout, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnAbout);
    //*)
}

BanyanChartFrame::~BanyanChartFrame() {
    //(*Destroy(BanyanChartFrame)
    //*)
}



void BanyanChartFrame::OnNew(wxCommandEvent& event) {
    this->File.newInstance();
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

    this->File.newInstance(openFileDialog.GetPath().mb_str());
}

void BanyanChartFrame::OnSave(wxCommandEvent& WXUNUSED(event)) {
    if (File.getPath() == fs::path()) {
        wxFileDialog saveFileDialog(this, _("Save BanyanChart file"), "", "", "BanyanChart files (*.byfc)|*.byfc", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
        if (saveFileDialog.ShowModal() == wxID_CANCEL) {
            return;
        }

        this->File.setPath(std::string(saveFileDialog.GetPath().mb_str()));
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

    this->File.save(std::string(saveFileDialog.GetPath().mb_str()));
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
    if (this->Canvas_dragging && event.Dragging())
    {
        int delta_x = event.GetPosition().x - this->Canvas_mousePrevX;
        int delta_y = event.GetPosition().y - this->Canvas_mousePrevY;

        this->Canvas_mouseX += delta_x;
        this->Canvas_mouseY += delta_y;

        this->Canvas_mousePrevX = event.GetPosition().x;
        this->Canvas_mousePrevY = event.GetPosition().y;
        Refresh(); // trigger paint event
    }
}

void BanyanChartFrame::mouseDown(wxMouseEvent& event) {
    if (event.GetPosition().x >= this->Canvas_mouseX && event.GetPosition().x <= this->Canvas_mouseX + this->WIDTH &&
        event.GetPosition().y >= this->Canvas_mouseY && event.GetPosition().y <= this->Canvas_mouseY + this->HEIGHT)
    {
        this->Canvas_dragging = true;
        this->Canvas_mousePrevX = event.GetPosition().x;
        this->Canvas_mousePrevY = event.GetPosition().y;
    }
}

void BanyanChartFrame::mouseReleased(wxMouseEvent& event) {
    this->Canvas_dragging = false;
}

void BanyanChartFrame::rightClick(wxMouseEvent& event) {
}

void BanyanChartFrame::mouseLeftWindow(wxMouseEvent& event) {
    this->Canvas_dragging = false;
}

void BanyanChartFrame::mouseWheelMoved(wxMouseEvent& event) {
}

void BanyanChartFrame::paintEvent(wxPaintEvent& event) {
    wxPaintDC dc(this);
    this->Canvas_render(dc);
}



void BanyanChartFrame::Canvas_render(wxDC&  dc) {
    dc.DrawText(wxT("Testing"), 40, 60); // draw some text

    dc.SetBrush(*wxBLUE_BRUSH); // blue filling
    dc.SetPen( wxPen( wxColor(255,175,175), 10 ) ); // 10-pixels-thick pink outline
    dc.DrawRectangle( this->Canvas_mouseX, this->Canvas_mouseY, this->WIDTH, this->HEIGHT );
}
