#ifndef TEAMANDPLAYER_H_
#define TEAMANDPLAYER_H_
#include <iostream>
#include "Player.h"
#include "AvlTree.h"
class Team;



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
   
    
public:
    AvlTree<Player> players;
    AvlTree<PlayerStats> PlayersOnTeamOrderdByStats;
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
    void setGamesTeamPlayed(int gamesTeamPlayed)
    {
        this->gamesTeamPlayed = gamesTeamPlayed;
    }
    AVLNode<Player> *InsertPlayerToTeam( const Player &playerToInsert) 
    {
        players.root = players.Insert(players.GetRoot(), playerToInsert);
        numOfPlayers++;
        if (playerToInsert.isGoalKeeper())
        {
            numOfGoalKeepers++;
        }
        std::cout<<"Player "<<playerToInsert.getPlayerId()<<" was added to team "<<id<<std::endl;
        players.PrintInOrder(players.GetRoot());


        return players.find(players.GetRoot(), playerToInsert);
    }
    AVLNode<PlayerStats> *InsertPlayerToTeamStatsTree(const PlayerStats &playerToInsert)
    {
        PlayersOnTeamOrderdByStats.root = PlayersOnTeamOrderdByStats.Insert(PlayersOnTeamOrderdByStats.GetRoot(), playerToInsert);//o(logn)
        return PlayersOnTeamOrderdByStats.find(PlayersOnTeamOrderdByStats.GetRoot(), playerToInsert);//o(logn)
    }

    //<< operator for team
    friend std::ostream &operator<<(std::ostream &os, const Team &team)
    {
        os <<"team id" << team.id << " " << team.numOfPlayers << " " << team.numOfGoalKeepers << " " << "points:"<< team.points << " " << team.gamesTeamPlayed << " " << team.TotalGoalsScored << " " << team.TotalCards<<"---"<<std::endl;
        return os;
    }

    

   

    AVLNode<Player> *findPlayerById(AVLNode<Player> *node, int playerId)
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
};

#endif // TEAMANDPLAYER_H_