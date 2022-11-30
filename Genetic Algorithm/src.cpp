#include<iostream>
#include <vector>
#include <algorithm>

using namespace std;

void genetic_algorithm(vector <vector <int>>& chromosomes);
vector <int> generate_chromosome();
void generate_chromosomes(vector <vector <int>>& chromosomes);
void cross_over(vector <vector <int>>& chromosomes, vector <vector <int>>& children);
void mutation(vector <vector <int>>& children);
void selection(vector <vector <int>>& chromosomes, vector <vector <int>>& children);
int fitness(const vector <int>& chromosome);
bool check_status_of_chromosome(int r, int c, const vector <int>& chromosome);
void print_final_chromosome(const vector <int>& chromosome);

#define NUMBER_OF_CHROMOSOMES 200

void main()
{
	srand(time(NULL)); // To make the rand is not static 
	vector <vector <int>> chromosomes(NUMBER_OF_CHROMOSOMES, vector <int> (8));
	generate_chromosomes(chromosomes); // generat the first generation 
	genetic_algorithm(chromosomes); // start the genetic algorithm
}

// The genetic algorithm function 
void genetic_algorithm(vector <vector <int>>& chromosomes)
{
	int itearation = 0; // number of iterations 
	while (fitness(chromosomes[0]) != 8)
	{
		vector <vector <int>> children;
		cross_over(chromosomes, children);
		mutation(children);
		selection(chromosomes, children);

		cout << "\nIteration Number => " << ++itearation << '\n';
		cout << "Best Rank = " << fitness(chromosomes[0]) << '\n';
		cout << "_______________________________\n";
	}
	print_final_chromosome(chromosomes[0]);
}

void generate_chromosomes(vector <vector <int>>& chromosomes)
{
	for (int i = 0; i < NUMBER_OF_CHROMOSOMES; i++)
	{
		chromosomes[i] = generate_chromosome();
	}
}

vector <int> generate_chromosome()
{
	vector <int> chromosome(8);
	for (int i = 0; i < 8; i++)
	{
		chromosome[i] = (rand() % 8);
	}
	return chromosome;
}

void cross_over(vector <vector <int>>& chromosomes, vector <vector <int>>& children)
{
	vector <vector <int>> result_of_cross_over;

	for (int i = 0; i < NUMBER_OF_CHROMOSOMES; i += 2)
	{
		vector <int> parent1 = chromosomes[i];
		vector <int> parent2 = chromosomes[i + 1];
		vector <int> child1(8);
		vector <int> child2(8);
		
		int split = 1 + (rand() % 7);
		for (int i = 0; i < 8; i++)
		{
			if (i < split)
			{
				child1[i] = parent1[i];
			}
			else
			{
				child1[i] = parent2[i];
			}
		}
		for (int i = 0; i < 8; i++)
		{
			if (i < split)
			{
				child2[i] = parent2[i];
			}
			else
			{
				child2[i] = parent1[i];
			}
		}
		result_of_cross_over.emplace_back(child1);
		result_of_cross_over.emplace_back(child2);
	}
	children = result_of_cross_over;
}

void mutation(vector <vector <int>>& children)
{
	for (int i = 0; i < NUMBER_OF_CHROMOSOMES; i++)
	{
		int n = 1 + (rand() % 7);
		for (int j = 0; j < n; j++)
		{
			int choise = rand() % 2;
			if (choise)
				children[i][(rand() % 8)] = (rand() % 8);
		}
	}
}

void selection(vector <vector <int>>& chromosomes, vector <vector <int>>& children)
{
	vector <vector <int>> v;
	for (int i = 0; i < NUMBER_OF_CHROMOSOMES; i++)
		v.emplace_back(chromosomes[i]);
	for (int i = 0; i < NUMBER_OF_CHROMOSOMES; i++)
		v.emplace_back(children[i]);

	sort(v.rbegin(), v.rend(), [](const vector <int>& v1, const vector <int>& v2) {return fitness(v1) < fitness(v2); });
	
	for (int i = 0; i < NUMBER_OF_CHROMOSOMES; i++)
		chromosomes[i] = v[i];
}


int fitness(const vector <int>& chromosome)
{
	int rank = 0;
	for (int i = 0; i < 8; i++)
	{
		int r = i, c = chromosome[i];
		rank += check_status_of_chromosome(r, c, chromosome);
	}
	return rank;
}

bool check_status_of_chromosome(int r, int c, const vector <int>& chromosome)
{
	// check columns
	for (int i = 0; i < 8; i++)
	{
		if (i != r && chromosome[i] == c)
			return false;
	}

	// check diagonals:
	// main diagonal
	for (int i = r + 1, j = c + 1; i < 8 && j < 8; i++, j++)
	{
		if (chromosome[i] == j)
			return false;
	}
	for (int i = r - 1, j = c - 1; i >= 0 && j >= 0; i--, j--)
	{
		if (chromosome[i] == j)
			return false;
	}
	// reverse diagonal
	for (int i = r - 1, j = c + 1; i >= 0 && j < 8; i--, j++)
	{
		if (chromosome[i] == j)
			return false;
	}
	for (int i = r + 1, j = c - 1; i < 8 && j >= 0; i++, j--)
	{
		if (chromosome[i] == j)
			return false;
	}
	return true;
}

void print_final_chromosome(const vector <int>& chromosome)
{
	cout << "\n_______________________________\n\nFinished, Congrats\nThe final order is : \n\n";
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (chromosome[i] == j)
				cout << "Q" << " ";
			else
				cout << "*" << " ";
		}
		cout << '\n';
	}
	cout << "\n\n";
}