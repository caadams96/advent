//
// Created by corey on 2/8/2023.
//

#ifndef ADVENT_GLOBALS_H
#define ADVENT_GLOBALS_H
#define hash_prime 1009 \

#define streq(a,b) (strncmp(a,b,5) ==0)  \

#define min_treasure GOLD
#define is_treasure(t) (t>=min_treasure)
#define max_obj CHAIN \

#define ok default_msg[RELAX] \

#define new_mess(x) message[k++]= x
#define mess_wd(w) new_word(w,k)  \

#define min_in_cave inside
#define min_lower_loc emist
#define min_forced_loc crack
#define max_loc didit
#define max_spec troll \

#define lighted 1
#define oil 2
#define liquid 4
#define cave_hint 8
#define bird_hint 16
#define snake_hint 32
#define twist_hint 64
#define dark_hint 128
#define witt_hint 256 \

#define travel_size 740
#define rem_size 15 \

#define make_loc(x,l,s,f)  \
{long_desc[x]= l;short_desc[x]= s;flags[x]= f;start[x]= q;}
#define make_inst(m,c,d)  \
{q->mot= m;q->cond= c;q->dest= d;q++;}
#define ditto(m)  \
{q->mot= m;q->cond= (q-1) ->cond;q->dest= (q-1) ->dest;q++;} \

#define holds(o) 100+o
#define sees(o) 200+o
#define not(o,k) 300+o+100*k
#define remark(m) remarks[++rem_count]= m
#define sayit max_spec+rem_count \

#define max_pirate_loc dead2 \

#define forced_move(loc) (loc>=min_forced_loc)
#define FORCE 0 \

#define toting(t) (place[t]<0)  \

#define move(t,l) {carry(t) ;drop(t,l) ;}
#define destroy(t) move(t,limbo)  \

#define new_obj(t,n,b,l) { \
name[t]= n; \
base[t]= b; \
offset[t]= note_ptr; \
prop[t]= (is_treasure(t) ?-1:0) ; \
drop(t,l) ; \
} \

#define new_note(n) note[note_ptr++]= n \

#define buf_size 72 \

#define here(t) (toting(t) ||place[t]==loc)
#define water_here ((flags[loc]&(liquid+oil) ) ==liquid)
#define oil_here ((flags[loc]&(liquid+oil) ) ==liquid+oil)
#define no_liquid_here ((flags[loc]&liquid) ==0)  \

#define try_motion(m) {mot= m;goto try_move;}
#define stay_put try_motion(NOWHERE)  \

#define report(m) {printf("%s\n",m) ;continue;}
#define default_to(v) report(default_msg[v])
#define change_to(v) {oldverb= verb;verb= v;goto transitive;} \

#define dark ((flags[loc]&lighted) ==0&&(prop[LAMP]==0||!here(LAMP) ) )  \

#define object_in_bottle ((obj==WATER&&prop[BOTTLE]==0) || \
(obj==OIL&&prop[BOTTLE]==2) )  \

#define bottle_empty (prop[BOTTLE]==1||prop[BOTTLE]<0)  \

#define clam_oyster (obj==CLAM?"clam":"oyster")  \

#define pct(r) (ran(100) <r)  \

#define nd 5
#define chest_loc dead2
#define message_loc pony \

#define pirate_not_spotted (place[MESSAGE]==limbo)
#define too_easy(i) (i==PYRAMID&&(loc==proom||loc==droom) )  \

#define closing (clock1<0)  \

#define max_deaths 3 \

#define max_score 350 \

#define n_hints 8 \

#define highest_class 8 \

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

typedef enum{false,true}boolean;

typedef enum{no_type,motion_type,object_type,
    action_type,message_type}wordtype;
typedef struct{
    char text[6];
    char word_type;
    char meaning;
}hash_entry;

typedef enum{
    N,S,E,W,NE,SE,NW,SW,
    U,D,L,R,IN,OUT,FORWARD,BACK,
    OVER,ACROSS,UPSTREAM,DOWNSTREAM,
    ENTER,CRAWL,JUMP,CLIMB,LOOK,CROSS,
    ROAD,HILL,WOODS,VALLEY,HOUSE,
    GULLY,STREAM,DEPRESSION,ENTRANCE,CAVE,
    ROCK,SLAB,BED,PASSAGE,CAVERN,
    CANYON,AWKWARD,SECRET,BEDQUILT,RESERVOIR,
    GIANT,ORIENTAL,SHELL,BARREN,BROKEN,DEBRIS,VIEW,FORK,
    PIT,SLIT,CRACK,DOME,HOLE,WALL,HALL,ROOM,FLOOR,
    STAIRS,STEPS,COBBLES,SURFACE,DARK,LOW,OUTDOORS,
    Y2,XYZZY,PLUGH,PLOVER,OFFICE,NOWHERE}motion;

