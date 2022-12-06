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
    int teamTopScorerGoals = 0;
    int teamTopScorerId = 0;
    int teamTopScorerCards = 0;

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
    void setTeamID(int id)
    {
        this->id = id;
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
    Team(const Team &other) : id(other.id), numOfPlayers(other.numOfPlayers), numOfGoalKeepers(other.numOfGoalKeepers),
                              points(other.points), gamesTeamPlayed(other.gamesTeamPlayed), TotalGoalsScored(other.TotalGoalsScored), TotalCards(other.TotalCards), players(other.players), PlayersOnTeamOrderdByStats(other.PlayersOnTeamOrderdByStats) {}
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
    void setNumOfPlayers(int numOfPlayers)
    {
        this->numOfPlayers = numOfPlayers;
    }
    void setNumOfGoalKeepers(int numOfGoalKeepers)
    {
        this->numOfGoalKeepers = numOfGoalKeepers;
    }
    void setPoints(int points)
    {
        this->points = points;
    }
    void setGamesTeamPlayed(int gamesTeamPlayed)
    {
        this->gamesTeamPlayed = gamesTeamPlayed;
    }
    void setTotalGoalsScored(int TotalGoalsScored)
    {
        this->TotalGoalsScored = TotalGoalsScored;
    }
    void setTotalCards(int TotalCards)
    {
        this->TotalCards = TotalCards;
    }

    void setTeamTopScorerGoals(int teamTopScorerGoals)
    {
        this->teamTopScorerGoals = teamTopScorerGoals;
    }

    void setTeamTopScorerId(int teamTopScorerId)
    {
        this->teamTopScorerId = teamTopScorerId;
    }

    void setTeamTopScorerCards(int teamTopScorerCards)
    {
        this->teamTopScorerCards = teamTopScorerCards;
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

    int getTeamTopScorerGoals()
    {
        return teamTopScorerGoals;
    }

    int getTeamTopScorerId()
    {
        return teamTopScorerId;
    }

    int getTeamTopScorerCards()
    {
        return teamTopScorerCards;
    }

    AVLNode<Player> *InsertPlayerToTeam(const Player &playerToInsert)
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
    AVLNode<PlayerStats> *InsertPlayerToTeamStatsTree(const PlayerStats &playerToInsert)
    {
        PlayersOnTeamOrderdByStats.root = PlayersOnTeamOrderdByStats.Insert(PlayersOnTeamOrderdByStats.GetRoot(), playerToInsert); // o(logn)
        return PlayersOnTeamOrderdByStats.find(PlayersOnTeamOrderdByStats.GetRoot(), playerToInsert);                              // o(logn)
    }

    //<< operator for team
    friend std::ostream &operator<<(std::ostream &os, const Team &team)
    {
        os << "team id" << team.id << " number of players " << team.numOfPlayers << " number GK " << team.numOfGoalKeepers << "  points "
           << "points:" << team.points << " games Played " << team.gamesTeamPlayed << " totalGoals " << team.TotalGoalsScored << " totalCards " << team.TotalCards << "---" << std::endl;
        return os;
    }
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
    void RemovePlayerFromTeam(const Player &PlayerToRemove)
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
    void removePlayerFromStatsTeam(const PlayerStats &playerToRemove)
    {
        PlayersOnTeamOrderdByStats.root = PlayersOnTeamOrderdByStats.Remove(PlayersOnTeamOrderdByStats.GetRoot(), playerToRemove); // o(logn)
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
