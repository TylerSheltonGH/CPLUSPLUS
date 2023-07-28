#include "Collision.h"

bool Collision::CheckBox(CollisionData A, CollisionData B)
{
    if (A.position.x < B.position.x + B.size.x &&
        A.position.x + A.size.x > B.position.x&&
        A.position.y < B.position.y + B.size.y &&
        A.position.y + A.size.y > B.position.y) {
        return true;
    }

	return false;
}
