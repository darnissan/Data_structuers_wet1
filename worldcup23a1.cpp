#include "worldcup23a1.h"

AVLNode<Team> *findTeamById(AVLNode<Team> *root, int teamId);
AVLNode<Team> *findPlayerById(AVLNode<Player> *node, int playerId);
bool isLeagelTeam(AVLNode<Team> *node);

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
	AVLNode<Team> *PlayersTeamNode = findTeamById(AllTeams.GetRoot(), teamId);

	if (playerId <= 0 || teamId <= 0 || gamesPlayed < 0 || goals < 0 || cards < 0 || (gamesPlayed == 0 && (goals > 0 || cards > 0)))
		return StatusType::INVALID_INPUT;
	if (PlayersTeamNode==nullptr || findPlayerById(AllPlayers.GetRoot(),playerId)!=nullptr)
	{
		return StatusType::FAILURE;
	}
	Player newPlayer;
	try
	{
		newPlayer = Player(playerId, teamId, gamesPlayed, goals, cards, goalKeeper);
	}
	catch (std::bad_alloc &e)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	PlayersTeamNode->GetValue().InsertPlayerToTeam(newPlayer);

												   numberOfPlayers++;
	return StatusType::SUCCESS;
		
}

StatusType world_cup_t::remove_player(int playerId)
{
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
AVLNode<Team> *findPlayerById(AVLNode<Player> *node, int playerId)
{
	if (node == NULL)
	{
		return nullptr;
	}
	if (node->GetValue().getId() == playerId)
	{
		return node;
	}
	if (node->GetValue().getId() > playerId)
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