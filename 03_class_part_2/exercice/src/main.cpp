#include <cstdio>
#include <cstring>

//- Create 5 classes `Size2D`, `Position2D`, `Entity`, `Player`, `Enemy`.
//- All classes should have their members private.
//- `Size2D` should have a `width` and a `height` as `int`.
//- `Position2D` should have a `x` and a `y` as `int`.
//- An entity should have a life, a size and a position. (Note: The position corresponds to the
// center of the entity).
//- Both `Player` and `Enemy` should inherit from `Entity`.
//- When an entity is created it should call the method `initialLife()` to set its life.
//- A player has an initial life of `3`, and an enemy has `10`.
//- Both classes are able to move its position by a (x, y) translation.
//- A player has an hitbox being 2 times smaller than its size.
//- An enemy has an hitbox being identical to its size.
//- Add a `isHit` method that takes as input a position and should tell whether an entity was hit or
// not.

int main()
{
	// Enemy enemy(Size2D {5, 5}, Position2D {0, 0});

	// Player player(Size2D {4, 4}, Position2D {5, 5});

	// if (player.isHit(
	// 		Position2D {
	// 			4,
	// 			4,
	// 		})) {
	// 	printf("Player was hit at position (4, 6)\n");
	// }

	// player.move(3, 7);

	// enemy.move(-2, 3);

	// player.resetLife();

	// enemy.resetLife();

	return 0;
}
