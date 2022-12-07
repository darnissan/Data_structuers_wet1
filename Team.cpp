#include "Team.h"
  Team::Team()
    {
        this->id = 0;
        this->numOfPlayers = 0;
        this->numOfGoalKeepers = 0;
        this->points = 0;
        this->gamesTeamPlayed = 0;
        this->TotalGoalsScored = 0;
        this->TotalCards = 0;
    }
    Team::Team(int id, int points) : id(id), numOfPlayers(0), numOfGoalKeepers(0), points(points), gamesTeamPlayed(0), TotalGoalsScored(0), TotalCards(0)
    {
    }
    Team::~Team()
    {
    }
    void Team::setTeamID(int id)
    {
        this->id = id;
    }
    // assign operator
    Team &Team::operator=(const Team &other)
    {
        if (this != &other)
        {
            this->id = other.id;
            this->numOfPlayers = other.numOfPlayers;
            this->numOfGoalKeepers = other.numOfGoalKeepers;
            this->points = other.points;
            this->gamesTeamPlayed = other.gamesTeamPlayed;
            this->TotalGoalsScored = other.TotalGoalsScored;
            this->TotalCards = other.TotalCards;
            this->players.Clear();
            this->players.root = nullptr;

            this->players.root = copyTree(this->players.root, other.players.root);
            this->PlayersOnTeamOrderdByStats.Clear();
            this->PlayersOnTeamOrderdByStats.root = nullptr;
            this->PlayersOnTeamOrderdByStats.root = copyTree(this->PlayersOnTeamOrderdByStats.root, other.PlayersOnTeamOrderdByStats.root);
        }
        return *this;
    }
    // copy constructor
    Team::Team(const Team &other) : id(other.id), numOfPlayers(other.numOfPlayers), numOfGoalKeepers(other.numOfGoalKeepers),
                              points(other.points), gamesTeamPlayed(other.gamesTeamPlayed), TotalGoalsScored(other.TotalGoalsScored), TotalCards(other.TotalCards), players(other.players), PlayersOnTeamOrderdByStats(other.PlayersOnTeamOrderdByStats) {}
    // defult constructor

    // operator== for team
    bool Team::operator==(const Team &other) const
    {
        return (this->id == other.id);
    }
    // operator > for team
    bool Team::operator>(const Team &other) const
    {
        return (this->id > other.id);
    }
    // operator < for team
    bool Team::operator<(const Team &other) const
    {
        return (this->id < other.id);
    }
    void Team::setNumOfPlayers(int numOfPlayers)
    {
        this->numOfPlayers = numOfPlayers;
    }
    void Team::setNumOfGoalKeepers(int numOfGoalKeepers)
    {
        this->numOfGoalKeepers = numOfGoalKeepers;
    }
    void Team::setPoints(int points)
    {
        this->points = points;
    }
    void Team::setGamesTeamPlayed(int gamesTeamPlayed)
    {
        this->gamesTeamPlayed = gamesTeamPlayed;
    }
    void Team::setTotalGoalsScored(int TotalGoalsScored)
    {
        this->TotalGoalsScored = TotalGoalsScored;
    }
    void Team::setTotalCards(int TotalCards)
    {
        this->TotalCards = TotalCards;
    }

    void Team::setTeamTopScorerGoals(int teamTopScorerGoals)
    {
        this->teamTopScorerGoals = teamTopScorerGoals;
    }

    void Team::setTeamTopScorerId(int teamTopScorerId)
    {
        this->teamTopScorerId = teamTopScorerId;
    }

    void Team::setTeamTopScorerCards(int teamTopScorerCards)
    {
        this->teamTopScorerCards = teamTopScorerCards;
    }

    int Team::getId() const
    {
        return id;
    }
    int Team::getNumOfPlayers() const
    {
        return numOfPlayers;
    }
    int Team::getNumOfGoalKeepers() const
    {
        return numOfGoalKeepers;
    }
    int Team::getPoints() const
    {
        return points;
    }
    int Team::getGamesTeamPlayed() const
    {
        return gamesTeamPlayed;
    }
    int Team::getTotalGoalsScored() const
    {
        return TotalGoalsScored;
    }
    int Team::getTotalCards() const
    {
        return TotalCards;
    }

    int Team::getTeamTopScorerGoals()
    {
        return teamTopScorerGoals;
    }

    int Team::getTeamTopScorerId()
    {
        return teamTopScorerId;
    }

    int Team::getTeamTopScorerCards()
    {
        return teamTopScorerCards;
    }

    AVLNode<Player> *Team::InsertPlayerToTeam(const Player &playerToInsert)
    {
        players.root = players.Insert(players.GetRoot(), playerToInsert);
        numOfPlayers++;
        this->TotalCards += playerToInsert.getCards();
        this->TotalGoalsScored += playerToInsert.getGoals();
        if (playerToInsert.isGoalKeeper())
        {
            numOfGoalKeepers++;
        }
        //   std::cout<<"Player "<<playerToInsert.getPlayerId()<<" was added to team "<<id<<std::endl;
        //   players.PrintInOrder(players.GetRoot());

        return players.find(players.GetRoot(), playerToInsert);
    }
    AVLNode<PlayerStats> *Team::InsertPlayerToTeamStatsTree(const PlayerStats &playerToInsert)
    {
        PlayersOnTeamOrderdByStats.root = PlayersOnTeamOrderdByStats.Insert(PlayersOnTeamOrderdByStats.GetRoot(), playerToInsert); // o(logn)
        return PlayersOnTeamOrderdByStats.find(PlayersOnTeamOrderdByStats.GetRoot(), playerToInsert);                              // o(logn)
    }

    //<< operator for team
  
    
    void Team::RemovePlayerFromTeam(const Player &PlayerToRemove)
    {
        players.root = players.Remove(players.GetRoot(), PlayerToRemove);
        numOfPlayers--;
        this->TotalCards -= PlayerToRemove.getCards();
        this->TotalGoalsScored -= PlayerToRemove.getGoals();
        if (PlayerToRemove.isGoalKeeper())
        {
            numOfGoalKeepers--;
        }
        //   std::cout<<"Player "<<playerToInsert.getPlayerId()<<" was added to team "<<id<<std::endl;
        //   players.PrintInOrder(players.GetRoot());
    }
    void Team::removePlayerFromStatsTeam(const PlayerStats &playerToRemove)
    {
        PlayersOnTeamOrderdByStats.root = PlayersOnTeamOrderdByStats.Remove(PlayersOnTeamOrderdByStats.GetRoot(), playerToRemove); // o(logn)
    }

    AVLNode<Player> *Team::findPlayerById(AVLNode<Player> *node, int playerId)
    {
        if (node == NULL)
        {
            return nullptr;
        }
        if (node->GetValue().getPlayerId() == playerId)
        {
            return node;
        }
        if (node->GetValue().getPlayerId() > playerId)
        {
            return findPlayerById(node->GetLeft(), playerId);
        }
        else
        {
            return findPlayerById(node->GetRight(), playerId);
        }
    }