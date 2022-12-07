#ifndef TEAMANDPLAYER_H_
#define TEAMANDPLAYER_H_
#include <iostream>
#include "Player.h"

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
    int teamTopScorerGoals = 0;
    int teamTopScorerId = 0;
    int teamTopScorerCards = 0;

public:
    AvlTree<Player> players;
    AvlTree<PlayerStats> PlayersOnTeamOrderdByStats;
    Team();
    Team(int id, int points);
    ~Team();
    void setTeamID(int id);
    // assign operator
    Team &operator=(const Team &other);
 
    // copy constructor
    Team(const Team &other);
    // defult constructor
    template <class T>
    AVLNode<T> *copyTree(AVLNode<T> *dst, AVLNode<T> *src)
    {
        // Check if the source tree is empty. If it is, there is nothing to copy,
        // so we can return immediately.
        if (src == nullptr)
            return nullptr;

        if (dst == nullptr)
        {
            dst = new AVLNode<T>(src->GetValue());
        }
        // Copy the value from the source tree to the destination tree
        dst->SetValue(src->GetValue());

        // Recursively copy the left and right subtrees of the source tree
        // to the destination tree
        dst->SetLeft(copyTree(dst->GetLeft(), src->GetLeft()));
        dst->SetRight(copyTree(dst->GetRight(), src->GetRight()));
        // how to delete the new memory carfully?
        return dst;
    }
    // operator== for team
    bool operator==(const Team &other) const;
    // operator > for team
    bool operator>(const Team &other) const;
    // operator < for team
    bool operator<(const Team &other) const;
    void setNumOfPlayers(int numOfPlayers);
    void setNumOfGoalKeepers(int numOfGoalKeepers);
    void setPoints(int points);
    void setGamesTeamPlayed(int gamesTeamPlayed);
    void setTotalGoalsScored(int TotalGoalsScored);
    void setTotalCards(int TotalCards);

    void setTeamTopScorerGoals(int teamTopScorerGoals);
    void setTeamTopScorerId(int teamTopScorerId);

    void setTeamTopScorerCards(int teamTopScorerCards);

    int getId() const;
    int getNumOfPlayers() const;
    int getNumOfGoalKeepers() const;
    int getPoints() const;
    int getGamesTeamPlayed() const;
    int getTotalGoalsScored() const;
    int getTotalCards() const;

    int getTeamTopScorerGoals();

    int getTeamTopScorerId();

    int getTeamTopScorerCards();

    AVLNode<Player> *InsertPlayerToTeam(const Player &playerToInsert);
    AVLNode<PlayerStats> *InsertPlayerToTeamStatsTree(const PlayerStats &playerToInsert);

    //<< operator for team
    friend std::ostream &operator<<(std::ostream &os, const Team &team)
    {
        os << "team id" << team.id << " number of players " << team.numOfPlayers << " number GK " << team.numOfGoalKeepers << "  points "
           << "points:" << team.points << " games Played " << team.gamesTeamPlayed << " totalGoals " << team.TotalGoalsScored << " totalCards " << team.TotalCards << "---" << std::endl;
        return os;
    }
    
    void RemovePlayerFromTeam(const Player &PlayerToRemove);
    void removePlayerFromStatsTeam(const PlayerStats &playerToRemove);

    AVLNode<Player> *findPlayerById(AVLNode<Player> *node, int playerId);
};

#endif // TEAMANDPLAYER_H_
