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
