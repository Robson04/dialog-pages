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
Dialog-Pages cooperates with large strings which means you can enter whatever you want. Now you can fit a lot of content into one dialog.
1. function ShowPlayerDialogPages ~ parametrs/arguments
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

2. public OnDialogPagesResponse(playerid, dialogid, response, listitem, btn_next_index, btn_previous_index)
  - **playerid** - player ID.
  - **dialogid** - dialog ID for check specific dialog.
  - **response** - returns true/false depending on which button is clicked in the dialog box.
  - **listitem** - return the index of the row clicked depending on the page.
  - **btn_next_index** - return the index of the next button that changes page.
  - **btn_previous_index** - return the index of the previous button that changes page.
