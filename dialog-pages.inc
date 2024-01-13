
/*
*
*
*
*   ---------------------------------------------------
*
*	Creater - @Bren828 					
*									01 October 2023
*
*   Version: 1.0
*
*   ---------------------------------------------------
*
*
*	https://github.com/Bren828/dialog-pages
*
*
*
*
* Create dialog
*    Dialog_Page(playerid, max_lines, const function[], style, const caption[], info[], const button1[], const button2[] = "", sinfo = sizeof(info))
*    Return: Returns (0) on failure or (1) on success
*
*   
* Set string value
*    SetValueDialogPage(playerid, line, value)
*    Return: Returns (0) on failure or (1) on success
*
*
* Get string value
*    GetValueDialogPage(playerid, listitem)
*    Return: Returns the value
*
*
* Set page number
*    SetPageDialogPage(playerid, page)
*    Return: Returns (0) on failure or (1) on success
*
*
* Get page number
*    GetPageDialogPage(playerid)
*    Return: Returns the page number
*
*
* Get the last pressed line
*    GetLastPressedLineDialogPage(playerid)
*    Return: Returns the value
*
*
* Set max lines
*    SetMaxLinesDialogPage(playerid, max_lines)
*    Return: Returns (0) on failure or (1) on success
*
*/

#if defined _dialog_pages_included 
	#endinput
#endif
#define _dialog_pages_included


#if !defined _mdialog_included
	#error "Please include mdialog.inc before dialog-pages.inc"
#endif


#if !defined DP_MAX_LISTITEM
    #define DP_MAX_LISTITEM 20
#endif


#if !defined DP_DIALOG_ID
    #define DP_DIALOG_ID 28028
#endif


#if !defined DP_NEXT_BUTTON
    #define DP_NEXT_BUTTON "> Next"
#endif


#if !defined DP_BACK_BUTTON
    #define DP_BACK_BUTTON "< Back"
#endif



enum DIALOG_PAGES_EN
{
    dl_Page,
    dl_NextButton,
    dl_BackButton,
    dl_ListitemID[DP_MAX_LISTITEM],
    dl_Function[MAX_FUNCTION_NAME],
    dl_MaxLines,
    dl_TotalMaxLines,
    dl_LastPressedLine
}
static _dialog_page[MAX_PLAYERS][DIALOG_PAGES_EN];



stock Dialog_Page(playerid, max_lines, const function[], style, const caption[], info[], const button1[] = "Select", const button2[] = "Cancel", sinfo = sizeof(info))
{
    if(strcmp(_dialog_page[playerid][dl_Function], function, true) || strlen(_dialog_page[playerid][dl_Function]) <= 1)
    {
        if(_dialog_page[playerid][dl_TotalMaxLines] == 0) _dialog_page[playerid][dl_TotalMaxLines] = DP_MAX_LISTITEM;

        _dialog_page[playerid][dl_Page] = 0;
        _dialog_page[playerid][dl_NextButton] = 0;
        _dialog_page[playerid][dl_BackButton] = 0;
    }

    _dialog_page[playerid][dl_MaxLines] = 0;
    format(_dialog_page[playerid][dl_Function], MAX_FUNCTION_NAME, function);

    new line_max;

    for(new x = (_dialog_page[playerid][dl_Page] * _dialog_page[playerid][dl_TotalMaxLines]); x < max_lines; x ++)
    {
       	if(x >= max_lines) break;

        if(line_max <= _dialog_page[playerid][dl_TotalMaxLines] -1)
        {
            _dialog_page[playerid][dl_MaxLines] ++;
        }

        line_max ++;
        if(line_max >= _dialog_page[playerid][dl_TotalMaxLines] + 1)
        {
            strcat(info, DP_NEXT_BUTTON, sinfo);
            strcat(info, "\n", sinfo);

            _dialog_page[playerid][dl_NextButton] = line_max;
            break;
        }
    }

    if(_dialog_page[playerid][dl_Page] >= 1)
    {
        strcat(info, DP_BACK_BUTTON, sinfo);
        strcat(info, "\n", sinfo);

        _dialog_page[playerid][dl_BackButton] = line_max + 1;
    }


    if(line_max == 0 && _dialog_page[playerid][dl_Page] == 0) 
    {
        return 0;       
    }


    if(max_lines - 1 >= (_dialog_page[playerid][dl_Page] + 1) * (_dialog_page[playerid][dl_TotalMaxLines] + 1))
    {
        printf("[dialog-pages warning]: 'max_lines' more than '#define DP_MAX_LISTITEM'", _dialog_page[playerid][dl_TotalMaxLines], line_max);
        
        printf("[dialog-pages warning]: Need to increase the '#define DP_MAX_LISTITEM' by %d", DP_MAX_LISTITEM + max_lines - (_dialog_page[playerid][dl_Page] + 1) * (_dialog_page[playerid][dl_TotalMaxLines] + 1));
    
        printf("[dialog-pages warning]: Function: %s | Caption: %s\n", function, caption);
    }


    MDialog_ShowPlayerDialog(playerid, DP_DIALOG_ID, style, caption, info, button1, button2);

    return 1;
}



stock SetValueDialogPage(playerid, line, value)
{
    if(line < 0 || line >= DP_MAX_LISTITEM) return 0;
    
    _dialog_page[playerid][dl_ListitemID][line] = value;
    return 1;
}


stock GetValueDialogPage(playerid, listitem)
{   
    if(listitem < 0 || listitem >= DP_MAX_LISTITEM) return 0;
    
    return _dialog_page[playerid][dl_ListitemID][listitem];
}  


stock SetPageDialogPage(playerid, page) 
{
    if(page < 0) return 0;

    _dialog_page[playerid][dl_Page] = page;
    _dialog_page[playerid][dl_NextButton] = 0;
    if(page == 0) _dialog_page[playerid][dl_BackButton] = 0;
    
    return 1;
}


stock GetPageDialogPage(playerid) 
{
    return _dialog_page[playerid][dl_Page];
}


stock GetLastPressedLineDialogPage(playerid) 
{
    return _dialog_page[playerid][dl_LastPressedLine];
}


stock SetMaxLinesDialogPage(playerid, max_lines)
{
    if(max_lines < 1 || max_lines >= DP_MAX_LISTITEM) return 0;

    _dialog_page[playerid][dl_TotalMaxLines] = max_lines;

    return 1;
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
            if(_dialog_page[playerid][dl_NextButton] >= 1 && _dialog_page[playerid][dl_NextButton] - 1 == listitem)
            {
                _dialog_page[playerid][dl_NextButton] = 0;
                _dialog_page[playerid][dl_Page] ++;

                Dialog_Show(playerid, _dialog_page[playerid][dl_Function]);

                return 1;
            }

            if(_dialog_page[playerid][dl_BackButton] >= 1 && _dialog_page[playerid][dl_BackButton] - 1 == listitem) 
            {
                _dialog_page[playerid][dl_BackButton] = 0;
                _dialog_page[playerid][dl_Page] --;

                Dialog_Show(playerid, _dialog_page[playerid][dl_Function]);

                return 1;
            }

            if(listitem < 0 || listitem >= _dialog_page[playerid][dl_TotalMaxLines] || _dialog_page[playerid][dl_MaxLines] <= listitem) return 1;
            
            _dialog_page[playerid][dl_LastPressedLine] = listitem;
        }

        new function[MAX_FUNCTION_NAME] = "dre_";
	    strcat(function, _dialog_page[playerid][dl_Function], sizeof(function));

        CallLocalFunction(function, "ddds", playerid, response, listitem, inputtext);

		return 1;
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

