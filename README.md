# 🥇 Dynamic Dialog-Pages for San Andreas MultiPlayer 

Using this library you will can create pages in dialogs with a few lines of code. You can display many more lines in the dialog aside from the 4096 character limit.
> Let's see how it's working.

### First of all init include for your gamemode.
```pawn
#include "dialog-pages.inc"
```

To create dialog-pages you must use this function. This function have more arguments than the orginal. Additional arguments add library hints how the dialog exactly should look.
```pawn
ShowPlayerDialogPages(playerid, dialogid, dialogstyle, caption[], info[], button1[], button2[], maxitemslist = 15, nextbutton[] = "Next page", lastbutton[] = "Previous page", bool:dynamic = false);
```
  - **playerid** - player ID.
  - **dialogid** - dialog ID to check action.
  - **dialogstyle** - dialog format: *DIALOG_STYLE_LIST, DIALOG_STYLE_TABLIST, DIALOG_STYLE_TABLIST_HEADERS*
  - **caption[]** - title string dialog.
  - **info[]** - main string content dialog.
  - **button1[]** - string content for first button.
  - **button2[]** - string content for last button.
  - **maxitemlist** - number of lines for one page.
  - **nextbutton[]** - string content for next page button.
  - **lastbutton[]** - string content for previous page button.
  - **bool:dynamic** - if you would control dialog manualy (mainly buttons for page changes) you can set this boolean to true. If you use dynamic dialog-pages you must assign the action by yourself to the buttons chaning pages. If set to false, the include assign the page change button itself without your interference. You can learn more about dynamic dialogs below.

Dialog-Pages cooperates with large strings which means you can enter whatever you want. Now you can fit a lot of content into one dialog.

To check the action for dialog-pages use the initialized function in the library:

```pawn
public OnDialogPagesResponse(playerid, dialogid, response, listitem, btn_next_index, btn_previous_index)
```
  - **playerid** - player ID.
  - **dialogid** - dialog ID for check specific dialog.
  - **response** - returns true/false depending on which button is clicked in the dialog box.
  - **listitem** - return the index of the row clicked depending on the page.
  - **btn_next_index** - return the index of the next button that changes page.
  - **btn_previous_index** - return the index of the previous button that changes page.

**The last two arguments of this public are only useful when you indicate that the selecyed dialog is dynamic. With two arguments, you are able to check if one of the page change buttons has been clicked.**

## Let's see how to create a dialog which isn't dynamic.
> Let's create a loop which will generate for example 100 lines and put it into dialog. Let's make dialog which designate that there're only 10 lines per page. We can estimate that if we have 100 lines and divide it into 10 possible lines in one page in dialog there will be 10 pages - because **10 * 10 = 100**
```pawn
new string[4096], tmp_str[64];
for(new i = 0; i < 100; i++)
{
    format(tmp_str, sizeof tmp_str, "Random number: %i\n", random(999));
    strcat(string, tmp_str);
}
ShowPlayerDialogPages(playerid, 9812, DIALOG_STYLE_LIST, "Dialog-Pages - Test.", string, "Select", "Cancel", 15, "Next page", "Previous Page", false);
```
> If your intention isn't to create a dynamic dialog, you don't need to set the last argument because the default value is false.
```pawn
ShowPlayerDialogPages(playerid, 9812, DIALOG_STYLE_LIST, "Dialog-Pages - Test.", string, "Select", "Cancel", 15, "Next page", "Previous Page");
```
> The same goes for the buttons chaning pages. If you don't want to change them, you can just skip the arguments last three arguments:
```pawn
ShowPlayerDialogPages(playerid, 9812, DIALOG_STYLE_LIST, "Dialog-Pages - Test.", string, "Select", "Cancel", 15);
```
> Also, you don't need to enter the number of lines per page. The default is 15.
```pawn
ShowPlayerDialogPages(playerid, 9812, DIALOG_STYLE_LIST, "Dialog-Pages - Test.", string, "Select", "Cancel");
```
See how easy it is to use this library!

**Just remember that if you want to change the previous content button, you have to enter the previous full arguments.**

#### Let's check how to refer to the dialog. Let us make that after clicking the "Select" button then server send message for player with the index  that was selected on the page in the dialog when will be displayed.
```pawn
public OnDialogPagesResponse(playerid, dialogid, response, listitem, btn_next_index, btn_previous_index)
{
    switch(dialogid)
    {
        case 9812: //ID of dialog which we checking.
        {
            if(response)
            {
                new string[128];
                format(string, sizeof string, "You selected row: %i", listitem);
                SendClientMessage(playerid, -1, string);
            }
        }
    }
    return 1;
}
```
