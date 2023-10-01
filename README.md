# dialog-pages

Pages in the dialog

![Crosshair](https://raw.githubusercontent.com/Bren828/dialog-pages/main/preview.png)

## Reference
* [Installation](https://github.com/Bren828/dialog-pages#installation)
* [Example](https://github.com/Bren828/dialog-pages#example)
* [Functions](https://github.com/Bren828/dialog-pages#functions)
* [Definition](https://github.com/Bren828/dialog-pages#definition)

## Dependencies
* [mdialog](https://github.com/Open-GTO/mdialog)

## Installation

Include in your code and begin using the library:
```pawn
#include <dialog-pages>
```

## Example
```pawn
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
```

## Functions

#### Dialog_Page(playerid, max_lines, const function[], style, const caption[], info[], const button1[], const button2[] = "", sinfo = sizeof(info))
> Show dialog
> * `playerid` - The ID of the player to show the dialog to
> * `max_lines` - Max list item
> * `function` - The name of the dialog `Dialog:Test`
> * `style` - The style of the dialog
> * `caption[]` - The title at the top of the dialog
> * `info[]` - The text to display in the main dialog
> * `button1[]` - The text on the left button
> * `button2[]` - The text on the right button
> * `Return` - Returns (0) on failure or (1) on success

#### SetValueDialogPage(playerid, line, value)
> Set string value
> * `playerid` - The ID of the player to show the dialog to
> * `line` - Line number
> * `value` - Item

#### GetValueDialogPage(playerid, listitem)
> Get string value
> * `playerid` - The ID of the player to show the dialog to
> * `listitem` - The ID of the list item selected by the player
> * `Return` - Returns the value

#### SetPageDialogPage(playerid, page) 
> Set page number
> * `playerid` - The ID of the player to show the dialog to
> * `page` - Page number

#### GetPageDialogPage(playerid) 
> Get page number
> * `playerid` - The ID of the player to show the dialog to
> * `Return` - Returns the page number

#### GetLastPressedLineDialogPage(playerid) 
> Get the last pressed line
> * `playerid` - The ID of the player to show the dialog to
> * `Return` - Returns the line number

#### SetMaxLinesDialogPage(playerid, max_lines)
> Set max lines
> * `playerid` - The ID of the player to show the dialog to
> * `max_lines` - Max lines in `Dialog_Page`
> * `Return` - Returns (0) on failure or (1) on success




## Definition

```pawn
#define DP_MAX_LISTITEM 20

#define DP_DIALOG_ID 28028

static DP_NEXT_BUTTON[] = "> Next";

static DP_BACK_BUTTON[] = "< Back";
```
