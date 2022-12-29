

void doEntities() {
    Entity *e, *prev;

    prev = &stage.entityHead;

    for (e = stage.entityHead.next; e!= NULL; e = e->next) {

        if (e->tick != NULL) e->tick(e);

        if (e->health <= 0) {
            if (e == stage.entityEnd) stage.entityEnd = prev;

            prev->next = e->next;

            if (e->data != NULL) free(e->data);

            free(e);

            e = prev;
        }
        prev = e;   
    }
}