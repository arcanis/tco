# Tail Call Optimizations in C++

## Or: when `std::function` works against you

I'm currently working on a little card game, and wanted to write a C++ library to be able to run automated games and build stats about what works and what doesn't. Because an imperative is that this library can be compiled to asm.js, I needed the API to be asynchronous as much as possible - Emscripten doesn't let you pause in the middle of the execution, unless you use the embedded interpreter, which wouldn't benefits from the asm.js optimizations.

My first train of thought was to build an API similar to this one:

```c++
struct Game {

    using ActionCallbackCallback = std::function<void (void)>;
    using ActionCallback = std::function<void (ActionCallbackCallback const &, Game const &, Action const & action)>;
    void setActionCallback(ActionCallback const & callback);

    using PlayerCallbackCallback = std::function<void (ActionList const &)>;
    using PlayerCallback = std::function<void (PlayerCallbackCallback const &, Game const &, Player::Id playerId>;
    void setPlayerCallback(PlayerCallback const & callback);

};
```

Basically, the library would provide two hooks that the userland code could attach to: the "Action Callback" would get executed everytime the game environment would change (when a card is drawn, played, etc), and would only be useful to notify the client of what happens in real time (for example to allow for asynchronous animations, etc). Then, once in a while, the "Player Callback" would get called, and the userland code would be able to send back the actions that need to be executed via an "action list". The code that would call the code above was similar to what you can find below:

```c++
void Game::run(State state = State::UPKEEP_STEP)
{
    switch (state)
    {
        case State::UPKEEP_STEP: {

            auto actions = actions::makeCardDraw(*this);

            m_actionCallback([=](void) {
                this->applyActions(actions);
                this->run(MAIN_STEP);
            }, *this, actions);

        } break;

        case State::MAIN_STEP: {

            m_playerCallback([=](ActionList const & actions) {
                this->applyActions(actions);
                this->run(END_STEP);
            });

        } break;

        // ... etc
    }
}
```

But once this code was written, something suddenly appeared to me: we're calling `run`, which in turn calls `m_actionCallback`, which in turns call `run`, which in turn calls `m_playerCallback`, which in turn calls `run`, etc, until the game ends or crash. And it would be a bit problematic for the game to crash, right? Especially if multiple games are hosted in the same process! Thankfully it's not *that* bad, because it would ask for a lot of recursion and any reasonable game would probably be over by then. But still. I don't like the word "probably", especially when there is so many ways for the players to affect the outcome.

Then I remembered something: tail call optimization. The optimization that kicks in when a function does nothing with its last function call, and return immediately after. In such a case, the compilers can drop the current function stack frame immediately *before* returning instead of after, which means that the stack will never grow out of measure. That's it! I'm saved!

Except that I wasn't. The first time I ran my program, everything worked as expected, including the stack overflow. Needless to say, I was pretty bummed. What happened? Maybe GCC didn't support tail call optimizations, after all...

And that's how my quest began. I really like.
