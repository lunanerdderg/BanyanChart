/***************************************************************
 * Name:      BanyanChartMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    lunanerdderg ()
 * Created:   2026-09-19
 * Copyright: lunanerdderg (https://github.com/lunanerdderg)
 * License:   BSD 3-Clause Clear License
----------------------------------------------------------------
BanyanChart Copyright (c) 2026 lunanerdderg
<https://github.com/lunanerdderg/BanyanChart/blob/main/README.md>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted (subject to the limitations in the disclaimer
below) provided that the following conditions are met:

     * Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.

     * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.

     * Neither the name of the copyright holder nor the names of its
     contributors may be used to endorse or promote products derived from this
     software without specific prior written permission.

DISCLAIMER

NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

***************************************************************/

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
const wxWindowID BanyanChartFrame::idMenuUndo = wxNewId();
const wxWindowID BanyanChartFrame::idMenuRedo = wxNewId();
const wxWindowID BanyanChartFrame::idMenuCut = wxNewId();
const wxWindowID BanyanChartFrame::idMenuCopy = wxNewId();
const wxWindowID BanyanChartFrame::idMenuPaste = wxNewId();
const wxWindowID BanyanChartFrame::idMenuDuplicate = wxNewId();
const wxWindowID BanyanChartFrame::idMenuAddBlock = wxNewId();
const wxWindowID BanyanChartFrame::idMenuAddNode = wxNewId();
const wxWindowID BanyanChartFrame::idMenuDelete = wxNewId();
const wxWindowID BanyanChartFrame::idMenuEditText = wxNewId();
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
    m_pLogFile = fopen("log.txt", "w+");
    if (m_pLogFile == NULL) {
        return;
    }
    wxLogStderr* pFileLogger = new wxLogStderr(m_pLogFile);
    delete wxLog::SetActiveTarget(pFileLogger);
    wxLog::SetLogLevel(wxLOG_Info);
    wxLog::SetVerbose(true);
    wxLogDebug(L"Debug");

    File = FileParser();
    this->Canvas_copied = {{}};
    this->Canvas_initializeBoxes(true);
    this->Canvas_resetHistory();
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
    MenuItem17 = new wxMenuItem(Menu3, idMenuUndo, _("Undo\tCtrl-Z"), _("Undo last change"), wxITEM_NORMAL);
    Menu3->Append(MenuItem17);
    MenuItem18 = new wxMenuItem(Menu3, idMenuRedo, _("Redo\tCtrl-Y"), _("Redo previously undone change"), wxITEM_NORMAL);
    Menu3->Append(MenuItem18);
    Menu3->AppendSeparator();
    MenuItem14 = new wxMenuItem(Menu3, idMenuCut, _("Cut\tCtrl-X"), _("Copy blocks + nodes and delete"), wxITEM_NORMAL);
    Menu3->Append(MenuItem14);
    MenuItem15 = new wxMenuItem(Menu3, idMenuCopy, _("Copy\tCtrl-C"), _("Copy blocks + nodes"), wxITEM_NORMAL);
    Menu3->Append(MenuItem15);
    MenuItem16 = new wxMenuItem(Menu3, idMenuPaste, _("Paste\tCtrl-V"), _("Duplicate copied blocks + nodes"), wxITEM_NORMAL);
    Menu3->Append(MenuItem16);
    Menu3->AppendSeparator();
    MenuItem13 = new wxMenuItem(Menu3, idMenuDuplicate, _("Duplicate\tCtrl-D"), _("Duplicate all selected"), wxITEM_NORMAL);
    Menu3->Append(MenuItem13);
    MenuItem7 = new wxMenuItem(Menu3, idMenuAddBlock, _("Add block"), _("Add a block"), wxITEM_NORMAL);
    Menu3->Append(MenuItem7);
    MenuItem11 = new wxMenuItem(Menu3, idMenuAddNode, _("Add node"), _("Add a node to a block"), wxITEM_NORMAL);
    Menu3->Append(MenuItem11);
    Menu3->AppendSeparator();
    MenuItem8 = new wxMenuItem(Menu3, idMenuDelete, _("Delete\tDelete"), _("Delete a block"), wxITEM_NORMAL);
    Menu3->Append(MenuItem8);
    MenuItem12 = new wxMenuItem(Menu3, idMenuEditText, _("Edit text"), _("Edit the text of a block or node"), wxITEM_NORMAL);
    Menu3->Append(MenuItem12);
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

    Connect(idMenuUndo, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnUndo);
    Connect(idMenuRedo, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnRedo);
    Connect(idMenuCut, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnCut);
    Connect(idMenuCopy, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnCopy);
    Connect(idMenuPaste, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnPaste);
    Connect(idMenuDuplicate, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnDuplicate);
    Connect(idMenuAddBlock, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnAddBlock);
    Connect(idMenuAddNode, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnAddNode);
    Connect(idMenuDelete, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnDelete);
    Connect(idMenuEditText, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnEditText);

    Connect(idMenuAbout, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&BanyanChartFrame::OnAbout);
}
BanyanChartFrame::~BanyanChartFrame() {
    //(*Destroy(BanyanChartFrame)
    //*)
}




