#include <stdio.h>
#include <math.h>

struct particle {
    float mass;
    float posX;
    float posY;
};

float distance(struct particle particle1, struct particle particle2) {
    float deltaX = particle1.posX - particle2.posX;
    float deltaY = particle1.posY - particle2.posY;
    float distance = sqrtf(deltaX * deltaX + deltaY * deltaY);

    return distance;
}

float force(struct particle particle1, struct particle particle2) {
    float dist = distance(particle1, particle2);
    float force = (particle1.mass * particle2.mass) / powf(dist, 2);

    return force;
}

int main() {
    struct particle particle1, particle2;

    scanf("%f %f %f", &(particle1.mass), &(particle1.posX), &(particle1.posY));
    scanf("%f %f %f", &(particle2.mass), &(particle2.posX), &(particle2.posY));

    printf("%.4f\n", force(particle1, particle2));

    return 0;
}
