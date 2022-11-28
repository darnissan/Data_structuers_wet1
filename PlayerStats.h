#ifndef PLAYER_STATS_H_
#define PLAYER_STATS_H_
#include <iostream>
class PlayerStats 
{
private:
    int playerId;
    int goals;
    int cards;
    int closesetFromLeftID;
    int closesetFromRightID;

public:
    PlayerStats() : playerId(0), goals(0), cards(0), closesetFromLeftID(0), closesetFromRightID(0) {}
   
    explicit PlayerStats(int playerId, int goals, int cards)
    {
        this->playerId = playerId;
        this->goals = goals;
        this->cards = cards;
    }
  
 

    void setClosestFromLeftID(int id)
    {
        closesetFromLeftID = id;
    }

    void setClosestFromRightID(int id)
    {
        closesetFromRightID = id;
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