bool BanyanChartFrame::Canvas_selectionMade(bool useCopied) {
    if (useCopied) {
        for (size_t blockIndex = 0; blockIndex != -1 && blockIndex < this->Canvas_copied.size(); ++blockIndex) {
            for (size_t nodeIndex = 0; nodeIndex != -1 && nodeIndex < this->Canvas_copied.at(blockIndex).size(); ++nodeIndex) {
                if (this->Canvas_copied.at(blockIndex).at(nodeIndex)) {
                    return true;
                }
            }
        }
    }
    else {
        for (size_t blockIndex = 0; blockIndex != -1 && blockIndex < this->Canvas_selected.size(); ++blockIndex) {
            for (size_t nodeIndex = 0; nodeIndex != -1 && nodeIndex < this->Canvas_selected.at(blockIndex).size(); ++nodeIndex) {
                if (this->Canvas_selected.at(blockIndex).at(nodeIndex)) {
                    return true;
                }
            }
        }
    }
    return false;
}

void BanyanChartFrame::Canvas_initializeBoxes(bool reset) {
    size_t numBlocks = this->File.getNumBlocks();
    if (reset) {
        this->Canvas_dragging = false;
        this->Canvas_frameX = 0;
        this->Canvas_frameY = 0;

        this->Canvas_selected = {};
        this->Canvas_blockDraggingList = {};
        this->Canvas_blockXList = {};
        this->Canvas_blockYList = {};
        this->Canvas_blockWList = {};
        this->Canvas_blockHList = {};

        if (numBlocks > 0) {
            this->Canvas_selected.resize(numBlocks);
            this->Canvas_blockDraggingList.resize(numBlocks);
            this->Canvas_blockXList.resize(numBlocks);
            this->Canvas_blockYList.resize(numBlocks);
            this->Canvas_blockWList.resize(numBlocks);
            this->Canvas_blockHList.resize(numBlocks);
        }
    }
    if (reset && numBlocks > 0) {
        std::vector<size_t> step = {this->File.getFirstBlock()}, nextStep = {}, previousIndeces = {};

        for (size_t numSteps = 0; step.size() > 0; ++numSteps) {
            // Each step
            for (size_t block = 0; block != -1 && block < step.size(); ++block) {
                // Each block
                if (step.at(block) != -2 && std::find(previousIndeces.begin(), previousIndeces.end(), step.at(block)) == previousIndeces.end()) { // If block was not already seen
                    this->Canvas_blockDraggingList.at(step.at(block)) = false;
                    this->Canvas_selected.at(step.at(block)) = {false};
                    for (size_t nodeIndex = 1; nodeIndex < this->File.getNumNodes(step.at(block)); ++nodeIndex) {
                        if (this->File.getNodeAddress(step.at(block), nodeIndex) != -2) {
                            this->Canvas_selected.at(step.at(block)).push_back(false);
                        }
                    }
                    this->Canvas_blockXList.at(step.at(block)) = (block*2 + 1)*this->Canvas_width / (step.size()*2 + 1.0);
                    this->Canvas_blockYList.at(step.at(block)) = (numSteps*2 + 1)*this->Canvas_blockHeight * 3 / 4.0;
                    this->Canvas_blockWList.at(step.at(block)) = this->Canvas_blockWidth;
                    this->Canvas_blockHList.at(step.at(block)) = this->Canvas_blockHeight;

                    previousIndeces.push_back(step.at(block));
                    std::vector<size_t> tempAddressList = this->File.getBlockAddress(step.at(block));

                    nextStep.insert(nextStep.end(), tempAddressList.begin() + 1, tempAddressList.end());
                }
            }
            // Each step
            step = nextStep;
            nextStep = {};
        }
    }
    else {
        size_t startNum = this->Canvas_blockDraggingList.size();
        for (size_t i = 0; i != -1 && i < startNum && i < numBlocks; ++i) { // - this->Canvas_blockDraggingList.size()));
            this->Canvas_blockDraggingList.at(i) = false;
            this->Canvas_selected.at(i) = {false};
            for (size_t nodeIndex = 1; nodeIndex < this->File.getNumNodes(i); ++nodeIndex) {
                this->Canvas_selected.at(i).at(nodeIndex) = false;
            }
        }
        for (size_t i = startNum; i != -1 && i < numBlocks; ++i) { // - this->Canvas_blockDraggingList.size()));
            this->Canvas_blockDraggingList.push_back(false);
            this->Canvas_selected.push_back({false});
            for (size_t nodeIndex = 1; nodeIndex < this->File.getNumNodes(i); ++nodeIndex) {
                this->Canvas_selected.at(i).push_back(false);
            }
            this->Canvas_blockXList.push_back(100);
            this->Canvas_blockYList.push_back(i*this->Canvas_blockHeight*2);
            this->Canvas_blockWList.push_back(this->Canvas_blockWidth);
            this->Canvas_blockHList.push_back(this->Canvas_blockHeight);
        }
    }
}

