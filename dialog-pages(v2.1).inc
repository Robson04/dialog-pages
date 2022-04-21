/*
    Dialog Pages V2.0
    Author: Robson04
*/

#include "a_samp"
#include "YSI_Coding\y_hooks"

#define MAX_DIALOG_CAPTION_LEN (64)
#define MAX_DIALOG_HEADER_LEN (512)
#define MAX_DIALOG_INFO_LEN (8192)
#define MAX_DIALOG_BUTTON_LEN (128)

#define BUTTON_NEXT_PAGE 0
#define BUTTON_PREVIOUS_PAGE 1
#define INVALID_BUTTON_ID -1

#define DIALOG_PAGES_CAPTION 0
#define DIALOG_PAGES_INFO 1

forward bool:IsButtonUsed(playerid, buttontype);
forward OnDialogPagesResponse(playerid, dialogid, response, listitem, inputtext[], btn_next_index, btn_previous_index);

enum DIALOG_PAGES
{
    bool:IsDialogActivate,
    DialogID,
    DialogStyle,
    Caption[MAX_DIALOG_CAPTION_LEN],
    Info[MAX_DIALOG_INFO_LEN],
    Button1[MAX_DIALOG_BUTTON_LEN],
    Button2[MAX_DIALOG_BUTTON_LEN],
    NextButton[MAX_DIALOG_BUTTON_LEN],
    LastButton[MAX_DIALOG_BUTTON_LEN],

    ItemCount,
    CurrentPage,
    MaxItemsSplit,
    PagesList,
    Header[MAX_DIALOG_HEADER_LEN],
    TabList,
    bool:IsDynamic
};
new PlayerDialogPagesCache[MAX_PLAYERS][DIALOG_PAGES];

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    if(PlayerDialogPagesCache[playerid][IsDialogActivate] == true)
    {
        if(dialogid == PlayerDialogPagesCache[playerid][DialogID])
        {
            new button_next = INVALID_BUTTON_ID, button_previous = INVALID_BUTTON_ID;
            if(IsDialogPagesButtonUsed(playerid, BUTTON_NEXT_PAGE))
                button_next = (GetDialogPagesListItemCount(playerid) - 1) + 1;
            if(IsDialogPagesButtonUsed(playerid, BUTTON_PREVIOUS_PAGE))
            {
                if(IsDialogPagesButtonUsed(playerid, BUTTON_NEXT_PAGE))
                    button_previous = (GetDialogPagesListItemCount(playerid) - 1) + 2;
                else button_previous = (GetDialogPagesListItemCount(playerid) - 1) + 1;
            }

            if(listitem == button_next || listitem == button_previous)
            {
                if(listitem == button_next)
                {
                    if(PlayerDialogPagesCache[playerid][IsDynamic] == false)
                        ShowPlayerDialogNextPage(playerid);
                    else
                    {
                        new edited_listitem = 0;
                        if(PlayerDialogPagesCache[playerid][CurrentPage] == 1)
                        {
                            edited_listitem = listitem;
                            OnDialogPagesResponse(playerid, dialogid, response, edited_listitem, inputtext, button_next, button_previous);
                        }
                        else
                        {
                            new page_listitems = (PlayerDialogPagesCache[playerid][CurrentPage] - 1) * PlayerDialogPagesCache[playerid][MaxItemsSplit], tmp_btn_next = page_listitems + button_next, tmp_btn_prev = page_listitems + button_previous;
                            edited_listitem = page_listitems + listitem;
                            OnDialogPagesResponse(playerid, dialogid, response, edited_listitem, inputtext, tmp_btn_next, tmp_btn_prev);
                        }
                    }
                }
                else if(listitem == button_previous)
                {
                    if(PlayerDialogPagesCache[playerid][IsDynamic] == false)
                        ShowPlayerDialogPreviousPage(playerid);
                    else
                    {
                        new edited_listitem = 0;
                        if(PlayerDialogPagesCache[playerid][CurrentPage] == 1)
                        {
                            edited_listitem = listitem;
                            OnDialogPagesResponse(playerid, dialogid, response, edited_listitem, inputtext, button_next, button_previous);
                        }
                        else
                        {
                            new page_listitems = (PlayerDialogPagesCache[playerid][CurrentPage] - 1) * PlayerDialogPagesCache[playerid][MaxItemsSplit], tmp_btn_next = page_listitems + button_next, tmp_btn_prev = page_listitems + button_previous;
                            edited_listitem = page_listitems + listitem;
                            OnDialogPagesResponse(playerid, dialogid, response, edited_listitem, inputtext, tmp_btn_next, tmp_btn_prev);
                        }
                    }
                }
            }
            else
            {
                new edited_listitem = 0;
                if(PlayerDialogPagesCache[playerid][CurrentPage] == 1)
                {
                    edited_listitem = listitem;
                    OnDialogPagesResponse(playerid, dialogid, response, edited_listitem, inputtext, button_next, button_previous);
                    ClearDialogPagesData(playerid);
                }
                else
                {
                    new page_listitems = (PlayerDialogPagesCache[playerid][CurrentPage] - 1) * PlayerDialogPagesCache[playerid][MaxItemsSplit], tmp_btn_next = page_listitems + button_next, tmp_btn_prev = page_listitems + button_previous;
                    edited_listitem = page_listitems + listitem;
                    OnDialogPagesResponse(playerid, dialogid, response, edited_listitem, inputtext, tmp_btn_next, tmp_btn_prev);
                    ClearDialogPagesData(playerid);
                }
            }
        }
        else ClearDialogPagesData(playerid);
    }
    return 0;
}

