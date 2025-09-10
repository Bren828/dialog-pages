
/*
*
*
*
*   ---------------------------------------------------
*
*	Creater - @Bren828 					
*									10 September 2025
*
*   Version: 1.1
*
*   ---------------------------------------------------
*
*
*	https://github.com/Bren828/dialog-pages
*
*
*/

#if defined _dialog_pages_included 
	#endinput
#endif
#define _dialog_pages_included


#if !defined _mdialog_included
	#error "Please include mdialog.inc before dialog-pages.inc"
#endif


#if !defined DP_MAX_LINES
    #define DP_MAX_LINES 500
#endif

#if !defined DP_MAX_LINES_ON_PAGE
    #define DP_MAX_LINES_ON_PAGE 20
#endif

#if !defined DP_MAX_TEXT_LINE_LENGTH
    #define DP_MAX_TEXT_LINE_LENGTH 160
#endif

#if !defined DP_MAX_TEXT_CAPTION_LENGTH
    #define DP_MAX_TEXT_CAPTION_LENGTH 128
#endif

#if !defined DP_MAX_TEXT_BUTTON_LENGTH
    #define DP_MAX_TEXT_BUTTON_LENGTH 32
#endif

#if !defined DP_DIALOG_ID
    #define DP_DIALOG_ID 28028
#endif

#if !defined DP_CALLBACK_NAME
    #define DP_CALLBACK_NAME "dre_"
#endif

#if !defined DP_NEXT_BUTTON
    #define DP_NEXT_BUTTON "> Next"
#endif

#if !defined DP_BACK_BUTTON
    #define DP_BACK_BUTTON "< Back"
#endif


enum DIALOG_PAGES_EN
{
    dp_Page,
    dp_MaxLines,
  
    dp_Function[MAX_FUNCTION_NAME],
    dp_Style,
    dp_Caption[DP_MAX_TEXT_CAPTION_LENGTH],
    dp_Button1[DP_MAX_TEXT_BUTTON_LENGTH],
    dp_Button2[DP_MAX_TEXT_BUTTON_LENGTH],
    dp_Header[DP_MAX_TEXT_LINE_LENGTH],
}
static _dialog_page[MAX_PLAYERS][DIALOG_PAGES_EN];



enum DIALOG_PAGES_LINE_EN
{
    dpl_Text[DP_MAX_TEXT_LINE_LENGTH],
    dpl_ExtraID,
}
static _dialog_page_line[MAX_PLAYERS][DP_MAX_LINES][DIALOG_PAGES_LINE_EN];



stock Dialog_SetString(playerid, const text[], extra_id = 0)
{
    new next_slot = _dialog_page[playerid][dp_MaxLines];

    if(next_slot >= DP_MAX_LINES) 
        return printf("Dialog_SetString >>> Increase the DP_MAX_LINES function value to %d", next_slot) & 0;

    format(_dialog_page_line[playerid][next_slot][dpl_Text], DP_MAX_TEXT_LINE_LENGTH, text);
    _dialog_page_line[playerid][next_slot][dpl_ExtraID] = extra_id;


    _dialog_page[playerid][dp_MaxLines] = next_slot + 1;
    return 1;
}


stock Dialog_ClearPage(playerid)
{
    _dialog_page[playerid][dp_MaxLines] = 0;

    _dialog_page[playerid][dp_Page] = 1;
    return 1;
}


stock Dialog_SetHeader(playerid, const header[])
{
    format(_dialog_page[playerid][dp_Header], DP_MAX_TEXT_LINE_LENGTH, "%s\n", header);
    return 1;
}


stock Dialog_Page(playerid, const function[], style, const caption[], const button1[], const button2[], const next_button[] = DP_NEXT_BUTTON, const back_button[] = DP_BACK_BUTTON)
{
    if(!_dialog_page[playerid][dp_MaxLines] || !_dialog_page[playerid][dp_Page]) 
        return print("Dialog_Page >>> Use the Dialog_ClearPages() function before the Dialog_Page() function") & 0;


    new info[DP_MAX_TEXT_LINE_LENGTH + (DP_MAX_TEXT_LINE_LENGTH * DP_MAX_LINES_ON_PAGE) + DP_MAX_TEXT_BUTTON_LENGTH + DP_MAX_TEXT_BUTTON_LENGTH],
        page = _dialog_page[playerid][dp_Page],
		next = 0,
		max_line;

    if(style == DIALOG_STYLE_TABLIST_HEADERS) strcat(info, _dialog_page[playerid][dp_Header]);


    for(new i = 0; i < _dialog_page[playerid][dp_MaxLines]; i++)
	{
		if(max_line >= (page * DP_MAX_LINES_ON_PAGE) && max_line < (page * DP_MAX_LINES_ON_PAGE) + DP_MAX_LINES_ON_PAGE) next ++;

		if(max_line >= (page - 1) * DP_MAX_LINES_ON_PAGE && max_line < ((page - 1) * DP_MAX_LINES_ON_PAGE) + DP_MAX_LINES_ON_PAGE)
		{
			format(info, sizeof info, "%s%s\n", info, _dialog_page_line[playerid][max_line][dpl_Text]);
		}

		max_line++;
	}


    if(!max_line) 
		return 0;

	if(next) 
        strcat(info, next_button);

	if(page > 1) 
        format(info, sizeof(info), "%s\n%s", info, back_button);


    format(_dialog_page[playerid][dp_Function], MAX_FUNCTION_NAME, function);

    _dialog_page[playerid][dp_Style] = style;
    format(_dialog_page[playerid][dp_Caption], DP_MAX_TEXT_CAPTION_LENGTH, caption);
    format(_dialog_page[playerid][dp_Button1], DP_MAX_TEXT_BUTTON_LENGTH, button1);
    format(_dialog_page[playerid][dp_Button2], DP_MAX_TEXT_BUTTON_LENGTH, button2);

    MDialog_ShowPlayerDialog(playerid, DP_DIALOG_ID, style, caption, info, button1, button2);
    return 1;
}


