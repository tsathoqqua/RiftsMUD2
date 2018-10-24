

/* $Header: /mud/tkv/bin/player/RCS/_score.c,v 1.2 1995/08/26 23:41:43 mudriver Exp $

 * $Log: _score.c,v $

 * Revision 1.2  1995/08/26  23:41:43  mudriver

 * Changed the query_[hp,mp,sp,max_hp,max_sp,max_mp] calls

 * to reflect the new query_body(string what) function.

 *

 * Revision 1.1  1995/07/09  10:00:50  mudriver

 * Initial revision

 *

 * /bin/player/_score.c

 * created completely by Zortek

 */

#include <std.h>



inherit DAEMON;



string         *ADVENTURERa_PIC = (

    {

    "  \\\\^/^/^/^/       ",

    "   }/_/_/_/   \\\\^/^",

    " _=[______]  .  }___",

    "/  () . () . _=[___",

    ".  .       ./  ()  ",

    " .               . ",

    ".  .   .      .    ",

    });



string         *ADVENTURERb_PIC = (

    {

    " .  ..  ...   _  _ ",

    "   ../\\  ..../ \\/ \\",

    " _/\\/  \\o/\\_//\\/   ",

    "/  /    \\  \\/  \\  /",

    "  /             \\/ ",

    " /  /\\_   /  /\\  \\ ",

    "/  /  \\\\    /  \\  \\",

    });



string         *NONE_PIC = (

    {

    "\\\\               //",

    " \\\\ Unaffiliated// ",

    "  \\\\_         _//  ",

    "    _ %^BOLD%^WHITE%^CITIZEN%^RESET%^ _    ",

    "  //           \\\\  ",

    " // Join a Guild\\\\ ",

    "//               \\\\",

    });



/*

 * string * BASE_PIC = ({ "", "", "", |                   | "", "", "",

 * "", }); 

 */



string         *PALADIN_PIC = (

    {

    "          _______  ",

    "         [|     |] ",

    "    |    [|     |] ",

    " oxx]========>  // ",

    "    |     \\\\   //  ",

    "           \\\\_//   ",

    "                   ",

    });



string         *ARCHMAGE_PIC = (

    {

    "              ==   ",

    "    ______    ||   ",

    "   /     /   /  \\  ",

    "  /     //  /XXX_\\ ",

    " /_____//   \\____/ ",

    "{_____{/   ########",

    "                   ",

    });



string         *FIGHTER_PIC = (

    {

    "                   ",

    "       _______     ",

    " ----~~   _   \\    ",

    "         !}\\( |    ",

    "  ----_   \\___/    ",

    "        ~--__)     ",

    "                   ",

    });



string         *NIGHTBLADE_PIC = (

    {



    "         xxXXXxx.  ",

    "N B    XXXXX'    \\ ",

    "I L   XXXXX.   O  |",

    "G A   XX( XXx     /",

    "H D    XXXXX~   ,/ ",

    "T E     ~--__,/'   ",

    "                   ",

    });



string         *PRIEST_PIC = (

    {

    "      .____,      ",

    "      \\~~~//      ",

    "   |\\\\_| ||_/||   ",

    "   |  _  .__ ||   ",

    "   |// | || \\||   ",

    "      /___\\\\      ",

    "                  ",

    });



string         *RANGER_PIC = (

    {

    "    /              ",

    "   /{         ._,  ",

    "  / :}       //^\\\\ ",

    "=X---}-->   |{{ }}|",

    "  \\ :}       \\\\v//\\",

    "   \\{        / ~~\\ ",

    "    \\              ",

    });



string         *CHAOS_PIC = (

    {

    "  __-{ ,___, }-__  ",

    " ///^|:Q\\_/Q:|^\\\\\\ ",

    "^~   |{< : >}|   ~^",

    "     | ~\\:/~ |     ",

    "     {---V---}     ",

    "     |       |     ",

    "     {-------}     ",

    });



string         *OTHER_PIC = (

    {

    "  _______________  ",

    " /_\\             \\ ",

    "   | Your  Class | ",

    "  _|     is      | ",

    " / |  NOT  KNOWN | ",

    " | |  ..-+ +-..  | ",

    " \\_/_____________/ ",

    });



#define MAX_BAR_COLS 55



string 

bargraph(int gauge, int max, int flag)

