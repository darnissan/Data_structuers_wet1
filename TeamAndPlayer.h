#ifndef TEAMANDPLAYER_H_
#define TEAMANDPLAYER_H_
#include <iostream>

#include "AvlTree.h"

class Player;
class Team
{
private:
    int id;
    int numOfPlayers;
    int numOfGoalKeepers;
    int points;
    int gamesTeamPlayed;
    int TotalGoalsScored;
    int TotalCards;
    AvlTree<Player> *players;

public:
    Team(int id, int points) : id(id), points(points), numOfPlayers(0), numOfGoalKeepers(0), gamesTeamPlayed(0), TotalGoalsScored(0), TotalCards(0)
    {
        players = new AvlTree<Player>();
    }
    ~Team()
    {
        delete players;
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
    Team() : id(0), numOfPlayers(0), numOfGoalKeepers(0), points(0), gamesTeamPlayed(0), TotalGoalsScored(0), TotalCards(0)
    {
        players = new AvlTree<Player>();
    }
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
    AvlTree<Player> *getPlayers() const
    {
        return players;
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