stock ShowPlayerDialogPages(playerid, dialogid, dialogstyle, const caption[], info[], const button1[], const button2[], maxitemslist = 15, const nextbutton[] = "Next page", const lastbutton[] = "Previous page", bool:dynamic = false)
{
    ClearDialogPagesData(playerid);
    PlayerDialogPagesCache[playerid][DialogID] = dialogid;
    PlayerDialogPagesCache[playerid][DialogStyle] = dialogstyle;
    format(PlayerDialogPagesCache[playerid][Caption], MAX_DIALOG_CAPTION_LEN, caption);

    if(dialogstyle == DIALOG_STYLE_TABLIST)
    {
        new header[MAX_DIALOG_HEADER_LEN], findbacknd = strfind(info, "\n", true, 0), tablist_pos = -1;
        strmid(header, info, 0, findbacknd + 1);
        for(;;)
        {
            tablist_pos = strfind(header, "\t", true, tablist_pos + 1);
            if(tablist_pos == -1) break;
            else PlayerDialogPagesCache[playerid][TabList]++;
        }
    }
    else if(dialogstyle == DIALOG_STYLE_TABLIST_HEADERS)
    {
        new findbacknd = strfind(info, "\n", true, 0), tablist_pos = -1;
        strmid(PlayerDialogPagesCache[playerid][Header], info, 0, findbacknd + 1);
        for(;;)
        {
            tablist_pos = strfind(PlayerDialogPagesCache[playerid][Header], "\t", true, tablist_pos + 1);
            if(tablist_pos == -1) break;
            else PlayerDialogPagesCache[playerid][TabList]++;
        }
        strdel(info, 0, findbacknd + 1);
    }

    new tmp_str[6];
    strmid(tmp_str, info, strlen(info) - 1, strlen(info));
    if(strcmp(tmp_str, "\n", true) != 0) strcat(info, "\n", MAX_DIALOG_INFO_LEN);
    strcat(PlayerDialogPagesCache[playerid][Info], info);

    format(PlayerDialogPagesCache[playerid][Button1], MAX_DIALOG_BUTTON_LEN, button1);
    format(PlayerDialogPagesCache[playerid][Button2], MAX_DIALOG_BUTTON_LEN, button2);
    format(PlayerDialogPagesCache[playerid][NextButton], MAX_DIALOG_BUTTON_LEN, nextbutton);
    format(PlayerDialogPagesCache[playerid][LastButton], MAX_DIALOG_BUTTON_LEN, lastbutton);
    PlayerDialogPagesCache[playerid][MaxItemsSplit] = maxitemslist;
    PlayerDialogPagesCache[playerid][IsDynamic] = dynamic;

    new pos = -1;
    for(;;)
    {
        pos = strfind(info, "\n", true, pos + 1);
        if(pos == -1) break;
        else PlayerDialogPagesCache[playerid][ItemCount]++;
    }

    new Float:tmp_pages = floatdiv(PlayerDialogPagesCache[playerid][ItemCount], maxitemslist);
    PlayerDialogPagesCache[playerid][PagesList] = floatround(tmp_pages, floatround_round);
    if(floatfract(tmp_pages) > 0.0 && floatfract(tmp_pages) < 0.5) PlayerDialogPagesCache[playerid][PagesList]++;
    if(PlayerDialogPagesCache[playerid][PagesList] == 0) PlayerDialogPagesCache[playerid][PagesList] = 1;
    PlayerDialogPagesCache[playerid][CurrentPage] = 1;

    new tmp_info[MAX_DIALOG_INFO_LEN], index = 0, tmp_pos = -1, itemlist_end = -1;
    for(;;)
    {
        tmp_pos = strfind(info, "\n", true, tmp_pos + 1);
        if(tmp_pos == -1) break;
        else
        {
            if(index < maxitemslist)
            {
                itemlist_end = tmp_pos;
                index++;
            }
            else break;
        }
    }
    strmid(tmp_info, info, 0, itemlist_end);
    if(PlayerDialogPagesCache[playerid][DialogStyle] == DIALOG_STYLE_TABLIST_HEADERS)
        strins(tmp_info, PlayerDialogPagesCache[playerid][Header], 0);
    AddDialogPagesButtons(playerid, tmp_info);

    ShowPlayerDialog(playerid, dialogid, dialogstyle, StringFormatDialogPagesCaption(playerid, PlayerDialogPagesCache[playerid][Caption]), StringFormatDialogPagesInfo(playerid, tmp_info), button1, button2);
    PlayerDialogPagesCache[playerid][IsDialogActivate] = true;
    return 1;
}

