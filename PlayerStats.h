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
    int closesetFromAllLeftID = -1;
    int closesetFromAllRightID = -1;
    int closesetFromTeamLeftID = -1;
    int closesetFromTeamRightID = -1;

public:
    PlayerStats();

    explicit PlayerStats(int playerId, int goals, int cards);

    void setClosestFromAllLeftID(int id);

    void setClosestFromAllRightID(int id);
    void setClosestFromTeamLeftID(int id);
    void setClosestFromTeamRightID(int id);
    int getClosestFromAllLeftID();
    int getClosestFromAllRightID();
    int getClosestFromTeamLeftID();
    int getClosestFromTeamRightID();

    // operator <
    bool operator<(const PlayerStats &other) const;
    // operator >
    bool operator>(const PlayerStats &other) const;
    // operator ==
    bool operator==(const PlayerStats &other) const;
    // operator !=
    bool operator!=(const PlayerStats &other) const;
    // operator <<
    friend std::ostream &operator<<(std::ostream &os, const PlayerStats &player)
    {
        os << "playerId: " << player.playerId << " goals: " << player.goals << " cards: " << player.cards << std::endl;
        return os;
    }
    int getPlayerId() const;
    int getGoals() const;
    int getCards() const;
    void updatePlayerStats(int goals, int cards);
};
#endif // PLAYER_STATS_H_