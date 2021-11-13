#include "View.hpp"

const string CLOVER_CODE = "\xE2\x99\xA3";
const string HEART_CODE = "\xE2\x99\xA5";
const string SPADE_CODE = "\xE2\x99\xA0";
const string DIAMOND_CODE = "\xE2\x99\xA6";

View::View(Game *model) 
{
    this->model = model;
}

View::View() {}

View::~View() {}

string View::getResponse(string str)
{
    display(str, FG_GREEN);
    string response;
    getline(cin, response);
    return response;
}

void View::displayPlayers() const
{
    View::display("Liste des joueurs : ", FG_GREEN, false);
    for(Player *player : model->getPlayers())
        View::display(player->getName() + " ", FG_GREEN, false);
    View::display("");
}

void View::displayBoard() const
{
    if(model->getDeck()->getBoard().size() > 0 && model->getSeeBoard() != SEE_NOTHING)
    {
        View::display("Contenu du terrain : ", FG_BLUE);
        if(model->getSeeBoard() == SEE_ALL)
        {
            for(Card *card: model->getDeck()->getBoard()){
                View::displayCard(card);
            }
        }else if(model->getSeeBoard() == SEE_LAST){
            View::displayCard(model->getDeck()->getBoard().back());
        }
        View::display();
    }
}

void View::displayPlayersCards() const
{
    View::display("Carte des joueurs : ", FG_BLUE);
    for(Player *player : model->getPlayers()){
        if(model->getSeeOwn() == SEE_ALL){
            View::display(player->getName() + ": ", FG_GREEN);
            int index = 0;
            for(Card * card : player->getCards()){
                index++;
                int help = model->isPlayable(card) ? FG_YELLOW : FG_BLUE;
                View::display(to_string(index) + " - ", help, false);
                View::displayCard(card);
            }
        }else{
            View::display(player->getName() + ": " + to_string(player->getCards().size()), FG_GREEN, false);
        }
        View::display("");
    }
    View::display("");
}

void View::displayScore() const
{
    if(dynamic_cast<Score *>(model) != nullptr)
    {
        Score *score = dynamic_cast<Score *>(model);
        if (score->getPoints().size() != model->getPlayers().size()) return;

        display("Score final :", FG_GREEN);

        int index = 0;
        for (Player *player : model->getPlayers())
        {
            View::display(player->getName() +" "+to_string(score->getPoints()[index]), FG_BLUE);
            index++;
        }
    }
}

void View::display(string str, int code, bool br)
{
    cout << "\033[" << code << "m" << str << "\033[" << FG_DEFAULT << "m";
    if (br) cout << endl;
}

void View::displayCard(Card * card)
{

    if(card->getType() == UNO) return View::displayCardUno(card);

    string value = getCardValue(card);
    int style = card->getColor() == HEART || card->getColor() == SPADE ? FG_RED : FG_DEFAULT;

    display("["+ value + getCardColor(card) + "] ", style, false);

    if(card->getHint() != -1){
        display("[" + getCardColor(card, false) + "] ", FG_DEFAULT, false);
    }
}

void View::displayCardUno(Card * card)
{
    cout << "[";
    if(card->getValue() >= 0 && card->getValue() <= 9){
        cout << card->getValue();
    } else if(card->getValue() == PlusDeux){
        cout << "+2";
    } else if(card->getValue() == PlusQuatre){
        cout << "+4";
    } else if(card->getValue() == Joker){
        cout << "Joker";
    } else if(card->getValue() == PasseTonTour){
        cout << "Passe ton tour";
    } else if(card->getValue() == InversementDeSens){
        cout << "Inversement de sens";
    }

    if(!(card->getValue() == Joker && card->getColor() == -1) && card->getValue() != PlusQuatre){
        cout << ", ";
        if(card->getColor() == Bleu){
            cout << "Bleu";
        } else if(card->getColor() == Rouge) {
            cout << "Rouge";
        } else if(card->getColor() == Jaune) {
            cout << "Jaune";
        } else if(card->getColor() == Vert) {
            cout << "Vert";
        } else {
            cout << "Joker";
        }
    }
    cout << "] ";
    if(card->getHint() != -1){
        display("[" + getCardColor(card, false) + "] ", FG_DEFAULT, false);
    }
}

string View::getCardValue(Card * card)
{
    switch (card->getValue()) {
        case Valet: return "V";
        case Dame: return "D";
        case Roi: return "R";
        case As: return "A";
        case Joker: return "J";
        default: return to_string(card->getValue());
    }
}

string View::getCardColor(Card * card, bool colorOrHint)
{
    int field = colorOrHint ? card->getColor() : card->getHint();
    if(card->getType() == UNO){
        switch (field) {
            case Vert: return "G";
            case Rouge: return "R";
            case Bleu: return "B";
            case Jaune: return "Y";
            default: return to_string(card->getColor());
        }
    }else{
        switch (field) {
            case CLOVER: return CLOVER_CODE;
            case HEART: return HEART_CODE;
            case DIAMOND: return DIAMOND_CODE;
            case SPADE: return SPADE_CODE;
            default: return to_string(card->getColor());
        }
    }
}

