CMD:test(playerid, params[])
{
    Dialog_Show(playerid, Dialog:Test_Dialog_Page);
    return 1;
}


DialogCreate:Test_Dialog_Page(playerid)
{
    new string[DP_MAX_TEXT_LINE_LENGTH]; // DP_MAX_TEXT_LINE_LENGTH = 160


	Dialog_SetHeader(playerid, "#\tText"); //for style DIALOG_STYLE_TABLIST_HEADERS


    for(new x; x < 200; x ++)
    {
		format(string, sizeof(string), "#%d. \t Benches %d\n", x+1, x);

		Dialog_SetString(playerid, string);
    }

    Dialog_Page(playerid, Dialog:Test_Dialog_Page, DIALOG_STYLE_TABLIST_HEADERS, "Caption", "Select", "Cancel");
    return 1;
}


DialogResponse:Test_Dialog_Page(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

	new text[DP_MAX_TEXT_LINE_LENGTH]; // DP_MAX_TEXT_LINE_LENGTH = 160
	Dialog_GetString(playerid, listitem, text); // or inputtext

	new extraid = Dialog_GetExtraID(playerid, listitem);
	new current_page = Dialog_GetPageNumber(playerid);


    new string[144];
    format(string, sizeof(string), "text: %s | extra id: %d | current_page: %d", text, extraid, current_page);
    SendClientMessage(playerid, -1, string);


    Dialog_ShowPage(playerid); // show page again
    return 1;
}

