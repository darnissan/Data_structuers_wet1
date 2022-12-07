#include "PlayerStats.h"
    PlayerStats::PlayerStats() : playerId(0), goals(0), cards(0), closesetFromAllLeftID(-1), closesetFromAllRightID(-1), closesetFromTeamLeftID(-1), closesetFromTeamRightID(-1)
    {
    }
   PlayerStats::~PlayerStats()=default;

     PlayerStats::PlayerStats(int playerId, int goals, int cards)
    {
        this->playerId = playerId;
        this->goals = goals;
        this->cards = cards;
    }

    void PlayerStats::setClosestFromAllLeftID(int id)
    {
        closesetFromAllLeftID = id;
    }

    void PlayerStats::setClosestFromAllRightID(int id)
    {
        closesetFromAllRightID = id;
    }
    void PlayerStats::setClosestFromTeamLeftID(int id)
    {
        closesetFromTeamLeftID = id;
    }
    void PlayerStats::setClosestFromTeamRightID(int id)
    {
        closesetFromTeamRightID = id;
    }
    int PlayerStats::getClosestFromAllLeftID()
    {
        return closesetFromAllLeftID;
    }
    int PlayerStats::getClosestFromAllRightID()
    {
        return closesetFromAllRightID;
    }
    int PlayerStats::getClosestFromTeamLeftID()
    {
        return closesetFromTeamLeftID;
    }
    int PlayerStats::getClosestFromTeamRightID()
    {
        return closesetFromTeamRightID;
    }

    // operator <
    bool PlayerStats::operator<(const PlayerStats &other) const
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
    bool PlayerStats::operator>(const PlayerStats &other) const
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
    bool PlayerStats::operator==(const PlayerStats &other) const
    {
        if (playerId == other.playerId)
        {
            return true;
        }
        return false;
    }
    // operator !=
    bool PlayerStats::operator!=(const PlayerStats &other) const
    {
        if (playerId != other.playerId)
        {
            return true;
        }
        return false;
    }
    
    int PlayerStats::getPlayerId() const
    {
        return playerId;
    }
    int PlayerStats::getGoals() const
    {
        return goals;
    }
    int PlayerStats::getCards() const
    {
        return cards;
    }
    void PlayerStats::updatePlayerStats(int goals, int cards)
    {

        this->goals += goals;
        this->cards += cards;
    }