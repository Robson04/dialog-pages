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

## 📄 Let's see how to create a dialog which isn't dynamic. 📄
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

Ready. In this way, we have created a dialg with the pages that sends a message to the client who exactly clicked the index with the "Select" button.

## 📑 Let's see how to create a dialog which is dynamic. 📑
> We will create the same dialog as above, only that it will be dynamic. We set ``bool:dynamic`` to **true** (in this case we have to give all the arguments in the function).
```pawn
new string[4096], tmp_str[64];
for(new i = 0; i < 100; i++)
{
    format(tmp_str, sizeof tmp_str, "Random number: %i\n", random(999));
    strcat(string, tmp_str);
}
ShowPlayerDialogPages(playerid, 9812, DIALOG_STYLE_LIST, "Dialog-Pages - Test.", string, "Select", "Cancel", 15, "Next page", "Previous Page", true);
```
When you using dynamic dialogs, you are forced to add an action for page buttons on the your code. To give them an action, you need to use the OnDialogPagesResponse callback and check which button has been clicked. For this condition, you will need the last two callback parameters. Just see 109 line:
```pawn
public OnDialogPagesResponse(playerid, dialogid, response, listitem, inputtext[], btn_next_index, btn_previous_index)
{
    switch(dialogid)
    {
        case 9812:
        {
            if(listitem == btn_next_index || listitem == btn_previous_index) //line 109
            {
                if(listitem == btn_next_index) 
                    ShowPlayerDialogNextPage(playerid); 
                else ShowPlayerDialogPreviousPage(playerid); 
            }
            else ClearDialogPagesData(playerid); //line 115
        }
    }
    return 1;
}
```

> Functions for manage a dynamic dialogs below:
```pawn
ShowPlayerDialogNextPage(playerid); //- open a next page if the next page exist.
ShowPlayerDialogPreviousPage(playerid); //- open a previous page if previous page exist.
ShowPlayerDialogCurrentPage(playerid); //- open a current page.
ClearDialogPagesData(playerid); //- clearing a all data dialog-pages for player.
```

This code above checks to see if one of the page change buttons is clicked and gives them the same action that the include gives by default.
> An important element is the reset of dialog data. If you are using dynamic dialogs you are forced to reset the data after the dialog is completely closed. You must always keep this in mind as data cleansing is only required in dynamic dialogs.

> Look at 115 line, if player wasn't clicked button for changing pages he must clicked a normal list so you will be forced to reset dialog data for player because if player click on the normal list, the dialog is completely closed.

If we wanted to do exactly the same as in the static dialog above, we should code it this way in OnDialogPagesResponse.
```pawn
public OnDialogPagesResponse(playerid, dialogid, response, listitem, inputtext[], btn_next_index, btn_previous_index)
{
    switch(dialogid)
    {
        case 9812:
        {
            if(listitem == btn_next_index || listitem == btn_previous_index)
            {
                if(listitem == btn_next_index) 
                    ShowPlayerDialogNextPage(playerid); 
                else ShowPlayerDialogPreviousPage(playerid); 
            }
            else 
            {
                if(response)
                {
                    new string[128];
                    format(string, sizeof string, "You selected row: %i", listitem);
                    SendClientMessage(playerid, -1, string);
                }
                ClearDialogPagesData(playerid); //remember to reset player data if dialog completely closed.
            }
        }
    }
    return 1;
}
```

> Creating dynamic dialogs is very important for people who want to change actions for buttons that change page. Coding them is very simple and simple to operate. This way you can edit the action of the buttons.

## Display of the current page or the maximum number of pages in caption or info.
> By placing the appropriate phrases, which are given below in the title or in the main text, you are able to display the current page viewed or the number of all generated pages by Dialog-Pages.
```
#currentpage - display a current page.
#pagelist - display a all list of pages.
```

Example:
```pawn
ShowPlayerDialogPages(playerid, 9812, DIALOG_STYLE_LIST, "Test dialog. (Page: #currentpage/#pagelist)", string, "Select", "Cancel");
```

## Feedback and contact with library autors:
- Author of this include is Robson04. If you would contact with me, you can find me in discord: **Robson04#8010**
