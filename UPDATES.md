# More configurations


After referred to other projects, I noticed a lot of interesting interactions between particles that i have never seen in my simulation.
It might be because i don't configure "interactions" properly, but that is for this update.

> [!IMPORTANT]
> Config format has changed. Either remove old config file or change its format.


## Added

- [ ] Configs:
    - [ ] `sizes`: World sizes. If `Fullscreen` is `true`, it will be ignored.
    - [ ] `background`: Background color.
    - [ ] `damping`: Velocity reduction, this helps slow down particles over time.
    - [ ] `gravity`: Basically `interactions` but affect all particles.
    - [ ] `affectRange`: The ranges of interaction between particles.


## Changed

- [ ] Config format.
- [ ] Minor performance boost.
