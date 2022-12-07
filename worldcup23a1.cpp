#include "worldcup23a1.h"

template <class T>
void printBT(const std::string &prefix, const AVLNode<T> *node, bool isLeft);
template <class T>
void printBTs(const AVLNode<T> *node);
AVLNode<Team> *findTeamById(AVLNode<Team> *root, int teamId);
AVLNode<Player> *findPlayerById(AVLNode<Player> *node, int playerId);
bool isLeagelTeam(AVLNode<Team> *node);
int ClosestDiffFromLeftWrapper(AVLNode<PlayerStats> *node, PlayerStats &searcher);
void ClosestDiffFromLeft(AVLNode<PlayerStats> *node, PlayerStats &searcher, PlayerStats &minDiffcurrent);
int ClosestDiffFromRightWrapper(AVLNode<PlayerStats> *node, PlayerStats &searcher);
template <class T>
bool isAvlTREE(AVLNode<T> *node);

AVLNode<Player> *SortedArrayToTree(Player *sortedArr, int start, int end);

AVLNode<Player> *MergeTwoTrees(AVLNode<Player> *root1, AVLNode<Player> *root2, int FirstTreesSize, int SecondTreeSize);

void InOrderPlayerStatsToArray(AVLNode<PlayerStats> *root1, int *arr1, int *index);

void InOrderTreeToArray(AVLNode<Player> *root1, AVLNode<Player> *arr1, int *index);

void InOrderTreeToArray(AVLNode<Player> *root1, Player *arr1, int *index);
AVLNode<PlayerStats> *MergeTwoTrees(AVLNode<PlayerStats> *root1, AVLNode<PlayerStats> *root2, int FirstTreesSize, int SecondTreeSize);
void InOrderTreeToArray(AVLNode<PlayerStats> *root1, PlayerStats *arr1, int *index);
PlayerStats *MergeTwoArrays(PlayerStats *arr1, PlayerStats *arr2, int size1, int size2);
Player *MergeTwoArrays(Player *arr1, Player *arr2, int size1, int size2);
AVLNode<PlayerStats> *SortedArrayToTree(PlayerStats *sortedArr, int start, int end);
world_cup_t::world_cup_t()
{
	// TODO: Your code goes here
}

world_cup_t::~world_cup_t()
{

	// TODO: Your code goes here
}