typedef enum{
    NOTHING,KEYS,LAMP,GRATE,GRATE_,
    CAGE,ROD,ROD2,TREADS,TREADS_,
    BIRD,DOOR,PILLOW,SNAKE,CRYSTAL,CRYSTAL_,TABLET,CLAM,OYSTER,
    MAG,DWARF,KNIFE,FOOD,BOTTLE,WATER,OIL,
    MIRROR,MIRROR_,PLANT,PLANT2,PLANT2_,
    STALACTITE,SHADOW,SHADOW_,
    AXE,ART,PIRATE,DRAGON,DRAGON_,
    BRIDGE,BRIDGE_,TROLL,TROLL_,TROLL2,TROLL2_,
    BEAR,MESSAGE,GEYSER,PONY,BATTERIES,MOSS,
    GOLD,DIAMONDS,SILVER,JEWELS,COINS,CHEST,EGGS,TRIDENT,VASE,
    EMERALD,PYRAMID,PEARL,RUG,RUG_,SPICES,CHAIN}object;


typedef enum{
    ABSTAIN,TAKE,DROP,OPEN,CLOSE,ON,OFF,WAVE,CALM,GO,RELAX,
    POUR,EAT,DRINK,RUB,TOSS,
    WAKE,FEED,FILL,BREAK,BLAST,KILL,
    SAY,READ,FEEFIE,BRIEF,FIND,INVENTORY,SCORE,QUIT}action;


typedef enum{
    inhand= -1,limbo,
    road,hill,house,valley,forest,woods,slit,outside,
    inside,cobbles,debris,awk,bird,spit,
    emist,nugget,efiss,wfiss,wmist,
    like1,like2,like3,like4,like5,like6,like7,
    like8,like9,like10,like11,like12,like13,like14,
    brink,elong,wlong,
    diff0,diff1,diff2,diff3,diff4,diff5,
    diff6,diff7,diff8,diff9,diff10,
    pony,cross,hmk,west,south,ns,y2,jumble,windoe,
    dirty,clean,wet,dusty,complex,
    shell,arch,ragged,sac,ante,witt,
    bedquilt,cheese,soft,
    e2pit,w2pit,epit,wpit,
    narrow,giant,block,immense,
    falls,steep,abovep,sjunc,tite,low,crawl,window,
    oriental,misty,alcove,proom,droom,
    slab,abover,mirror,res,
    scan1,scan2,scan3,secret,
    wide,tight,tall,boulders,
    scorr,swside,
    dead0,dead1,dead2,dead3,dead4,dead5,dead6,
    dead7,dead8,dead9,dead10,dead11,
    neside,corr,fork,warm,view,chamber,lime,fbarr,barr,
    neend,swend,
    crack,neck,lose,cant,climb,check,snaked,
    thru,duck,sewer,upnout,didit,
    ppass,pdrop,troll}location;


typedef struct{
    motion mot;
    int cond;
    location dest;
}instruction;

hash_entry hash_table[hash_prime];
wordtype current_type;

char*default_msg[30];

char*message[13];

instruction travels[travel_size];
instruction*start[max_loc+2];
char*long_desc[max_loc+1];
char*short_desc[max_loc+1];
int flags[max_loc+1];
char*remarks[rem_size];
int rem_count;
int visits[max_loc+1];

char all_alike[]= "You are in a maze of twisty little passages, all alike.";
char dead_end[]= "Dead end.";
int slit_rmk,grate_rmk,bridge_rmk,loop_rmk;

object first[max_loc+1];
object link[max_obj+1];
object base[max_obj+2];
int prop[max_obj+1];
location place[max_obj+1];
char*name[max_obj+1];
char*note[100];
int offset[max_obj+1];
int holding;
int note_ptr= 0;

char buffer[buf_size];
char word1[buf_size],word2[buf_size];

location oldoldloc,oldloc,loc,newloc;

motion mot;
action verb;
action oldverb;
object obj;
object oldobj;
wordtype command_type;
int turns;

int west_count;

boolean was_dark;

int interval= 5;
char pitch_dark_msg[]=
        "It is now pitch dark.  If you proceed you will most likely fall into a pit.";

int tally= 15;
int lost_treasures;

boolean gave_up;

