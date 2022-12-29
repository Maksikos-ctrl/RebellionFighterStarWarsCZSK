
/* will be used to represent almost any entity in the game: 

   texture == image 

   dx, dy(delta) = which will be used to determine the direction they are moving.

  tick will be called each frame to handle things like movement, timeouts,

  die will be called when an entity is killed (almost exclusively after being struck by a bullet). 

  ?You can't use typedef to create a new type with the same name as an existing type, even if the underlying type is different.

 */

struct sEntity {
    int type;
    double x, y;
    AtlasImage *texture;
    int health;
    // a pointer to a function with no return type and no arguments, representing additional data associated with the entity
    void (*data);
    // tick: a pointer to a function with no return type and a single Entity pointer argument, representing a function that is called every frame to update the entity
    void (*tick)(Entity *self);
    void (*die)(Entity *self);
    Entity *next;
};

typedef struct {
    double reload;
    // how fast we can shoot
    int reloadRate;
    double speed;
} Fighter;

// This struct will be used to hold the information about our small yellow alien, who moves back and forth across the screen, as seen in the game and the screenshot above. We'll see more on how these aliens work in a little while. 

typedef struct {
    double swing, startDelay;

} SwingingAlien;


// struct which handles our points pickup, named PointsPod: 
typedef struct {
    double dx, dy;
    double timeout;
} PointsPod;


struct sBullet {
    double x, y;
    double dx, dy;
    int dead;
    AtlasImage *texture;
    Entity *host;
    Bullet *next;
};


struct sStar {
    double x, y;
    double speed;
}

typedef struct {
    Entity entityHead, *entityEnd;
    Bullet bulletHead, *bulletEnd;
    int hasAliens, score, highscore;
} Stage;