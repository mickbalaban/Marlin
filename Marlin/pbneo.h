#define SLEEP_ANIMATION 0
#define HEATING_ANIMATION 1
#define ACTIVE_ANIMATION 2
#define READY_ANIMATION 3
#define DANGER_ANIMATION 4
#define FILAMENTCHANGE_ANIMATION 5

void pbneo_update();
void pbneo_init();

void pbneo_set_animation(int anim);
int pbneo_get_animation();
