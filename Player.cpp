#include "Player.h"

    Player::Player()
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
    //~Player()
    //{
    //}

    Player::Player(int playerId, int teamId) : playerId(playerId), teamId(teamId), gamesPlayed(0), goals(0), cards(0), goalKeeper(false)
    {
        // gamesTeamPlayedBefore =
        // closesetFromLeft =
        // closesetFromRight =
        // pointerToTeam =
    }
    Player::Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper) : playerId(playerId), teamId(teamId), gamesPlayed(gamesPlayed),
                                                                                               goals(goals), cards(cards), goalKeeper(goalKeeper)
    {
        // gamesTeamPlayedBefore =
        // closesetFromLeft =
        // closesetFromRight =
        // pointerToTeam =
    }
    // get pointer to team
    AVLNode<Team>* Player::getPointerToTeamAvlNode() const
    {
        return pointerToTeamAvlNode;
    }
    void Player::setPointerToTeam(AVLNode<Team> *pointerToTeam)
    {
        this->pointerToTeamAvlNode = pointerToTeam;
    }

    bool Player::isGoalKeeper() const
    {
        return goalKeeper;
    }
    int Player::getPlayerId() const
    {
        return playerId;
    }
    int Player::getGoals() const
    {
        return goals;
    }
    int Player::getCards() const
    {
        return cards;
    }
    // operator <
    bool Player::operator<(const Player &player) const
    {
        if (playerId < player.playerId)
        {
            return true;
        }
        return false;
    }
    // operator >
    bool Player::operator>(const Player &player) const
    {
        if (playerId > player.playerId)
        {
            return true;
        }
        return false;
    }
    // operator ==
    bool Player::operator==(const Player &player) const
    {
        if (playerId == player.playerId)
        {
            return true;
        }
        return false;
    }
    // operator !=
    bool Player::operator!=(const Player &player) const
    {
        if (playerId != player.playerId)
        {
            return true;
        }
        return false;
    }
    void Player::setGamesTeamPlayedBefore(int gamesTeamPlayedBefore)
    {
        this->gamesTeamPlayedBefore = gamesTeamPlayedBefore;
    }
    // operator <<
    
    void Player::setpointerToPlayerStatsAvlNodeONAllPlayers(AVLNode<PlayerStats> *pointerToPlayerStatsAvlNodeONAllPlayers)
    {

        this->pointerToPlayerStatsAvlNodeONAllPlayers = pointerToPlayerStatsAvlNodeONAllPlayers;
    }
    void Player::SetpointerToPlayerStatsAvlNodeONTeam(AVLNode<PlayerStats> *pointerToPlayerStatsAvlNodeONTeam)
    {
        this->pointerToPlayerStatsAvlNodeONTeam = pointerToPlayerStatsAvlNodeONTeam;
    }
    AVLNode<Team> * Player::getTeamNode() const
    {
        return pointerToTeamAvlNode;
    }
    AVLNode<PlayerStats> *Player::getpointerToPlayerStatsAvlNodeONAllPlayers() const
    {
        return pointerToPlayerStatsAvlNodeONAllPlayers;
    }
    AVLNode<PlayerStats> *Player::getpointerToPlayerStatsAvlNodeONTeam() const
    {
        return pointerToPlayerStatsAvlNodeONTeam;
    }
    void Player::updatePlayerStats(int gamesPlayed, int goals, int cards)
    {
        this->gamesPlayed += gamesPlayed;
        this->goals += goals;
        this->cards += cards;
    }

    void Player::setTeamId(int newTeamId)
    {
        this->teamId = newTeamId;
    }
    AVLNode<Player> *Player::getPointerToAllPlayerAvlNode()
    {
        return pointerToAllPlayerAvlNode;
    }
    void Player::setPointerToAllPlayerAvlNode(AVLNode<Player> *pointerToAllPlayerAvlNode)
    {
        this->pointerToAllPlayerAvlNode = pointerToAllPlayerAvlNode;
    }
    int Player::GetGamesPlayed()
    {
        return this->gamesPlayed;
    }
    int Player::GetGamesTeamPlayedBefore()
    {
        return this->gamesTeamPlayedBefore;
    }