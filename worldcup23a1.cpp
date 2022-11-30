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
	std::cout << "team added" << std::endl;
	AllTeams.PrintInOrder(AllTeams.GetRoot());
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
	numberOfTeams--;
	if (isLeagelTeam(TeamAfterSearch))
	{
		numberOfLeagelTeams--;
	}
	std::cout << "team removed" << std::endl;
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
	if (TheTeamOfThePlayerNode == nullptr || findPlayerById(AllPlayers.GetRoot(), playerId) != nullptr)
	{
		return StatusType::FAILURE;
	}

	// creating the player and his stats
	Player newPlayer;
	PlayerStats newPlayerStats;
	try
	{
		newPlayer = Player(playerId, teamId, gamesPlayed, goals, cards, goalKeeper);
		newPlayerStats = PlayerStats(playerId, goals, cards);
	}

	catch (std::bad_alloc &e)
	{
		return StatusType::ALLOCATION_ERROR;
	}

	//updating top scorer
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
	// creating the node of the player thats going to be added to the tree of players held by the team
	AVLNode<Player> *PlayerNodeOnTeamPlayersTree;
	// setting the player node to point on the team node in the tree of teams
	newPlayer.setPointerToTeam(TheTeamOfThePlayerNode); // o(1)

	newPlayer.setGamesTeamPlayedBefore(TheTeamOfThePlayerNode->GetValue().getGamesTeamPlayed()); // o(1)

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

	newPlayer.SetpointerToPlayerStatsAvlNodeONTeam(TheTeamOfThePlayerNode->GetValue().InsertPlayerToTeamStatsTree(newPlayerStats)); // o(logn)
	// setting the pointer held by the player instance to the player stats tree
	ALLPayersOrderdByStats.root=ALLPayersOrderdByStats.Insert(ALLPayersOrderdByStats.GetRoot(), newPlayerStats);
	newPlayer.setpointerToPlayerStatsAvlNodeONAllPlayers(findPlayerStatsByStats(ALLPayersOrderdByStats.GetRoot(), newPlayerStats));

	// updating the left and right closets from both all players and team players stats
	updateClosest(closestFromAllLeftId);
	updateClosest(closestFromAllRightId);
	updateClosest(closestFromTeamLeftId);
	updateClosest(closestFromAllRightId);

	// adding player  to players tree held by its team
	PlayerNodeOnTeamPlayersTree = TheTeamOfThePlayerNode->GetValue().InsertPlayerToTeam(newPlayer);

	// adding player to All players tree held by worldCup
	AllPlayers.root = AllPlayers.Insert(AllPlayers.GetRoot(), newPlayer);

	// still needs to link between the avlnode on all players tree to the avlnode on the team tree and the avl node on players by stats tree

	// adding player to All players_ordered_by_stats
	PlayerNodeOnTeamPlayersTree->GetValue().setpointerToPlayerStatsAvlNodeONAllPlayers(ALLPayersOrderdByStats.find(ALLPayersOrderdByStats.GetRoot(), newPlayerStats));

	
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

	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{/*
	// TODO: Your code goes here
	if (playerId <= 0)
		return StatusType::INVALID_INPUT;
	player = findPlayerById(AllPlayers.GetRoot(), playerId);
	if (player == nullptr)
		return StatusType::FAILURE;
	try
	{
		// remove code is in the destructor
		delete player
	}
	catch (std::bad_alloc &e)
	{
		return StatusType::ALLOCATION_ERROR;
	}

	numberOfPlayers--;
*/
	return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
											int scoredGoals, int cardsReceived)
{

	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
	// TODO: Your code goes here
	return 22;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
	return 30003;
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
	// TODO: Your code goes here
	return 2008;
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
	// TODO: Your code goes here
	static int i = 0;
	return (i++ == 0) ? 11 : 2;
}

StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
	// TODO: Your code goes here
	output[0] = 4001;
	output[1] = 4002;
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
	// TODO: Your code goes here
	return 1006;
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
	// TODO: Your code goes here
	return 2;
}

