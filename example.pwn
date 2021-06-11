public OnDialogPagesResponse(playerid, dialogid, response, listitem, inputtext[])
{
    new string[128];
    format(string, sizeof string, "[Dialog-Pages Debug] You decided to response = %s. Listitem index = %i.", (response) ? ("true") : ("false"), listitem);
    SendClientMessage(playerid, 0xFFF0000, string);
    return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
    if(strcmp(cmdtext, "/dialogtest1", true) == 0)
    {
        //DIALOG_STYLE_LIST
        new string[4096], tmp_str[64];
        for(new i = 0; i < 100; i++)
        {
            format(tmp_str, sizeof tmp_str, "Loop row index: %i\n", i);
            strcat(string, tmp_str);
        }
        ShowPlayerDialogPages(playerid, 9812, DIALOG_STYLE_LIST, "Dialog-Pages ~ Robson04.", string, "Select", "Cancel", 15);
    }
    if(strcmp(cmdtext, "/dialogtest2", true) == 0)
    {
        //DIALOG_STYLE_TABLIST
        new string[8192], tmp_str[64];
        for(new i = 0; i < 200; i++)
        {
            format(tmp_str, sizeof tmp_str, "Colum 1\tColum 2\tIndex: %i\n", i);
            strcat(string, tmp_str);
        }
        ShowPlayerDialogPages(playerid, 9812, DIALOG_STYLE_TABLIST, "Dialog-Pages ~ Robson04. (Page: #currentpage)", string, "Select", "Cancel", 12, "{A0A0A0}>>>", "{A0A0A0}<<<");
    }
    if(strcmp(cmdtext, "/dialogtest3", true) == 0)
    {
        //DIALOG_STYLE_TABLIST_HEADERS
        new string[8192] = "Colum 1\tColum 2\tColum 3\n", tmp_str[64];
        for(new i = 0; i < 275; i++)
        {
            format(tmp_str, sizeof tmp_str, "Hello world\t%x\tIndex: %i\n", random(999999), i);
            strcat(string, tmp_str);
        }
        ShowPlayerDialogPages(playerid, 9812, DIALOG_STYLE_TABLIST_HEADERS, "Dialog-Pages (Page: #currentpage/#pagelist)", string, "Select", "Cancel", 18, "{ff0000}-> Next page", "{000FFF}<- Previous page");
    }
    return 1;
}
