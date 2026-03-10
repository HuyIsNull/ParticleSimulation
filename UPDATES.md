# Memory Fix 


Previously, I mentioned about the program's memory usage problem.
It was because of Grid. I realized that freed memory wouldn't return to the OS right away, but be kept by the program for future uses.
It's helpful when you allocate memory for every frame( If you idiotic enough to do that ), but at the same time, because of Grid memory hungry, the program's memory usage would increase.

Now instead of 2D array of std::vector, I used 1D array represent a 2D grid and sort it by grid index.
It would be a little bit slower, but the program's memory usage would be stable.
