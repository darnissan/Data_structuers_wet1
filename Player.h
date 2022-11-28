#ifndef PLAYER_H_
#define PLAYER_H_
#include <iostream>
#include "AvlTree.h"
#include "PlayerStats.h"
class Team;

class Player
{
protected:
    int playerId;
    int teamId;
    int gamesPlayed;
    int goals;
    int cards;
    bool goalKeeper;

    int gamesTeamPlayedBefore;
    AVLNode<PlayerStats> *pointerToPlayerStatsAvlNodeONAllPlayers=nullptr;
    AVLNode<Team> *pointerToTeamAvlNode;

    void DeletePlayer(Player *player);

public:
    // defualt constructor
    
    Player()
    {
        playerId = 0;
        teamId = 0;
        gamesPlayed = 0;
        goals = 0;
        cards = 0;
        goalKeeper = false;
        gamesTeamPlayedBefore = 0;
       
        pointerToTeamAvlNode = NULL;
        
    }
    ~Player()
    {
        if (pointerToPlayerStatsAvlNodeONAllPlayers != nullptr)
        {
            delete pointerToPlayerStatsAvlNodeONAllPlayers;
        }
    }
    
    Player(int playerId, int teamId) : playerId(playerId), teamId(teamId), gamesPlayed(0), goals(0), cards(0), goalKeeper(false)
    {
        // gamesTeamPlayedBefore =
        // closesetFromLeft =
        // closesetFromRight =
        // pointerToTeam =
    }
    Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper) : playerId(playerId), teamId(teamId), gamesPlayed(gamesPlayed),
                                                                                               goals(goals), cards(cards), goalKeeper(goalKeeper)
    {
        // gamesTeamPlayedBefore =
        // closesetFromLeft =
        // closesetFromRight =
        // pointerToTeam =
    }
    //get pointer to team
    AVLNode<Team> *getPointerToTeamAvlNode() const
    {
        return pointerToTeamAvlNode;
    }
    void setPointerToTeam(AVLNode<Team> *pointerToTeam)
    {
        this->pointerToTeamAvlNode = pointerToTeam;
    }
   
    bool isGoalKeeper() const
    {
        return goalKeeper;
    }
    int getPlayerId() const
    {
        return playerId;
    }
    // operator <
    bool operator<(const Player &player) const
    {
        if (playerId < player.playerId)
        {
            return true;
        }
        return false;
    }
    // operator >
    bool operator>(const Player &player) const
    {
        if (playerId > player.playerId)
        {
            return true;
        }
        return false;
    }
    // operator ==
    bool operator==(const Player &player) const
    {
        if (playerId == player.playerId)
        {
            return true;
        }
        return false;
    }
    // operator !=
    bool operator!=(const Player &player) const
    {
        if (playerId != player.playerId)
        {
            return true;
        }
    }
    // operator <<
    friend std::ostream &operator<<(std::ostream &os, const Player &player)
    {
        os << "playerId: " << player.playerId << " teamId: " << player.teamId << " gamesPlayed: " << player.gamesPlayed << " goals: " << player.goals << " cards: " << player.cards << " goalKeeper: " << player.goalKeeper << std::endl;
        return os;
    }
    void setpointerToPlayerStatsAvlNodeONAllPlayers(AVLNode<PlayerStats> *pointerToPlayerStatsAvlNodeONAllPlayers)
    {
        this->pointerToPlayerStatsAvlNodeONAllPlayers = pointerToPlayerStatsAvlNodeONAllPlayers;
    }
    
};




#endif // PLAYER_H_