{

    string          borg;

    int             i,

                    columns;



    if (!max)

        max = 1;

    columns = (MAX_BAR_COLS * gauge) / max - 1;

    if(flag)

    switch(to_int(columns)) {

      case -100..6:

        borg = "%^FLASH%^%^B_RED%^%^YELLOW%^";

        break;

      case 7..14:

        borg = "%^B_RED%^%^YELLOW%^";

        break;

      case 15..30:

        borg = "%^YELLOW%^";

        break;

      case 31..45:

        borg = "%^BLUE%^BOLD%^";

        break;

      case 46..54:

        borg = "%^GREEN%^%^BOLD%^";

        break;

      default:

        borg = "";

        break;

    }

    else

    switch(to_int(columns)) {

      case -100..6:

        borg = "";

        break;

      case 7..14:

        borg = "%^BOLD%^GREEN%^";

        break;

      case 15..30:

        borg = "%^BOLD%^BLUE%^";

        break;

      case 31..45:

        borg = "%^YELLOW%^";

        break;

      case 46..50:

        borg = "%^B_RED%^%^BOLD%^";

        break;

      default:

        borg = "%^FLASH%^%^B_RED%^%^YELLOW%^";

        break;

    }

    for (i = 0; i < MAX_BAR_COLS; i++)

        borg += (i <= columns ? "*" : " ");



    return borg;

}



string          dashes =

"----------------------------------------------------------------------";





int 

cmd_newscore(string who)

