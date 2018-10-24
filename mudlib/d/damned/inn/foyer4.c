#include <std.h>

inherit ROOM;

void create() {
  ::create();
    set_property("indoors", 1);
    set_property("light", 2);
    set("short", "The Blue Dragon Inn foyer");
    set("long",
	"You reach a fourth-story landing.  You see hallways leading "+
	"to the south, east, and west.  You see a staircase leading down.");
    add_exit("/d/damned/inn/foyer3", "down");
    add_exit("/d/damned/inn/hall_40", "west");
    add_exit("/d/damned/inn/hall_41", "south");
    add_exit("/d/damned/inn/hall_42", "east");
    return;
}

