# 🥇 Dynamic Dialog-Pages for San Andreas MultiPlayer 

Using this library you will can create pages in dialogs with a few lines of code. You can display many more lines in the dialog aside from the 4096 character limit.
> Let's see how it's working.

To create dialog-pages you must use this function. This function have more arguments than the orginal. Additional arguments add library hints how the dialog exactly should look.
```pawn
ShowPlayerDialogPages(playerid, dialogid, dialogstyle, caption[], info[], button1[], button2[], maxitemslist = 15, nextbutton[] = "Next page", lastbutton[] = "Previous page", bool:dynamic = false);
```
