void initSupplyShip(void) {
    sEntity *e;
    SupplyShip *s = malloc(sizeof(SupplyShip));
    memset(s, 0, sizeof(SupplyShip));

    if (SupplyShipTexture == NULL) SupplyShipTexture = getAtlasImage("assets/supplyShip.png", 1); 

    e = spawnEntity(ET_SUPPLYSHIP);
    e->y = 50;
    e->health = 5;
    e->texture = supplyShipTexture;
    e->data = s;

    if (rand() % 2 == 0) {
        e->x = -supplyShipTexture->rect.w;
        s->dx = 3;
    } else {
        e->x = SCREEN_WIDTH;
        s->dx = -3;
    }


    e->tick = tick;
    e->draw = draw;
    e->takeDamage = takeDamage;
    e->die = die;
}


static void tick(sEntity *e) {
    SupplyShip *s = (SupplyShip *) self->data;
    
    self->x += (s->dx * app.deltaTime);

    if ((s->dx < 0 && self->x < -75) || (s->dx > 0 && self->x > SCREEN_WIDTH)) {
        self->health = 0;
    }

    s->damageTimer = fmax(s->damageTimer - app.deltaTime, 0);

    if (player->health > 0 && collision(self->x, self->y, self->texture->rect.w, self->texture->rect.h, player->x, player->y, player->texture->rect.w, player->texture->rect.h)) {

        self->health = 0;
        self->die(self);

        player->health = 0;
        player->die(player);
    }
}

static void die(sEntity *self) {
    
	
    // Add an explosion at the center of the player's ship

    addExplosion(self->x + (self->texture->rect.w / 2), self->y + (self->texture->rect.h / 2));


	// Add a power-up pod at the center of the asteroid
    addPowerUpPod(self->x + (self->texture->rect.w / 2), self->y + (self->texture->rect.h / 2));
}