void BanyanChartFrame::Canvas_resetHistory() {
    this->Canvas_historyIndex = 0;
    this->Canvas_textHistory = {this->File.getBlockTextList()};
    this->Canvas_addressHistory = {this->File.getBlockAddressList()};
}
void BanyanChartFrame::Canvas_saveStateToHistory() {
    ++this->Canvas_historyIndex;
    if (this->Canvas_historyIndex >= this->Canvas_textHistory.size()) {
        this->Canvas_textHistory.push_back(this->File.getBlockTextList());
        this->Canvas_addressHistory.push_back(this->File.getBlockAddressList());
    }
    else {
        this->Canvas_textHistory.at(this->Canvas_historyIndex) = this->File.getBlockTextList();
        this->Canvas_addressHistory.at(this->Canvas_historyIndex) = this->File.getBlockAddressList();
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

void BanyanChartFrame::duplicate(std::vector<std::vector<bool>> selectionList) {
    for (size_t blockIndex = 0; blockIndex != -1 && blockIndex < selectionList.size(); ++blockIndex) {
        bool add = false;
        std::vector<std::string> curBlockTexts = {""};
        std::vector<size_t> curBlockAddresses = {0};
        if (selectionList.at(blockIndex).at(0)) {
            curBlockTexts.at(0) = File.getBlockBody(blockIndex);
            add = true;
        }
        for (size_t nodeIndex = 1; nodeIndex != -1 && nodeIndex < selectionList.at(blockIndex).size(); ++nodeIndex) {
            if (selectionList.at(blockIndex).at(nodeIndex)) {
                curBlockTexts.push_back(this->File.getNodeText(blockIndex, nodeIndex));
                if (nodeIndex == 0) {
                    curBlockAddresses.push_back(0);
                }
                else {
                    curBlockAddresses.push_back(this->File.getNodeAddress(blockIndex, nodeIndex));
                }
                add = true;
            }
        }
        if (add) {
            this->File.addBlock(curBlockTexts, curBlockAddresses);
        }
    }
}
void BanyanChartFrame::Canvas_duplicate(bool useCopied) {
    if (useCopied && this->Canvas_copied.size() > 0 && this->Canvas_selectionMade(true)) {
        this->duplicate(Canvas_copied);
        this->Canvas_initializeBoxes(false);
        Refresh();
    }
    else if (!useCopied && this->Canvas_selected.size() > 0 && this->Canvas_selectionMade()) {
        this->duplicate(Canvas_selected);
        this->Canvas_initializeBoxes(false);
        Refresh();
    }
    this->Canvas_saveStateToHistory();
}




void BanyanChartFrame::OnNew(wxCommandEvent& event) {
    if (this->unsaved) {
        if (wxMessageBox(_("Current content has not been saved! Proceed?"), _("Please confirm"), wxICON_QUESTION | wxYES_NO, this) == wxNO ) {
            return;
        }
    }
    this->File.newInstance();
    this->Canvas_resetHistory();
    this->Canvas_initializeBoxes(true);
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
    if (openFileDialog.ShowModal() == wxID_CANCEL) { return; }
        this->File.newInstance(openFileDialog.GetPath());
        this->Canvas_resetHistory();
        this->Canvas_initializeBoxes(true);
        Refresh();
        this->unsaved = false;
}
void BanyanChartFrame::OnSave(wxCommandEvent& WXUNUSED(event)) {
    if (File.getPath() == "") {
        wxFileDialog saveFileDialog(this, _("Save BanyanChart file"), "", "", "BanyanChart files (*.byfc)|*.byfc", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
        if (saveFileDialog.ShowModal() != wxID_CANCEL) {
            this->File.setPath(saveFileDialog.GetPath());
            this->File.save();
            this->unsaved = false;
        }
    }
    else {
        this->File.save();
        this->unsaved = false;
    }
}
void BanyanChartFrame::OnSaveAs(wxCommandEvent& WXUNUSED(event)) {
    wxFileDialog saveFileDialog(this, _("Save BanyanChart file"), "", "", "BanyanChart files (*.byfc)|*.byfc", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() != wxID_CANCEL) {
        this->File.save(saveFileDialog.GetPath());
        this->unsaved = false;
    }
}




void BanyanChartFrame::OnUndo(wxCommandEvent& WXUNUSED(event)) {
    if (this->Canvas_historyIndex > 0) {
        --this->Canvas_historyIndex;
        this->File.setBlockLists(this->Canvas_textHistory.at(this->Canvas_historyIndex), this->Canvas_addressHistory.at(this->Canvas_historyIndex));
        this->Canvas_initializeBoxes(true);
        Refresh();
    }
}
void BanyanChartFrame::OnRedo(wxCommandEvent& WXUNUSED(event)) {
    if (this->Canvas_historyIndex < this->Canvas_textHistory.size() - 1) {
        ++this->Canvas_historyIndex;
        this->File.setBlockLists(this->Canvas_textHistory.at(this->Canvas_historyIndex), this->Canvas_addressHistory.at(this->Canvas_historyIndex));
        this->Canvas_initializeBoxes(true);
        Refresh();
    }
}

void BanyanChartFrame::OnCut(wxCommandEvent& WXUNUSED(event)) {
    if (this->Canvas_selectionMade()) {
        this->Canvas_copied = {};
        this->Canvas_cutTextList = {};
        this->Canvas_cutAddressList = {};
        for (size_t blockIndex = 0; blockIndex != -1 && blockIndex < this->Canvas_selected.size(); ++blockIndex) {
            bool add = false;
            std::vector<std::string> curBlockTexts = {""};
            std::vector<size_t> curBlockAddresses = {0};
            if (this->Canvas_selected.at(blockIndex).at(0)) {
                curBlockTexts.at(0) = File.getBlockBody(blockIndex);
                add = true;
            }
            for (size_t nodeIndex = 1; nodeIndex != -1 && nodeIndex < this->Canvas_selected.at(blockIndex).size(); ++nodeIndex) {
                if (this->Canvas_selected.at(blockIndex).at(nodeIndex)) {
                    curBlockTexts.push_back(this->File.getNodeText(blockIndex, nodeIndex));
                    if (nodeIndex == 0) {
                        curBlockAddresses.push_back(0);
                    }
                    else {
                        curBlockAddresses.push_back(this->File.getNodeAddress(blockIndex, nodeIndex));
                    }
                    add = true;
                }
            }
            if (add) {
                this->Canvas_cutTextList.push_back(curBlockTexts);
                this->Canvas_cutAddressList.push_back(curBlockAddresses);
            }
        }
        this->Canvas_deleteSelected();
        this->Canvas_saveStateToHistory();
        Refresh();
    }
}
void BanyanChartFrame::OnCopy(wxCommandEvent& WXUNUSED(event)) {
    this->Canvas_copied = this->Canvas_selected;
    this->Canvas_cutTextList = {};
    this->Canvas_cutAddressList = {};
}
void BanyanChartFrame::OnPaste(wxCommandEvent& WXUNUSED(event)) {
    if (this->Canvas_cutTextList.size() > 0 && this->Canvas_cutAddressList.size() > 0) {
        this->File.addMultipleBlocks(this->Canvas_cutTextList, this->Canvas_cutAddressList);
    }
    else {
        this->Canvas_duplicate(true);
    }
    this->Canvas_saveStateToHistory();
    this->Canvas_initializeBoxes(false);
    Refresh();
}
void BanyanChartFrame::OnDuplicate(wxCommandEvent& WXUNUSED(event)) {
    this->Canvas_duplicate();
    this->Canvas_saveStateToHistory();
}
void BanyanChartFrame::OnAddBlock(wxCommandEvent& WXUNUSED(event)) {
    this->File.addBlock("");
    this->Canvas_saveStateToHistory();
    this->Canvas_initializeBoxes(false);
    Refresh();
    this->unsaved = true;
}
void BanyanChartFrame::OnAddNode(wxCommandEvent& WXUNUSED(event)) { // BOOKMARK
    for (size_t blockIndex = 0; blockIndex != -1 && blockIndex < this->Canvas_selected.size(); ++blockIndex) {
        bool continueLooping = true;
        for (size_t nodeIndex = 0; continueLooping && nodeIndex != -1 && nodeIndex < this->Canvas_selected.at(blockIndex).size(); ++nodeIndex) {
            if (this->Canvas_selected.at(blockIndex).at(nodeIndex)) {
                this->Canvas_selected.at(blockIndex).push_back(false);
                this->File.addNode(blockIndex, "", -2);
                continueLooping = false;
            }
        }
    }
    this->Canvas_saveStateToHistory();
    Refresh();
    this->unsaved = true;
}
void BanyanChartFrame::Canvas_deleteSelected() {
    for (size_t i = this->Canvas_selected.size() - 1; i != -1 && i < this->File.getNumBlocks(); --i) {
        if (this->Canvas_selected.at(i).at(0)) {
            this->File.removeBlock(i);
            this->Canvas_blockDraggingList.erase(this->Canvas_blockDraggingList.begin() + i);
            this->Canvas_blockXList.erase(this->Canvas_blockXList.begin() + i);
            this->Canvas_blockYList.erase(this->Canvas_blockYList.begin() + i);
            this->Canvas_blockWList.erase(this->Canvas_blockWList.begin() + i);
            this->Canvas_blockHList.erase(this->Canvas_blockHList.begin() + i);
            this->Canvas_selected.erase(this->Canvas_selected.begin() + i);
            this->unsaved = true;
        }
        else {
            for (size_t nodeIndex = this->Canvas_selected.at(i).size() - 1; nodeIndex != -1 && nodeIndex < this->Canvas_selected.at(i).size(); --nodeIndex) {
                if (this->Canvas_selected.at(i).at(nodeIndex)) {
                    this->File.removeNode(i, nodeIndex);
                    this->Canvas_selected.at(i).erase(this->Canvas_selected.at(i).begin() + nodeIndex);
                    this->unsaved = true;
                }
            }
        }
    }
    this->Canvas_saveStateToHistory();
}
void BanyanChartFrame::OnDelete(wxCommandEvent& WXUNUSED(event)) {
    this->Canvas_deleteSelected();
    Refresh();
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
void BanyanChartFrame::changeText(size_t blockIndex, size_t nodeIndex, std::string contents) {
    wxTextEntryDialog textDialog(this, _("Enter text"), _("Text Editor"), _(contents.c_str()));
    if (textDialog.ShowModal() != wxID_CANCEL) {
        this->changeText(textDialog.GetValue(), blockIndex, nodeIndex);
    }
}
void BanyanChartFrame::doubleClick(wxMouseEvent& event) {
    size_t blockIndex = -1;
    size_t nodeIndex = 0;
    for (size_t b = 0; b != -1 && b < this->Canvas_selected.size(); ++b) {
        for (size_t n = 0; n != -1 && n < this->Canvas_selected.at(b).size(); ++n) {
            if (this->Canvas_collision(event.GetPosition().x, event.GetPosition().y, b, n)) {
                blockIndex = b;
                nodeIndex = n;
            }
        }
    }
    if (blockIndex != -1) {
        this->changeText(blockIndex, nodeIndex, this->File.getNodeText(blockIndex, nodeIndex).c_str());
        this->Canvas_saveStateToHistory();
        Refresh();
    }
}
void BanyanChartFrame::OnEditText(wxCommandEvent& WXUNUSED(event)) {
    bool multipleSelections = false;
    std::string content = "";
    for (size_t blockIndex = 0; blockIndex != -1 && !multipleSelections && blockIndex < this->Canvas_selected.size(); ++blockIndex) {
        for (size_t nodeIndex = 0; nodeIndex != -1 && !multipleSelections && nodeIndex < this->Canvas_selected.at(blockIndex).size(); ++nodeIndex) {
            if (this->Canvas_selected.at(blockIndex).at(nodeIndex)) {
                if (content == "") {
                    content = this->File.getNodeText(blockIndex, nodeIndex);
                }
                else {
                    multipleSelections = true;
                }
            }
        }
    }
    if (multipleSelections || content != "") {
        if (multipleSelections) {
            content = "";
        }
        wxTextEntryDialog textDialog(this, _("Enter text"), _("Text Editor"), _(content.c_str()));
        if (textDialog.ShowModal() != wxID_CANCEL) {
            for (size_t blockIndex = 0; blockIndex != -1 && blockIndex < this->Canvas_selected.size(); ++blockIndex) {
                for (size_t nodeIndex = 0; nodeIndex != -1 && nodeIndex < this->Canvas_selected.at(blockIndex).size(); ++nodeIndex) {
                    if (this->Canvas_selected.at(blockIndex).at(nodeIndex)) {
                        this->changeText(textDialog.GetValue().ToStdString(), blockIndex, nodeIndex);
                    }
                }
            }
            this->Canvas_saveStateToHistory();
            Refresh();
        }
    }
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




bool BanyanChartFrame::Canvas_collision(int xLocation, int yLocation, size_t blockIndex) {
    if (blockIndex >= this->Canvas_selected.size()) {
        return false;
    }

    const double blockXLocation = this->Canvas_getXPosition(this->Canvas_blockXList.at(blockIndex));
    const double blockYLocation = this->Canvas_getYPosition(this->Canvas_blockYList.at(blockIndex));
    const double blockWidth = this->Canvas_getProportions(this->Canvas_blockWList.at(blockIndex));
    double blockHeight;
    if (this->Canvas_selected.at(blockIndex).size() > 1) {
        blockHeight = this->Canvas_getProportions(this->Canvas_blockHList.at(blockIndex) * 3 / 4.0);
    }
    else {
        blockHeight = this->Canvas_getProportions(this->Canvas_blockHList.at(blockIndex));
    }
    return (xLocation >= blockXLocation && xLocation <= blockXLocation + this->Canvas_getProportions(blockWidth) &&
            yLocation >= blockYLocation && yLocation <= blockYLocation + this->Canvas_getProportions(blockHeight));
}
bool BanyanChartFrame::Canvas_collision(int xLocation, int yLocation, size_t blockIndex, size_t nodeIndex) {
    if (nodeIndex == 0) {
        return this->Canvas_collision(xLocation, yLocation, blockIndex);
    }
    size_t nodeListSize;
    if (blockIndex >= this->Canvas_selected.size() || nodeIndex >= (nodeListSize = this->Canvas_selected.at(blockIndex).size())) {
        return false;
    }
    const double nodeXLocation = this->Canvas_getXPosition(this->Canvas_blockXList.at(blockIndex) + (nodeIndex - 1) * this->Canvas_blockWList.at(blockIndex) / ((double)(nodeListSize - 1)));
    const double nodeYLocation = this->Canvas_getYPosition(this->Canvas_blockYList.at(blockIndex) + this->Canvas_blockHList.at(blockIndex) * 3 / 4.0);
    const double nodeWidth = this->Canvas_getProportions(this->Canvas_blockWList.at(blockIndex) / ((double)(nodeListSize - 1)));
    const double nodeHeight = this->Canvas_getProportions(this->Canvas_blockHList.at(blockIndex) / 4.0);
    return (xLocation >= nodeXLocation && xLocation <= nodeXLocation + nodeWidth &&
            yLocation >= nodeYLocation && yLocation <= nodeYLocation + nodeHeight);
}

void BanyanChartFrame::mouseMoved(wxMouseEvent& event) {
    if (!this->Canvas_draggingNode && this->Canvas_dragging && event.Dragging()) {
        int delta_x = event.GetPosition().x - this->Canvas_mousePrevX;
        int delta_y = event.GetPosition().y - this->Canvas_mousePrevY;

        this->Canvas_frameX += Canvas_getProportions(delta_x, true);
        this->Canvas_frameY += Canvas_getProportions(delta_y, true);

        this->Canvas_blockMoved = true;
    }
    else if (!this->Canvas_dragging && !this->Canvas_draggingNode) {
        for (size_t index = 0; index != -1 && index < this->Canvas_blockDraggingList.size(); ++index) {
            for (size_t nodeIndex = 1; nodeIndex != -1 && nodeIndex < this->Canvas_selected.at(index).size(); ++nodeIndex) {
                if (this->Canvas_mouseDown && ((this->Canvas_nodeDraggedBlock == index && this->Canvas_nodeDraggedNode == nodeIndex) || this->Canvas_selected.at(index).at(nodeIndex)) && this->Canvas_collision(event.GetPosition().x, event.GetPosition().y, index, nodeIndex)) {
                    this->Canvas_dragging = false;
                    this->Canvas_draggingNode = true;
                    Refresh();
                    return; // EXIT FUNCTION EARLY
                }
            }
            if (this->Canvas_blockDraggingList.at(index) && event.Dragging()) {
                int delta_x = event.GetPosition().x - this->Canvas_mousePrevX;
                int delta_y = event.GetPosition().y - this->Canvas_mousePrevY;

                this->Canvas_blockXList.at(index) += Canvas_getProportions(delta_x, true);
                this->Canvas_blockYList.at(index) += Canvas_getProportions(delta_y, true);

                this->Canvas_blockMoved = true;
            }
        }
    }
    this->Canvas_mousePrevX = event.GetPosition().x;
    this->Canvas_mousePrevY = event.GetPosition().y;
    Refresh();
}
void BanyanChartFrame::mouseDown(wxMouseEvent& event) {
    this->Canvas_mouseDown = true;
    if (!this->Canvas_draggingNode) {
        bool ctrlPressed = event.ControlDown();
        bool shiftPressed = event.ShiftDown();
        bool selectionMade = false;
        size_t prevSelectedBlockIndex = -1;
        this->Canvas_blockDraggingList = {};
        for (size_t blockIndex = 0; blockIndex != -1 && blockIndex < this->Canvas_selected.size(); ++blockIndex) {
            this->Canvas_blockDraggingList.push_back(false);
            if (this->Canvas_selected.at(blockIndex).at(0)) {
                this->Canvas_blockDraggingList.back() = true;
            }
            if (this->Canvas_collision(event.GetPosition().x, event.GetPosition().y, blockIndex)) {
                this->Canvas_dragging = false;
                if (!ctrlPressed && !shiftPressed && prevSelectedBlockIndex != -1) {
                    this->Canvas_blockDraggingList.at(prevSelectedBlockIndex) = false;
                }
                this->Canvas_blockDraggingList.at(blockIndex) = true;
                if (!this->Canvas_selected.at(blockIndex).at(0)) {
                    prevSelectedBlockIndex = blockIndex;
                }
                selectionMade = true;
            }
            for (size_t nodeIndex = this->Canvas_selected.at(blockIndex).size() - 1; nodeIndex > 0 && nodeIndex < this->Canvas_selected.at(blockIndex).size(); --nodeIndex) {
                if (this->Canvas_collision(event.GetPosition().x, event.GetPosition().y, blockIndex, nodeIndex)) {
                    this->Canvas_nodeDraggedBlock = blockIndex;
                    this->Canvas_nodeDraggedNode = nodeIndex;
                    selectionMade = true;
                }
            }
        }
        if (!selectionMade) {
            this->Canvas_dragging = true;
        }
        this->Canvas_mousePrevX = event.GetPosition().x;
        this->Canvas_mousePrevY = event.GetPosition().y;
        Refresh();
    }
}

void BanyanChartFrame::mouseReleased(wxMouseEvent& event) { // BOOKMARK (Maybe make node connections by allowing them to be dragged to blocks?)
    this->Canvas_mouseDown = false;
    bool ctrlPressed = event.ControlDown();
    bool shiftPressed = event.ShiftDown();
    for (size_t blockIndex = this->Canvas_selected.size() - 1; blockIndex != -1 && blockIndex < this->Canvas_selected.size(); --blockIndex) {
        if (!this->Canvas_draggingNode) {
            this->Canvas_blockDraggingList.at(blockIndex) = false;
        }
        if (!this->Canvas_draggingNode && !this->Canvas_blockMoved) {
            for (size_t nodeIndex = this->Canvas_selected.at(blockIndex).size() - 1; nodeIndex != -1 && nodeIndex < this->Canvas_selected.at(blockIndex).size(); --nodeIndex) {
                if (this->Canvas_collision(event.GetPosition().x, event.GetPosition().y, blockIndex, nodeIndex)) {
                    if (ctrlPressed) {
                        this->Canvas_selected.at(blockIndex).at(nodeIndex) = !this->Canvas_selected.at(blockIndex).at(nodeIndex);
                    }
                    else if (shiftPressed) {
                        bool newNodeValue = !this->Canvas_selected.at(blockIndex).at(nodeIndex);
                        for (size_t newNodeIndex = 0; newNodeIndex != -1 && newNodeIndex < this->Canvas_selected.at(blockIndex).size(); ++newNodeIndex) {
                            this->Canvas_selected.at(blockIndex).at(newNodeIndex) = newNodeValue;
                        }
                    }
                    else {
                        for (size_t prevSelectedIndex = 0; prevSelectedIndex != -1 && prevSelectedIndex < this->Canvas_selected.size(); ++prevSelectedIndex) {
                            for (size_t prevNodeIndex = 0; prevNodeIndex != -1 && prevNodeIndex < this->Canvas_selected.at(prevSelectedIndex).size(); ++prevNodeIndex) {
                                this->Canvas_selected.at(prevSelectedIndex).at(prevNodeIndex) = false;
                            }
                        }
                        this->Canvas_selected.at(blockIndex).at(nodeIndex) = true;
                        this->Canvas_dragging = false;
                        this->Canvas_blockMoved = false;
                        Refresh();
                        return; // EXIT FUNCTION EARLY
                    }
                }
                else if (!ctrlPressed && !shiftPressed) {
                    this->Canvas_selected.at(blockIndex).at(nodeIndex) = false;
                }
            }
        }
        else if (this->Canvas_draggingNode && !ctrlPressed && !shiftPressed && this->Canvas_collision(event.GetPosition().x, event.GetPosition().y, blockIndex)) {
            for (size_t targetBlockIndex = 0; targetBlockIndex != -1 && targetBlockIndex < this->Canvas_selected.size(); ++targetBlockIndex) {
                for (size_t targetNodeIndex = 1; targetNodeIndex != -1 && targetNodeIndex < this->Canvas_selected.at(targetBlockIndex).size(); ++targetNodeIndex) {
                    if ((this->Canvas_nodeDraggedBlock == targetBlockIndex && this->Canvas_nodeDraggedNode == targetNodeIndex) || this->Canvas_selected.at(targetBlockIndex).at(targetNodeIndex)) {
                        this->File.setNodeAddress(blockIndex, targetBlockIndex, targetNodeIndex);
                    }
                }
            }
            this->Canvas_saveStateToHistory();
        }
//        else if (!ctrlPressed && !shiftPressed) {
//            for (size_t nodeIndex = 0; nodeIndex != -1 && nodeIndex < this->Canvas_selected.at(blockIndex).size(); ++nodeIndex) {
//                this->Canvas_selected.at(blockIndex).at(nodeIndex) = false;
//            }
//        }
    }
    this->Canvas_nodeDraggedBlock = -1;
    this->Canvas_nodeDraggedNode = -1;
    this->Canvas_draggingNode = false;
    this->Canvas_dragging = false;
    this->Canvas_blockMoved = false;
    Refresh();
}

void BanyanChartFrame::rightClick(wxMouseEvent& event) {
}

void BanyanChartFrame::mouseLeftWindow(wxMouseEvent& event) {
    for (size_t index = 0; index != -1 && index < this->Canvas_blockDraggingList.size(); ++index) {
        this->Canvas_blockDraggingList.at(index) = false;
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
    this->Canvas_width = dc.GetSize().GetWidth();
    if (this->Canvas_justInitialized) {
        this->Canvas_initializeBoxes(true);
        this->Canvas_justInitialized = false;
    }
    dc.SetBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    for (size_t blockIndex = 0; blockIndex != -1 && blockIndex < this->Canvas_selected.size() && blockIndex < this->File.getNumBlocks(); ++blockIndex) {
        size_t nodeListSize = this->Canvas_selected.at(blockIndex).size();
        const double blockXLocation = this->Canvas_getXPosition(this->Canvas_blockXList.at(blockIndex));
        const double blockYLocation = this->Canvas_getYPosition(this->Canvas_blockYList.at(blockIndex));
        const double blockWidth = this->Canvas_getProportions(this->Canvas_blockWList.at(blockIndex));
        double blockHeight;
        if (nodeListSize > 1) {
            blockHeight = this->Canvas_getProportions(this->Canvas_blockHList.at(blockIndex) * 3 / 4);
        }
        else {
            blockHeight = this->Canvas_getProportions(this->Canvas_blockHList.at(blockIndex));
        }
        if (blockXLocation + this->Canvas_blockWidth > 0 && blockXLocation < this->GetClientSize().GetWidth() && blockYLocation + blockHeight > 0 && blockYLocation < this->GetClientSize().GetHeight()) {
            // Boxes
            if (this->Canvas_selected.at(blockIndex).at(0)) {
                dc.SetPen(wxPen(wxColor(255,75,75), this->Canvas_getProportions(2)));
            }
            else {
                dc.SetPen(wxPen(wxColor(255,175,175), this->Canvas_getProportions()));
            }
            dc.DrawRectangle(blockXLocation, blockYLocation, blockWidth, blockHeight);
            if (this->Canvas_selected.at(blockIndex).at(0)) {
                dc.SetPen(wxPen(wxColor(255,175,175), this->Canvas_getProportions()));
            }
            wxFont tempFont = font;
            this->SetFont(tempFont.Scale(this->Canvas_getProportions()));
            dc.DrawText(this->File.getBlockBody(blockIndex).c_str(), blockXLocation, blockYLocation);
            // Nodes
            if (nodeListSize > 1) {
                const double nodeYLocation = this->Canvas_getYPosition(this->Canvas_blockYList.at(blockIndex) + this->Canvas_blockHList.at(blockIndex) * 3 / 4);
                const double nodeWidth = this->Canvas_getProportions(this->Canvas_blockWList.at(blockIndex) / (nodeListSize - 1));
                const double nodeHeight = this->Canvas_getProportions(this->Canvas_blockHList.at(blockIndex) / 4);
                for (size_t nodeIndex = 1; nodeIndex != -1 && nodeIndex < nodeListSize && nodeIndex < this->File.getNumNodes(blockIndex); ++nodeIndex) {
                    const double nodeXLocation = this->Canvas_getXPosition(this->Canvas_blockXList.at(blockIndex) + (nodeIndex - 1) * this->Canvas_blockWList.at(blockIndex) / (nodeListSize - 1));
                    size_t pointer = this->File.getNodeAddress(blockIndex, nodeIndex);
                    if (pointer != -2 && pointer < this->Canvas_blockDraggingList.size()) {
                        dc.SetPen(wxPen(wxColor(255,215,215), this->Canvas_getProportions()));
                        dc.DrawLine(nodeXLocation + nodeWidth / 2.0, nodeYLocation + nodeHeight, this->Canvas_getXPosition(this->Canvas_blockXList.at(pointer) + this->Canvas_blockWList.at(pointer) / 2.0), this->Canvas_getYPosition(this->Canvas_blockYList.at(pointer)));
                    }
                    if ((this->Canvas_nodeDraggedBlock != -1 || this->Canvas_draggingNode) && (this->Canvas_selected.at(blockIndex).at(nodeIndex) || (this->Canvas_nodeDraggedBlock == blockIndex && this->Canvas_nodeDraggedNode == nodeIndex)) && this->Canvas_mouseDown) {
                        dc.SetPen(wxPen(wxColor(255,75,75), this->Canvas_getProportions(2)));
                        dc.DrawLine(nodeXLocation + nodeWidth / 2.0, nodeYLocation + nodeHeight, wxGetMousePosition().x, wxGetMousePosition().y);
                    }
                    if (this->Canvas_selected.at(blockIndex).at(nodeIndex)) {
                        dc.SetPen(wxPen(wxColor(255,75,75), this->Canvas_getProportions(2)));
                    }
                    else {
                        dc.SetPen(wxPen(wxColor(255,175,175), this->Canvas_getProportions()));
                    }
                    dc.DrawRectangle(nodeXLocation, nodeYLocation, nodeWidth, nodeHeight);
//                    wxFont tempFont = font;
//                    this->SetFont(tempFont.Scale(this->Canvas_getProportions() * 3 / 4.0));
                    dc.DrawText(this->File.getNodeText(blockIndex, nodeIndex).c_str(), nodeXLocation, nodeYLocation);
                }
            }
        }
    }
}