{

    string          title,

                    alerts,

                   *pic_string,

                   *attrib,

                    borg,

                    gm,

                    age3, hand, hand2,

                    foo;

    int             hp,

                    max_hp,

                    mp,

                    max_mp,

                    sp,

                    max_sp,

                    level,

                    intoxification,

                    qp,

                    age2;

    object          tp,

                    op;



    tp = this_player();

    attrib = ({ "", "", "", "", "", "", "", "", });



    if (!who)

        op = tp;

    else if (!wizardp(tp))

          return 0;

    else if (!(op = find_living(who)))

         return 0;

    else if (!(op = find_living(who)))

         return 0;



    title = (string) op->query_title();

    hp = (int) op->query_hp();

    max_hp = (int) op->query_max_hp();

    sp = (int) op->query_internal_encumbrance();

    max_sp = (int) op->query_max_internal_encumbrance();

    mp = (int) op->query_mp();

    max_mp = (int) op->query_max_mp();



// Some Mods by Drizzt 3/27/96

    age2 = (int) op->query_age();

    qp = (int) op->query_quest_points();

      if(age2>86400) age3 = (age2/86400 + " Days");

      else if(age2>3600) age3 = (age2/3600) + " Hours";

      else age3 = (age2/60) + " Min";

    hand = (string) op->query_property("handedness");

    if(op->query_property("ambidextry")) {

    hand2 = "You are ambidextrious";

    }

    else 

    hand2 = "You are "+hand+"ed.";



    attrib[0] = sprintf("%d", (int) op->query_level());

    attrib[1] = capitalize((string) op->query_race());

    attrib[2] = age3;

    attrib[3] = sprintf("%d", (int)op->query_property("dev points"));

    intoxification = (int) op->query_intox();

    switch (intoxification) {

      case 10000..420: attrib[4] = "FUBAR"; break;

      case 419..300:   attrib[4] = "Smashed"; break;

      case 299..180:   attrib[4] = "Roaring drunk"; break;

      case 170..90:    attrib[4] = "Drunk"; break;

      case 89..36:     attrib[4] = "Tipsy"; break;

      case 35..1:      attrib[4] = "Buzzed"; break;

      case 0:

      default:         attrib[4] = "Sober"; break;

    }

    // reusing variable

    intoxification = (int)op->query_quenched();

    switch (intoxification) {

      case 10000..420: attrib[5] = "Liquid Blob!"; break;

      case 419..300:   attrib[5] = "Bloated"; break;

      case 299..180:   attrib[5] = "Full"; break;

      case 170..90:    attrib[5] = "Satisfied"; break;

      case 89..36:     attrib[5] = "Thirsty"; break;

      case 35..1:      attrib[5] = "Parched"; break;

      case 0:

      default:         attrib[5] = "Dehydrated"; break;

    }

    // reusing variable AGAIN :)

    intoxification = (int)op->query_stuffed();

    switch (intoxification) {

      case 10000..420: attrib[6] = "Glutton!"; break;

      case 419..300:   attrib[6] = "Distended"; break;

      case 299..180:   attrib[6] = "Full"; break;

      case 170..90:    attrib[6] = "Satisfied"; break;

      case 89..36:     attrib[6] = "Hungry"; break;

      case 35..1:      attrib[6] = "Malnurished"; break;

      case 0:

      default:         attrib[6] = "Starving"; break;

    }

    attrib[7] = capitalize((string) op->query_class());

    alerts = (op->query_poisoning() ? "Poison " : " ");

    switch (op->query_class()) {

        case "none":

            pic_string = NONE_PIC;

            break;

        case "arch-mage":

            pic_string = ARCHMAGE_PIC;

            break;

        case "chaotic-lord":

            pic_string = CHAOS_PIC;

            break;

        case "cleric":

            pic_string = PRIEST_PIC;

            break;

        case "elementalist":

            pic_string = ARCHMAGE_PIC;

            break;

        case "enchanter":

            pic_string = ARCHMAGE_PIC;

            break;

        case "fighter":

            pic_string = FIGHTER_PIC;

            break;

        case "necromancer":

            pic_string = ARCHMAGE_PIC;

            break;

        case "nightblade":

            pic_string = NIGHTBLADE_PIC;

            break;

        case "sword-mage":

            pic_string = PALADIN_PIC;

            break;

        case "thief":

            pic_string = RANGER_PIC;

            break;

        case "tinker":

            pic_string = ADVENTURERb_PIC;

            break;

        case "war-priest":

            pic_string = PRIEST_PIC;

            break;

        case "paladin":

            pic_string = PALADIN_PIC;

            break;

        case "child":

            pic_string = NONE_PIC;

            break;

       default:

            pic_string = OTHER_PIC;

    }

    if((string)op->query_class() != "child") {

      gm = "/d/damned/guilds/join_rooms/"+(string)op->query_class()+"_join.c";

      gm = gm->query_master();

    }

    else gm = "None";

    if(wizardp(op)) gm = "immortal";

    message("Ninfo", "%^BOLD%^%^WHITE%^" + sprintf("%|72s\n", title), tp);

    message("Ninfo", "%^BLUE%^" + sprintf("%s\n", dashes), tp);



    message("Ninfo", "%^BLUE%^       +------------------------------------------------------------+%^RESET%^ \n", tp);

    message("Ninfo", "Health %^BLUE%^|%^RESET%^" + bargraph(hp, max_hp,1) + "%^RESET%^%^BLUE%^|%^RESET%^ " + hp + "\n", tp);

    message("Ninfo", "Mental %^BLUE%^|%^RESET%^" + bargraph(mp, max_mp,1) + "%^RESET%^%^BLUE%^|%^RESET%^ " + mp + "\n", tp);

    message("Ninfo", "Carry  %^BLUE%^|%^RESET%^" + bargraph(sp, max_sp,0) + "%^RESET%^%^BLUE%^|%^RESET%^ " + sp + "\n", tp);

    message("Ninfo", "%^BLUE%^       +------------------------------------------------------------+\n", tp);



    message("Ninfo", "%^BLUE%^" + sprintf("%s\n", dashes), tp);



    message("Ninfo", "%^BLUE%^ Level: %^RESET%^" + sprintf("%-15s", attrib[0]) + "%^BLUE%^|%^RESET%^" + pic_string[0] + "%^BLUE%^|%^GREEN%^          WEALTH\n", tp);



    message("Ninfo", "%^BLUE%^  Race: %^RESET%^" + sprintf("%-15s", attrib[1]) + "%^BLUE%^|%^RESET%^" + pic_string[1] + "%^BLUE%^|%^RESET%^   Platinum:  " + sprintf("%11i\n", op->query_money("platinum")), tp);



    message("Ninfo", "%^BLUE%^   Age: %^RESET%^" + sprintf("%-15s", attrib[2]) + "%^BLUE%^|%^RESET%^" + pic_string[2] + "%^BLUE%^|%^RESET%^       Gold:  " + sprintf("%11i\n", op->query_money("gold")), tp);



    message("Ninfo", "%^BLUE%^DevPts: %^RESET%^" + sprintf("%-15s", attrib[3]) + "%^BLUE%^|%^RESET%^" + pic_string[3] + "%^BLUE%^|%^RESET%^   Electrum:  " + sprintf("%11i\n", op->query_money("electrum")), tp);



    message("Ninfo", "%^BLUE%^ State: %^RESET%^" + sprintf("%-15s", attrib[4]) + "%^BLUE%^|%^RESET%^" + pic_string[4] + "%^BLUE%^|%^RESET%^     Silver:  " + sprintf("%11i\n", op->query_money("silver")), tp);



    message("Ninfo", "%^BLUE%^Thirst: %^RESET%^" + sprintf("%-15s", attrib[5]) + "%^BLUE%^|%^RESET%^" + pic_string[5] + "%^BLUE%^|--------------------------\n", tp);



    message("Ninfo", "%^BLUE%^Hunger: %^RESET%^" + sprintf("%-15s", attrib[6]) + "%^BLUE%^|%^RESET%^" + pic_string[6] + "%^BLUE%^|%^RESET%^ Experience:  " + sprintf("%11i\n", op->query_exp()), tp);



    message("Ninfo", "%^BLUE%^Alerts: %^RESET%^" + sprintf("%-15s", alerts) + "%^RESET%^%^BLUE%^]=-"+sprintf("%|15s", attrib[7] )+"-=[%^RESET%^     Master:  " + sprintf("%11s\n", capitalize(gm)), tp);



    message("Ninfo", sprintf("%-15s", hand2) + "  %^BLUE%^|%^RESET%^                   " + "%^BLUE%^|%^RESET%^  Quest Pts:  " + sprintf("%11d\n", qp), tp);



    message("Ninfo", "%^BLUE%^" + sprintf("%s\n", dashes) + "%^RESET%^", tp);

    return 1;

}



int 

help()

{

    write(@HELP

Syntax:  score [person]



This command gives you information about your character.



See also:  status, biography, skills, stats, money, inventory.

HELP

);

    return 1;

}













