stock AddDialogPagesButtons(playerid, info[MAX_DIALOG_INFO_LEN])
{
    if(PlayerDialogPagesCache[playerid][PagesList] > 1)
    {
        if(PlayerDialogPagesCache[playerid][PagesList] != PlayerDialogPagesCache[playerid][CurrentPage])
        {
            new button_next[MAX_DIALOG_BUTTON_LEN + 11] = "", tmp_str[16]; //+ rgb and \n
            format(button_next, sizeof button_next, "\n%s", PlayerDialogPagesCache[playerid][NextButton]);
            for(new i = PlayerDialogPagesCache[playerid][TabList]; i > 0; i--)
            {
                format(tmp_str, sizeof tmp_str, "\t{000000}");
                strcat(button_next, tmp_str);
            }
            strcat(info, button_next);
        }

        if(PlayerDialogPagesCache[playerid][CurrentPage] != 1)
        {
            new button_last[MAX_DIALOG_BUTTON_LEN + 11] = "", tmp_str[16]; //+ rgb and \n
            format(button_last, sizeof button_last, "\n%s", PlayerDialogPagesCache[playerid][LastButton]);
            for(new i = PlayerDialogPagesCache[playerid][TabList]; i >= 0; i--)
            {
                format(tmp_str, sizeof tmp_str, "\t{000000}");
                strcat(button_last, tmp_str);
            }
            strcat(info, button_last);
        }
    }
    return 1;
}

