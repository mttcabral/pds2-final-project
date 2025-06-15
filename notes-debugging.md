# notes about SAT debugging

## summary :
SAT breaks completely when dealing with any rotated polygons
likely due to rotation code conflicting with anything that composes SAT
Maybe rotation as a whole is implemented wrong

### this branch contains important fixes to oversights, but the problem persists
- things such as logic errors due to copy/paste similar code over time
- some geometry errors such as calculating vectors wrong between two vertices

## guesses on what is wrong: 
##### (~) indicates it's likely to be fixed but still is not the answer, look again later
- polygon projection
- rotated points or vectors or normals being calculated wrong (~)
- floating point problems
- use of std::set causing missing axes or duplicated axes
- updating polygons/hitboxes positions inconsistencies
- order of declared vertices for polygon matter (~)
- idk, the hole could be even deeper

## other notes
#### found when testing
- rotating a rectangle completely broke the colision detection, no colision was ever occouring when it should
- rotating the player (regular octagon) also broke it, but not in the same way (it was just highly off)

- link explaining SAT colision detection:
- https://dyn4j.org/2010/01/sat/
### debugging leftovers, maybe useful later

``` 
..........polygon.......... (player when first declared in main)
vertices: count: 8
(226.131, 400) (218.478, 418.478) (200, 426.131) (181.522, 418.478) (173.869, 400) (181.522, 381.522) (200, 373.869) (218.478, 381.522) 
edgeVectors: 
(-18.4776, -7.65366) (-18.4776, 7.65366) (-7.65367, -18.4776) (-7.65367, 18.4776) (7.65366, 18.4776) (7.65367, -18.4776) (18.4776, -7.65366) (18.4776, 7.65369) 
edgeNormals: 
(-0.92388, 0.382683) (-0.92388, -0.382683) (-0.382684, 0.923879) (-0.382683, -0.92388) (0.382683, -0.92388) (0.382683, 0.92388) (0.92388, -0.382683) (0.92388, 0.382683) angle: 0

..........polygon.......... (test 50,300 obstacle when declared in main)
vertices: count: 4
(1025, 250) (975, 250) (975, 550) (1025, 550) 
edgeVectors: 
(-50, 0) (0, -300) (0, 300) (50, 0) 
edgeNormals: 
(-1, 0) (-0, -1) (-0, 1) (1, 0) angle: 0

..........polygon.......... (same obstacle rotated 45 degrees)
vertices: count: 4
(1123.74, 311.612) (1088.39, 276.256) (876.256, 488.388) (911.612, 523.744) 
edgeVectors: 
(-212.132, 212.132) (-35.3553, -35.3553) (35.3553, 35.3553) (212.132, -212.132) 
edgeNormals: 
(-0.707107, -0.707107) (-0.707107, 0.707107) (0.707107, -0.707107) (0.707107, 0.707107) angle: PI/4 made
```

##### important: overtime (game running), information on obstacle polygon in game
The supposed logic for movement of the obstacle is to move regularly to the left and purely in X coords

