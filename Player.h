#ifndef PLAYER_H_
#define PLAYER_H_
#include <iostream>

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
    AVLNode<PlayerStats> *pointerToPlayerStatsAvlNodeONAllPlayers = nullptr;
    AVLNode<Team> *pointerToTeamAvlNode = nullptr;
    AVLNode<PlayerStats> *pointerToPlayerStatsAvlNodeONTeam = nullptr;
    AVLNode<Player> *pointerToAllPlayerAvlNode = nullptr;
    void DeletePlayer(Player *player);

public:
    // defualt constructor

    Player();
    //~Player()
    //{
    //}

    Player(int playerId, int teamId);
    
    Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper);
    // get pointer to team
    AVLNode<Team> *getPointerToTeamAvlNode() const;
    void setPointerToTeam(AVLNode<Team> *pointerToTeam);

    bool isGoalKeeper() const;
    int getPlayerId() const;
    int getGoals() const;
    int getCards() const;
    // operator <
    bool operator<(const Player &player) const;
    // operator >
    bool operator>(const Player &player) const;
    // operator ==
    bool operator==(const Player &player) const;
    // operator !=
    bool operator!=(const Player &player) const;
    void setGamesTeamPlayedBefore(int gamesTeamPlayedBefore);
    // operator <<
    
    void setpointerToPlayerStatsAvlNodeONAllPlayers(AVLNode<PlayerStats> *pointerToPlayerStatsAvlNodeONAllPlayers);
    void SetpointerToPlayerStatsAvlNodeONTeam(AVLNode<PlayerStats> *pointerToPlayerStatsAvlNodeONTeam);
    AVLNode<Team> *getTeamNode() const;
    AVLNode<PlayerStats> *getpointerToPlayerStatsAvlNodeONAllPlayers() const;
    AVLNode<PlayerStats> *getpointerToPlayerStatsAvlNodeONTeam() const;
    void updatePlayerStats(int gamesPlayed, int goals, int cards);

    void setTeamId(int newTeamId);
    AVLNode<Player> *getPointerToAllPlayerAvlNode();
    void setPointerToAllPlayerAvlNode(AVLNode<Player> *pointerToAllPlayerAvlNode);
    int GetGamesPlayed();
    int GetGamesTeamPlayedBefore();
    friend std::ostream &operator<<(std::ostream &os, const Player &player)
    {
        os << "playerId: " << player.playerId << " teamId: " << player.teamId << " gamesPlayed: " << player.gamesPlayed << " goals: " << player.goals << " cards: " << player.cards << " goalKeeper: " << player.goalKeeper << std::endl;
        return os;
    }
};

#endif // PLAYER_H_