

void doEntities(void) {
    sEntity *e, *prev;

    prev = &stage.entityHead;

    for (e = stage.entityHead.next; e!= NULL; e = e->next) {

        if (e->tick != NULL) e->tick(e);

        if (e->health <= 0) {
            if (e == stage.entityEnd) stage.entityEnd = prev;

            prev->next = e->next;

            
            deadEnd->next = e;
            deadEnd = e;
            deadEnd->next = Null;
            

            e = prev;
        }
        prev = e;   
    }
}


void clearEntities(void) {
    
    sEntity * e;

    while (stage.entityHead.next != NULL) {
        e = stage.entityHead.next;

        stage.entityHead.next = e->next;

        if (e->data != NULL) free(e->data);

        free(e);
    }

    stage.entityEnd = &stage.entityHead;    

}

void clearDeadEntities(void) {
     sEntity *e;

    while (deadHead.next) {
        e = deadHead.next;

        deadHead.next = e->next;

        if (e->data != NULL) free(e->data);

        free(e);
    }

    deadEnd = &deadHead;
}