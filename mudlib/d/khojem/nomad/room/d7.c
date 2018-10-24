//      Wizard:  Khojem
//      desert 7
//      d7.c

#include <std.h>

inherit ROOM;

void reset() {
    ::reset();
    if(!present("urchin")) {
      new("/wizards/khojem/nomad/mon/sand_urchin")->move(this_object());
    }
}

void create() {
    ::create();
    set_property("light", 4);
    set_property("night light",1);
    set_property("indoors", 0);
    set("short", "The scorching desert");
    set("day long",
      "The bright, hot sun burns down on the back of your neck.  "+
      "You notice a few scattered tracks in the sand that lead out.  "+
      "Your feet and legs sink deep into the sand.  Every step is "+
      "a struggle as you wade through the hot sand.  Sand dunes are "+
      "all around you."
   );
    set("night long",
      "The night air chills your bones and robs you of body heat.  "+
      "You notice a few scattered tracks in the sand that lead out.  "+
      "Your feet and legs sink deep into the sand.  Every step is "+
      "a struggle as you wade through the cold sand.  Sand dunes are "+
      "all around you."
    );
    add_exit("/wizards/khojem/nomad/room/d1","northeast");
    add_exit("/wizards/khojem/nomad/room/d8","north");
    add_exit("/wizards/khojem/nomad/room/r2","west");
    set_items(([
     ({ "track","tracks" }) :
        "The tracks are footprints in the sand that have not been swept away.",
     ({ "sand","sand dunes","dunes" }) :
        "The high sand dunes block your view to the horizon.\n",
    ]));
    set_smell("default", "The dry, arid air burns your nose.");
    set_listen("default", "The silence is interrupted only by your footsteps.");
}