stock ShowPlayerDialogNextPage(playerid)
{
    if(PlayerDialogPagesCache[playerid][IsDialogActivate] == true)
    {
        if(PlayerDialogPagesCache[playerid][PagesList] > PlayerDialogPagesCache[playerid][CurrentPage])
        {
            PlayerDialogPagesCache[playerid][CurrentPage]++;
            new tmp_info[MAX_DIALOG_INFO_LEN], previous_listitems = (PlayerDialogPagesCache[playerid][CurrentPage] - 1) * PlayerDialogPagesCache[playerid][MaxItemsSplit],
                start_pos = -1, end_pos = -1;
            new tmp_pos = -1, index = 0;
            for(;;)
            {
                tmp_pos = strfind(PlayerDialogPagesCache[playerid][Info], "\n", true, tmp_pos + 1);
                if(tmp_pos == -1) break;
                else
                {
                    if(index < previous_listitems)
                    {
                        start_pos = tmp_pos;
                        index++;
                    }
                    else break;
                }
            }

            tmp_pos = start_pos; index = 0;
            for(;;)
            {
                tmp_pos = strfind(PlayerDialogPagesCache[playerid][Info], "\n", true, tmp_pos + 1);
                if(tmp_pos == -1) break;
                else
                {
                    if(index < PlayerDialogPagesCache[playerid][MaxItemsSplit])
                    {
                        end_pos = tmp_pos;
                        index++;
                    }
                    else break;
                }
            }
            strmid(tmp_info, PlayerDialogPagesCache[playerid][Info], start_pos + 1, end_pos);
            if(PlayerDialogPagesCache[playerid][DialogStyle] == DIALOG_STYLE_TABLIST_HEADERS)
                strins(tmp_info, PlayerDialogPagesCache[playerid][Header], 0);
            AddDialogPagesButtons(playerid, tmp_info);

            ShowPlayerDialog(playerid, PlayerDialogPagesCache[playerid][DialogID], PlayerDialogPagesCache[playerid][DialogStyle], StringFormatDialogPagesCaption(playerid, PlayerDialogPagesCache[playerid][Caption]), StringFormatDialogPagesInfo(playerid, tmp_info), PlayerDialogPagesCache[playerid][Button1], PlayerDialogPagesCache[playerid][Button2]);
        }
        else ShowPlayerDialogCurrentPage(playerid);
    }
    return 1;
}

stock ShowPlayerDialogPreviousPage(playerid)
{
    if(PlayerDialogPagesCache[playerid][IsDialogActivate] == true)
    {
        if(PlayerDialogPagesCache[playerid][PagesList] - PlayerDialogPagesCache[playerid][CurrentPage] >= 0 && PlayerDialogPagesCache[playerid][CurrentPage] != 1)
        {
            PlayerDialogPagesCache[playerid][CurrentPage]--;
            new tmp_info[MAX_DIALOG_INFO_LEN], previous_listitems = (PlayerDialogPagesCache[playerid][CurrentPage] - 1) * PlayerDialogPagesCache[playerid][MaxItemsSplit],
                start_pos = -1, end_pos = -1;
            new tmp_pos = -1, index = 0;
            for(;;)
            {
                tmp_pos = strfind(PlayerDialogPagesCache[playerid][Info], "\n", true, tmp_pos + 1);
                if(tmp_pos == -1) break;
                else
                {
                    if(index < previous_listitems)
                    {
                        start_pos = tmp_pos;
                        index++;
                    }
                    else break;
                }
            }

            tmp_pos = start_pos; index = 0;
            for(;;)
            {
                tmp_pos = strfind(PlayerDialogPagesCache[playerid][Info], "\n", true, tmp_pos + 1);
                if(tmp_pos == -1) break;
                else
                {
                    if(index < PlayerDialogPagesCache[playerid][MaxItemsSplit])
                    {
                        end_pos = tmp_pos;
                        index++;
                    }
                    else break;
                }
            }
            strmid(tmp_info, PlayerDialogPagesCache[playerid][Info], start_pos + 1, end_pos);
            if(PlayerDialogPagesCache[playerid][DialogStyle] == DIALOG_STYLE_TABLIST_HEADERS)
                strins(tmp_info, PlayerDialogPagesCache[playerid][Header], 0);
            AddDialogPagesButtons(playerid, tmp_info);

            ShowPlayerDialog(playerid, PlayerDialogPagesCache[playerid][DialogID], PlayerDialogPagesCache[playerid][DialogStyle], StringFormatDialogPagesCaption(playerid, PlayerDialogPagesCache[playerid][Caption]), StringFormatDialogPagesInfo(playerid, tmp_info), PlayerDialogPagesCache[playerid][Button1], PlayerDialogPagesCache[playerid][Button2]);
        }
        else ShowPlayerDialogCurrentPage(playerid);
    }
    return 1;
}

