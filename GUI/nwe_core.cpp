#include "nwe_core.h"

// thanks MaGetzUb
#pragma comment(linker,"/manifestdependency:\"type='win32' "\
                       "name='Microsoft.Windows.Common-Controls' "\
                       "version='6.0.0.0' "\
                       "processorArchitecture='*' "\
                       "publicKeyToken='6595b64144ccf1df' "\
                       "language='*' "\
                       "\"")

#include <Richedit.h>
#include <windowsx.h>

#include <iostream>

#include "nwe_widget.h"

#pragma region Win32MessageLookupTable
// Borrowed from https://github.com/Skight/wndspy

struct SymbolTabeItem {
	LONG value;
	LPCTSTR symbol;
};

#define Make_SymbolTableItem(x) { (LONG)(x), TEXT(#x) }

const SymbolTabeItem Win32Messages[] = {
	Make_SymbolTableItem(BM_CLICK),
	Make_SymbolTableItem(BM_GETCHECK),
	Make_SymbolTableItem(BM_GETIMAGE),
	Make_SymbolTableItem(BM_GETSTATE),
	Make_SymbolTableItem(BM_SETCHECK),
	Make_SymbolTableItem(BM_SETIMAGE),
	Make_SymbolTableItem(BM_SETSTATE),
	Make_SymbolTableItem(BM_SETSTYLE),
	Make_SymbolTableItem(CB_ADDSTRING),
	Make_SymbolTableItem(CB_DELETESTRING),
	Make_SymbolTableItem(CB_DIR),
	Make_SymbolTableItem(CB_FINDSTRING),
	Make_SymbolTableItem(CB_FINDSTRINGEXACT),
	Make_SymbolTableItem(CB_GETCOUNT),
	Make_SymbolTableItem(CB_GETCURSEL),
	Make_SymbolTableItem(CB_GETDROPPEDCONTROLRECT),
	Make_SymbolTableItem(CB_GETDROPPEDSTATE),
	Make_SymbolTableItem(CB_GETDROPPEDWIDTH),
	Make_SymbolTableItem(CB_GETEDITSEL),
	Make_SymbolTableItem(CB_GETEXTENDEDUI),
	Make_SymbolTableItem(CB_GETHORIZONTALEXTENT),
	Make_SymbolTableItem(CB_GETITEMDATA),
	Make_SymbolTableItem(CB_GETITEMHEIGHT),
	Make_SymbolTableItem(CB_GETLBTEXT),
	Make_SymbolTableItem(CB_GETLBTEXTLEN),
	Make_SymbolTableItem(CB_GETLOCALE),
	Make_SymbolTableItem(CB_GETMINVISIBLE),
	Make_SymbolTableItem(CB_GETTOPINDEX),
	Make_SymbolTableItem(CB_INSERTSTRING),
	Make_SymbolTableItem(CB_LIMITTEXT),
	Make_SymbolTableItem(CB_RESETCONTENT),
	Make_SymbolTableItem(CB_SELECTSTRING),
	Make_SymbolTableItem(CB_SETCURSEL),
	Make_SymbolTableItem(CB_SETDROPPEDWIDTH),
	Make_SymbolTableItem(CB_SETEDITSEL),
	Make_SymbolTableItem(CB_SETEXTENDEDUI),
	Make_SymbolTableItem(CB_SETHORIZONTALEXTENT),
	Make_SymbolTableItem(CB_SETITEMDATA),
	Make_SymbolTableItem(CB_SETITEMHEIGHT),
	Make_SymbolTableItem(CB_SETLOCALE),
	Make_SymbolTableItem(CB_SETTOPINDEX),
	Make_SymbolTableItem(CB_SETMINVISIBLE),
	Make_SymbolTableItem(CB_SHOWDROPDOWN),
	Make_SymbolTableItem(DM_GETDEFID),
	Make_SymbolTableItem(DM_REPOSITION),
	Make_SymbolTableItem(DM_SETDEFID),
	Make_SymbolTableItem(EM_CANUNDO),
	Make_SymbolTableItem(EM_CHARFROMPOS),
	Make_SymbolTableItem(EM_EMPTYUNDOBUFFER),
	Make_SymbolTableItem(EM_FMTLINES),
	Make_SymbolTableItem(EM_GETFIRSTVISIBLELINE),
	Make_SymbolTableItem(EM_GETLIMITTEXT),
	Make_SymbolTableItem(EM_GETLINE),
	Make_SymbolTableItem(EM_GETLINECOUNT),
	Make_SymbolTableItem(EM_GETMARGINS),
	Make_SymbolTableItem(EM_GETMODIFY),
	Make_SymbolTableItem(EM_GETPASSWORDCHAR),
	Make_SymbolTableItem(EM_GETRECT),
	Make_SymbolTableItem(EM_GETSEL),
	Make_SymbolTableItem(EM_GETTHUMB),
	Make_SymbolTableItem(EM_GETWORDBREAKPROC),
	Make_SymbolTableItem(EM_LIMITTEXT),
	Make_SymbolTableItem(EM_LINEFROMCHAR),
	Make_SymbolTableItem(EM_LINEINDEX),
	Make_SymbolTableItem(EM_LINELENGTH),
	Make_SymbolTableItem(EM_LINESCROLL),
	Make_SymbolTableItem(EM_POSFROMCHAR),
	Make_SymbolTableItem(EM_REPLACESEL),
	Make_SymbolTableItem(EM_REDO),
	Make_SymbolTableItem(EM_SCROLL),
	Make_SymbolTableItem(EM_SCROLLCARET),
	Make_SymbolTableItem(EM_SETLIMITTEXT),
	Make_SymbolTableItem(EM_SETMARGINS),
	Make_SymbolTableItem(EM_SETMODIFY),
	Make_SymbolTableItem(EM_SETPASSWORDCHAR),
	Make_SymbolTableItem(EM_SETREADONLY),
	Make_SymbolTableItem(EM_SETRECT),
	Make_SymbolTableItem(EM_SETRECTNP),
	Make_SymbolTableItem(EM_SETSEL),
	Make_SymbolTableItem(EM_UNDO),
	Make_SymbolTableItem(HDM_DELETEITEM),
	Make_SymbolTableItem(HDM_GETITEM),
	Make_SymbolTableItem(HDM_GETITEMCOUNT),
	Make_SymbolTableItem(HDM_INSERTITEM),
	Make_SymbolTableItem(HDM_LAYOUT),
	Make_SymbolTableItem(HDM_SETITEM),
	Make_SymbolTableItem(HKM_GETHOTKEY),
	Make_SymbolTableItem(HKM_SETHOTKEY),
	Make_SymbolTableItem(HKM_SETRULES),
	Make_SymbolTableItem(LB_ADDFILE),
	Make_SymbolTableItem(LB_ADDSTRING),
	Make_SymbolTableItem(LB_DELETESTRING),
	Make_SymbolTableItem(LB_DIR),
	Make_SymbolTableItem(LB_FINDSTRING),
	Make_SymbolTableItem(LB_FINDSTRINGEXACT),
	Make_SymbolTableItem(LB_GETANCHORINDEX),
	Make_SymbolTableItem(LB_GETCARETINDEX),
	Make_SymbolTableItem(LB_GETCOUNT),
	Make_SymbolTableItem(LB_GETCURSEL),
	Make_SymbolTableItem(LB_GETHORIZONTALEXTENT),
	Make_SymbolTableItem(LB_GETITEMDATA),
	Make_SymbolTableItem(LB_GETITEMHEIGHT),
	Make_SymbolTableItem(LB_GETITEMRECT),
	Make_SymbolTableItem(LB_GETLOCALE),
	Make_SymbolTableItem(LB_GETSEL),
	Make_SymbolTableItem(LB_GETSELCOUNT),
	Make_SymbolTableItem(LB_GETSELITEMS),
	Make_SymbolTableItem(LB_GETTEXT),
	Make_SymbolTableItem(LB_GETTEXTLEN),
	Make_SymbolTableItem(LB_GETTOPINDEX),
	Make_SymbolTableItem(LB_INSERTSTRING),
	Make_SymbolTableItem(LB_ITEMFROMPOINT),
	Make_SymbolTableItem(LB_RESETCONTENT),
	Make_SymbolTableItem(LB_SELECTSTRING),
	Make_SymbolTableItem(LB_SELITEMRANGE),
	Make_SymbolTableItem(LB_SELITEMRANGEEX),
	Make_SymbolTableItem(LB_SETANCHORINDEX),
	Make_SymbolTableItem(LB_SETCARETINDEX),
	Make_SymbolTableItem(LB_SETCOLUMNWIDTH),
	Make_SymbolTableItem(LB_SETCOUNT),
	Make_SymbolTableItem(LB_SETCURSEL),
	Make_SymbolTableItem(LB_SETHORIZONTALEXTENT),
	Make_SymbolTableItem(LB_SETITEMDATA),
	Make_SymbolTableItem(LB_SETITEMHEIGHT),
	Make_SymbolTableItem(LB_SETLOCALE),
	Make_SymbolTableItem(LB_SETSEL),
	Make_SymbolTableItem(LB_SETTOPINDEX),
	Make_SymbolTableItem(LVM_APPROXIMATEVIEWRECT),
	Make_SymbolTableItem(LVM_ARRANGE),
	Make_SymbolTableItem(LVM_CREATEDRAGIMAGE),
	Make_SymbolTableItem(LVM_DELETEALLITEMS),
	Make_SymbolTableItem(LVM_DELETECOLUMN),
	Make_SymbolTableItem(LVM_DELETEITEM),
	Make_SymbolTableItem(LVM_EDITLABEL),
	Make_SymbolTableItem(LVM_ENSUREVISIBLE),
	Make_SymbolTableItem(LVM_FINDITEM),
	Make_SymbolTableItem(LVM_GETBKCOLOR),
	Make_SymbolTableItem(LVM_GETCALLBACKMASK),
	Make_SymbolTableItem(LVM_GETCOLUMN),
	Make_SymbolTableItem(LVM_GETCOLUMNORDERARRAY),
	Make_SymbolTableItem(LVM_GETCOLUMNWIDTH),
	Make_SymbolTableItem(LVM_GETCOUNTPERPAGE),
	Make_SymbolTableItem(LVM_GETEDITCONTROL),
	Make_SymbolTableItem(LVM_GETEXTENDEDLISTVIEWSTYLE),
	Make_SymbolTableItem(LVM_GETHOTCURSOR),
	Make_SymbolTableItem(LVM_GETHOTITEM),
	Make_SymbolTableItem(LVM_GETIMAGELIST),
	Make_SymbolTableItem(LVM_GETISEARCHSTRING),
	Make_SymbolTableItem(LVM_GETITEM),
	Make_SymbolTableItem(LVM_GETITEMCOUNT),
	Make_SymbolTableItem(LVM_GETITEMPOSITION),
	Make_SymbolTableItem(LVM_GETITEMRECT),
	Make_SymbolTableItem(LVM_GETITEMSPACING),
	Make_SymbolTableItem(LVM_GETITEMSTATE),
	Make_SymbolTableItem(LVM_GETITEMTEXT),
	Make_SymbolTableItem(LVM_GETNEXTITEM),
	Make_SymbolTableItem(LVM_GETORIGIN),
	Make_SymbolTableItem(LVM_GETOUTLINECOLOR),
	Make_SymbolTableItem(LVM_GETSELECTEDCOUNT),
	Make_SymbolTableItem(LVM_GETSTRINGWIDTH),
	Make_SymbolTableItem(LVM_GETSUBITEMRECT),
	Make_SymbolTableItem(LVM_GETTEXTBKCOLOR),
	Make_SymbolTableItem(LVM_GETTEXTCOLOR),
	Make_SymbolTableItem(LVM_GETTOPINDEX),
	Make_SymbolTableItem(LVM_GETVIEWRECT),
	Make_SymbolTableItem(LVM_INSERTCOLUMN),
	Make_SymbolTableItem(LVM_INSERTGROUP),
	Make_SymbolTableItem(LVM_INSERTITEM),
	Make_SymbolTableItem(LVM_MOVEGROUP),
	Make_SymbolTableItem(LVM_REDRAWITEMS),
	Make_SymbolTableItem(LVM_SCROLL),
	Make_SymbolTableItem(LVM_SETBKCOLOR),
	Make_SymbolTableItem(LVM_SETCALLBACKMASK),
	Make_SymbolTableItem(LVM_SETCOLUMN),
	Make_SymbolTableItem(LVM_SETCOLUMNORDERARRAY),
	Make_SymbolTableItem(LVM_SETCOLUMNWIDTH),
	Make_SymbolTableItem(LVM_SETEXTENDEDLISTVIEWSTYLE),
	Make_SymbolTableItem(LVM_SETHOTCURSOR),
	Make_SymbolTableItem(LVM_SETHOTITEM),
	Make_SymbolTableItem(LVM_SETICONSPACING),
	Make_SymbolTableItem(LVM_SETIMAGELIST),
	Make_SymbolTableItem(LVM_SETITEM),
	Make_SymbolTableItem(LVM_SETITEMCOUNT),
	Make_SymbolTableItem(LVM_SETITEMPOSITION),
	Make_SymbolTableItem(LVM_SETITEMSTATE),
	Make_SymbolTableItem(LVM_SETITEMTEXT),
	Make_SymbolTableItem(LVM_SETOUTLINECOLOR),
	Make_SymbolTableItem(LVM_SETTEXTBKCOLOR),
	Make_SymbolTableItem(LVM_SETTEXTCOLOR),
	Make_SymbolTableItem(LVM_UPDATE),
	Make_SymbolTableItem(PBM_DELTAPOS),
	Make_SymbolTableItem(PBM_GETPOS),
	Make_SymbolTableItem(PBM_GETRANGE),
	Make_SymbolTableItem(PBM_SETPOS),
	Make_SymbolTableItem(PBM_SETRANGE),
	Make_SymbolTableItem(PBM_SETRANGE32),
	Make_SymbolTableItem(PBM_SETSTEP),
	Make_SymbolTableItem(PBM_STEPIT),
	Make_SymbolTableItem(SB_GETBORDERS),
	Make_SymbolTableItem(SB_GETPARTS),
	Make_SymbolTableItem(SB_GETRECT),
	Make_SymbolTableItem(SB_GETTEXT),
	Make_SymbolTableItem(SB_GETTEXTLENGTH),
	Make_SymbolTableItem(SB_SETMINHEIGHT),
	Make_SymbolTableItem(SB_SETPARTS),
	Make_SymbolTableItem(SB_SETTEXT),
	Make_SymbolTableItem(SB_SIMPLE),
	Make_SymbolTableItem(SBM_ENABLE_ARROWS),
	Make_SymbolTableItem(SBM_GETPOS),
	Make_SymbolTableItem(SBM_GETRANGE),
	Make_SymbolTableItem(SBM_GETSCROLLINFO),
	Make_SymbolTableItem(SBM_SETPOS),
	Make_SymbolTableItem(SBM_SETRANGE),
	Make_SymbolTableItem(SBM_SETRANGEREDRAW),
	Make_SymbolTableItem(SBM_SETSCROLLINFO),
	Make_SymbolTableItem(STM_GETICON),
	Make_SymbolTableItem(STM_GETIMAGE),
	Make_SymbolTableItem(STM_SETICON),
	Make_SymbolTableItem(STM_SETIMAGE),
	Make_SymbolTableItem(TB_ADDBITMAP),
	Make_SymbolTableItem(TB_ADDBUTTONS),
	Make_SymbolTableItem(TB_ADDSTRING),
	Make_SymbolTableItem(TB_AUTOSIZE),
	Make_SymbolTableItem(TB_BUTTONCOUNT),
	Make_SymbolTableItem(TB_BUTTONSTRUCTSIZE),
	Make_SymbolTableItem(TB_CHANGEBITMAP),
	Make_SymbolTableItem(TB_CHECKBUTTON),
	Make_SymbolTableItem(TB_COMMANDTOINDEX),
	Make_SymbolTableItem(TB_CUSTOMIZE),
	Make_SymbolTableItem(TB_DELETEBUTTON),
	Make_SymbolTableItem(TB_ENABLEBUTTON),
	Make_SymbolTableItem(TB_GETBITMAP),
	Make_SymbolTableItem(TB_GETBITMAPFLAGS),
	Make_SymbolTableItem(TB_GETBUTTON),
	Make_SymbolTableItem(TB_GETBUTTONSIZE),
	Make_SymbolTableItem(TB_GETBUTTONTEXT),
	Make_SymbolTableItem(TB_GETDISABLEDIMAGELIST),
	Make_SymbolTableItem(TB_GETHOTIMAGELIST),
	Make_SymbolTableItem(TB_GETIMAGELIST),
	Make_SymbolTableItem(TB_GETITEMRECT),
	Make_SymbolTableItem(TB_GETRECT),
	Make_SymbolTableItem(TB_GETROWS),
	Make_SymbolTableItem(TB_GETSTATE),
	Make_SymbolTableItem(TB_GETSTYLE),
	Make_SymbolTableItem(TB_GETTEXTROWS),
	Make_SymbolTableItem(TB_GETTOOLTIPS),
	Make_SymbolTableItem(TB_HIDEBUTTON),
	Make_SymbolTableItem(TB_INDETERMINATE),
	Make_SymbolTableItem(TB_INSERTBUTTON),
	Make_SymbolTableItem(TB_ISBUTTONCHECKED),
	Make_SymbolTableItem(TB_ISBUTTONHIDDEN),
	Make_SymbolTableItem(TB_ISBUTTONINDETERMINATE),
	Make_SymbolTableItem(TB_ISBUTTONPRESSED),
	Make_SymbolTableItem(TB_LOADIMAGES),
	Make_SymbolTableItem(TB_MOVEBUTTON),
	Make_SymbolTableItem(TB_PRESSBUTTON),
	Make_SymbolTableItem(TB_SETBITMAPSIZE),
	Make_SymbolTableItem(TB_SETBUTTONSIZE),
	Make_SymbolTableItem(TB_SETBUTTONWIDTH),
	Make_SymbolTableItem(TB_SETCMDID),
	Make_SymbolTableItem(TB_SETDISABLEDIMAGELIST),
	Make_SymbolTableItem(TB_SETHOTIMAGELIST),
	Make_SymbolTableItem(TB_SETIMAGELIST),
	Make_SymbolTableItem(TB_SETINDENT),
	Make_SymbolTableItem(TB_SETMAXTEXTROWS),
	Make_SymbolTableItem(TB_SETPARENT),
	Make_SymbolTableItem(TB_SETROWS),
	Make_SymbolTableItem(TB_SETSTATE),
	Make_SymbolTableItem(TB_SETSTYLE),
	Make_SymbolTableItem(TB_SETTOOLTIPS),
	Make_SymbolTableItem(TCM_ADJUSTRECT),
	Make_SymbolTableItem(TCM_DELETEALLITEMS),
	Make_SymbolTableItem(TCM_DELETEITEM),
	Make_SymbolTableItem(TCM_DESELECTALL),
	Make_SymbolTableItem(TCM_GETEXTENDEDSTYLE),
	Make_SymbolTableItem(TCM_GETCURFOCUS),
	Make_SymbolTableItem(TCM_GETCURSEL),
	Make_SymbolTableItem(TCM_GETIMAGELIST),
	Make_SymbolTableItem(TCM_GETITEM),
	Make_SymbolTableItem(TCM_GETITEMCOUNT),
	Make_SymbolTableItem(TCM_GETITEMRECT),
	Make_SymbolTableItem(TCM_GETROWCOUNT),
	Make_SymbolTableItem(TCM_GETTOOLTIPS),
	Make_SymbolTableItem(TCM_HIGHLIGHTITEM),
	Make_SymbolTableItem(TCM_INSERTITEM),
	Make_SymbolTableItem(TCM_REMOVEIMAGE),
	Make_SymbolTableItem(TCM_SETCURFOCUS),
	Make_SymbolTableItem(TCM_SETCURSEL),
	Make_SymbolTableItem(TCM_SETIMAGELIST),
	Make_SymbolTableItem(TCM_SETITEM),
	Make_SymbolTableItem(TCM_SETITEMEXTRA),
	Make_SymbolTableItem(TCM_SETITEMSIZE),
	Make_SymbolTableItem(TCM_SETPADDING),
	Make_SymbolTableItem(TCM_SETTOOLTIPS),
	Make_SymbolTableItem(TTM_ACTIVATE),
	Make_SymbolTableItem(TTM_ADDTOOL),
	Make_SymbolTableItem(TTM_DELTOOL),
	Make_SymbolTableItem(TTM_ENUMTOOLS),
	Make_SymbolTableItem(TTM_GETCURRENTTOOL),
	Make_SymbolTableItem(TTM_GETDELAYTIME),
	Make_SymbolTableItem(TTM_GETMARGIN),
	Make_SymbolTableItem(TTM_GETMAXTIPWIDTH),
	Make_SymbolTableItem(TTM_GETTEXT),
	Make_SymbolTableItem(TTM_GETTIPBKCOLOR),
	Make_SymbolTableItem(TTM_GETTIPTEXTCOLOR),
	Make_SymbolTableItem(TTM_GETTITLE),
	Make_SymbolTableItem(TTM_GETTOOLCOUNT),
	Make_SymbolTableItem(TTM_GETTOOLINFO),
	Make_SymbolTableItem(TTM_POP),
	Make_SymbolTableItem(TTM_POPUP),
	Make_SymbolTableItem(TTM_SETDELAYTIME),
	Make_SymbolTableItem(TTM_SETMARGIN),
	Make_SymbolTableItem(TTM_SETMAXTIPWIDTH),
	Make_SymbolTableItem(TTM_SETTIPBKCOLOR),
	Make_SymbolTableItem(TTM_SETTIPTEXTCOLOR),
	Make_SymbolTableItem(TTM_SETTITLE),
	Make_SymbolTableItem(TTM_SETTOOLINFO),
	Make_SymbolTableItem(TTM_UPDATETIPTEXT),
	Make_SymbolTableItem(TTM_WINDOWFROMPOINT),
	Make_SymbolTableItem(TVM_DELETEITEM),
	Make_SymbolTableItem(TVM_EDITLABEL),
	Make_SymbolTableItem(TVM_ENDEDITLABELNOW),
	Make_SymbolTableItem(TVM_ENSUREVISIBLE),
	Make_SymbolTableItem(TVM_EXPAND),
	Make_SymbolTableItem(TVM_GETBKCOLOR),
	Make_SymbolTableItem(TVM_GETTEXTCOLOR),
	Make_SymbolTableItem(TVM_GETCOUNT),
	Make_SymbolTableItem(TVM_GETEDITCONTROL),
	Make_SymbolTableItem(TVM_GETIMAGELIST),
	Make_SymbolTableItem(TVM_GETINDENT),
	Make_SymbolTableItem(TVM_GETISEARCHSTRING),
	Make_SymbolTableItem(TVM_GETITEM),
	Make_SymbolTableItem(TVM_GETITEMRECT),
	Make_SymbolTableItem(TVM_GETNEXTITEM),
	Make_SymbolTableItem(TVM_GETVISIBLECOUNT),
	Make_SymbolTableItem(TVM_INSERTITEM),
	Make_SymbolTableItem(TVM_SELECTITEM),
	Make_SymbolTableItem(TVM_SETIMAGELIST),
	Make_SymbolTableItem(TVM_SETINDENT),
	Make_SymbolTableItem(TVM_SETITEM),
	Make_SymbolTableItem(TVM_SORTCHILDREN),
	Make_SymbolTableItem(TVM_SETBKCOLOR),
	Make_SymbolTableItem(TVM_SETTEXTCOLOR),
	Make_SymbolTableItem(UDM_GETACCEL),
	Make_SymbolTableItem(UDM_GETBASE),
	Make_SymbolTableItem(UDM_GETBUDDY),
	Make_SymbolTableItem(UDM_GETPOS),
	Make_SymbolTableItem(UDM_GETRANGE),
	Make_SymbolTableItem(UDM_SETACCEL),
	Make_SymbolTableItem(UDM_SETBASE),
	Make_SymbolTableItem(UDM_SETBUDDY),
	Make_SymbolTableItem(UDM_SETPOS),
	Make_SymbolTableItem(UDM_SETRANGE),
	Make_SymbolTableItem(WM_ACTIVATE),
	Make_SymbolTableItem(WM_ACTIVATEAPP),
	Make_SymbolTableItem(WM_APPCOMMAND),
	Make_SymbolTableItem(WM_CANCELJOURNAL),
	Make_SymbolTableItem(WM_CANCELMODE),
	Make_SymbolTableItem(WM_CAPTURECHANGED),
	Make_SymbolTableItem(WM_CHANGEUISTATE),
	Make_SymbolTableItem(WM_CHAR),
	Make_SymbolTableItem(WM_CHARTOITEM),
	Make_SymbolTableItem(WM_CHILDACTIVATE),
	Make_SymbolTableItem(WM_CLEAR),
	Make_SymbolTableItem(WM_CLOSE),
	Make_SymbolTableItem(WM_COMMAND),
	Make_SymbolTableItem(WM_COMPACTING),
	Make_SymbolTableItem(WM_COMPAREITEM),
	Make_SymbolTableItem(WM_CONTEXTMENU),
	Make_SymbolTableItem(WM_COPY),
	Make_SymbolTableItem(WM_COPYDATA),
	Make_SymbolTableItem(WM_CTLCOLOR),
	Make_SymbolTableItem(WM_CTLCOLORBTN),
	Make_SymbolTableItem(WM_CTLCOLORDLG),
	Make_SymbolTableItem(WM_CTLCOLOREDIT),
	Make_SymbolTableItem(WM_CTLCOLORLISTBOX),
	Make_SymbolTableItem(WM_CTLCOLORSCROLLBAR),
	Make_SymbolTableItem(WM_CTLCOLORSTATIC),
	Make_SymbolTableItem(WM_CUT),
	Make_SymbolTableItem(WM_DEADCHAR),
	Make_SymbolTableItem(WM_DELETEITEM),
	Make_SymbolTableItem(WM_DESTROY),
	Make_SymbolTableItem(WM_DEVICECHANGE),
	Make_SymbolTableItem(WM_DEVMODECHANGE),
	Make_SymbolTableItem(WM_DISPLAYCHANGE),
	Make_SymbolTableItem(WM_DRAWITEM),
	Make_SymbolTableItem(WM_DROPFILES),
	Make_SymbolTableItem(WM_ENABLE),
	Make_SymbolTableItem(WM_ENDSESSION),
	Make_SymbolTableItem(WM_ENTERIDLE),
	Make_SymbolTableItem(WM_ENTERMENULOOP),
	Make_SymbolTableItem(WM_ENTERSIZEMOVE),
	Make_SymbolTableItem(WM_ERASEBKGND),
	Make_SymbolTableItem(WM_EXITMENULOOP),
	Make_SymbolTableItem(WM_EXITSIZEMOVE),
	Make_SymbolTableItem(WM_FONTCHANGE),
	Make_SymbolTableItem(WM_GETDLGCODE),
	Make_SymbolTableItem(WM_GETFONT),
	Make_SymbolTableItem(WM_GETHOTKEY),
	Make_SymbolTableItem(WM_GETICON),
	Make_SymbolTableItem(WM_GETMINMAXINFO),
	Make_SymbolTableItem(WM_GETOBJECT),
	Make_SymbolTableItem(WM_GETTEXT),
	Make_SymbolTableItem(WM_GETTEXTLENGTH),
	Make_SymbolTableItem(WM_HELP),
	Make_SymbolTableItem(WM_HOTKEY),
	Make_SymbolTableItem(WM_HSCROLL),
	Make_SymbolTableItem(WM_IME_CHAR),
	Make_SymbolTableItem(WM_IME_COMPOSITION),
	Make_SymbolTableItem(WM_IME_COMPOSITIONFULL),
	Make_SymbolTableItem(WM_IME_CONTROL),
	Make_SymbolTableItem(WM_IME_ENDCOMPOSITION),
	Make_SymbolTableItem(WM_IME_KEYDOWN),
	Make_SymbolTableItem(WM_IME_KEYUP),
	Make_SymbolTableItem(WM_IME_NOTIFY),
	Make_SymbolTableItem(WM_IME_SELECT),
	Make_SymbolTableItem(WM_IME_SETCONTEXT),
	Make_SymbolTableItem(WM_IME_STARTCOMPOSITION),
	Make_SymbolTableItem(WM_INITMENU),
	Make_SymbolTableItem(WM_INITMENUPOPUP),
	Make_SymbolTableItem(WM_INPUTLANGCHANGE),
	Make_SymbolTableItem(WM_INPUTLANGCHANGEREQUEST),
	Make_SymbolTableItem(WM_KEYDOWN),
	Make_SymbolTableItem(WM_KEYUP),
	Make_SymbolTableItem(WM_KILLFOCUS),
	Make_SymbolTableItem(WM_LBUTTONDBLCLK),
	Make_SymbolTableItem(WM_LBUTTONDOWN),
	Make_SymbolTableItem(WM_LBUTTONUP),
	Make_SymbolTableItem(WM_MBUTTONDBLCLK),
	Make_SymbolTableItem(WM_MBUTTONDOWN),
	Make_SymbolTableItem(WM_MBUTTONUP),
	Make_SymbolTableItem(WM_MDIACTIVATE),
	Make_SymbolTableItem(WM_MDICASCADE),
	Make_SymbolTableItem(WM_MDICREATE),
	Make_SymbolTableItem(WM_MDIDESTROY),
	Make_SymbolTableItem(WM_MDIGETACTIVE),
	Make_SymbolTableItem(WM_MDIICONARRANGE),
	Make_SymbolTableItem(WM_MDIMAXIMIZE),
	Make_SymbolTableItem(WM_MDINEXT),
	Make_SymbolTableItem(WM_MDIREFRESHMENU),
	Make_SymbolTableItem(WM_MDIRESTORE),
	Make_SymbolTableItem(WM_MDISETMENU),
	Make_SymbolTableItem(WM_MDITILE),
	Make_SymbolTableItem(WM_MEASUREITEM),
	Make_SymbolTableItem(WM_MENUCHAR),
	Make_SymbolTableItem(WM_MENUCOMMAND),
	Make_SymbolTableItem(WM_MENUDRAG),
	Make_SymbolTableItem(WM_MENUGETOBJECT),
	Make_SymbolTableItem(WM_MENURBUTTONUP),
	Make_SymbolTableItem(WM_MENUSELECT),
	Make_SymbolTableItem(WM_MOUSEACTIVATE),
	Make_SymbolTableItem(WM_MOUSEHOVER),
	Make_SymbolTableItem(WM_MOUSELEAVE),
	Make_SymbolTableItem(WM_MOUSEMOVE),
	Make_SymbolTableItem(WM_MOUSEWHEEL),
	Make_SymbolTableItem(WM_MOVE),
	Make_SymbolTableItem(WM_MOVING),
	Make_SymbolTableItem(WM_NCACTIVATE),
	Make_SymbolTableItem(WM_NCCALCSIZE),
	Make_SymbolTableItem(WM_NCCREATE),
	Make_SymbolTableItem(WM_NCDESTROY),
	Make_SymbolTableItem(WM_NCHITTEST),
	Make_SymbolTableItem(WM_NCLBUTTONDBLCLK),
	Make_SymbolTableItem(WM_NCLBUTTONDOWN),
	Make_SymbolTableItem(WM_NCLBUTTONUP),
	Make_SymbolTableItem(WM_NCMBUTTONDBLCLK),
	Make_SymbolTableItem(WM_NCMBUTTONDOWN),
	Make_SymbolTableItem(WM_NCMBUTTONUP),
	Make_SymbolTableItem(WM_NCMOUSELEAVE),
	Make_SymbolTableItem(WM_NCMOUSEHOVER),
	Make_SymbolTableItem(WM_NCMOUSEMOVE),
	Make_SymbolTableItem(WM_NCPAINT),
	Make_SymbolTableItem(WM_NCRBUTTONDBLCLK),
	Make_SymbolTableItem(WM_NCRBUTTONDOWN),
	Make_SymbolTableItem(WM_NCRBUTTONUP),
	Make_SymbolTableItem(WM_NCXBUTTONDBLCLK),
	Make_SymbolTableItem(WM_NCXBUTTONDOWN),
	Make_SymbolTableItem(WM_NCXBUTTONUP),
	Make_SymbolTableItem(WM_NEXTDLGCTL),
	Make_SymbolTableItem(WM_NEXTMENU),
	Make_SymbolTableItem(WM_NOTIFY),
	Make_SymbolTableItem(WM_NOTIFYFORMAT),
	Make_SymbolTableItem(WM_PAINT),
	Make_SymbolTableItem(WM_PAINTICON),
	Make_SymbolTableItem(WM_PALETTECHANGED),
	Make_SymbolTableItem(WM_PALETTEISCHANGING),
	Make_SymbolTableItem(WM_PARENTNOTIFY),
	Make_SymbolTableItem(WM_PASTE),
	Make_SymbolTableItem(WM_POWER),
	Make_SymbolTableItem(WM_POWERBROADCAST),
	Make_SymbolTableItem(WM_PRINT),
	Make_SymbolTableItem(WM_PRINTCLIENT),
	Make_SymbolTableItem(WM_QUERYDRAGICON),
	Make_SymbolTableItem(WM_QUERYENDSESSION),
	Make_SymbolTableItem(WM_QUERYNEWPALETTE),
	Make_SymbolTableItem(WM_QUERYOPEN),
	Make_SymbolTableItem(WM_QUERYUISTATE),
	Make_SymbolTableItem(WM_QUEUESYNC),
	Make_SymbolTableItem(WM_QUIT),
	Make_SymbolTableItem(WM_RBUTTONDBLCLK),
	Make_SymbolTableItem(WM_RBUTTONDOWN),
	Make_SymbolTableItem(WM_RBUTTONUP),
	Make_SymbolTableItem(WM_RENDERALLFORMATS),
	Make_SymbolTableItem(WM_RENDERFORMAT),
	Make_SymbolTableItem(WM_SETCURSOR),
	Make_SymbolTableItem(WM_SETFOCUS),
	Make_SymbolTableItem(WM_SETFONT),
	Make_SymbolTableItem(WM_SETHOTKEY),
	Make_SymbolTableItem(WM_SETICON),
	Make_SymbolTableItem(WM_SETREDRAW),
	Make_SymbolTableItem(WM_SETTEXT),
	Make_SymbolTableItem(WM_SETTINGCHANGE),
	Make_SymbolTableItem(WM_SHOWWINDOW),
	Make_SymbolTableItem(WM_SIZE),
	Make_SymbolTableItem(WM_SIZING),
	Make_SymbolTableItem(WM_SPOOLERSTATUS),
	Make_SymbolTableItem(WM_STYLECHANGED),
	Make_SymbolTableItem(WM_STYLECHANGING),
	Make_SymbolTableItem(WM_SYNCPAINT),
	Make_SymbolTableItem(WM_SYSCHAR),
	Make_SymbolTableItem(WM_SYSCOLORCHANGE),
	Make_SymbolTableItem(WM_SYSCOMMAND),
	Make_SymbolTableItem(WM_SYSDEADCHAR),
	Make_SymbolTableItem(WM_SYSKEYDOWN),
	Make_SymbolTableItem(WM_SYSKEYUP),
	Make_SymbolTableItem(WM_TCARD),
	Make_SymbolTableItem(WM_THEMECHANGED),
	Make_SymbolTableItem(WM_TIMECHANGE),
	Make_SymbolTableItem(WM_TIMER),
	Make_SymbolTableItem(WM_UNDO),
	Make_SymbolTableItem(WM_UNICHAR),
	Make_SymbolTableItem(WM_UNINITMENUPOPUP),
	Make_SymbolTableItem(WM_UPDATEUISTATE),
	Make_SymbolTableItem(WM_USERCHANGED),
	Make_SymbolTableItem(WM_VKEYTOITEM),
	Make_SymbolTableItem(WM_VSCROLL),
	Make_SymbolTableItem(WM_WINDOWPOSCHANGED),
	Make_SymbolTableItem(WM_WINDOWPOSCHANGING),
	Make_SymbolTableItem(WM_WININICHANGE),
	Make_SymbolTableItem(WM_XBUTTONDBLCLK),
	Make_SymbolTableItem(WM_XBUTTONDOWN),
	Make_SymbolTableItem(WM_XBUTTONUP),
	{ 0, NULL }
};