StatusType world_cup_t::add_team(int teamId, int points)
{
	// TODO: Your code goes here
	if (teamId <= 0 || points < 0)
	{
		return StatusType::INVALID_INPUT;
	}
	Team newTeam;

	try
	{
		newTeam = Team(teamId, points);
	}
	catch (std::bad_alloc &e)
	{
		return StatusType::ALLOCATION_ERROR;
	}

	if (AllTeams.isItInTree(AllTeams.GetRoot(), newTeam))
		return StatusType::FAILURE;
	AllTeams.root = AllTeams.Insert(AllTeams.GetRoot(), newTeam);

	numberOfTeams++;
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
	// TODO: Your code goes here
	if (teamId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	AVLNode<Team> *TeamAfterSearch = findTeamById(AllTeams.GetRoot(), teamId);
	if (TeamAfterSearch == NULL || TeamAfterSearch->GetValue().getNumOfPlayers() > 0)

	{
		return StatusType::FAILURE;
	}
	AllTeams.root = AllTeams.Remove(AllTeams.GetRoot(), TeamAfterSearch->GetValue());
	if (isInLeagelTeamsTree(teamId))
	{
		leagelTeams.Remove(leagelTeams.root, IDandTotalPoints(teamId, 0));
	}
	numberOfTeams--;
	if (isLeagelTeam(TeamAfterSearch))
	{
		numberOfLeagelTeams--;
	}
	// std::cout << "team removed" << std::endl;
	AllTeams.PrintInOrder(AllTeams.GetRoot());
	return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
								   int goals, int cards, bool goalKeeper)
{
	// TODO: Your code goes here
	// checking invalid input
	// Adding  player to All players tree held by worldCup
	// Adding player  to players tree held by its team
	// Adding player to All players_ordered_by_stats
	// Adding player to All players_ordered_by_stats_on_his_team
	// updating the closest from left and right on ALL players stats tree
	// updating the closest from left and right on ALL players stats tree on his team
	AVLNode<Team> *TheTeamOfThePlayerNode = findTeamById(AllTeams.GetRoot(), teamId); // finding the team of the player By binary search on AVL tree O(logn)

	// checking whether the input is valid
	if (playerId <= 0 || teamId <= 0 || gamesPlayed < 0 || goals < 0 || cards < 0 || (gamesPlayed == 0 && (goals > 0 || cards > 0)))
		return StatusType::INVALID_INPUT;

	// checking whether the team exists or the player already exists
	if (TheTeamOfThePlayerNode == NULL || findPlayerById(AllPlayers.GetRoot(), playerId) != NULL)
	{
		return StatusType::FAILURE;
	}

	// creating the player and his stats
	Player newPlayer;
	PlayerStats newPlayerStats;
	try
	{
		newPlayer = Player(playerId, teamId, gamesPlayed, goals, cards, goalKeeper);
		newPlayer.setGamesTeamPlayedBefore(TheTeamOfThePlayerNode->GetValue().getGamesTeamPlayed());
		newPlayerStats = PlayerStats(playerId, goals, cards);
	}

	catch (std::bad_alloc &e)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	int oldIDAndTotalPoints = TheTeamOfThePlayerNode->GetValue().getPoints() + TheTeamOfThePlayerNode->GetValue().getTotalGoalsScored() - TheTeamOfThePlayerNode->GetValue().getTotalCards();
	// updating top scorer
	if (newPlayer.getGoals() > topScorerGoals)
	{
		topScorerGoals = newPlayer.getGoals();
		topScorerId = newPlayer.getPlayerId();
		topScorerCards = newPlayer.getCards();
	}
	else if (newPlayer.getGoals() == topScorerGoals)
	{
		if (newPlayer.getCards() < topScorerCards)
		{
			topScorerGoals = newPlayer.getGoals();
			topScorerId = newPlayer.getPlayerId();
			topScorerCards = newPlayer.getCards();
		}
		else if (newPlayer.getCards() == topScorerCards)
		{
			if (newPlayer.getPlayerId() > topScorerId)
			{
				topScorerGoals = newPlayer.getGoals();
				topScorerId = newPlayer.getPlayerId();
				topScorerCards = newPlayer.getCards();
			}
		}
	}

	if (newPlayer.getGoals() > TheTeamOfThePlayerNode->GetValue().getTeamTopScorerGoals())
	{
		TheTeamOfThePlayerNode->GetValue().setTeamTopScorerGoals(newPlayer.getGoals());
		TheTeamOfThePlayerNode->GetValue().setTeamTopScorerId(newPlayer.getPlayerId());
		TheTeamOfThePlayerNode->GetValue().setTeamTopScorerCards(newPlayer.getCards());
	}
	else if (newPlayer.getGoals() == TheTeamOfThePlayerNode->GetValue().getTeamTopScorerGoals())
	{
		if (newPlayer.getCards() < TheTeamOfThePlayerNode->GetValue().getTeamTopScorerCards())
		{
			TheTeamOfThePlayerNode->GetValue().setTeamTopScorerGoals(newPlayer.getGoals());
			TheTeamOfThePlayerNode->GetValue().setTeamTopScorerId(newPlayer.getPlayerId());
			TheTeamOfThePlayerNode->GetValue().setTeamTopScorerCards(newPlayer.getCards());
		}
		else if (newPlayer.getCards() == TheTeamOfThePlayerNode->GetValue().getTeamTopScorerCards())
		{
			if (newPlayer.getPlayerId() > TheTeamOfThePlayerNode->GetValue().getTeamTopScorerId())
			{
				TheTeamOfThePlayerNode->GetValue().setTeamTopScorerGoals(newPlayer.getGoals());
				TheTeamOfThePlayerNode->GetValue().setTeamTopScorerId(newPlayer.getPlayerId());
				TheTeamOfThePlayerNode->GetValue().setTeamTopScorerCards(newPlayer.getCards());
			}
		}
	}

	// creating the node of the player thats going to be added to the tree of players held by the team
	AVLNode<Player> *PlayerNodeOnTeamPlayersTree;
	AVLNode<Player> *PlayerNodeOnAllPlayersTree;
	AVLNode<PlayerStats> *PlayerNodeOnAllPlayersStatsTree;

	AllPlayers.root = AllPlayers.Insert(AllPlayers.GetRoot(), newPlayer);
	PlayerNodeOnAllPlayersTree = findPlayerById(AllPlayers.GetRoot(), playerId);
	// setting the player node to point on the team node in the tree of teams
	PlayerNodeOnAllPlayersTree->GetValue().setPointerToTeam(TheTeamOfThePlayerNode); // o(1)

	PlayerNodeOnAllPlayersTree->GetValue().setGamesTeamPlayedBefore(TheTeamOfThePlayerNode->GetValue().getGamesTeamPlayed()); // o(1)

	// calculating the player closests from left and right
	int closestFromAllLeftId = ClosestDiffFromLeftWrapper(ALLPayersOrderdByStats.GetRoot(), newPlayerStats);   // o(logn)
	int closestFromAllRightId = ClosestDiffFromRightWrapper(ALLPayersOrderdByStats.GetRoot(), newPlayerStats); // o(logn)
	newPlayerStats.setClosestFromAllLeftID(closestFromAllLeftId);											   // o(1)
	newPlayerStats.setClosestFromAllRightID(closestFromAllRightId);											   // o(1)

	int closestFromTeamLeftId = ClosestDiffFromLeftWrapper(TheTeamOfThePlayerNode->GetValue().PlayersOnTeamOrderdByStats.GetRoot(), newPlayerStats);   // o(logn)
	int closestFromTeamRightId = ClosestDiffFromRightWrapper(TheTeamOfThePlayerNode->GetValue().PlayersOnTeamOrderdByStats.GetRoot(), newPlayerStats); // o(logn)
	newPlayerStats.setClosestFromTeamLeftID(closestFromTeamLeftId);																					   // o(1)
	newPlayerStats.setClosestFromTeamRightID(closestFromTeamRightId);																				   // o(1)
	// adding the player stats to the stats tree
	ALLPayersOrderdByStats.root = ALLPayersOrderdByStats.Insert(ALLPayersOrderdByStats.GetRoot(), newPlayerStats); // o(logn)
	PlayerNodeOnAllPlayersStatsTree=ALLPayersOrderdByStats.find(ALLPayersOrderdByStats.GetRoot(), newPlayerStats); // o(logn)
		PlayerNodeOnAllPlayersTree->GetValue().SetpointerToPlayerStatsAvlNodeONTeam(TheTeamOfThePlayerNode->GetValue().InsertPlayerToTeamStatsTree(newPlayerStats)); // o(logn)
	// setting the pointer held by the player instance to the player stats tree
	// ALLPayersOrderdByStats.root = ALLPayersOrderdByStats.Insert(ALLPayersOrderdByStats.GetRoot(), newPlayerStats);
	PlayerNodeOnAllPlayersTree->GetValue().setpointerToPlayerStatsAvlNodeONAllPlayers(PlayerNodeOnAllPlayersStatsTree); // o(1)

	// updating the left and right closets from both all players and team players stats
	updateClosest(closestFromAllLeftId);
	updateClosest(closestFromAllRightId);
	updateClosest(closestFromTeamLeftId);
	updateClosest(closestFromTeamRightId);

	// adding player  to players tree held by its team
	PlayerNodeOnTeamPlayersTree = TheTeamOfThePlayerNode->GetValue().InsertPlayerToTeam(newPlayer);

	// adding player to All players tree held by worldCup
	AllPlayers.root = AllPlayers.Insert(AllPlayers.GetRoot(), newPlayer);

	// still needs to link between the avlnode on all players tree to the avlnode on the team tree and the avl node on players by stats tree

	// adding player to All players_ordered_by_stats
	PlayerNodeOnTeamPlayersTree->GetValue().setpointerToPlayerStatsAvlNodeONAllPlayers(PlayerNodeOnAllPlayersStatsTree);
	PlayerNodeOnTeamPlayersTree->GetValue().setPointerToAllPlayerAvlNode(PlayerNodeOnAllPlayersTree);
	AllPlayers.find(AllPlayers.GetRoot(), newPlayer)->GetValue().setPointerToAllPlayerAvlNode(PlayerNodeOnAllPlayersTree);
	/*
	std::cout << "player added" <<newPlayer << std::endl;
	std::cout<<"--------------------------------------"<<std::endl;
	std::cout<<"closest from all left id: "<<closestFromAllLeftId<<std::endl;
	std::cout<<"closest from all right id: "<<closestFromAllRightId<<std::endl;
	std::cout<<"closest from team left id: "<<closestFromTeamLeftId<<std::endl;
	std::cout<<"closest from team right id: "<<closestFromTeamRightId<<std::endl;
	std::cout << "--------------------------------------" << std::endl;
	std::cout << "inorder of stats tree" << std::endl;
	printBTs( ALLPayersOrderdByStats.GetRoot());
	std::cout << "--------------------------------------" << std::endl;
	*/
	numberOfPlayers++;
	if (isLeagelTeam(TheTeamOfThePlayerNode) && isInLeagelTeamsTree(teamId) == false)
	{
		int TotalPoints = TheTeamOfThePlayerNode->GetValue().getPoints() + TheTeamOfThePlayerNode->GetValue().getTotalGoalsScored() - TheTeamOfThePlayerNode->GetValue().getTotalCards();

		IDandTotalPoints teamPair(teamId, TotalPoints);
		leagelTeams.root = leagelTeams.Insert(leagelTeams.GetRoot(), teamPair);
	}

	else if (isLeagelTeam(TheTeamOfThePlayerNode))
	{
		int newTotalPoint = TheTeamOfThePlayerNode->GetValue().getPoints() + TheTeamOfThePlayerNode->GetValue().getTotalGoalsScored() - TheTeamOfThePlayerNode->GetValue().getTotalCards();

		IDandTotalPoints OldteamPair(teamId, oldIDAndTotalPoints);
		IDandTotalPoints newTeamPair(teamId, newTotalPoint);
		leagelTeams.root = leagelTeams.Remove(leagelTeams.root, OldteamPair);
		leagelTeams.root = leagelTeams.Insert(leagelTeams.root, newTeamPair);
	}
	// std::cout<<" player added id "<<playerId<< std::endl;
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
	if (playerId <= 0)
		return StatusType::INVALID_INPUT;
	AVLNode<Player> *playerNodeOnAllPlayersTree = findPlayerById(AllPlayers.GetRoot(), playerId);
	if (playerNodeOnAllPlayersTree == NULL)
	{
		return StatusType::FAILURE;
	}
	Player playerInstance = playerNodeOnAllPlayersTree->GetValue();																	   // finding the player on player tree By binary search on AVL tree O(logn)
	AVLNode<Team> *TheTeamOfThePlayerNode = playerNodeOnAllPlayersTree->GetValue().getPointerToTeamAvlNode();						   // getting player team
	AVLNode<PlayerStats> *playerNodeOnPlayerStatsTree = playerNodeOnAllPlayersTree->GetValue().getpointerToPlayerStatsAvlNodeONTeam(); // finding the player on player stats tree By binary search on AVL tree O(logn)
	PlayerStats playerStatsInstance = playerNodeOnPlayerStatsTree->GetValue();
	bool isGK = playerNodeOnAllPlayersTree->GetValue().isGoalKeeper();
	// checking whether the input is valid

	// checking whether the player exists

	// set new closest;
	int closestFromAllLeftId = playerNodeOnPlayerStatsTree->GetValue().getClosestFromAllLeftID();
	int closestFromAllRightId = playerNodeOnPlayerStatsTree->GetValue().getClosestFromAllRightID();

	
	// trying to remove player
	try
	{
		AllPlayers.root = AllPlayers.Remove(AllPlayers.GetRoot(), playerNodeOnAllPlayersTree->GetValue());
		ALLPayersOrderdByStats.root = ALLPayersOrderdByStats.Remove(ALLPayersOrderdByStats.GetRoot(), playerStatsInstance);
		TheTeamOfThePlayerNode->GetValue().players.root = TheTeamOfThePlayerNode->GetValue().players.Remove(TheTeamOfThePlayerNode->GetValue().players.root, playerInstance);
		TheTeamOfThePlayerNode->GetValue().PlayersOnTeamOrderdByStats.root = TheTeamOfThePlayerNode->GetValue().PlayersOnTeamOrderdByStats.Remove(TheTeamOfThePlayerNode->GetValue().PlayersOnTeamOrderdByStats.root, playerStatsInstance);
	}
	catch (std::bad_alloc &e)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	if (playerId == topScorerId)
	{
		topScorerId = playerNodeOnPlayerStatsTree->GetValue().getPlayerId();
		AVLNode<PlayerStats> *newTopScorer = ALLPayersOrderdByStats.GetRoot();
		if (newTopScorer != NULL)
		{
			while (newTopScorer->GetRight() != NULL)
			{
				newTopScorer = newTopScorer->GetRight();
			}
			topScorerGoals = newTopScorer->GetValue().getGoals();
			topScorerCards = newTopScorer->GetValue().getCards();
			topScorerId = newTopScorer->GetValue().getPlayerId();
		}
	}
	// set new closest;
	updateClosest(closestFromAllLeftId);
	updateClosest(closestFromAllRightId);
	TheTeamOfThePlayerNode->GetValue().setNumOfPlayers(TheTeamOfThePlayerNode->GetValue().getNumOfPlayers() - 1);
	if (isGK)
	{
		TheTeamOfThePlayerNode->GetValue().setNumOfGoalKeepers(TheTeamOfThePlayerNode->GetValue().getNumOfGoalKeepers() - 1);
	}
	// find new top scorer

	if (playerId == TheTeamOfThePlayerNode->GetValue().getTeamTopScorerId())
	{
		;
	}

	numberOfPlayers--;
	// std::cout << "player removed" << std::endl;
	// AllTeams.PrintInOrder(AllTeams.GetRoot());

	// check if the removed player's team is still legal
	if (!(isLeagelTeam(TheTeamOfThePlayerNode)))
	{
		numberOfLeagelTeams--;
		leagelTeams.root = leagelTeams.Remove(leagelTeams.root, IDandTotalPoints(TheTeamOfThePlayerNode->GetValue().getId(), 0));
	}
	return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
											int scoredGoals, int cardsReceived)
{
	if (playerId <= 0 || gamesPlayed < 0 || scoredGoals < 0 || cardsReceived < 0)
		return StatusType::INVALID_INPUT;
	if (findPlayerById(AllPlayers.GetRoot(), playerId) == NULL)
		return StatusType::FAILURE;

	try
	{
		AVLNode<PlayerStats> *PlayerStatsAllPlayers;
		AVLNode<PlayerStats> *PlayerStatsTeam;
		AVLNode<Player> *playerNodeOnAllPlayersTree;
		AVLNode<Player> *playerNodeOnTeamPlayersTree;
		AVLNode<Team> *teamNodeOnTeamsTree;
		PlayerStats oldPlayerStats;
		PlayerStats newPlayerStats;
		playerNodeOnAllPlayersTree = findPlayerById(AllPlayers.GetRoot(), playerId);
		teamNodeOnTeamsTree = playerNodeOnAllPlayersTree->GetValue().getPointerToTeamAvlNode();
		playerNodeOnTeamPlayersTree = teamNodeOnTeamsTree->GetValue().findPlayerById(teamNodeOnTeamsTree->GetValue().players.GetRoot(), playerId);

		int oldGoals = playerNodeOnAllPlayersTree->GetValue().getGoals();
		int oldCards = playerNodeOnAllPlayersTree->GetValue().getCards();
		oldPlayerStats = PlayerStats(playerId, oldGoals, oldCards);

		int newGoals = oldGoals + scoredGoals;
		int newCards = oldCards + cardsReceived;
		newPlayerStats = PlayerStats(playerId, newGoals, newCards);

		// updating the player stats
		playerNodeOnAllPlayersTree->GetValue().updatePlayerStats(gamesPlayed, scoredGoals, cardsReceived);
		playerNodeOnTeamPlayersTree->GetValue().updatePlayerStats(gamesPlayed, scoredGoals, cardsReceived);

		// updating top scorer
		if (newGoals > topScorerGoals)
		{
			topScorerGoals = newGoals;
			topScorerId = playerId;
			topScorerCards = newCards;
		}
		else if (newGoals == topScorerGoals)
		{
			if (newCards < topScorerCards)
			{
				topScorerGoals = newGoals;
				topScorerId = playerId;
				topScorerCards = newCards;
			}
			else if (newCards == topScorerCards)
			{
				if (playerId > topScorerId)
				{
					topScorerGoals = newGoals;
					topScorerId = playerId;
					topScorerCards = newCards;
				}
			}
		}

		if (newGoals > teamNodeOnTeamsTree->GetValue().getTeamTopScorerGoals())
		{
			teamNodeOnTeamsTree->GetValue().setTeamTopScorerGoals(newGoals);
			teamNodeOnTeamsTree->GetValue().setTeamTopScorerId(playerId);
			teamNodeOnTeamsTree->GetValue().setTeamTopScorerCards(newCards);
		}
		else if (newGoals == teamNodeOnTeamsTree->GetValue().getTeamTopScorerGoals())
		{
			if (newCards < teamNodeOnTeamsTree->GetValue().getTeamTopScorerCards())
			{
				teamNodeOnTeamsTree->GetValue().setTeamTopScorerGoals(newGoals);
				teamNodeOnTeamsTree->GetValue().setTeamTopScorerId(playerId);
				teamNodeOnTeamsTree->GetValue().setTeamTopScorerCards(newCards);
			}
			else if (newCards == teamNodeOnTeamsTree->GetValue().getTeamTopScorerCards())
			{
				if (playerId > teamNodeOnTeamsTree->GetValue().getTeamTopScorerId())
				{
					teamNodeOnTeamsTree->GetValue().setTeamTopScorerGoals(newGoals);
					teamNodeOnTeamsTree->GetValue().setTeamTopScorerId(playerId);
					teamNodeOnTeamsTree->GetValue().setTeamTopScorerCards(newCards);
				}
			}
		}

		// updating the closest from all players stats
		int OldclosestFromAllLeftId = ClosestDiffFromLeftWrapper(ALLPayersOrderdByStats.GetRoot(), oldPlayerStats); // o(logn)

		int OldclosestFromAllRightId = ClosestDiffFromRightWrapper(ALLPayersOrderdByStats.GetRoot(), oldPlayerStats);									   // o(logn)
		int OldclosestFromTeamLeftId = ClosestDiffFromLeftWrapper(teamNodeOnTeamsTree->GetValue().PlayersOnTeamOrderdByStats.GetRoot(), oldPlayerStats);   // o(logn)
		int OldclosestFromTeamRightId = ClosestDiffFromRightWrapper(teamNodeOnTeamsTree->GetValue().PlayersOnTeamOrderdByStats.GetRoot(), oldPlayerStats); // o(logn)
		if (ALLPayersOrderdByStats.find(ALLPayersOrderdByStats.root, oldPlayerStats) != NULL)
			ALLPayersOrderdByStats.root = ALLPayersOrderdByStats.Remove(ALLPayersOrderdByStats.root, oldPlayerStats);
			
		if (teamNodeOnTeamsTree->GetValue().PlayersOnTeamOrderdByStats.find(teamNodeOnTeamsTree->GetValue().PlayersOnTeamOrderdByStats.root, oldPlayerStats))
			teamNodeOnTeamsTree->GetValue().PlayersOnTeamOrderdByStats.root = teamNodeOnTeamsTree->GetValue().PlayersOnTeamOrderdByStats.Remove(teamNodeOnTeamsTree->GetValue().PlayersOnTeamOrderdByStats.GetRoot(), oldPlayerStats);

		ALLPayersOrderdByStats.root = ALLPayersOrderdByStats.Insert(ALLPayersOrderdByStats.GetRoot(), newPlayerStats);
		teamNodeOnTeamsTree->GetValue().PlayersOnTeamOrderdByStats.root = teamNodeOnTeamsTree->GetValue().PlayersOnTeamOrderdByStats.Insert(teamNodeOnTeamsTree->GetValue().PlayersOnTeamOrderdByStats.GetRoot(), newPlayerStats);
		// NEED TO LINK THE PLAYER STATS TO THE PLAYER
		PlayerStatsAllPlayers = ALLPayersOrderdByStats.find(ALLPayersOrderdByStats.GetRoot(), newPlayerStats);
		PlayerStatsTeam = teamNodeOnTeamsTree->GetValue().PlayersOnTeamOrderdByStats.find(teamNodeOnTeamsTree->GetValue().PlayersOnTeamOrderdByStats.GetRoot(), newPlayerStats);
		playerNodeOnAllPlayersTree->GetValue().setpointerToPlayerStatsAvlNodeONAllPlayers(PlayerStatsAllPlayers);
		playerNodeOnAllPlayersTree->GetValue().SetpointerToPlayerStatsAvlNodeONTeam(PlayerStatsTeam);
		playerNodeOnTeamPlayersTree->GetValue().SetpointerToPlayerStatsAvlNodeONTeam(PlayerStatsTeam);
		playerNodeOnTeamPlayersTree->GetValue().setpointerToPlayerStatsAvlNodeONAllPlayers(PlayerStatsAllPlayers);

		// THE BUG IS HERE

		int NewclosestFromAllLeftId = ClosestDiffFromLeftWrapper(ALLPayersOrderdByStats.GetRoot(), newPlayerStats);
		// o(logn)
		int NewclosestFromAllRightId = ClosestDiffFromRightWrapper(ALLPayersOrderdByStats.GetRoot(), newPlayerStats);									   // o(logn)
		int NewclosestFromTeamLeftId = ClosestDiffFromLeftWrapper(teamNodeOnTeamsTree->GetValue().PlayersOnTeamOrderdByStats.GetRoot(), newPlayerStats);   // o(logn)
		int NewclosestFromTeamRightId = ClosestDiffFromRightWrapper(teamNodeOnTeamsTree->GetValue().PlayersOnTeamOrderdByStats.GetRoot(), newPlayerStats); // o(logn)

		// updating the closest from team players stats

		if (OldclosestFromAllLeftId != -1)
		{
			updateClosest(OldclosestFromAllLeftId);
		}
		if (OldclosestFromAllRightId != -1)
		{
			updateClosest(OldclosestFromAllRightId);
		}
		if (OldclosestFromTeamLeftId != -1)
		{
			updateClosest(OldclosestFromTeamLeftId);
		}
		if (OldclosestFromTeamRightId != -1)
		{
			updateClosest(OldclosestFromTeamRightId);
		}

		if (NewclosestFromAllLeftId != -1)
		{
			updateClosest(NewclosestFromAllLeftId);
		}
		if (NewclosestFromAllRightId != -1)
		{
			updateClosest(NewclosestFromAllRightId);
		}
		if (NewclosestFromTeamLeftId != -1)
		{
			updateClosest(NewclosestFromTeamLeftId);
		}
		if (NewclosestFromTeamRightId != -1)
		{
			updateClosest(NewclosestFromTeamRightId);
		}
		PlayerStatsAllPlayers->GetValue().setClosestFromAllLeftID(NewclosestFromAllLeftId);
		PlayerStatsAllPlayers->GetValue().setClosestFromAllRightID(NewclosestFromAllRightId);
		PlayerStatsAllPlayers->GetValue().setClosestFromTeamLeftID(NewclosestFromTeamLeftId);
		PlayerStatsAllPlayers->GetValue().setClosestFromTeamRightID(NewclosestFromTeamRightId);
		PlayerStatsTeam->GetValue().setClosestFromAllLeftID(NewclosestFromAllLeftId);
		PlayerStatsTeam->GetValue().setClosestFromAllRightID(NewclosestFromAllRightId);
		PlayerStatsTeam->GetValue().setClosestFromTeamLeftID(NewclosestFromTeamLeftId);
		PlayerStatsTeam->GetValue().setClosestFromTeamRightID(NewclosestFromTeamRightId);

		// update Leagel teams tree

		if (isLeagelTeam(teamNodeOnTeamsTree))
		{
			int oldTotalPoints = (leagelTeams.find(leagelTeams.root, IDandTotalPoints(teamNodeOnTeamsTree->GetValue().getId(), 0))->GetValue().getTotalPoints());
			oldTotalPoints = oldTotalPoints + scoredGoals - cardsReceived;
			leagelTeams.find(leagelTeams.root, IDandTotalPoints(teamNodeOnTeamsTree->GetValue().getId(), 0))->GetValue().setTotalPoints(oldTotalPoints);
		}
	}
	catch (const std::exception &e)
	{
		return StatusType::ALLOCATION_ERROR;
	}

	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{

	// TODO: Your code goes here
	if (teamId1 <= 0 || teamId2 <= 0 || teamId2 == teamId1)
	{
		return StatusType::INVALID_INPUT;
	}
	if (findTeamById(AllTeams.root, teamId1) == NULL || findTeamById(AllTeams.root, teamId2) == NULL || isInLeagelTeamsTree(teamId1) == false || isInLeagelTeamsTree(teamId2) == false)
	{
		return StatusType::FAILURE;
	}

	try
	{
		AVLNode<Team> *team1node = findTeamById(AllTeams.root, teamId1);
		AVLNode<Team> *team2node = findTeamById(AllTeams.root, teamId2);
		int Team1TotalScore = team1node->GetValue().getPoints() + team1node->GetValue().getTotalGoalsScored() - team1node->GetValue().getTotalCards();
		int Team2TotalScore = team2node->GetValue().getPoints() + team2node->GetValue().getTotalGoalsScored() - team2node->GetValue().getTotalCards();
		if (Team1TotalScore == Team2TotalScore)
		{
			team1node->GetValue().setPoints(team1node->GetValue().getPoints() + 1);
			team2node->GetValue().setPoints(team2node->GetValue().getPoints() + 1);
		}
		else if (Team1TotalScore > Team2TotalScore)
		{
			team1node->GetValue().setPoints(team1node->GetValue().getPoints() + 3);
		}
		else
		{
			team2node->GetValue().setPoints(team2node->GetValue().getPoints() + 3);
		}
		team1node->GetValue().setGamesTeamPlayed(team1node->GetValue().getGamesTeamPlayed() + 1);
		team2node->GetValue().setGamesTeamPlayed(team2node->GetValue().getGamesTeamPlayed() + 1);
	}
	catch (const std::exception &e)
	{
		return StatusType::ALLOCATION_ERROR;
	}

	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
	if (playerId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	if (findPlayerById(AllPlayers.root, playerId) == NULL)
	{
		return StatusType::FAILURE;
	}
	int numPlayedGames;
	try
	{
		AVLNode<Player> *playerNode = findPlayerById(AllPlayers.root, playerId);
		AVLNode<Team> *teamNode = playerNode->GetValue().getPointerToTeamAvlNode();
		numPlayedGames = playerNode->GetValue().GetGamesPlayed() + teamNode->GetValue().getGamesTeamPlayed() - playerNode->GetValue().GetGamesTeamPlayedBefore();
	}
	catch (const std::exception &e)
	{
		return StatusType::ALLOCATION_ERROR;
	}

	return numPlayedGames;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	if (teamId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	if (findTeamById(AllTeams.root, teamId) == NULL)
	{
		return StatusType::FAILURE;
	}
	int teampoints;
	try
	{
		AVLNode<Team> *teamNode = findTeamById(AllTeams.root, teamId);
		teampoints = teamNode->GetValue().getPoints();
	}
	catch (const std::exception &e)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	return teampoints;
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{

	/**/
	if (teamId2 == teamId1 || teamId2 <= 0 || teamId1 <= 0 || newTeamId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	if (findTeamById(AllTeams.GetRoot(), teamId1) == NULL || findTeamById(AllTeams.GetRoot(), teamId2) == NULL)
	{
		return StatusType::FAILURE;
	}
	if ((teamId1 != newTeamId) && (teamId2 != newTeamId) && findTeamById(AllTeams.GetRoot(), newTeamId) != NULL)
	{
		return StatusType::FAILURE;
	}

	try
	{

		AVLNode<Team> *team1Node = findTeamById(AllTeams.GetRoot(), teamId1);
		AVLNode<Team> *team2Node = findTeamById(AllTeams.GetRoot(), teamId2);
		AVLNode<Team> *nodeForLeagel = nullptr;
		if (isLeagelTeam(team1Node))
		{
			leagelTeams.root = leagelTeams.Remove(leagelTeams.root, IDandTotalPoints(teamId1, team1Node->GetValue().getPoints()));
		}
		if (isLeagelTeam(team2Node))
		{
			leagelTeams.root = leagelTeams.Remove(leagelTeams.root, IDandTotalPoints(teamId2, team2Node->GetValue().getPoints()));
		}
		if (newTeamId == teamId1) // meaning every player is going to teamid1
		{

			AVLNode<Player> *newPlayerTree = MergeTwoTrees(team1Node->GetValue().players.GetRoot(), team2Node->GetValue().players.GetRoot(), team1Node->GetValue().getNumOfPlayers(), team2Node->GetValue().getNumOfPlayers());
			AVLNode<PlayerStats> *newPlayerStatsTree = MergeTwoTrees(team1Node->GetValue().PlayersOnTeamOrderdByStats.GetRoot(), team2Node->GetValue().PlayersOnTeamOrderdByStats.GetRoot(), team1Node->GetValue().getNumOfPlayers(), team2Node->GetValue().getNumOfPlayers());
			team1Node->GetValue().PlayersOnTeamOrderdByStats.root = team1Node->GetValue().PlayersOnTeamOrderdByStats.Clear(team1Node->GetValue().PlayersOnTeamOrderdByStats.root);
			team1Node->GetValue().players.root = team1Node->GetValue().players.Clear(team1Node->GetValue().players.root);
			team1Node->GetValue().players.root = newPlayerTree;
			team1Node->GetValue().PlayersOnTeamOrderdByStats.root = newPlayerStatsTree;
			team1Node->GetValue().setNumOfPlayers(team1Node->GetValue().getNumOfPlayers() + team2Node->GetValue().getNumOfPlayers());
			team1Node->GetValue().setPoints(team1Node->GetValue().getPoints() + team2Node->GetValue().getPoints());
			team1Node->GetValue().setNumOfGoalKeepers(team1Node->GetValue().getNumOfGoalKeepers() + team2Node->GetValue().getNumOfGoalKeepers());
			team1Node->GetValue().setGamesTeamPlayed(team1Node->GetValue().getGamesTeamPlayed() + team2Node->GetValue().getGamesTeamPlayed());
			team1Node->GetValue().setTotalGoalsScored(team1Node->GetValue().getTotalGoalsScored() + team2Node->GetValue().getTotalGoalsScored());
			team1Node->GetValue().setTotalCards(team1Node->GetValue().getTotalCards() + team2Node->GetValue().getTotalCards());
			// team2Node->GetValue().setTeamID(-1);
			AllTeams.root = AllTeams.Remove(AllTeams.GetRoot(), team2Node->GetValue());
			nodeForLeagel = team1Node;
			//	ChangePlayersTeamId(team1Node->GetValue().players.root, teamId1);
			//	ChangePlayersTeamPointer(team1Node->GetValue().players.root, team1Node);
			// updating leagel teams tree
		}
		else if (newTeamId == teamId2) // meaning every player is going to teamid2
		{
			// ChangePlayersTeamId(team1Node->GetValue().players.root, teamId2);
			// ChangePlayersTeamPointer(team1Node->GetValue().players.root, team2Node);
			AVLNode<Player> *newPlayerTree = MergeTwoTrees(team1Node->GetValue().players.GetRoot(), team2Node->GetValue().players.GetRoot(), team1Node->GetValue().getNumOfPlayers(), team2Node->GetValue().getNumOfPlayers());
			AVLNode<PlayerStats> *newPlayerStatsTree = MergeTwoTrees(team1Node->GetValue().PlayersOnTeamOrderdByStats.GetRoot(), team2Node->GetValue().PlayersOnTeamOrderdByStats.GetRoot(), team1Node->GetValue().getNumOfPlayers(), team2Node->GetValue().getNumOfPlayers());
			team2Node->GetValue().PlayersOnTeamOrderdByStats.DeleteTree(team2Node->GetValue().PlayersOnTeamOrderdByStats.GetRoot());
			team2Node->GetValue().players.DeleteTree(team2Node->GetValue().players.GetRoot());
			team2Node->GetValue().players.root = newPlayerTree;
			team2Node->GetValue().PlayersOnTeamOrderdByStats.root = newPlayerStatsTree;
			team2Node->GetValue().setNumOfPlayers(team1Node->GetValue().getNumOfPlayers() + team2Node->GetValue().getNumOfPlayers());
			team2Node->GetValue().setPoints(team1Node->GetValue().getPoints() + team2Node->GetValue().getPoints());
			team2Node->GetValue().setNumOfGoalKeepers(team1Node->GetValue().getNumOfGoalKeepers() + team2Node->GetValue().getNumOfGoalKeepers());
			team2Node->GetValue().setGamesTeamPlayed(team1Node->GetValue().getGamesTeamPlayed() + team2Node->GetValue().getGamesTeamPlayed());
			team2Node->GetValue().setTotalGoalsScored(team1Node->GetValue().getTotalGoalsScored() + team2Node->GetValue().getTotalGoalsScored());
			team2Node->GetValue().setTotalCards(team1Node->GetValue().getTotalCards() + team2Node->GetValue().getTotalCards());
			// team2Node->GetValue().setTeamID(-1);
			AllTeams.root = AllTeams.Remove(AllTeams.GetRoot(), team1Node->GetValue());
			// ChangePlayersTeamId(team2Node->GetValue().players.root, teamId2);
			// ChangePlayersTeamPointer(team2Node->GetValue().players.root, team2Node);
			nodeForLeagel = team2Node;
		}
		else
		{
			int newPoints = team1Node->GetValue().getPoints() + team2Node->GetValue().getPoints();
			int newGamesPlayed = team1Node->GetValue().getGamesTeamPlayed() + team2Node->GetValue().getGamesTeamPlayed();
			int newGoalsScored = team1Node->GetValue().getTotalGoalsScored() + team2Node->GetValue().getTotalGoalsScored();
			int newTotalCards = team1Node->GetValue().getTotalCards() + team2Node->GetValue().getTotalCards();
			int newNumOfPlayers = team1Node->GetValue().getNumOfPlayers() + team2Node->GetValue().getNumOfPlayers();

			AVLNode<Team> *newTeamNode;
			AllTeams.root = AllTeams.Insert(AllTeams.GetRoot(), Team(newTeamId, newPoints));
			newTeamNode = findTeamById(AllTeams.GetRoot(), newTeamId);
			newTeamNode->GetValue().setGamesTeamPlayed(newGamesPlayed);
			newTeamNode->GetValue().setTotalGoalsScored(newGoalsScored);
			newTeamNode->GetValue().setTotalCards(newTotalCards);
			newTeamNode->GetValue().setNumOfPlayers(newNumOfPlayers);
			newTeamNode->GetValue().setGamesTeamPlayed(newGamesPlayed);
			newTeamNode->GetValue().setNumOfGoalKeepers(team1Node->GetValue().getNumOfGoalKeepers() + team2Node->GetValue().getNumOfGoalKeepers());
			AVLNode<Player> *newPlayerTree = MergeTwoTrees(team1Node->GetValue().players.GetRoot(), team2Node->GetValue().players.GetRoot(), team1Node->GetValue().getNumOfPlayers(), team2Node->GetValue().getNumOfPlayers());
			AVLNode<PlayerStats> *newPlayerStatsTree = MergeTwoTrees(team1Node->GetValue().PlayersOnTeamOrderdByStats.GetRoot(), team2Node->GetValue().PlayersOnTeamOrderdByStats.GetRoot(), team1Node->GetValue().getNumOfPlayers(), team2Node->GetValue().getNumOfPlayers());
			newTeamNode->GetValue().PlayersOnTeamOrderdByStats.root = newPlayerStatsTree;
			newTeamNode->GetValue().players.root = newPlayerTree;

			AllTeams.root = AllTeams.Remove(AllTeams.GetRoot(), team1Node->GetValue());
			AllTeams.root = AllTeams.Remove(AllTeams.GetRoot(), team2Node->GetValue());

			// ChangePlayersTeamId(newTeamNode->GetValue().players.root, newTeamId);
			// ChangePlayersTeamPointer(newTeamNode->GetValue().players.root, newTeamNode);
			nodeForLeagel = newTeamNode;
		}
		int totalPoints = AllTeams.find(AllTeams.root, nodeForLeagel->GetValue())->GetValue().getPoints();
		totalPoints += AllTeams.find(AllTeams.root, nodeForLeagel->GetValue())->GetValue().getTotalGoalsScored();
		totalPoints -= AllTeams.find(AllTeams.root, nodeForLeagel->GetValue())->GetValue().getTotalCards();
		leagelTeams.root = leagelTeams.Insert(leagelTeams.root, IDandTotalPoints(newTeamId, totalPoints));

		// inOrder travesrsal on both team's players tree to change to the teamId

		// inOrder traversal on Both team's Players Tress to change the pointer to the team Node

		// merging both teams players tree

		// merging both teams PlayersStats tree

		// updating the teams fields

		// updating worldCup in scenerio both team werent leagel and new team is leagel

		// deleting the the team with no Players

		// updating the number of teams in world cup
	}
	catch (std::bad_alloc &e)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	AVLNode<Team> *teamToChange = findTeamById(AllTeams.root, newTeamId);
	ChangePlayersTeamId(teamToChange->GetValue().players.root, newTeamId);
	ChangePlayersTeamPointer(teamToChange->GetValue().players.root, teamToChange);
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{

	if (teamId == 0)
	{
		return StatusType::INVALID_INPUT;
	}
	else if (teamId > 0)
	{
		AVLNode<Team> *TeamAfterSearch = findTeamById(AllTeams.GetRoot(), teamId);
		if (TeamAfterSearch == NULL || TeamAfterSearch->GetValue().getNumOfPlayers() == 0)
			return StatusType::FAILURE;
		else
		{

			return TeamAfterSearch->GetValue().getTeamTopScorerId();
		}
	}
	else
	{
		if (numberOfPlayers == 0)
			return StatusType::FAILURE;

		return topScorerId;
	}
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
	if (teamId == 0)
	{
		return StatusType::INVALID_INPUT;
	}
	if (teamId > 0 && findTeamById(AllTeams.root, teamId) == NULL)
	{
		return StatusType::FAILURE;
	}
	int allCount;
	try
	{
		if (teamId < 0)
		{
			allCount = numberOfPlayers;
		}
		else
		{
			allCount = findTeamById(AllTeams.root, teamId)->GetValue().getNumOfPlayers();
		}
	}
	catch (const std::exception &e)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	return allCount;
}

StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
	if (teamId == 0 || output == NULL)
	{
		return StatusType::INVALID_INPUT;
	}
	if (teamId > 0)
	{
		if (findTeamById(AllTeams.root, teamId) == NULL)
		{
			return StatusType::FAILURE;
		}
		int numberOfPlayersInTeam = findTeamById(AllTeams.root, teamId)->GetValue().getNumOfPlayers();
		if (numberOfPlayersInTeam == 0)
		{
			return StatusType::FAILURE;
		}
	}
	else if (teamId < 0 && numberOfPlayers == 0)
	{
		return StatusType::FAILURE;
	}
	if (teamId > 0)
	{
		AVLNode<Team> *TeamNode = findTeamById(AllTeams.root, teamId);

		int index = 0;

		InOrderPlayerStatsToArray(TeamNode->GetValue().PlayersOnTeamOrderdByStats.root, output, &index);
	}
	else
	{
		int index = 0;

		InOrderPlayerStatsToArray(ALLPayersOrderdByStats.root, output, &index);
	}
	return StatusType::SUCCESS;
}

void InOrderPlayerStatsToArray(AVLNode<PlayerStats> *root1, int *arr1, int *index)
{
	if (root1 == NULL)
	{
		return;
	}
	InOrderPlayerStatsToArray(root1->GetLeft(), arr1, index);
	arr1[*index] = root1->GetValue().getPlayerId();
	(*index)++;
	InOrderPlayerStatsToArray(root1->GetRight(), arr1, index);
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{

	if (playerId <= 0 || teamId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	AVLNode<Team> *teamNode = findTeamById(AllTeams.GetRoot(), teamId);
	if (teamNode == NULL || (teamNode->GetValue().findPlayerById(teamNode->GetValue().players.root, playerId) == NULL || numberOfPlayers == 1))
	{
		return StatusType::FAILURE;
	}
	int winner;
	try
	{
		winner = GetWinningClosestBySearcherID(teamId, playerId);
	}
	catch (const std::exception &e)
	{
		return StatusType::ALLOCATION_ERROR;
	}

	return winner;
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{

	if (minTeamId < 0 || maxTeamId < 0 || maxTeamId < minTeamId)
	{
		return StatusType::INVALID_INPUT;
	}
	int winnerId;
	LinkedList<IDandTotalPoints> KnockoutTeams;
	try
	{
		LinkedList<IDandTotalPoints> KnockoutTeams;
		ListNode<IDandTotalPoints> *tempKnockOut;
		KnockoutTeams.getValuesInRange(leagelTeams.root, minTeamId, maxTeamId);
		// std::cout << "the knockout list   " << KnockoutTeams << std::endl;

		if (KnockoutTeams.IsEmpty())
		{
			return StatusType::FAILURE;
		}

		while (KnockoutTeams.GetHead()->GetNext() != NULL)
		{
			tempKnockOut = KnockoutTeams.GetHead();
			int MatchWinnerId;
			int MatchWinnerPoints;
			while (tempKnockOut != NULL && tempKnockOut->GetNext() != NULL)
			{
				ListNode<IDandTotalPoints> *toBeDeleted;
				if (tempKnockOut->GetValue().getTotalPoints() > tempKnockOut->GetNext()->GetValue().getTotalPoints())
				{
					MatchWinnerId = tempKnockOut->GetValue().getId();
					MatchWinnerPoints = tempKnockOut->GetValue().getTotalPoints() + tempKnockOut->GetNext()->GetValue().getTotalPoints();
					tempKnockOut->SetValue(IDandTotalPoints(MatchWinnerId, MatchWinnerPoints));
					toBeDeleted = tempKnockOut->GetNext();
					tempKnockOut->SetNext(tempKnockOut->GetNext()->GetNext());
					delete toBeDeleted;
					tempKnockOut = tempKnockOut->GetNext();
				}
				else if (tempKnockOut->GetValue().getTotalPoints() < tempKnockOut->GetNext()->GetValue().getTotalPoints())
				{
					MatchWinnerId = tempKnockOut->GetNext()->GetValue().getId();
					MatchWinnerPoints = tempKnockOut->GetValue().getTotalPoints() + tempKnockOut->GetNext()->GetValue().getTotalPoints();
					tempKnockOut->SetValue(IDandTotalPoints(MatchWinnerId, MatchWinnerPoints));
					toBeDeleted = tempKnockOut->GetNext();
					tempKnockOut->SetNext(tempKnockOut->GetNext()->GetNext());
					delete toBeDeleted;
					tempKnockOut = tempKnockOut->GetNext();
				}
				else
				{
					MatchWinnerId = tempKnockOut->GetNext()->GetValue().getId() > tempKnockOut->GetValue().getId() ? tempKnockOut->GetNext()->GetValue().getId() : tempKnockOut->GetValue().getId();
					MatchWinnerPoints = tempKnockOut->GetValue().getTotalPoints() + tempKnockOut->GetNext()->GetValue().getTotalPoints();
					tempKnockOut->SetValue(IDandTotalPoints(MatchWinnerId, MatchWinnerPoints));
					toBeDeleted = tempKnockOut->GetNext();
					tempKnockOut->SetNext(tempKnockOut->GetNext()->GetNext());
					delete toBeDeleted;
					tempKnockOut = tempKnockOut->GetNext();
				}
			}
		}
		winnerId = KnockoutTeams.GetHead()->GetValue().getId();
		// std::cout << KnockoutTeams << " this is the knockout winner" << std::endl;
	}
	catch (const std::exception &e)
	{
		return StatusType::ALLOCATION_ERROR;
	}

	// TODO: Your code goes here

	return winnerId;
}

AVLNode<Team> *findTeamById(AVLNode<Team> *node, int teamId)
{
	if (node == NULL)
	{
		return NULL;
	}
	if (node->GetValue().getId() == teamId)
	{
		return node;
	}
	if (node->GetValue().getId() > teamId)
	{
		return findTeamById(node->GetLeft(), teamId);
	}
	else
	{
		return findTeamById(node->GetRight(), teamId);
	}
}
AVLNode<Player> *findPlayerById(AVLNode<Player> *node, int playerId)
{
	if (node == NULL)
	{
		return NULL;
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
bool isLeagelTeam(AVLNode<Team> *node)
{
	if (node->GetValue().getNumOfGoalKeepers() > 0 && node->GetValue().getNumOfPlayers() >= 11)
	{
		return true;
	}
	return false;
}

void ClosestDiffFromLeft(AVLNode<PlayerStats> *node, PlayerStats &searcher, PlayerStats &minDiffcurrent)
{

	if (node == NULL)
	{
		return;
	}

	if (node->GetValue() < searcher && node->GetValue() > minDiffcurrent)
	{
		minDiffcurrent = node->GetValue();
	}

	if (node->GetValue().getPlayerId() == searcher.getPlayerId())
	{
		return ClosestDiffFromLeft(node->GetLeft(), searcher, minDiffcurrent);
	}
	if (searcher < node->GetValue())
	{
		ClosestDiffFromLeft(node->GetLeft(), searcher, minDiffcurrent);
	}
	else
	{
		ClosestDiffFromLeft(node->GetRight(), searcher, minDiffcurrent);
	}
}
int ClosestDiffFromLeftWrapper(AVLNode<PlayerStats> *node, PlayerStats &searcher)
{
	if (node == NULL)
	{
		return -1;
	}

	PlayerStats minDiffcurrent = PlayerStats(-1, -1, 0);
	ClosestDiffFromLeft(node, searcher, minDiffcurrent);
	return minDiffcurrent.getPlayerId();
}

void ClosestDifffromRight(AVLNode<PlayerStats> *node, PlayerStats &searcher, PlayerStats &minDiffcurrent)
{

	if (node == NULL)
	{
		return;
	}

	if (node->GetValue() > searcher && node->GetValue() < minDiffcurrent)
	{
		minDiffcurrent = node->GetValue();
	}

	if (node->GetValue().getPlayerId() == searcher.getPlayerId())
	{
		return ClosestDifffromRight(node->GetRight(), searcher, minDiffcurrent);
	}
	if (searcher < node->GetValue())
	{
		ClosestDifffromRight(node->GetLeft(), searcher, minDiffcurrent);
	}
	else
	{
		ClosestDifffromRight(node->GetRight(), searcher, minDiffcurrent);
	}
}
int world_cup_t::ClosestDiffFromRightWrapper(AVLNode<PlayerStats> *node, PlayerStats &searcher)
{
	if (node == NULL)
	{
		return -1;
	}

	PlayerStats minDiffcurrent = PlayerStats(-1, topScorerGoals + 1, topScorerCards);
	ClosestDifffromRight(node, searcher, minDiffcurrent);
	return minDiffcurrent.getPlayerId();
}

void world_cup_t::updateClosest(int ToBeUpdatedID)
{
	if (ToBeUpdatedID > 0)
	{
		PlayerStats ToBeUpdatedStats;
		AVLNode<Player> *ToBeUpdatedNode = findPlayerById(AllPlayers.GetRoot(), ToBeUpdatedID);
		if (ToBeUpdatedNode != NULL)
		{
			AVLNode<Team> *TheTeamOfThePlayerNode = ToBeUpdatedNode->GetValue().getPointerToTeamAvlNode();
			ToBeUpdatedStats = PlayerStats(ToBeUpdatedNode->GetValue().getPlayerId(), ToBeUpdatedNode->GetValue().getGoals(), ToBeUpdatedNode->GetValue().getCards());
			AVLNode<PlayerStats> *ThePlayerStatsNode = ALLPayersOrderdByStats.find(ALLPayersOrderdByStats.root, ToBeUpdatedStats);
			if (ThePlayerStatsNode != NULL)
			{
				int closestFromTeamLeftId = ClosestDiffFromLeftWrapper(TheTeamOfThePlayerNode->GetValue().PlayersOnTeamOrderdByStats.GetRoot(), ToBeUpdatedStats);
				int closestFromTeamRightId = ClosestDiffFromRightWrapper(TheTeamOfThePlayerNode->GetValue().PlayersOnTeamOrderdByStats.GetRoot(), ToBeUpdatedStats);
				int closestFromAllLeftId = ClosestDiffFromLeftWrapper(ALLPayersOrderdByStats.GetRoot(), ToBeUpdatedStats);
				int closestFromAllRightId = ClosestDiffFromRightWrapper(ALLPayersOrderdByStats.GetRoot(), ToBeUpdatedStats);

				ThePlayerStatsNode->GetValue().setClosestFromTeamLeftID(closestFromTeamLeftId);
				ThePlayerStatsNode->GetValue().setClosestFromTeamRightID(closestFromTeamRightId);
				ThePlayerStatsNode->GetValue().setClosestFromAllLeftID(closestFromAllLeftId);
				ThePlayerStatsNode->GetValue().setClosestFromAllRightID(closestFromAllRightId);
			}
		}
		/*
		ToBeUpdatedNode->GetValue().getpointerToPlayerStatsAvlNodeONAllPlayers()->GetValue().setClosestFromAllLeftID(closestFromAllLeftId);
		ToBeUpdatedNode->GetValue().getpointerToPlayerStatsAvlNodeONAllPlayers()->GetValue().setClosestFromAllRightID(closestFromAllRightId);
		ToBeUpdatedNode->GetValue().getpointerToPlayerStatsAvlNodeONAllPlayers()->GetValue().setClosestFromTeamLeftID(closestFromTeamLeftId);
		ToBeUpdatedNode->GetValue().getpointerToPlayerStatsAvlNodeONAllPlayers()->GetValue().setClosestFromTeamRightID(closestFromTeamRightId);
		*/
	}
}
void world_cup_t::printTeam(int teamId)
{
	std::cout << "Printing all Players tree" << std::endl;
	// AllPlayers.PrintInOrder(AllPlayers.GetRoot());
	printBTs(AllPlayers.GetRoot());

	std::cout << "Printing all Players by stats tree" << std::endl;
	// ALLPayersOrderdByStats.PrintInOrder(ALLPayersOrderdByStats.GetRoot());
	printBTs(ALLPayersOrderdByStats.GetRoot());

	std::cout << "Printing all Teams tree" << std::endl;
	// AllTeams.PrintInOrder(AllTeams.GetRoot());
	printBTs(AllTeams.GetRoot());

	std::cout << "Printing the given " << teamId << " team players tree" << std::endl;
	AVLNode<Team> *TheTeamNode = findTeamById(AllTeams.GetRoot(), teamId);
	// TheTeamNode->GetValue().players.PrintInOrder(TheTeamNode->GetValue().players.GetRoot());
	printBTs(TheTeamNode->GetValue().players.GetRoot());

	std::cout << "Printing the given " << teamId << " team players by stats tree" << std::endl;
	// TheTeamNode->GetValue().PlayersOnTeamOrderdByStats.PrintInOrder(TheTeamNode->GetValue().PlayersOnTeamOrderdByStats.GetRoot());
	printBTs(TheTeamNode->GetValue().PlayersOnTeamOrderdByStats.GetRoot());

	std::cout << " Printing legeal team" << std::endl;
	printBTs(leagelTeams.GetRoot());
}

template <class T>
void printBT(const std::string &prefix, const AVLNode<T> *node, bool isLeft)
{
	if (node != NULL)
	{
		std::cout << prefix;

		std::cout << (isLeft ? "├──" : "└──");

		// print the value of the node
		std::cout << node->GetValue() << std::endl;

		// enter the next tree level - left and right branch
		printBT(prefix + (isLeft ? "│   " : "    "), node->GetLeft(), true);
		printBT(prefix + (isLeft ? "│   " : "    "), node->GetRight(), false);
	}
}
template <class T>
void printBTs(const AVLNode<T> *node)
{
	printBT("", node, false);
}

int world_cup_t::GetWinningClosestBySearcherID(int TeamId, int Playerid)
{
	AVLNode<Team> *TeamNode = findTeamById(AllTeams.GetRoot(), TeamId);
	AVLNode<Player> *searcherPlayerNode = TeamNode->GetValue().findPlayerById(TeamNode->GetValue().players.root, Playerid);
	AVLNode<PlayerStats> *searcher = searcherPlayerNode->GetValue().getpointerToPlayerStatsAvlNodeONAllPlayers();
	int leftId = searcher->GetValue().getClosestFromAllLeftID();
	int rightId = searcher->GetValue().getClosestFromAllRightID();
	PlayerStats playerSt = searcher->GetValue();
	if (leftId == -1 || findPlayerById(AllPlayers.GetRoot(), leftId) == NULL)
	{
		return rightId;
	}
	if (rightId == -1 || findPlayerById(AllPlayers.GetRoot(), rightId) == NULL)
	{
		return leftId;
	}
	/*
	AVLNode<Player> *leftPlayer = findPlayerById(AllPlayers.GetRoot(), leftID);
	AVLNode<Player> *rightPlayer = findPlayerById(AllPlayers.GetRoot(), rightID);
	if (leftPlayer==NULL || leftPlayer->GetValue().getpointerToPlayerStatsAvlNodeONAllPlayers()==NULL)
	{
		return rightID;
	}
	else if (rightPlayer == NULL || rightPlayer->GetValue().getpointerToPlayerStatsAvlNodeONAllPlayers() == NULL)
	{
		return leftID;
	}
	*/
	PlayerStats leftPlayerStats = findPlayerById(AllPlayers.GetRoot(), leftId)->GetValue().getpointerToPlayerStatsAvlNodeONAllPlayers()->GetValue();
	PlayerStats rightPlayerStats = findPlayerById(AllPlayers.GetRoot(), rightId)->GetValue().getpointerToPlayerStatsAvlNodeONAllPlayers()->GetValue();
	if (abs(leftPlayerStats.getGoals() - playerSt.getGoals()) < abs(rightPlayerStats.getGoals() - playerSt.getGoals()))
	{
		return leftId;
	}
	else if (abs(leftPlayerStats.getGoals() - playerSt.getGoals()) > abs(rightPlayerStats.getGoals() - playerSt.getGoals()))
	{
		return rightId;
	}
	else
	{
		if (abs(leftPlayerStats.getCards() - playerSt.getCards()) < abs(rightPlayerStats.getCards() - playerSt.getCards()))
		{
			return leftId;
		}
		else if (abs(leftPlayerStats.getCards() - playerSt.getCards()) > abs(rightPlayerStats.getCards() - playerSt.getCards()))
		{
			return rightId;
		}

		else
		{
			if (abs(leftPlayerStats.getPlayerId() - playerSt.getPlayerId()) < abs(rightPlayerStats.getPlayerId() - playerSt.getPlayerId()))
			{
				return leftId;
			}
			else if (abs(leftPlayerStats.getPlayerId() - playerSt.getPlayerId()) > abs(rightPlayerStats.getPlayerId() - playerSt.getPlayerId()))
			{
				return rightId;
			}
			else
			{
				if (leftPlayerStats.getPlayerId() < rightPlayerStats.getPlayerId())
				{
					return rightId;
				}
			}
		}

		return -1;
	}

	// return MatchTheWinningClosest(playerSt, leftId, rightId);
}

int world_cup_t::MatchTheWinningClosest(PlayerStats &searcher, int leftID, int rightID)
{
	if (leftID == -1)
	{
		return rightID;
	}
	if (rightID == -1)
	{
		return leftID;
	}
	/*
	AVLNode<Player> *leftPlayer = findPlayerById(AllPlayers.GetRoot(), leftID);
	AVLNode<Player> *rightPlayer = findPlayerById(AllPlayers.GetRoot(), rightID);
	if (leftPlayer==NULL || leftPlayer->GetValue().getpointerToPlayerStatsAvlNodeONAllPlayers()==NULL)
	{
		return rightID;
	}
	else if (rightPlayer == NULL || rightPlayer->GetValue().getpointerToPlayerStatsAvlNodeONAllPlayers() == NULL)
	{
		return leftID;
	}
	*/
	PlayerStats leftPlayerStats = findPlayerById(AllPlayers.GetRoot(), leftID)->GetValue().getpointerToPlayerStatsAvlNodeONAllPlayers()->GetValue();
	PlayerStats rightPlayerStats = findPlayerById(AllPlayers.GetRoot(), rightID)->GetValue().getpointerToPlayerStatsAvlNodeONAllPlayers()->GetValue();
	if (abs(leftPlayerStats.getGoals() - searcher.getGoals()) < abs(rightPlayerStats.getGoals() - searcher.getGoals()))
	{
		return leftID;
	}
	else if (abs(leftPlayerStats.getGoals() - searcher.getGoals()) > abs(rightPlayerStats.getGoals() - searcher.getGoals()))
	{
		return rightID;
	}
	else
	{
		if (abs(leftPlayerStats.getCards() - searcher.getCards()) < abs(rightPlayerStats.getCards() - searcher.getCards()))
		{
			return leftID;
		}
		else if (abs(leftPlayerStats.getCards() - searcher.getCards()) > abs(rightPlayerStats.getCards() - searcher.getCards()))
		{
			return rightID;
		}

		else
		{
			if (abs(leftPlayerStats.getPlayerId() - searcher.getPlayerId()) < abs(rightPlayerStats.getPlayerId() - searcher.getPlayerId()))
			{
				return leftID;
			}
			else if (abs(leftPlayerStats.getPlayerId() - searcher.getPlayerId()) > abs(rightPlayerStats.getPlayerId() - searcher.getPlayerId()))
			{
				return rightID;
			}
			else
			{
				if (leftPlayerStats.getPlayerId() < rightPlayerStats.getPlayerId())
				{
					return rightID;
				}
			}
		}

		return -1;
	}
}

AVLNode<PlayerStats> *world_cup_t::findPlayerStatsByStats(AVLNode<PlayerStats> *node, PlayerStats &playerStats)
{
	if (node == NULL)
	{
		return NULL;
	}
	if (node->GetValue().getPlayerId() == playerStats.getPlayerId())
	{
		return node;
	}
	else if (playerStats < node->GetValue())
	{
		return findPlayerStatsByStats(node->GetLeft(), playerStats);
	}
	else
	{
		return findPlayerStatsByStats(node->GetRight(), playerStats);
	}
}
void world_cup_t::printInOrderAllPlayerStats()
{
	ALLPayersOrderdByStats.PrintInOrder(ALLPayersOrderdByStats.GetRoot());
}

void world_cup_t::ChangePlayersTeamId(AVLNode<Player> *node, int newTeamId)
{
	if (node == NULL)
	{
		return;
	}
	ChangePlayersTeamId(node->GetLeft(), newTeamId);
	node->GetValue().setPointerToAllPlayerAvlNode(findPlayerById(AllPlayers.GetRoot(), node->GetValue().getPlayerId()));
	node->GetValue().getPointerToAllPlayerAvlNode()->GetValue().setTeamId(newTeamId);
	node->GetValue().setTeamId(newTeamId);
	ChangePlayersTeamId(node->GetRight(), newTeamId);
}
void world_cup_t::ChangePlayersTeamPointer(AVLNode<Player> *node, AVLNode<Team> *newTeamNode)
{
	if (node == NULL)
	{
		return;
	}
	ChangePlayersTeamPointer(node->GetLeft(), newTeamNode);
	node->GetValue().setPointerToAllPlayerAvlNode(findPlayerById(AllPlayers.GetRoot(), node->GetValue().getPlayerId()));
	node->GetValue().getPointerToAllPlayerAvlNode()->GetValue().setPointerToTeam(newTeamNode);
	node->GetValue().setPointerToTeam(newTeamNode);
	ChangePlayersTeamPointer(node->GetRight(), newTeamNode);
}

AVLNode<Player> *MergeTwoTrees(AVLNode<Player> *root1, AVLNode<Player> *root2, int FirstTreesSize, int SecondTreeSize)
{
	Player *arr1 = new Player[FirstTreesSize];
	int index1 = 0;
	InOrderTreeToArray(root1, arr1, &index1);

	Player *arr2 = new Player[SecondTreeSize];
	int index2 = 0;
	InOrderTreeToArray(root2, arr2, &index2);

	Player *arr3 = MergeTwoArrays(arr1, arr2, FirstTreesSize, SecondTreeSize);
	delete[] arr1;
	delete[] arr2;
	AVLNode<Player> *newTree = SortedArrayToTree(arr3, 0, FirstTreesSize + SecondTreeSize - 1);
	delete[] arr3;
	return newTree;
}

void InOrderTreeToArray(AVLNode<Player> *root1, Player *arr1, int *index)
{
	if (root1 == NULL)
	{
		return;
	}
	InOrderTreeToArray(root1->GetLeft(), arr1, index);

	arr1[*index] = root1->GetValue();
	(*index)++;
	InOrderTreeToArray(root1->GetRight(), arr1, index);
}

Player *MergeTwoArrays(Player *arr1, Player *arr2, int size1, int size2)
{
	Player *arr3 = new Player[size1 + size2];
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < size1 && j < size2)
	{
		if (arr1[i] < arr2[j])
		{
			arr3[k] = arr1[i];
			i++;
			;
		}
		else
		{
			arr3[k] = arr2[j];
			j++;
		}
		k++;
	}
	while (i < size1)
	{
		arr3[k] = arr1[i];
		i++;
		k++;
	}
	while (j < size2)
	{
		arr3[k] = arr2[j];
		j++;
		k++;
	}
	return arr3;
}

AVLNode<Player> *SortedArrayToTree(Player *sortedArr, int start, int end)
{
	if (start > end)
	{
		return NULL;
	}
	int mid = (start + end) / 2;
	AVLNode<Player> *root1 = new AVLNode<Player>((sortedArr[mid]));
	root1->SetValue(sortedArr[mid]);
	root1->SetLeft(SortedArrayToTree(sortedArr, start, mid - 1));
	root1->SetRight(SortedArrayToTree(sortedArr, mid + 1, end));

	return root1;
}
bool world_cup_t::isInLeagelTeamsTree(int teamId)
{
	if (leagelTeams.find(leagelTeams.root, IDandTotalPoints(teamId, 0)) == NULL)
	{
		return false;
	}
	return true;
}

AVLNode<PlayerStats> *MergeTwoTrees(AVLNode<PlayerStats> *root1, AVLNode<PlayerStats> *root2, int FirstTreesSize, int SecondTreeSize)
{
	PlayerStats *arr1 = new PlayerStats[FirstTreesSize];
	int index1 = 0;
	InOrderTreeToArray(root1, arr1, &index1);

	PlayerStats *arr2 = new PlayerStats[SecondTreeSize];
	int index2 = 0;
	InOrderTreeToArray(root2, arr2, &index2);

	PlayerStats *arr3 = MergeTwoArrays(arr1, arr2, FirstTreesSize, SecondTreeSize);
	delete[] arr1;
	delete[] arr2;
	AVLNode<PlayerStats> *newTree = SortedArrayToTree(arr3, 0, FirstTreesSize + SecondTreeSize - 1);
	delete[] arr3;
	return newTree;
}

void InOrderTreeToArray(AVLNode<PlayerStats> *root1, PlayerStats *arr1, int *index)
{
	if (root1 == NULL)
	{
		return;
	}
	InOrderTreeToArray(root1->GetLeft(), arr1, index);

	arr1[*index] = root1->GetValue();
	(*index)++;
	InOrderTreeToArray(root1->GetRight(), arr1, index);
}

PlayerStats *MergeTwoArrays(PlayerStats *arr1, PlayerStats *arr2, int size1, int size2)
{
	PlayerStats *arr3 = new PlayerStats[size1 + size2];
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < size1 && j < size2)
	{
		if (arr1[i] < arr2[j])
		{
			arr3[k] = arr1[i];
			i++;
			;
		}
		else
		{
			arr3[k] = arr2[j];
			j++;
		}
		k++;
	}
	while (i < size1)
	{
		arr3[k] = arr1[i];
		i++;
		k++;
	}
	while (j < size2)
	{
		arr3[k] = arr2[j];
		j++;
		k++;
	}
	return arr3;
}

AVLNode<PlayerStats> *SortedArrayToTree(PlayerStats *sortedArr, int start, int end)
{
	if (start > end)
	{
		return NULL;
	}
	int mid = (start + end) / 2;
	AVLNode<PlayerStats> *root1 = new AVLNode<PlayerStats>((sortedArr[mid]));
	root1->SetValue(sortedArr[mid]);
	root1->SetLeft(SortedArrayToTree(sortedArr, start, mid - 1));
	root1->SetRight(SortedArrayToTree(sortedArr, mid + 1, end));

	return root1;
}