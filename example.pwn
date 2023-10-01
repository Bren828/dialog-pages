


new Benches[60];


CMD:test(playerid, params[])
{
	for(new x; x < sizeof(Benches); x ++)
	{
		Benches[x] = x+1;
	}

	SetPageDialogPage(playerid, 0);
	Dialog_Show(playerid, Dialog:Test_Dialog_Page);
	return 1;
}


DialogCreate:Test_Dialog_Page(playerid)
{
	new max_lines = 20, // max lines
        max_benches,
        line, 
    	string[ (14 + 5) * 20 ],
        page = GetPageDialogPage(playerid)
    ;

    for(new x; x < sizeof(Benches); x ++)
    {
        if(Benches[x] == 0) continue;

        if( max_benches >= page * max_lines) // page check
        {
            if(line >= max_lines) // page ended
            {
                max_benches++;
                break;
            }

			// your code

            format(string, sizeof(string), "%s #%d - Benches %d\n", string, max_benches + 1, Benches[x]);

            SetValueDialogPage(playerid, line, x); // remember the cell number
            line ++;
        }

        max_benches++;
    }

    new check = Dialog_Page(playerid, max_benches, Dialog:Test_Dialog_Page, DIALOG_STYLE_TABLIST, "Dialog pages", string, "Select", "Cancel");

    if(check == 0)
	{
		Dialog_Message(playerid, "Dialog pages", "{FFFFFF}No benches", "Close");
		return 1;
	}

    return 1;
}



DialogResponse:Test_Dialog_Page(playerid, response, listitem, inputtext[])
{
    if(!response) 
	{
		return 1;
	}

    // your code
    new slot = GetValueDialogPage(playerid, listitem); // we get the cell number
	
	new string[144];
	format(string, sizeof(string), "Benches ID: %d", Benches[slot]);
	SendClientMessage(playerid, -1, string);


	Dialog_Show(playerid, Dialog:Test_Dialog_Page);
    return 1;
}