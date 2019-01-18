# SpaceStationRescue

#Workers
* Wandering.
* Boundary collision.
* Collision with Player.
* Collision with Sweepers.

#Alien nests
* Spawn one Predator each.
* 3 nests total.
* Health of 10.
* Health bar UI on screen.
* Shoot heat seeking missiles.
* Spawn randomly in maze every game.

  #Missiles
  * Follows player position.
  * Fires when player is in range.
  * Same speed as player.
  
#Predator ships
* Path finding to player.
* Fires missiles.
* Same speed as player.
* Highlights path finding on tile map.

#Sweeper bots
* Wanders from the offset.
  * Seeks workers in range.
    * Flees from the player.
* All primary functions work in harmony.
* Has one life.
* Collides with player bullet.
* Collides with workers.
* Contains a count of workers collected.

#Power Ups
* Sheild that protects player for 15 seconds.
* Speed up for 15 seconds.
* Both indicate their use on screen.
* One use each.
* When used their prompt disappers.


#Radar
* Presents constantly in the bottom left corner.
* Shows a wider view of the game world to give more vision to the player.
* Everything can be seen on the minimap.

#Player
* Has keyboard controls (arrow keys).
* Has acceleration and deceleration.
* Has max speed.
* Shoots a laser in straight lines.
* Laser collides with nests and sweepers
* Collides with workers.
* Has 4 health.
* Health represented by in game UI.
* Contains power ups.

#Game World
* Tile map.
* Flow field.
* vectorfield.
* On screen UI.
* Maze blocks and regular blocks.

#Other#
* Environment variable.
* Doxygen.
* End game sates.
