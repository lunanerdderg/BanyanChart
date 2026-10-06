/***************************************************************
 * Name:      BanyanChartMain.h
 * Purpose:   Defines Application Frame
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

#ifndef BANYANCHARTMAIN_H
#define BANYANCHARTMAIN_H

#include "FileParser.h"

//(*Headers(BanyanChartFrame)
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
//*)

class FileParser;
class BanyanChartFrame: public wxFrame
{
    public:

        BanyanChartFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~BanyanChartFrame();

    private:
        wxFont font;
        FileParser File;
        bool unsaved = false;

        void duplicate(std::vector<std::vector<bool>>);
        void changeText(std::string, size_t, size_t=0); void changeText(wxString, size_t, size_t=0); void changeText(const char[], size_t, size_t=0); void changeText(size_t, size_t=0,std::string="");

        // Canvas
        const int Canvas_blockWidth = 200, Canvas_blockHeight = 75;
        int Canvas_frameX = 0, Canvas_frameY = 0, Canvas_mousePrevX, Canvas_mousePrevY;
        unsigned int Canvas_zoom = 100;
        size_t Canvas_nodeDraggedBlock = -1, Canvas_nodeDraggedNode = -1;
        bool Canvas_dragging = false, Canvas_blockMoved = false, Canvas_mouseDown = false, Canvas_draggingNode = false;
        std::vector<bool> Canvas_blockDraggingList = {};
        std::vector<double> Canvas_blockXList = {}, Canvas_blockYList = {}, Canvas_blockWList = {}, Canvas_blockHList = {};
        std::vector<std::vector<bool>> Canvas_selected = {}, Canvas_copied = {};
        std::vector<std::vector<std::string>> Canvas_cutTextList = {};
        std::vector<std::vector<size_t>> Canvas_cutAddressList = {};

        bool Canvas_selectionMade(bool=false);
        bool Canvas_collision(int, int, size_t); bool Canvas_collision(int, int, size_t, size_t);
        double Canvas_getXPosition(double);
        double Canvas_getYPosition(double);
        double Canvas_getProportions(double=1, bool=false);
        void Canvas_copySelected();
        void Canvas_duplicate(bool=false);
        void Canvas_deleteSelected();
        void Canvas_render(wxDC&);
        void Canvas_initializeBoxes(bool=true);

        // ///////////////////////////
        void OnNew(wxCommandEvent& event);
        void OnOpen(wxCommandEvent& event);
        void OnSave(wxCommandEvent& event);
        void OnSaveAs(wxCommandEvent& event);

        void OnCut(wxCommandEvent& event);
        void OnCopy(wxCommandEvent& event);
        void OnPaste(wxCommandEvent& event);
        void OnDuplicate(wxCommandEvent& event);
        void OnAddBlock(wxCommandEvent& event);
        void OnAddNode(wxCommandEvent& event);
        void OnDelete(wxCommandEvent& event);
        void OnEditText(wxCommandEvent& event);

        void OnZoomIn(wxCommandEvent&);
        void OnZoomOut(wxCommandEvent&);
        //(*Handlers(BanyanChartFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void mouseMoved(wxMouseEvent& event);
        void mouseDown(wxMouseEvent& event);
        void mouseReleased(wxMouseEvent& event);
        void rightClick(wxMouseEvent& event);
        void mouseLeftWindow(wxMouseEvent& event);
        void mouseWheelMoved(wxMouseEvent& event);
        void paintEvent(wxPaintEvent& event);
        void doubleClick(wxMouseEvent& event);
        void keyPressed(wxKeyEvent& event);
        //*)

        //(*Identifiers(BanyanChartFrame)
        static const wxWindowID ID_CANVAS;
        static const wxWindowID idMenuNew;
        static const wxWindowID idMenuOpen;
        static const wxWindowID idMenuSave;
        static const wxWindowID idMenuSaveAs;
        static const wxWindowID idMenuQuit;
        static const wxWindowID idMenuCut;
        static const wxWindowID idMenuCopy;
        static const wxWindowID idMenuPaste;
        static const wxWindowID idMenuDuplicate;
        static const wxWindowID idMenuAddBlock;
        static const wxWindowID idMenuAddNode;
        static const wxWindowID idMenuDelete;
        static const wxWindowID idMenuEditText;
        static const wxWindowID idMenuZoomIn;
        static const wxWindowID idMenuZoomOut;
        static const wxWindowID idMenuAbout;
        static const wxWindowID ID_STATUSBAR1;
        //*)

        //(*Declarations(BanyanChartFrame)
        wxMenu* Menu3;
        wxMenu* Menu5;
        wxMenuItem* MenuItem10;
        wxMenuItem* MenuItem11;
        wxMenuItem* MenuItem12;
        wxMenuItem* MenuItem13;
        wxMenuItem* MenuItem14;
        wxMenuItem* MenuItem15;
        wxMenuItem* MenuItem16;
        wxMenuItem* MenuItem3;
        wxMenuItem* MenuItem4;
        wxMenuItem* MenuItem5;
        wxMenuItem* MenuItem6;
        wxMenuItem* MenuItem7;
        wxMenuItem* MenuItem8;
        wxMenuItem* MenuItem9;
        wxPanel* Canvas;
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // BANYANCHARTMAIN_H
