
/* structs.h will be used to represent almost any entity in the game: 

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
    void (*tick)(sEntity *self);
    void (*draw)(sEntity *self);
    void (*takeDamage)(sEntity *self, int amount);
    void (*die)(sEntity *self);
    sEntity *next;  
};

typedef struct {
    double reload;
    // how fast we can shoot
    int reloadRate;
    double speed;
    // will be used to invoke the sidearms when the player fires their guns.
    int invokeSidearm;
} Fighter;


typedef struct {
    int type;
    double changeTimer;
} PowerUpPod;


// This struct will be used to hold the information about our small yellow alien, who moves back and forth across the screen, as seen in the game and the screenshot above. We'll see more on how these aliens work in a little while. 

typedef struct {
    double swing, startDelay, reload, swingAmount;
    int sweepRange, dy;

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
    sBullet *next;
};


struct sStar {
    double x, y;
    double speed;
}

struct sExplosion {
    int x, y, frame, numFrames;
    double frameSpeed, frameTime;
    AtlasImage **texture;
    sExplosion *next;
}
 
typedef struct {
    sEntity entityHead, *entityEnd;
    sBullet bulletHead, *bulletEnd;
    int hasAliens, score, numWaveAliens;
} Stage;

typedef struct {
    double swoop, swoopAmount, startDelay,
    reload, dx, damageTimer;
} SwoopingAlien;


typedef struct {
    double startDelay, reload,
    dx, dy, damageTimer; 
} StraightAlien;


typedef struct {
    double dx, damageTimer;
} SupplyShip;

typedef struct {
    char name[MAX_NAME_lENGTH];
    int score;
} HighScore;

typedef struct {
    HighScore highScores[MAX_HIGH_SCORES];
} Game;

typedef struct {
    int maxHealth;
    double thinkTime, dx, reload, attackTime, numShootsToFire, timerDamage;
    void (*attack)(sEntity *self);
} Boss;

typedef struct {
    sEntity entityHead, *entityEnd;
    sBullet bulletHead, *bulletEnd;
    int hasAliens, score, numWaveAliens, waveNum;
    sEntity *boss;
}

