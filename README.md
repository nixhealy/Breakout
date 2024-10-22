# Breakout

W Kavanagh. June Summer 2024

## controls

Use mouse to move the paddle right and left.
P to pause.

## Powerups

big/small paddle (blue)
fast/slow ball (fancy yellow)
fire ball (green)

# Tasklist

## Suggested fixes

* Fix the compiler issues in the code (done!)

## Suggested tasks

* Implement mouse input for pad (done!)
* Improved VFX (ball trail, paddle hit response, brick particle destruction [done!])
* Better UI (progress bar rather than timer for countdown) (done!)
* GameLoop (done!)
* Better ball physics (Box2D)
* Leaderboards
* More ball types (e.g., multiball, sticky ball [where you shoot the ball from the paddle every time], tiny ball, big ball, brick-tracking ball)
* Sounds with increasing tone between bounces. (done!)
* Implement commentary with calls to an LLM such as LLama

# Time Details and Changelist
- Added mouse control (Time: Like an hour, but now I know what I'm doing, probably.)
  - Made velocity non-linear (Time: Fifteen minutes)
- Added a timer bar (Time: I got distracted. This actually took like twenty minutes.)
- Particle effects! (Time: This took like two hours because it kept breaking.)
- Reset game after dying/finishing (Time: Thirty minutes)
- Sound effects (Time: Another hour. Albeit, most of that was trying to find a good way to get isolated piano notes.)