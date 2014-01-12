#include "global.h"
#include "collision.h"

// int isCollision(BoundingBox *b1, BoundingBox *b2)
// {

//     if (b1->x - b1->boundingBox.x < b2->x + b2->boundingBox.x &&
//             b1->boundingBox.x + b1->boundingBox.x > b2->x - b2->boundingBox.x &&
//             b1->y - b1->boundingBox.y < b2->y + b2->boundingBox.y &&
//             b1->y + b1->boundingBox.y > b2->y - b2->boundingBox.y)
//     {
//         return 1;
//     }
//     else if (b1->boundingBox.x < 0)
//     {
//         return 1;
//     }
//     return 0;
// }