stock Dialog_ShowPage(playerid)
{
    if(!_dialog_page[playerid][dp_MaxLines] || !_dialog_page[playerid][dp_Page]) 
        return 0;

    return Dialog_Page(playerid, 
        _dialog_page[playerid][dp_Function], 
        _dialog_page[playerid][dp_Style], 
        _dialog_page[playerid][dp_Caption], 
        _dialog_page[playerid][dp_Button1],
        _dialog_page[playerid][dp_Button2]);
}


stock Dialog_GetString(playerid, listitem, text[])
{
    new page = _dialog_page[playerid][dp_Page]-1;

    if(page < 0 || !(0 <= listitem < DP_MAX_LINES_ON_PAGE))
        return 0;

    format(text, DP_MAX_TEXT_LINE_LENGTH, 
        _dialog_page_line[playerid][ listitem + (page * DP_MAX_LINES_ON_PAGE) ][dpl_Text]);

    return 1;
}


stock Dialog_GetExtraID(playerid, listitem)
{
    new page = _dialog_page[playerid][dp_Page]-1;

    if(page < 0 || !(0 <= listitem < DP_MAX_LINES_ON_PAGE))
        return 0;

    return _dialog_page_line[playerid][ listitem + (page * DP_MAX_LINES_ON_PAGE) ][dpl_ExtraID];
}


stock Dialog_GetPageNumber(playerid) 
{
    return _dialog_page[playerid][dp_Page];
}



#if defined _inc_y_hooks || defined _INC_y_hooks
    hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
#else
    public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
#endif
{
	if(dialogid == DP_DIALOG_ID) 
    {
        if(response)
        {
            if(!strcmp(inputtext, DP_NEXT_BUTTON)) 
            {
                _dialog_page[playerid][dp_Page] ++;

                Dialog_Page(playerid, 
                    _dialog_page[playerid][dp_Function], 
                    _dialog_page[playerid][dp_Style], 
                    _dialog_page[playerid][dp_Caption], 
                    _dialog_page[playerid][dp_Button1],
                    _dialog_page[playerid][dp_Button2]);

                return 1;
            }
            else if(!strcmp(inputtext, DP_BACK_BUTTON)) 
            {
                _dialog_page[playerid][dp_Page] --;	

                Dialog_Page(playerid, 
                    _dialog_page[playerid][dp_Function], 
                    _dialog_page[playerid][dp_Style], 
                    _dialog_page[playerid][dp_Caption], 
                    _dialog_page[playerid][dp_Button1],
                    _dialog_page[playerid][dp_Button2]);
                    
                return 1;
            }

            if(!(0 <= listitem < DP_MAX_LINES_ON_PAGE)) 
                return 1;
            

            new function[MAX_FUNCTION_NAME] = DP_CALLBACK_NAME;
            strcat(function, _dialog_page[playerid][dp_Function], sizeof(function));

            CallLocalFunction(function, "ddds", playerid, response, listitem, inputtext);
            return 1;
        }
	}

    #if !defined _inc_y_hooks && !defined _INC_y_hooks
        #if defined OnDialogResponse_DP
            return OnDialogResponse_DP(playerid, dialogid, response, listitem, inputtext);
        #else
            return 0;
        #endif
    #else
	    return 0;
    #endif
}

#if !defined _inc_y_hooks && !defined _INC_y_hooks
    #if defined _ALS_OnDialogResponse
        #undef OnDialogResponse
    #else
        #define _ALS_OnDialogResponse
    #endif

    #define OnDialogResponse OnDialogResponse_DP
    #if defined OnDialogResponse_DP
        forward OnDialogResponse_DP(playerid, dialogid, response, listitem, inputtext[]);
    #endif
#endif