stock ShowPlayerDialogCurrentPage(playerid)
{
    if(PlayerDialogPagesCache[playerid][IsDialogActivate] == true)
    {
        if(PlayerDialogPagesCache[playerid][CurrentPage] == 1)
        {
            new tmp_info[MAX_DIALOG_INFO_LEN], index = 0, itemlist_end = -1;
            for(;;)
            {
                if(index < PlayerDialogPagesCache[playerid][MaxItemsSplit])
                {
                    itemlist_end = strfind(PlayerDialogPagesCache[playerid][Info], "\n", true, itemlist_end + 1);
                    index++;
                }
                else break;
            }
            strmid(tmp_info, PlayerDialogPagesCache[playerid][Info], 0, itemlist_end + 1);
            if(PlayerDialogPagesCache[playerid][DialogStyle] == DIALOG_STYLE_TABLIST_HEADERS)
                strins(tmp_info, PlayerDialogPagesCache[playerid][Header], 0);
            AddDialogPagesButtons(playerid, tmp_info);

            ShowPlayerDialog(playerid, PlayerDialogPagesCache[playerid][DialogID], PlayerDialogPagesCache[playerid][DialogStyle], StringFormatDialogPagesCaption(playerid, PlayerDialogPagesCache[playerid][Caption]), StringFormatDialogPagesInfo(playerid, tmp_info), PlayerDialogPagesCache[playerid][Button1], PlayerDialogPagesCache[playerid][Button2]);
        }
        else
        {
            new listitem_count = (PlayerDialogPagesCache[playerid][CurrentPage] - 1) * PlayerDialogPagesCache[playerid][MaxItemsSplit],
                tmp_info[MAX_DIALOG_INFO_LEN], start_pos = -1, end_pos = -1;
            if(PlayerDialogPagesCache[playerid][DialogStyle] == DIALOG_STYLE_TABLIST_HEADERS)
                strcat(tmp_info, PlayerDialogPagesCache[playerid][Header]);

            new tmp_pos = -1, index = 0;
            for(;;)
            {
                tmp_pos = strfind(PlayerDialogPagesCache[playerid][Info], "\n", true, tmp_pos + 1);
                if(tmp_pos == -1) break;
                else
                {
                    if(index < listitem_count)
                    {
                        start_pos = tmp_pos;
                        index++;
                    }
                    else break;
                }
            }

            tmp_pos = start_pos; index = 0;
            for(;;)
            {
                tmp_pos = strfind(PlayerDialogPagesCache[playerid][Info], "\n", true, tmp_pos + 1);
                if(tmp_pos == -1) break;
                else
                {
                    if(index < PlayerDialogPagesCache[playerid][MaxItemsSplit])
                    {
                        end_pos = tmp_pos;
                        index++;
                    }
                    else break;
                }
            }
            if(start_pos != -1 && end_pos != -1)
            {
                strmid(tmp_info, PlayerDialogPagesCache[playerid][Info], start_pos + 1, end_pos);
                if(PlayerDialogPagesCache[playerid][DialogStyle] == DIALOG_STYLE_TABLIST_HEADERS)
                    strins(tmp_info, PlayerDialogPagesCache[playerid][Header], 0);
                AddDialogPagesButtons(playerid, tmp_info);

                ShowPlayerDialog(playerid, PlayerDialogPagesCache[playerid][DialogID], PlayerDialogPagesCache[playerid][DialogStyle], StringFormatDialogPagesCaption(playerid, PlayerDialogPagesCache[playerid][Caption]), StringFormatDialogPagesInfo(playerid, tmp_info), PlayerDialogPagesCache[playerid][Button1], PlayerDialogPagesCache[playerid][Button2]);
            }
            else return 0;
        }
    }
    return 1;
}

stock IsDialogPagesButtonUsed(playerid, buttontype)
{
    if(PlayerDialogPagesCache[playerid][IsDialogActivate] == true)
    {
        if(buttontype == BUTTON_NEXT_PAGE)
        {
            if(PlayerDialogPagesCache[playerid][CurrentPage] >= 1 && PlayerDialogPagesCache[playerid][CurrentPage] != PlayerDialogPagesCache[playerid][PagesList])
                return true;
        }
        else if(buttontype == BUTTON_PREVIOUS_PAGE)
        {
            if(PlayerDialogPagesCache[playerid][CurrentPage] != 1)
                return true;
        }
    }
    return false;
}

stock ClearDialogPagesData(playerid)
{
    new tmp_enum[DIALOG_PAGES];
    PlayerDialogPagesCache[playerid] = tmp_enum;
    return 1;
}