#pragma endregion

namespace nwe {
	String win32::messageToString(UINT msg) {
		StringStream ss;
		for (SymbolTabeItem sti : Win32Messages) {
			if (sti.symbol == nullptr) break;
			if (sti.value == msg) {
				ss << sti.symbol;
			}
		}

		if (!ss.str().empty()) {
			return ss.str();
		}

		ss << TEXT("Unknown(") << msg << TEXT(")");
		return ss.str();
	}
	
	Size win32::measureText(HWND handle, const nwe::String& text) {
		HDC dc = GetDC(handle);
		SIZE sz;
		GetTextExtentPoint32(dc, text.c_str(), text.size(), &sz);
		ReleaseDC(handle, dc);
		return { uint32_t(sz.cx + 2), uint32_t(sz.cy) };
	}

	void win32::setFont(HWND handle, const String& fontFamily, int size) {
		HDC hdc = GetDC(handle);
		const int fontHeight = -MulDiv(size, GetDeviceCaps(hdc, LOGPIXELSY), 72);
		ReleaseDC(handle, hdc);

		HFONT font = CreateFont(
			fontHeight, 0, 0, 0,
			FW_DONTCARE, false, false, false,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, FF_SWISS,
			fontFamily.c_str()
		);

		SendMessage(handle, WM_SETFONT, WPARAM(font), true);
	}