AVLNode<Team> *findTeamById(AVLNode<Team> *node, int teamId)
{
	if (node == NULL)
	{
		return nullptr;
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

	if (node == nullptr)
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
	if (node == nullptr)
	{
		return -1;
	}

	PlayerStats minDiffcurrent = PlayerStats(-1, -1, 0);
	ClosestDiffFromLeft(node, searcher, minDiffcurrent);
	return minDiffcurrent.getPlayerId();
}

void ClosestDifffromRight(AVLNode<PlayerStats> *node, PlayerStats &searcher, PlayerStats &minDiffcurrent)
{

	if (node == nullptr)
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
	if (node == nullptr)
	{
		return -1;
	}

	PlayerStats minDiffcurrent = PlayerStats(-1, topScorerGoals+1, topScorerCards);
	ClosestDifffromRight(node, searcher, minDiffcurrent);
	return minDiffcurrent.getPlayerId();
}

void world_cup_t::updateClosest(int ToBeUpdatedID)
{
	if (ToBeUpdatedID > 0)
	{
		PlayerStats ToBeUpdatedStats;
		AVLNode<Player> *ToBeUpdatedNode = findPlayerById(AllPlayers.GetRoot(), ToBeUpdatedID);
		AVLNode<Team> *TheTeamOfThePlayerNode = ToBeUpdatedNode->GetValue().getPointerToTeamAvlNode();
		ToBeUpdatedStats = PlayerStats(ToBeUpdatedNode->GetValue().getPlayerId(), ToBeUpdatedNode->GetValue().getGoals(), ToBeUpdatedNode->GetValue().getCards());
		int closestFromTeamLeftId = ClosestDiffFromLeftWrapper(TheTeamOfThePlayerNode->GetValue().PlayersOnTeamOrderdByStats.GetRoot(), ToBeUpdatedStats);
		int closestFromTeamRightId = ClosestDiffFromRightWrapper(TheTeamOfThePlayerNode->GetValue().PlayersOnTeamOrderdByStats.GetRoot(), ToBeUpdatedStats);
		int closestFromAllLeftId = ClosestDiffFromLeftWrapper(ALLPayersOrderdByStats.GetRoot(), ToBeUpdatedStats);
		int closestFromAllRightId = ClosestDiffFromRightWrapper(ALLPayersOrderdByStats.GetRoot(), ToBeUpdatedStats);
		ToBeUpdatedNode->GetValue().getpointerToPlayerStatsAvlNodeONAllPlayers()->GetValue().setClosestFromAllLeftID(closestFromAllLeftId);
		ToBeUpdatedNode->GetValue().getpointerToPlayerStatsAvlNodeONAllPlayers()->GetValue().setClosestFromAllRightID(closestFromAllRightId);
		ToBeUpdatedNode->GetValue().getpointerToPlayerStatsAvlNodeONAllPlayers()->GetValue().setClosestFromTeamLeftID(closestFromTeamLeftId);
		ToBeUpdatedNode->GetValue().getpointerToPlayerStatsAvlNodeONAllPlayers()->GetValue().setClosestFromTeamRightID(closestFromTeamRightId);
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
}

template <class T>
void printBT(const std::string &prefix, const AVLNode<T> *node, bool isLeft)
{
	if (node != nullptr)
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

int world_cup_t::GetWinningClosestBySearcherID(int id)
{
	AVLNode<Player> *searcherPlayerNode = findPlayerById(AllPlayers.GetRoot(), id);
	AVLNode<PlayerStats> *searcher = searcherPlayerNode->GetValue().getpointerToPlayerStatsAvlNodeONAllPlayers();
	
	return MatchTheWinningClosest(searcher->GetValue(), searcher->GetValue().getClosestFromAllLeftID(),searcher->GetValue().getClosestFromAllRightID()); 
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
	PlayerStats leftPlayerStats = findPlayerById(AllPlayers.GetRoot(), leftID)->GetValue().getpointerToPlayerStatsAvlNodeONAllPlayers()->GetValue();
	PlayerStats rightPlayerStats = findPlayerById(AllPlayers.GetRoot(), rightID)->GetValue().getpointerToPlayerStatsAvlNodeONAllPlayers()->GetValue();
	if (abs(leftPlayerStats.getGoals()-searcher.getGoals()) < abs(rightPlayerStats.getGoals()-searcher.getGoals()))
	{
		return leftID;
	}
	else if (abs(leftPlayerStats.getGoals()-searcher.getGoals()) > abs(rightPlayerStats.getGoals()-searcher.getGoals()))
	{
		return rightID;
	}
	else
	{
		if (abs(leftPlayerStats.getCards()-searcher.getCards()) < abs(rightPlayerStats.getCards()-searcher.getCards()))
		{
			return leftID;
		}
		else if (abs(leftPlayerStats.getCards()-searcher.getCards()) > abs(rightPlayerStats.getCards()-searcher.getCards()))
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
	if (node==nullptr)
	{
		return nullptr;
	}
	if (node->GetValue().getPlayerId()==playerStats.getPlayerId())
	{
		return node;
	}
	else if (playerStats<node->GetValue())
	{
		return findPlayerStatsByStats(node->GetLeft(), playerStats);
	}
	else
	{
		return findPlayerStatsByStats(node->GetRight(), playerStats);
	}
}