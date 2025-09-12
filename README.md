# dialog-pages

Pages in a dialog for the mdialog library

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

	new extraid = Dialog_GetExtraID(playerid, listitem); // Specified in Dialog_SetString
	new current_page = Dialog_GetPageNumber(playerid);


    new string[144];
    format(string, sizeof(string), "text: %s | extra id: %d | current_page: %d", text, extraid, current_page);
    SendClientMessage(playerid, -1, string);


    Dialog_ShowPage(playerid); // show page again
    return 1;
}
```

## Functions
<details>
<summary>Click to expand the list</summary>
	
#### Dialog_SetString(playerid, const text[], extra_id = 0)
> Set the line text
> * `playerid` - The ID of the player to show the dialog to
> * `text` - Text of the dialog line
> * `extra_id` - Extra value
> * `Return` - Returns (0) on failure or (1) on success

#### Dialog_Page(playerid, const function[], style, const caption[], const button1[], const button2[], const next_button[] = DP_NEXT_BUTTON, const back_button[] = DP_BACK_BUTTON)
> Show the dialog page
> * `playerid` - The ID of the player to show the dialog to
> * `function` - The name of the dialog `Dialog:Test`
> * `style` - The style of the dialog
> * `caption[]` - The title at the top of the dialog
> * `button1[]` - The text on the left button
> * `button2[]` - The text on the right button
> * `next_button[]` - Next button text
> * `back_button[]` - Back button text
> * `Return` - Returns (0) on failure or (1) on success

#### Dialog_SetHeader(playerid, const header[])
> Set heading for style DIALOG_STYLE_TABLIST_HEADERS
> * `playerid` - The ID of the player to show the dialog to
> * `header[]` - Text of the dialog header

#### Dialog_ShowPage(playerid)
> Show the dialog page
> * `playerid` - The ID of the player to show the dialog to
> * `Return` - Returns (0) on failure or (1) on success

#### Dialog_UpdatePage(playerid)
> Update all dialog pages
> * `playerid` - The ID of the player to show the dialog to
> * `Return` - Returns (0) on failure or (1) on success

#### Dialog_GetString(playerid, listitem, text[])
> Get text of string
> * `playerid` - The ID of the player to show the dialog to
> * `listitem` - The ID of the list item selected by the player
> * `Return` - Returns (0) on failure or (1) on success

#### Dialog_GetExtraID(playerid, listitem)
> Get ExtraID
> * `playerid` - The ID of the player to show the dialog to
> * `listitem` - The ID of the list item selected by the player
> * `Return` - Returns (0) on failure or (1) on success

#### Dialog_GetPageNumber(playerid) 
> Get the page number
> * `playerid` - The ID of the player to show the dialog to
</details>

## Definition
<details>
<summary>Click to expand the list</summary>
	
```pawn
#define DP_MAX_LINES 500
#define DP_MAX_LINES_ON_PAGE 20
#define DP_MAX_TEXT_LINE_LENGTH 160
#define DP_MAX_TEXT_CAPTION_LENGTH 128
#define DP_MAX_TEXT_BUTTON_LENGTH 32
#define DP_CALLBACK_NAME "dre_"
#define DP_NEXT_BUTTON "> Next"
#define DP_BACK_BUTTON "< Back"
```
</details>
