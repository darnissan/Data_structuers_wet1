#ifndef PLAYER_STATS_H_
#define PLAYER_STATS_H_
#include <iostream>
#include "AvlTree.h"
class PlayerStats 
{
private:
    int playerId;
    int goals;
    int cards;
    int closesetFromAllLeftID=-1;
    int closesetFromAllRightID=-1;
    int closesetFromTeamLeftID=-1;
    int closesetFromTeamRightID=-1;

        public : PlayerStats() : playerId(0), goals(0), cards(0), closesetFromAllLeftID(-1), closesetFromAllRightID(-1), closesetFromTeamLeftID(-1), closesetFromTeamRightID(-1)
    {
    }

    explicit PlayerStats(int playerId, int goals, int cards)
    {
        this->playerId = playerId;
        this->goals = goals;
        this->cards = cards;
    }
  
 

    void setClosestFromAllLeftID(int id)
    {
        closesetFromAllLeftID = id;
    }

    void setClosestFromAllRightID(int id)
    {
        closesetFromAllRightID = id;
    }
    void setClosestFromTeamLeftID(int id)
    {
        closesetFromTeamLeftID = id;
    }
    void setClosestFromTeamRightID(int id)
    {
        closesetFromTeamRightID = id;
    }
    int getClosestFromAllLeftID()
    {
        return closesetFromAllLeftID;
    }
    int getClosestFromAllRightID()
    {
        return closesetFromAllRightID;
    }
    int getClosestFromTeamLeftID()
    {
        return closesetFromTeamLeftID;
    }
    int getClosestFromTeamRightID()
    {
        return closesetFromTeamRightID;
    }

    // operator <
    bool operator<(const PlayerStats &other) const
    {
        if (this->goals < other.goals)
            return true;
        if (this->goals > other.goals)
            return false;
        if (this->goals == other.goals)
        {
            if (this->cards < other.cards)
                return false;
            if (this->cards > other.cards)
                return true;
            if (this->cards == other.cards)
            {
                if (playerId < other.playerId)
                    return true;
                if (playerId > other.playerId)
                    return false;
            }
        }
        return false;
    }
    // operator >
    bool operator>(const PlayerStats &other) const
    {
        if (goals > other.goals)
            return true;
        if (goals < other.goals)
            return false;
        if (goals == other.goals)
        {
            if (cards > other.cards)
                return false;
            if (cards < other.cards)
                return true;
            if (cards == other.cards)
            {
                if (playerId > other.playerId)
                    return true;
                if (playerId < other.playerId)
                    return false;
            }
        }
        return false;
    }
    // operator ==
    bool operator==(const PlayerStats &other) const
    {
        if (playerId == other.playerId)
        {
            return true;
        }
        return false;
    }
    // operator !=
    bool operator!=(const PlayerStats &other) const
    {
        if (playerId != other.playerId)
        {
            return true;
        }
    }
    // operator <<
    friend std::ostream &operator<<(std::ostream &os, const PlayerStats &player)
    {
        os << "playerId: " << player.playerId  << " goals: " << player.goals << " cards: " << player.cards << std::endl;
        return os;
    }
    int getPlayerId() const
    {
        return playerId;
    }
    int getGoals() const
    {
        return goals;
    }
    int getCards() const
    {
        return cards;
    }
   
};
#endif // PLAYER_STATS_H_