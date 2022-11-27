#ifndef TEAMANDPLAYER_H_
#define TEAMANDPLAYER_H_
#include <iostream>

#include "AvlTree.h"

class Player;
class Team
{
private:
    int id;
    int numOfPlayers = 0;
    int numOfGoalKeepers = 0;
    int points = 0;
    int gamesTeamPlayed = 0;
    int TotalGoalsScored = 0;
    int TotalCards = 0;
    AvlTree<Player> players;
    
public:
    Team()
    {
        this->id = 0;
        this->numOfPlayers = 0;
        this->numOfGoalKeepers = 0;
        this->points = 0;
        this->gamesTeamPlayed = 0;
        this->TotalGoalsScored = 0;
        this->TotalCards = 0;
    }
    Team(int id, int points) : id(id), numOfPlayers(0), numOfGoalKeepers(0), points(points), gamesTeamPlayed(0), TotalGoalsScored(0), TotalCards(0)
    {
        
    }
    ~Team()
    {
        
    }
    // assign operator
    Team &operator=(const Team &other)
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
            this->players = other.players;
        }
        return *this;
    }
    // copy constructor
    Team(const Team &other) : id(other.id), numOfPlayers(other.numOfPlayers), numOfGoalKeepers(other.numOfGoalKeepers),
                              points(other.points), gamesTeamPlayed(other.gamesTeamPlayed), TotalGoalsScored(other.TotalGoalsScored), TotalCards(other.TotalCards), players(other.players) {}
    // defult constructor

    // operator== for team
    bool operator==(const Team &other) const
    {
        return (this->id == other.id);
    }
    // operator > for team
    bool operator>(const Team &other) const
    {
        return (this->id > other.id);
    }
    // operator < for team
    bool operator<(const Team &other) const
    {
        return (this->id < other.id);
    }
    int getId() const
    {
        return id;
    }
    int getNumOfPlayers() const
    {
        return numOfPlayers;
    }
    int getNumOfGoalKeepers() const
    {
        return numOfGoalKeepers;
    }
    int getPoints() const
    {
        return points;
    }
    int getGamesTeamPlayed() const
    {
        return gamesTeamPlayed;
    }
    int getTotalGoalsScored() const
    {
        return TotalGoalsScored;
    }
    int getTotalCards() const
    {
        return TotalCards;
    }

    //<< operator for team
    friend std::ostream &operator<<(std::ostream &os, const Team &team)
    {
        os << team.id << " " << team.numOfPlayers << " " << team.numOfGoalKeepers << " " << team.points << " " << team.gamesTeamPlayed << " " << team.TotalGoalsScored << " " << team.TotalCards;
        return os;
    }
};
class Player
{
private:
    int id;
    bool isGoalKeeper;
    int goalsScored;
    int gamesPlayed;
    int gamesTeamPlayedBefore;
    int cards;
    Player *closesetFromLeft;
    Player *closesetFromRight;
    Team *pointerToTeam;
};
#endif // TEAMANDPLAYER_H_