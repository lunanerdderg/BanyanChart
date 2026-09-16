/***************************************************************
 * Name:      BanyanChartApp.cpp
 * Purpose:   Code for Application Class
 * Author:    lunanerdderg ()
 * Created:   2026-09-16
 * Copyright: lunanerdderg (https://github.com/lunanerdderg)
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "BanyanChartApp.h"

//(*AppHeaders
#include "BanyanChartMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(BanyanChartApp);

bool BanyanChartApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
        BanyanChartFrame* Frame = new BanyanChartFrame(0);
        Frame->Show();
        SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
