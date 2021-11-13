#include "Controller.hpp"

/**
 * Entry point of the app
 */
void Controller::start() 
{
    View::display("Welcome!", FG_BLUE);
    const string type = chooseGame();

    if(type.compare("1") == 0){
        model = new Bataille();
    }else if(type.compare("2") == 0){
       model = new Uno();
    }else if(type.compare("3") == 0){
       model = new Scopa();
    }else if(type.compare("4") == 0){
        model = new Briscola();
    }else if(type.compare("5") == 0){
        model = new CrazyEights();
    }else if(type.compare("exit") == 0){
        View::display("Bye!", FG_BLUE);
        exit(EXIT_SUCCESS);
    }else{
        View::display("Mauvaise entrée !", FG_RED);
        start();
        return;
    }

    view = View(model);
    model->setPlayers(createPlayers());

    view.display(model->getName() + " commencée :", FG_BLUE);
    view.displayPlayers();

    model->start();

    while (model->canContinue())
    {
        string name = model->turnOf()->getName();

        for(string s : model->messages(startOfTurn))//Display start of turn message
                View::display(s);

        //Check for playable cards
        if(!model->hasPlayable()){
            View::display(name + " n'a pas de carte jouable", FG_RED);
            model->draw();
            if(!model->hasPlayable()){
                View::display(name + " n'a toujours pas de carte jouable, il passe son tour", FG_RED);
                model->nextTurn();
            }        
        } else {

            view.displayPlayersCards();
            view.display("C'est le tour de : " + name, FG_YELLOW);
            view.displayBoard();

            Card *card = nullptr;
            vector<int> inputs;

            //if the current player isn't a robot, get necessary inputs
            if(!model->turnOf()->isRobot())
            {
                int step = 0;
                while(step != -1)
                {
                    for(string s : model->messages(step))
                        View::display(s);

                    int input = validateInput();
                    bool takeInput = false;
                    int newStep = model->InputMessages(step,input,&takeInput);
                    if(newStep == step)
                        View::display("Choix invalide !");
                    else
                        step = newStep;
                    if(takeInput)
                        inputs.push_back(input);
                }
            } else {//get the inputs from the model otherwise
                inputs = model->automatic();
            }

            card = model->turnOf()->getCards()[inputs[0]];

            View::display(name + " a choisi : ", FG_GREEN, false);
            View::displayCard(card);
            View::display();

            //Check if the card chosen is playable
            if(model->isPlayable(card)){
                model->iterate({inputs});
                View::display();
            }else{
                View::display("Cette carte n'est pas jouable !", FG_RED);
            }

            for(string s : model->messages(endOfTurn))//Display start of turn message
                View::display(s);
        }
    }

    view.displayScore();

    //Check if the game is over
    if (model->checkForWinners() != nullptr)
        View::display(model->checkForWinners()->getName() + " remporte la victoire !", FG_GREEN);
    else
        View::display("Egalité, pas de gagnants", FG_RED);

    //delete clone to keep Scopa compatible
    model->clean();
    model = 0;    
}

/**
 * Choose which game to play
 */
string Controller::chooseGame() 
{
    vector<string> games = {"1 - Bataille ", "2 - Uno ", "3 - Scopa", "4 - Briscola", "5 - Crazy Eights"};
    for(string game : games) View::display(game, FG_GREEN);
    return View::getResponse("Choisissez un jeu :");
}

/**
 * CLI: create players linked with min & max of the game
 */
vector<Player *> Controller::createPlayers()
{
    vector<Player *> players;
    while ((int)players.size() != model->getMax())
    {
        string index = to_string(players.size() + 1);
        string input = View::getResponse("Entrez le nom du joueur" + index+ ":\nEntrez 'robot' pour ajouter une IA.");

        //Check if the player added is a bot
        if(input.length() > 0){
            bool isRobot = input.compare("robot") == 0;
            string name = isRobot ? input + index : input;
            Player *player = new Player(name);
            player->setRobot(isRobot);
            players.push_back(player);

        } else if(model->getMin() <= (int)players.size() && input.length() == 0){
            return players;
        }
    }
    return players;
}

/**
 * Validation of the user input when choose a card to play
 */
int Controller::validateInput() const 
{
    int integer = -1;
    while (!(0 < integer && (integer < (int)model->turnOf()->getCards().size() + 1 || integer < (int)model->getDeck()->getBoard().size() + 1)))
    {
        string s = View::getResponse();
        stringstream input(s);
        input >> integer;
    }
    return integer-1;
}