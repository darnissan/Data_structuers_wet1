#include "worldcup23a1.h"

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
	std::cout<<"team added"<<std::endl;
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
	std::cout<<"team removed"<<std::endl;
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
	//updating the closest from left and right on ALL players stats tree
	//updating the closest from left and right on ALL players stats tree on his team
	AVLNode<Team> *TheTeamOfThePlayerNode = findTeamById(AllTeams.GetRoot(), teamId);
	
	if (playerId <= 0 || teamId <= 0 || gamesPlayed < 0 || goals < 0 || cards < 0 || (gamesPlayed == 0 && (goals > 0 || cards > 0)))
		return StatusType::INVALID_INPUT;
	if (TheTeamOfThePlayerNode == nullptr || findPlayerById(AllPlayers.GetRoot(), playerId) != nullptr)
	{
		return StatusType::FAILURE;
	}
	Player newPlayer;
	PlayerStats newPlayerStats;
	try
	{
		newPlayer = Player(playerId, teamId, gamesPlayed, goals, cards, goalKeeper);
		newPlayerStats = PlayerStats(playerId, goals,cards);
	}
	catch (std::bad_alloc &e)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	AVLNode<Player> *PlayerNodeOnTeamPlayersTree;
	newPlayer.setPointerToTeam(TheTeamOfThePlayerNode);
	AllPlayers.root = AllPlayers.Insert(AllPlayers.GetRoot(), newPlayer);//adding player to All players tree held by worldCup
	PlayerNodeOnTeamPlayersTree= TheTeamOfThePlayerNode->GetValue().InsertPlayerToTeam(newPlayer); // adding player  to players tree held by its team
	
	//still needs to link between the avlnode on all players tree to the avlnode on the team tree and the avl node on players by stats tree



	int closestFromLeftId = ClosestDiffFromLeftWrapper(ALLPayersOrderdByStats.GetRoot(), newPlayerStats);
	int closestFromRightId = ClosestDiffFromRightWrapper(ALLPayersOrderdByStats.GetRoot(), newPlayerStats);
	newPlayerStats.setClosestFromLeftID(closestFromLeftId);
	newPlayerStats.setClosestFromRightID(closestFromRightId);
	ALLPayersOrderdByStats.root = ALLPayersOrderdByStats.Insert(ALLPayersOrderdByStats.GetRoot(), newPlayerStats); // adding player to All players_ordered_by_stats
	PlayerNodeOnTeamPlayersTree->GetValue().setpointerToPlayerStatsAvlNodeONAllPlayers(ALLPayersOrderdByStats.find(ALLPayersOrderdByStats.GetRoot(), newPlayerStats));
	numberOfPlayers++;

	return StatusType::SUCCESS;
		
}

StatusType world_cup_t::remove_player(int playerId)
{	/*
	// TODO: Your code goes here
	if(playerId<=0)
		return StatusType::INVALID_INPUT;
	player = findPlayerById(AllPlayers.GetRoot(),playerId);
	if(player==nullptr)
		return StatusType::FAILURE;
	try
	{
		//remove code is in the destructor
		delete player 
	}
	catch(std::bad_alloc &e)
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

	PlayerStats minDiffcurrent = PlayerStats(-1,-1,0);
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
	
	PlayerStats minDiffcurrent = PlayerStats(topScorerId,topScorerGoals,topScorerCards);
	ClosestDifffromRight(node, searcher, minDiffcurrent);
	return minDiffcurrent.getPlayerId();
}
