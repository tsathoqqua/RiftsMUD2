//  Wizard:   Khojem
//  Monster:  legionnaire
//  File:     legion3.c

#include <std.h>
inherit MONSTER;

int query_kho_mon();

create() {
  int zlevel;
  ::create();
    set_name("legionnaire");
    set_id( ({ "legionnaire", "guard", "legion" }) );
    zlevel = 16 + random(5);
    set_level(zlevel);
    set_short("legionnaire");
    set_long("A massive, stone faced legionnaire stands glaring down at you."
      );
    set("race", "storm-giant");
    set_gender("male");
    set_body_type("human");
    set("gang bang",1);
    set_wimpy(0);
    add_money("silver", (200+random(99)));
	set_class("fighter");
	zlevel = random(3);
    if(zlevel == 0) {
   	    new("/wizards/khojem/port/weapon/flail")->move(this_object());
	    force_me("wield flail in right hand");
	    }
    if(zlevel == 1) {
	    new("/wizards/khojem/port/weapon/trident")->move(this_object());
	    force_me("wield trident in right hand and left hand");
	    }
    if(zlevel == 2) {
	    new("/wizards/khojem/port/weapon/falchion")->move(this_object());
	    force_me("wield falchion in right hand");
	    }
    new("/d/damned/virtual/corslet.armour")->move(this_object());
    force_me("wear corslet");
    new("/wizards/khojem/port/armor/legion_helm")->move(this_object());
    force_me("wear helmet");
    new("/wizards/khojem/port/armor/beaver")->move(this_object());
    force_me("wear beaver");    
}

int query_kho_mon() { return 1;}