int limit;

char*incantation[]= {"fee","fie","foe","foo","fum"};
int foobar;

int look_count;

int rx;

int dflag;
int dkill;

location dloc[nd+1]= {chest_loc,hmk,wfiss,y2,like3,complex};
location odloc[nd+1];
boolean dseen[nd+1];

int dtotal;
int attack;
int stick;
location ploc[19];

int knife_loc;

char*attack_msg[]= {"it misses","it gets you",
                    "none of them hit you","one of them gets you"};

int clock1= 15,clock2= 30;
boolean panic,closed;

boolean warned;

int death_count;
char*death_wishes[2*max_deaths]= {
        "Oh dear, you seem to have gotten yourself killed.  I might be able to\n\
help you out, but I've never really done this before.  Do you want me\n\
to try to reincarnate you?",
        "All right.  But don't blame me if something goes wr......\n\
                 --- POOF!! ---\n\
You are engulfed in a cloud of orange smoke.  Coughing and gasping,\n\
you emerge from the smoke and find....",
        "You clumsy oaf, you've done it again!  I don't know how long I can\n\
keep this up.  Do you want me to try reincarnating you again?",
        "Okay, now where did I put my resurrection kit?....  >POOF!<\n\
Everything disappears in a dense cloud of orange smoke.",
        "Now you've really done it!  I'm out of orange smoke!  You don't expect\n\
me to do a decent reincarnation without any orange smoke, do you?",
        "Okay, if you're so smart, do it yourself!  I'm leaving!"};

int bonus;

int hint_count[n_hints];
int hint_thresh[n_hints]= {0,0,4,5,8,75,25,20};
int hint_cost[n_hints]= {5,10,2,2,2,4,5,3};
char*hint_prompt[n_hints]= {
        "Welcome to Adventure!!  Would you like instructions?",
        "Hmmm, this looks like a clue, which means it'll cost you 10 points to\n\
read it.  Should I go ahead and read it anyway?",
        "Are you trying to get into the cave?",
        "Are you trying to catch the bird?",
        "Are you trying to deal somehow with the snake?",
        "Do you need help getting out of the maze?",
        "Are you trying to explore beyond the Plover Room?",
        "Do you need help getting out of here?"};

char*hint[n_hints]= {
        "Somewhere nearby is Colossal Cave, where others have found fortunes in\n\
treasure and gold, though it is rumored that some who enter are never\n\
seen again.  Magic is said to work in the cave.  I will be your eyes\n\
and hands.  Direct me with commands of one or two words.  I should\n\
warn you that I look at only the first five letters of each word, so\n\
you'll have to enter \"NORTHEAST\" as \"NE\" to distinguish it from\n\
\"NORTH\".  Should you get stuck, type \"HELP\" for some general hints.\n\
For information on how to end your adventure, etc., type \"INFO\".\n\
                        -  -  -\n\
The first adventure program was developed by Willie Crowther.\n\
Most of the features of the current program were added by Don Woods;\n\
all of its bugs were added by Don Knuth & mostly Corey Adams.",
        "It says, \"There is something strange about this place, such that one\n\
of the words I've always known now has a new effect.\"",
        "The grate is very solid and has a hardened steel lock.  You cannot\n\
enter without a key, and there are no keys in sight.  I would recommend\n\
looking elsewhere for the keys.",
        "Something seems to be frightening the bird just now and you cannot\n\
catch it no matter what you try.  Perhaps you might try later.",
        "You can't kill the snake, or drive it away, or avoid it, or anything\n\
like that.  There is a way to get by, but you don't have the necessary\n\
resources right now.",
        "You can make the passages look less alike by dropping things.",
        "There is a way to explore that region without having to worry about\n\
falling into a pit.  None of the objects available is immediately\n\
useful for discovering the secret.",
        "Don't go west."};
boolean hinted[n_hints];


int class_score[]= {35,100,130,200,250,300,330,349,9999};
char*class_message[]= {
        "You are obviously a rank amateur.  Better luck next time.",
        "Your score qualifies you as a novice class adventurer.",
        "You have achieved the rating \"Experienced Adventurer\".",
        "You may now consider yourself a \"Seasoned Adventurer\".",
        "You have reached \"Junior Master\" status.",
        "Your score puts you in Master Adventurer Class C.",
        "Your score puts you in Master Adventurer Class B.",
        "Your score puts you in Master Adventurer Class A.",
        "All of Adventuredom gives tribute to you, Adventure Grandmaster!"};
#endif //ADVENT_GLOBALS_H
