#include "a_samp.inc"
#include "../include/dialog-pages.inc"
#include "zcmd.inc"

#pragma dynamic 162940

#define MECHANIC 0
#define ELECTRICIAN 1
#define TEACHER 2
#define LOCKSMITH 3
#define PLUMBER 4
#define NONE 5
new const Careers[][] =
{
    {MECHANIC, "{F6FCCF}Mechanic"},
    {ELECTRICIAN, "{CFE3FC}Electrician"},
    {TEACHER, "{FCCFDA}Teacher"},
    {LOCKSMITH, "{D9FCCF}Locksmith"},
    {PLUMBER, "{CFFCDF}Plumber"},
    {NONE, "{999999}None"}
};

new const TestDialog[][][] =
{
    {
        {1, TEACHER, "Monica Washington"},
        {2, NONE, "Garrett Ford"},
        {3, ELECTRICIAN, "Alexander Baker"},
        {4, ELECTRICIAN, "Rosa Wong"},
        {5, ELECTRICIAN, "Edmund Jacobs"},
        {6, PLUMBER, "Lucy Cannon"},
        {7, NONE, "Freda Flowers"},
        {8, PLUMBER, "Shane Lowe"},
        {9, NONE, "Annette Alexander"},
        {10, LOCKSMITH, "Kimberly Craig"},
        {11, MECHANIC, "Myron Holland"},
        {12, NONE, "Rachel Watts"},
        {13, LOCKSMITH, "Vera Oliver"},
        {14, MECHANIC, "Sara Burton"},
        {15, NONE, "Erin Thompson"},
        {16, TEACHER, "Nicole Gordon"},
        {17, NONE, "Estelle Crawford"},
        {18, LOCKSMITH, "Rodolfo Carson"},
        {19, ELECTRICIAN, "Lucia Collins"},
        {20, ELECTRICIAN, "Roy Lewis"},
        {21, MECHANIC, "Antonia Wagner"},
        {22, TEACHER, "Kenneth Sanders"},
        {23, LOCKSMITH, "Louis Howell"},
        {24, TEACHER, "Taylor Watson"},
        {25, MECHANIC, "Mercedes Logan"},
        {26, NONE, "Harriet Cox"}
    }
};

CMD:dialogtest(playerid)
{
    new string[4096] = "#\tIdentity\tCareer\n";
    for(new i; i < 26; i++)
    {
        new tmp_str[128], career[32];
        for(new j, k = sizeof(Careers); j < k; j++)
        {
            if(TestDialog[0][i][1] == Careers[j][0])
                format(career, sizeof career, Careers[j][1]);
        }
        format(tmp_str, sizeof tmp_str, "%i\t{4361EA}%s\t%s\n", TestDialog[0][i][0], TestDialog[0][i][2], career);
        strcat(string, tmp_str);
    }
    ShowPlayerDialogPages(playerid, 947, DIALOG_STYLE_TABLIST_HEADERS, "List of professionally active people", string, "Hidden", "", 20, "> Next page", "< Previous Page");
    return 1;
}

public OnFilterScriptInit()
{
    printf("[Dialog-Pages]: Loaded test dialogs.");
    return 1;
}

public OnDialogPagesResponse(playerid, dialogid, response, listitem, inputtext[], btn_next_index, btn_previous_index)
{
    return 0;
}
