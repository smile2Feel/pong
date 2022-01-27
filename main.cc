int main(void)
{
    GAME_STATE state = MENU;    // initial state is the game menu
    PongMenu menu;
    PongGame game;

    Time previousTime = GetCurrentTime();
    const float UPDATE_RATE = 33; // 33 milliseconds each update
    float lag = 0;
    
    while(state != EXIT)
    {
        Time currentTime = GetCurrentTime();
        float elapsedTime = currentTime - previousTime;
        previousTime = currentTime;
        
        lag += elapsedTime;

        while(lag >= UPDATE_RATE)
        {
            GAME_STATE newState = state;
            if(state == MENU)
                newState = menu.Update(UPDATE_RATE);
            else if(state == IN_GAME)
                newState = game.Update(UPDATE_RATE);

            if(newState != state)
            {
                state = newState;
                if(newState == IN_GAME)
                    game = new PongGame(2);
                
                break; // if the state changes, we don't want to update again
            }
            lag -= UPDATE_RATE;
        }

        if(state == MENU)
            menu.Render(elapsedTime);
        else if(state == IN_GAME)
            game.Render(elapsedTime);
        else if(state == EXIT)
            break;
    }
}