	int runApplication(Widget* root) {
		HWND window = win32::createWindow({
			.title = TEXT("Nice Widget Engine"),
			.className = TEXT("NWE_Window"),
			.size = Size{ 600, 600 }
		});

		root->nativeBuild(win32::getBounds(window), window);
		auto&& wid = root->build();
		if (wid) {
			wid->nativeBuild(win32::getBounds(window), window);
		}

		MSG msg = {};
		while (GetMessage(&msg, nullptr, 0, 0) > 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		root->nativeDestroy();
		delete root;

		return msg.wParam;
	}

}

static LRESULT CALLBACK win32WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	//std::wcout << messageToString(msg) << std::endl;

	switch (msg) {
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

HWND nwe::win32::createWindow(WindowParams params, void* userData) {
	HINSTANCE instance = GetModuleHandle(0);

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = win32WndProc;
	wc.hInstance = instance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = HBRUSH(COLOR_WINDOW);
	wc.lpszClassName = params.className.c_str();
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, TEXT("Failed to initialize window."), TEXT("Error"), MB_OK);
		return nullptr;
	}

	RECT wect;
	wect.left = GetSystemMetrics(SM_CXSCREEN) / 2 - params.size.width / 2;
	wect.top = GetSystemMetrics(SM_CYSCREEN) / 2 - params.size.height / 2;
	wect.right = wect.left + params.size.width;
	wect.bottom = wect.top + params.size.height;

