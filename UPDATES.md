# Performance Improvements.


## Added


* **Grid data structure( Spatial Hashing )**: Which is basically 2d dynamic array.
By separating regions of particles, this helped decrease numbers of check on particles that are too far away.
You may ask why i don't use quadtree, well, my pea brain is not that smart.

    * **The Downsides**: With only 5000 particles and 350 std::vectors on my fullscreen, the program memory usage can go up to 500MB, which to me, is really bad. 

<br>

* **Configuration**: You can now add other particle types and change the number of particles in config.json file.

> [!WARNING]
> There are no safe format checks for config.json, so if something goes wrong, the program will crash.


## Changed

* Overengineered hin::Vector. 
