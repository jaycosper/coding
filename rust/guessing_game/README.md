# Guessing Game in Rust
## Desciption
Simple number guessing game written in Rust
## Defines
## Types
## APIs
## Required Libraries
rand
## Tested Target
- x86
## Usage
```
// Build and run default (debug) app
$ cargo run
// Build and run release app
$ cargo run --release
// Build default app binary
$ cargo build
// Build (compile) default app without binary
$ cargo check
// Build and open default app documentation (located in ./target/doc/<app>/index.html)
$ cargo doc --open
```
## Details
### Sample Output
```
.../coding/rust/guessing_game$ cargo run
   Compiling guessing_game v0.1.0 (/rust/guessing_game)
    Finished dev [unoptimized + debuginfo] target(s) in 0.47s
     Running `target/debug/guessing_game`
Guess the number!
Please input your guess.
50
You guessed: 50
Too small!
Please input your guess.
75
You guessed: 75
Too big!
Please input your guess.
not-a-number
Please input your guess.
68
You guessed: 68
Too small!
Please input your guess.
69
You guessed: 69
Too small!
Please input your guess.
74
You guessed: 74
Too big!
Please input your guess.
73
You guessed: 73
You win!
```
## References
Online Rust tutorial
https://doc.rust-lang.org/book/2018-edition/ch02-00-guessing-game-tutorial.html