	AdjustWindowRectEx(&wect, WS_OVERLAPPEDWINDOW, 0, 0);

	HWND handle = CreateWindowEx(
		0,
		params.className.c_str(),
		params.title.c_str(),
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
		wect.left, wect.top, wect.right - wect.left, wect.bottom - wect.top,
		params.parent, NULL,
		instance,
		NULL
	);
	setFont(handle, TEXT("Segoe UI"));

	SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)userData);

	ShowWindow(handle, SW_SHOW);
	UpdateWindow(handle);

	return handle;
}

HWND nwe::win32::createControl(WidgetParams params, uint64_t uniqueID, void* userData) {
	HWND parent = params.parent;
	HWND hwnd = CreateWindow(
		params.className.c_str(),
		TEXT(""),
		params.style,
		0, 0, 16, 16,
		parent,
		HMENU(uniqueID),
		HINSTANCE(GetWindowLongPtr(parent, GWLP_HINSTANCE)),
		nullptr
	);
	if (userData) {
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)userData);
	}
	setFont(hwnd, TEXT("Segoe UI"));
	return hwnd;
}

bool IsTopLevelWindow(HWND window) {
	long style = ::GetWindowLong(window, GWL_STYLE);
	if (!(style & WS_CHILD))
		return true;
	HWND parent = ::GetParent(window);
	return !parent || (parent == ::GetDesktopWindow());
}

nwe::Rect nwe::win32::getBounds(HWND handle) {
	if (IsTopLevelWindow(handle)) {
		WINDOWINFO winfo{};
		GetWindowInfo(handle, &winfo);
		return {
			.x = 0,
			.y = 0,
			.width = uint32_t(winfo.rcClient.right - winfo.rcClient.left),
			.height = uint32_t(winfo.rcClient.bottom - winfo.rcClient.top)
		};
	}

	RECT rec{};
	GetWindowRect(handle, &rec);
	ScreenToClient(GetParent(handle), (LPPOINT) & ((LPPOINT)&rec)[0]);
	ScreenToClient(GetParent(handle), (LPPOINT) & ((LPPOINT)&rec)[1]);
	return {
		.x = rec.left,
		.y = rec.top,
		.width = uint32_t(rec.right - rec.left),
		.height = uint32_t(rec.bottom - rec.top)
	};
}