- this rectangle is rotated
its curious how the Y coordinates of vertices are changing when they shouldnt
```
..........polygon..........
vertices: count: 4
(964.645, 152.513) (929.289, 117.157) (717.157, 329.289) (752.513, 364.645) 
edgeVectors: 
(-212.132, 212.132) (-35.3553, -35.3553) (35.3553, 35.3553) (212.132, -212.132) 
edgeNormals: 
(-0.707107, -0.707107) (-0.707107, 0.707107) (0.707107, -0.707107) (0.707107, 0.707107) angle: 0

..........polygon..........
vertices: count: 4
(954.038, 141.906) (918.683, 106.551) (706.551, 318.683) (741.906, 354.038) 
edgeVectors: 
(-212.132, 212.132) (-35.3553, -35.3553) (35.3553, 35.3553) (212.132, -212.132) 
edgeNormals: 
(-0.707107, -0.707107) (-0.707107, 0.707107) (0.707107, -0.707107) (0.707107, 0.707107) angle: 0

..........polygon..........
vertices: count: 4
(954.038, 141.906) (918.683, 106.551) (706.551, 318.683) (741.906, 354.038) 
edgeVectors: 
(-212.132, 212.132) (-35.3553, -35.3553) (35.3553, 35.3553) (212.132, -212.132) 
edgeNormals: 
(-0.707107, -0.707107) (-0.707107, 0.707107) (0.707107, -0.707107) (0.707107, 0.707107) angle: 0

..........polygon..........
vertices: count: 4
(943.431, 131.299) (908.076, 95.9441) (695.944, 308.076) (731.299, 343.431) 
edgeVectors: 
(-212.132, 212.132) (-35.3553, -35.3553) (35.3553, 35.3553) (212.132, -212.132) 
edgeNormals: 
(-0.707107, -0.707107) (-0.707107, 0.707107) (0.707107, -0.707107) (0.707107, 0.707107) angle: 0

..........polygon..........
vertices: count: 4
(932.825, 120.693) (897.47, 85.3375) (685.338, 297.47) (720.693, 332.825) 
edgeVectors: 
(-212.132, 212.132) (-35.3553, -35.3553) (35.3553, 35.3553) (212.132, -212.132) 
edgeNormals: 
(-0.707107, -0.707107) (-0.707107, 0.707107) (0.707107, -0.707107) (0.707107, 0.707107) angle: 0

..........polygon..........
vertices: count: 4
(922.218, 110.086) (886.863, 74.7309) (674.731, 286.863) (710.086, 322.218) 
edgeVectors: 
(-212.132, 212.132) (-35.3553, -35.3553) (35.3553, 35.3553) (212.132, -212.132) 
edgeNormals: 
(-0.707107, -0.707107) (-0.707107, 0.707107) (0.707107, -0.707107) (0.707107, 0.707107) angle: 0

..........polygon..........
vertices: count: 4
(911.612, 99.4796) (876.256, 64.1243) (664.124, 276.256) (699.48, 311.612) 
edgeVectors: 
(-212.132, 212.132) (-35.3553, -35.3553) (35.3553, 35.3553) (212.132, -212.132) 
edgeNormals: 
(-0.707107, -0.707107) (-0.707107, 0.707107) (0.707107, -0.707107) (0.707107, 0.707107) angle: 0

..........polygon..........
vertices: count: 4
(901.005, 88.873) (865.65, 53.5177) (653.518, 265.65) (688.873, 301.005) 
edgeVectors: 
(-212.132, 212.132) (-35.3553, -35.3553) (35.3553, 35.3553) (212.132, -212.132) 
edgeNormals: 
(-0.707107, -0.707107) (-0.707107, 0.707107) (0.707107, -0.707107) (0.707107, 0.707107) angle: 0

```

- this rectangle is NOT rotated
note how Y coordinates are not changing this time, only X coords like it is intended
```
..........polygon..........
vertices: count: 4
(995, 250) (945, 250) (945, 550) (995, 550) 
edgeVectors: 
(-50, 0) (0, -300) (0, 300) (50, 0) 
edgeNormals: 
(-1, 0) (-0, -1) (-0, 1) (1, 0) angle: 0

..........polygon..........
vertices: count: 4
(980, 250) (930, 250) (930, 550) (980, 550) 
edgeVectors: 
(-50, 0) (0, -300) (0, 300) (50, 0) 
edgeNormals: 
(-1, 0) (-0, -1) (-0, 1) (1, 0) angle: 0

..........polygon..........
vertices: count: 4
(965, 250) (915, 250) (915, 550) (965, 550) 
edgeVectors: 
(-50, 0) (0, -300) (0, 300) (50, 0) 
edgeNormals: 
(-1, 0) (-0, -1) (-0, 1) (1, 0) angle: 0

..........polygon..........
vertices: count: 4
(950, 250) (900, 250) (900, 550) (950, 550) 
edgeVectors: 
(-50, 0) (0, -300) (0, 300) (50, 0) 
edgeNormals: 
(-1, 0) (-0, -1) (-0, 1) (1, 0) angle: 0

..........polygon..........
vertices: count: 4
(935, 250) (885, 250) (885, 550) (935, 550) 
edgeVectors: 
(-50, 0) (0, -300) (0, 300) (50, 0) 
edgeNormals: 
(-1, 0) (-0, -1) (-0, 1) (1, 0) angle: 0

..........polygon..........
vertices: count: 4
(920, 250) (870, 250) (870, 550) (920, 550) 
edgeVectors: 
(-50, 0) (0, -300) (0, 300) (50, 0) 
edgeNormals: 
(-1, 0) (-0, -1) (-0, 1) (1, 0) angle: 0

..........polygon..........
vertices: count: 4
(905, 250) (855, 250) (855, 550) (905, 550) 
edgeVectors: 
(-50, 0) (0, -300) (0, 300) (50, 0) 
edgeNormals: 
(-1, 0) (-0, -1) (-0, 1) (1, 0) angle: 0

..........polygon..........
vertices: count: 4
(890, 250) (840, 250) (840, 550) (890, 550) 
```


```


```