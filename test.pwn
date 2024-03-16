#include "dialog-pages.inc" 

public OnPlayerCommandText(playerid, cmdtext[]) {

    if(!strcmp(cmdtext, "/test", true))
    {
        new string[4096], tmp_str[64];
        for(new i = 0; i < 100; i++)
        {
            format(tmp_str, sizeof tmp_str, "Random number: %i\n", random(999));
            strcat(string, tmp_str);
        }
        ShowPlayerDialogPages(playerid, 9700, DIALOG_STYLE_LIST, "Dialog-Pages - Test.", string, "Select", "Cancel", 10, "Next page", "Previous Page", true);

    }   
}

public OnDialogPagesResponse(playerid, dialogid, response, listitem, inputtext[], btn_next_index, btn_previous_index)
{
    switch(dialogid)
    {
        case 9700:
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