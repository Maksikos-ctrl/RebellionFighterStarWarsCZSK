
/* will be used to represent almost any entity in the game: 

   texture == image 

   dx, dy(delta) = which will be used to determine the direction they are moving.


 */

struct sEntity {
    double x, y;
    AtlasImage *texture;
    void (*data);
    Entity *next;
};

typedef struct {
    double reload;
    // how fast we can shoot
    int reloadRate;
    double speed;
} Fighter;


struct sBullet {
    double x, y;
    double dx, dy;
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
} Stage;