stock GetDialogPagesListItemCount(playerid)
{
    if(PlayerDialogPagesCache[playerid][IsDialogActivate] == true)
    {
        if(PlayerDialogPagesCache[playerid][CurrentPage] == 1)
        {
            new pos = -1, item_count = 0;
            for(;;)
            {
                pos = strfind(PlayerDialogPagesCache[playerid][Info], "\n", true, pos + 1);
                if(pos == -1) break;
                else
                {
                    if(item_count < PlayerDialogPagesCache[playerid][MaxItemsSplit])
                        item_count++;
                    else break;
                }
            }
            return item_count;
        }
        else
        {
            new page_listitems = (PlayerDialogPagesCache[playerid][CurrentPage] - 1) * PlayerDialogPagesCache[playerid][MaxItemsSplit],
                start_pos = -1, listitem_count = 0;

            new tmp_pos = -1, index = 0;
            for(;;)
            {
                tmp_pos = strfind(PlayerDialogPagesCache[playerid][Info], "\n", true, tmp_pos + 1);
                if(tmp_pos == -1) break;
                else
                {
                    if(index < page_listitems)
                    {
                        start_pos = tmp_pos;
                        index++;
                    }
                    else break;
                }
            }

            tmp_pos = start_pos; index = 0;
            for(;;)
            {
                tmp_pos = strfind(PlayerDialogPagesCache[playerid][Info], "\n", true, tmp_pos + 1);
                if(tmp_pos == -1) break;
                else
                {
                    if(index < PlayerDialogPagesCache[playerid][MaxItemsSplit])
                    {
                        listitem_count++;
                        index++;
                    }
                    else break;
                }
            }
            return listitem_count;
        }
    }
    return -1;
}

stock StringFormatDialogPagesInfo(playerid, const text[])
{
    new info[MAX_DIALOG_INFO_LEN];
    strcat(info, text);

    new info_pos = 0, info_lastfind = 0;
    for(;;)
    {
        info_pos = strfind(info, "#currentpage", true, info_lastfind);
        if(info_pos == -1) break;
        else
        {
            new string[64];
            format(string, sizeof string, "%i", PlayerDialogPagesCache[playerid][CurrentPage]);

            strdel(info, info_pos, info_pos + 12);
            strins(info, string, info_pos, MAX_DIALOG_INFO_LEN);
            info_lastfind = info_pos + 12;
        }
    }

    info_pos = 0; info_lastfind = 0;
    for(;;)
    {
        info_pos = strfind(info, "#pagelist", true, info_lastfind);
        if(info_pos == -1) break;
        else
        {
            new string[64];
            format(string, sizeof string, "%i", PlayerDialogPagesCache[playerid][PagesList]);

            strdel(info, info_pos, info_pos + 9);
            strins(info, string, info_pos, MAX_DIALOG_INFO_LEN);
            info_lastfind = info_pos + 8;
        }
    }
    return info;
}

stock StringFormatDialogPagesCaption(playerid, const text[])
{
    new caption[MAX_DIALOG_CAPTION_LEN];
    strcat(caption, text);

    new caption_pos = 0, caption_lastfind = 0;
    for(;;)
    {
        caption_pos = strfind(caption, "#currentpage", true, caption_lastfind);
        if(caption_pos == -1) break;
        else
        {
            new string[64];
            format(string, sizeof string, "%i", PlayerDialogPagesCache[playerid][CurrentPage]);

            strdel(caption, caption_pos, caption_pos + 12);
            strins(caption, string, caption_pos, MAX_DIALOG_CAPTION_LEN);
            caption_lastfind = caption_pos + 12;
        }
    }

    caption_pos = 0; caption_lastfind = 0;
    for(;;)
    {
        caption_pos = strfind(caption, "#pagelist", true, caption_lastfind);
        if(caption_pos == -1) break;
        else
        {
            new string[64];
            format(string, sizeof string, "%i", PlayerDialogPagesCache[playerid][PagesList]);

            strdel(caption, caption_pos, caption_pos + 9);
            strins(caption, string, caption_pos, MAX_DIALOG_CAPTION_LEN);
            caption_lastfind = caption_pos + 8;
        }
    }
    return caption;
}
