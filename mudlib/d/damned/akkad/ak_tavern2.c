inherit "std/room";


void create() {
  ::create();
    set_property("light",3);
    set_property("night light", 2);
    add_exit("/d/damned/akkad/ak_tavern1", "north");
    add_exit("/d/damned/akkad/ak_tav", "east");
    add_exit("/d/damned/akkad/ak_tavern3", "south");
    set("short","Midst of Tavern Street");
add_exit("/d/damned/akkad/castle_shop", "west");
    set("long", "You are in the midst of Tavern Street.\n"
	"To the east is the Silver Lion Tavern.\n"
"To the west is the castle shop.\n");
    
}
