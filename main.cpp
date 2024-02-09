#include<iostream>
#include<fstream>
using namespace std;

void read_number_from_file(ifstream& fin, char& num);
void write_on_file(ofstream& fout, char num);
char** initialize_twoD_array(char** arr, int row, int colm);
void write_on_file_full(char filename[], char** arr, int row, int colm);
char** read_number_from_file_full(char filename[], char** arr, int row, int colm);
char game_menu(char ch);
char check_blockage(char** arr, char** pointer, int row, int colm, int& a, int& b, char ch, int& score, int& life);
void display(char** arr, int row, int colm);
bool check_boundary(char** arr, int row, int colm, char ch);
void show_complete_path(char** pointer, int row, int colm);
void fill_array_from_file(ifstream& fin, int* arr, int size);
int return_max_index(int* arr, int size);
void max_score(ifstream& fin2, char fn_output[], int* max, int size);
void sorting_ascending(char fn_output[], char** name_arr, int* num, int row);
void easy(char** arr, char** pointer, int row, int colm,  char fn_hard[], char game_level,int&score);
void medium(char** arr, char** pointer, int row, int colm,  char fn_hard[], char game_level, int& score);
void hard(char** arr, char** pointer, int row, int colm,  char fn_hard[], char game_level, int& score);
char direction_menu(char ch);

int main()
{
	int a = 0, b = 0, temp = 0, counter = 0;
	int score = 0, live = 3;

	char game_level = '\0', d_choice = '\0', check = '\0';
	int row = 5, colm = 6;

	char** arr = NULL;// original array
	char** pointer = NULL;  //to save path

	pointer = initialize_twoD_array(pointer, row, colm);
	arr = initialize_twoD_array(arr, row, colm);

	char fn_easy[30] = { "easy.txt" };
	char fn_medium[30] = { "medium.txt" };
	char fn_hard[30] = { "hard.txt" };
	char fn_output[30] = { "record.txt" };
	char* name = new char[30];
	ofstream fout(fn_output);

	while (1)
	{
		cout << "enter name by user " << endl;
		cin.getline(name, 30);
		counter++;
		game_level = game_menu(game_level);
		if (game_level == 'e' || game_level == 'E')
		{
			 easy( arr, pointer, row, colm,  fn_easy,  game_level,score);
		}
		else if (game_level == 'm' || game_level == 'M')
		{
			medium(arr, pointer, row, colm,  fn_easy, game_level, score);
		}
		if (game_level == 'h' || game_level == 'H')
		{
			hard(arr, pointer, row, colm,  fn_easy, game_level, score);
		}

		cout << "He scored " << score << " in this game " << endl;
		show_complete_path(pointer, row, colm);
		fout << name;
		fout << " : " << score << endl;
		score = 0;

		while (1)
		{
			cout << "do you want to play y/n" << endl;
			cin >> check;
			cin.ignore();
			if (check == 'y' || check == 'n')
				break;
			else
			{
				cout << "you enter wrong option please enter from given choice " << endl;
				continue;
			}
		}
		if (check == 'n')
			break;
		else
			continue;
	}
	fout.close();

	int* max = new int[counter];
	ifstream fin2(fn_output);

	if (fin2.is_open())
	{
		max_score(fin2, fn_output, max, counter);
		fin2.close();
	}

	char** name_arr = new char* [counter];

	for (int r = 0; r < counter; r++)
	{
		name_arr[r] = new char[30];
		
	}

	sorting_ascending(fn_output, name_arr, max, counter);
	cout << "after sorting_ascending record " << endl;
	ofstream fout5(fn_output);

	if (fout5.is_open())
	{
		for (int r = 0; r < counter; r++)
		{
			fout5 << name_arr[r] << " ";
			fout5 << " : " << max[r] << endl;
			cout  << max[r]<<" : " << endl;
		}
		fout5.close();
	}
	
	system("pause");
	return 0;
}
void sorting_ascending(char fn_output[], char** name_arr, int* num, int row)
{
	char* temp = nullptr;
	ifstream fin(fn_output);
	if (fin.is_open())
	{
		for (int i = 0; i < row; i++)
		{
			fin.getline(name_arr[i], 30, ':');
			fin >> num[i];
			fin.ignore();
		}
		fin.close();
	}
	else
		cout << "file donot open " << endl;
	temp = nullptr;
	int place = 0;
	for (int i = 0; i < row - 1; i++)
	{
		for (int j = 0; j < row - 1 - i; j++)
		{
			if (num[j] > num[j + 1])
			{
				place = num[j];
				num[j] = num[j + 1];
				num[j+ 1] = place;
				temp = name_arr[j];
				name_arr[j] = name_arr[j + 1];
				name_arr[j + 1] = temp;
			}
		}
	}
	delete temp;
	temp = nullptr;
}
void hard(char** arr, char** pointer, int row, int colm,  char fn_hard[], char game_level, int& score)
{
	bool flag = false;
		char d_choice = '\0', check = '\0';
	int live = 3, a = 0, b = 0;
	arr = read_number_from_file_full(fn_hard, arr, row, colm);
	cout << "origional data " << endl;
	display(arr, row, colm);
	
	while (1)
	{
		if (arr[row - 1][colm - 2] == '*')
		{
			cout << "congragulations" << endl;
			break;
		}
		else if (live == 0)
		{
			cout << "you have lost the game having no life " << endl;
			break;
		}
		else
		{
			d_choice = direction_menu(d_choice);
			if (d_choice == 'u' || d_choice == 'U')
			{
				if (check_boundary(arr, row, colm, d_choice))
				{
					continue;
				}
				else
				{
					check = check_blockage(arr, pointer, row, colm, a, b, d_choice, score, live);
					if (check == '1')
					{
						
						display(arr, row, colm);
					}
				}
			}
			else if (d_choice == 'l' || d_choice == 'L')
			{
				if (check_boundary(arr, row, colm, d_choice))
				{
					continue;
				}
				else
				{
					check = check_blockage(arr, pointer, row, colm, a, b, d_choice, score, live);
					if (check == '1')
					{
						
						display(arr, row, colm);
					}
				}
			}
			else if (d_choice == 'r' || d_choice == 'R')
			{
				if (check_boundary(arr, row, colm, d_choice))
				{
					continue;
				}
				else
				{
					check = check_blockage(arr, pointer, row, colm, a, b, d_choice, score, live);
					if (check == '1')
					{
						
						display(arr, row, colm);
					}
				}
			}
			else if (d_choice == 'd' || d_choice == 'D')
			{
				if (check_boundary(arr, row, colm, d_choice))
				{
					continue;
				}
				else
				{
					check = check_blockage(arr, pointer, row, colm, a, b, d_choice, score, live);
					if (check == '1')
					{
						
						display(arr, row, colm);
					}
				}
			}
			
			
		}
	}
}
void medium(char** arr, char** pointer, int row, int colm,  char fn_medium[], char game_level, int& score)
{
	bool flag = false;
	char d_choice = '\0', check = '\0';
	int live = 3, a = 0, b = 0;
	arr = read_number_from_file_full(fn_medium, arr, row, colm);
	cout << "origional data " << endl;
	display(arr, row, colm);
	
	while (1)
	{
		if (arr[row - 1][colm - 2] == '*')
		{
			cout << "congragulations" << endl;
			break;
		}
		else if (live == 0)
		{
			cout << "you have lost the game having no life " << endl;
			break;
		}
		else
		{
			d_choice = direction_menu(d_choice);
			if (d_choice == 'u' || d_choice == 'U')
			{
				if (check_boundary(arr, row, colm, d_choice))
				{
					continue;
				}
				else
				{
					check = check_blockage(arr, pointer, row, colm, a, b, d_choice, score, live);
					if (check == '1')
					{
						
						display(arr, row, colm);
					}
				}
			}
			else if (d_choice == 'l' || d_choice == 'L')
			{
				if (check_boundary(arr, row, colm, d_choice))
				{
					continue;
				}
				else
				{
					check = check_blockage(arr, pointer, row, colm, a, b, d_choice, score, live);
					if (check == '1')
					{
						
						display(arr, row, colm);
					}
				}
			}
			else if (d_choice == 'r' || d_choice == 'R')
			{
				if (check_boundary(arr, row, colm, d_choice))
				{
					continue;
				}
				else
				{
					check = check_blockage(arr, pointer, row, colm, a, b, d_choice, score, live);
					if (check == '1')
					{
						
						display(arr, row, colm);
					}
				}
			}
			else if (d_choice == 'd' || d_choice == 'D')
			{
				if (check_boundary(arr, row, colm, d_choice))
				{
					continue;
				}
				else
				{
					check = check_blockage(arr, pointer, row, colm, a, b, d_choice, score, live);
					if (check == '1')
					{
						
						display(arr, row, colm);
					}
				}
			}
			
		}
	}
}
void easy(char** arr,char**pointer, int row, int colm, char fn_easy[], char game_level, int& score)
{
	bool flag = false;
	char d_choice='\0',check='\0';
	int live = 3, a = 0, b = 0;
	if (game_level == 'e' || game_level == 'E')
	{
		arr = read_number_from_file_full(fn_easy, arr, row, colm);
		cout << "origional data " << endl;
		display(arr, row, colm);
		while (1)
		{
			if (arr[row - 1][colm - 2] == '*')
			{
				cout << "congragulations" << endl;
				break;
			}
			else if (live == 0)
			{
				cout << "you have lost the game having no life " << endl;
				break;
			}
			else
			{
				d_choice = direction_menu(d_choice);
				if (d_choice == 'u' || d_choice == 'U')
				{
					if (check_boundary(arr, row, colm, d_choice))
					{
						continue;
					}
					else
					{
						check = check_blockage(arr, pointer, row, colm, a, b, d_choice, score, live);
						if (check == '1')
						{
							display(arr, row, colm);
						}
					}
				}
				else if (d_choice == 'l' || d_choice == 'L')
				{
					if (check_boundary(arr, row, colm, d_choice))
					{
						continue;
					}
					else
					{
						check = check_blockage(arr, pointer, row, colm, a, b, d_choice, score, live);
						if (check == '1')
						{
							
							display(arr, row, colm);
						}
					}
				}
				else if (d_choice == 'r' || d_choice == 'R')
				{
					if (check_boundary(arr, row, colm, d_choice))
					{
						continue;
					}
					else
					{
						check = check_blockage(arr, pointer, row, colm, a, b, d_choice, score, live);
						if (check == '1')
						{
							
							display(arr, row, colm);
						}
					}
				}
				else if (d_choice == 'd' || d_choice == 'D')
				{
					if (check_boundary(arr, row, colm, d_choice))
					{
						continue;
					}
					else
					{
						check = check_blockage(arr, pointer, row, colm, a, b, d_choice, score, live);
						if (check == '1')
						{
							display(arr, row, colm);
						}
					}
				}
			}
		}
	}
}
void max_score(ifstream& fin2, char fn_output[], int* max, int size)
{
	ifstream fin(fn_output);
	if (fin.is_open())
	{
		fill_array_from_file(fin, max, size);
		fin.close();
	}
	int index = return_max_index(max, size);
	char* waste = new char[30];
	for (int i = 0; i < size; i++)
	{
		fin2.getline(waste, 30);
		if (i == index)
		{
			cout << "maximum scores have " << endl;
			cout << waste << endl;
			break;
		}
	}
	delete[]waste;
	waste = nullptr;
}
int return_max_index(int* arr, int size)
{
	int posi = 0, maxi = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] > maxi)
		{
			maxi = arr[i];
			posi = i;
		}
	}return posi;
}
void fill_array_from_file(ifstream& fin, int* arr, int size)
{
	char* waste = new char[30];
	for (int i = 0; i < size; i++)
	{
		fin.getline(waste, 30, ':');
		fin >> arr[i];
	}
	delete[]waste;
	waste = nullptr;
}
void show_complete_path(char** pointer, int row, int colm)
{
	cout << "sample of input pass " << endl;
	pointer[0][0] = '*';
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < colm - 1; c++)
		{
			if (pointer[r][c] == '*')
			{
				cout << pointer[r][c];

			}
			else
				cout << " ";
		}
		cout << endl;
	}
}
void display(char** arr, int row, int colm)
{
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < colm - 1; c++)
		{
			cout << arr[r][c] << " ";
		}
		cout << endl;
	}
}
char check_blockage(char** arr, char** pointer, int row, int colm, int& a, int& b, char ch, int& score, int& life)
{
	char temp = 0, check = 0;
	if (ch == 'u' || ch == 'U')
	{
		if (arr[a - 1][b] == '1' || arr[a - 1][b] == 'd')
		{
			temp = arr[a][b];
			arr[a][b] = arr[a - 1][b];
			arr[a - 1][b] = temp;
			pointer[--a][b] = arr[a][b];
			score += 5;
			cout << " 5 bonus score" << endl;
			check = '1';
			return check;
		}
		else if (arr[a - 1][b] == '0')
		{
			cout << "you reduce 1 number " << endl;
			score -= 1;
			display(arr, row, colm);
			return check;
		}
		else if (arr[a - 1][b] == '-')
		{
			cout << "you lost 1 life and 5 marks " << endl;
			score -= 5;
			life--;
			display(arr, row, colm);
			return check;
		}
	}
	if (ch == 'l' || ch == 'L')
	{
		if (arr[a][b - 1] == '1' || arr[a][b - 1] == 'd')
		{
			temp = arr[a][b];
			arr[a][b] = arr[a][b - 1];
			arr[a][b - 1] = temp;
			pointer[a][--b] = arr[a][b];
			score += 5;
			cout << " 5 bonus score" << endl;
			check = '1';
			return check;
		}
		else if (arr[a][b - 1] == '0')
		{
			cout << "you reduce 1 number " << endl;
			score -= 1;
			display(arr, row, colm);
			return check;
		}
		else if (arr[a][b - 1] == '-')
		{
			cout << "you lost 1 life and 5 marks " << endl;
			score -= 5;
			life--;
			display(arr, row, colm);
			return check;
		}
	}
	if (ch == 'r' || ch == 'R')
	{
		if (arr[a][b + 1] == '1' || arr[a][b + 1] == 'd')
		{
			temp = arr[a][b];
			arr[a][b] = arr[a][b + 1];
			arr[a][b + 1] = temp;
			pointer[a][++b] = arr[a][b];
			score += 5;
			cout << " 5 bonus score" << endl;
			check = '1';
			return check;
		}
		else if (arr[a][b + 1] == '0')
		{
			cout << "you reduce 1 number " << endl;
			score -= 1;
			display(arr, row, colm);
			return check;
		}
		else if (arr[a][b + 1] == '-')
		{
			cout << "you lost 1 life and 5 marks " << endl;
			score -= 5;
			life--;
			display(arr, row, colm);
			return check;
		}
	}
	if (ch == 'd' || ch == 'D')
	{
		if (arr[a + 1][b] == '1' || arr[a + 1][b] == 'd')
		{
			temp = arr[a][b];
			arr[a][b] = arr[a + 1][b];
			arr[a + 1][b] = temp;
			pointer[++a][b] = arr[a][b];
			score += 5;
			cout << " 5 bonus score" << endl;
			check = '1';
			return check;
		}
		else if (arr[a + 1][b] == '0')
		{
			cout << "you reduce 1 number " << endl;
			score -= 1;
			display(arr, row, colm);
			return check;
		}
		else if (arr[a + 1][b] == '-')
		{
			cout << "you lost 1 life and 5 marks " << endl;
			score -= 5;
			life--;
			display(arr, row, colm);
			return check;
		}
	}
}
bool check_boundary(char** arr, int row, int colm, char ch)
{
	if (ch == 'u' || ch == 'U')
	{
		for (int c = 0; c < colm - 1; c++)
		{
			if (arr[0][c] == '*')
			{
				cout << "you donot move to the up side " << endl;
				return true;
			}
		}
		return false;
	}
	else if (ch == 'l' || ch == 'L')
	{
		for (int c = 0; c < colm - 1; c++)
		{
			if (arr[c][0] == '*')
			{
				cout << "you donot move to the left side " << endl;
				return true;
			}
		}
		return false;
	}
	else if (ch == 'd' || ch == 'D')
	{
		for (int c = 0; c < colm - 1; c++)
		{
			if (arr[row - 1][c] == '*')
			{
				cout << "you donot move to the down side " << endl;
				return true;
			}
		}
		return false;
	}
	else if (ch == 'r' || ch == 'R')
	{
		for (int c = 0; c < colm - 1; c++)
		{
			if (arr[c][row - 1] == '*')
			{
				cout << "you donot move to the right side " << endl;
				return true;
			}
		}
		return false;
	}
}
char direction_menu(char ch)
{
	while (1)
	{
		cout << "press u for up direction " << endl;
		cout << "press l for left direction " << endl;
		cout << "press d for down direction " << endl;
		cout << "press r for right direction " << endl;
		cout << "select your choice " << endl;
		cin >> ch;
		if (ch == 'u' || ch == 'U' || ch == 'l' || ch == 'L' || ch == 'd' || ch == 'D' || ch == 'r' || ch == 'R' || ch == 'p' || ch == 'P')
		{
			break;
		}
		else
			cout << "you enter wrong menu select from below menu" << endl;
	}
	return ch;
}
char game_menu(char ch)
{
	while (1)
	{
		cout << "press e for easy game " << endl;
		cout << "press m for medium game " << endl;
		cout << "press h for hard game " << endl;
		cout << "select your choice " << endl;
		cin >> ch;
		if (ch == 'e' || ch == 'E' || ch == 'm' || ch == 'M' || ch == 'h' || ch == 'H')
		{
			break;
		}
		else
			cout << "you enter wrong menu select from below menu" << endl;
	}
	return ch;
}
char** initialize_twoD_array(char** arr, int row, int colm)
{
	arr = new char* [row];
	for (int r = 0; r < row; r++)
	{
		arr[r] = new char[colm];
	}
	return arr;
}
void read_number_from_file(ifstream& fin, char& num)
{
	fin >> num;
}
void write_on_file(ofstream& fout, char num)
{
	fout << num << " ";
}
char** read_number_from_file_full(char filename[], char** arr, int row, int colm)
{
	char num = 0;
	ifstream fin(filename);
	if (fin.is_open())
	{
		for (int r = 0; r < row; r++)
		{
			for (int c = 0; c < colm - 1; c++)
			{
				read_number_from_file(fin, num);
				arr[r][c] = num;
			}
		}
	}
	else
		cout << "file donot open" << endl;
	fin.close();
	return arr;
}
void write_on_file_full(char filename[], char** arr, int row, int colm)
{
	ofstream fout(filename);
	if (fout.is_open())
	{
		for (int r = 0; r < row; r++)
		{
			for (int c = 0; c < colm - 1; c++)
			{
				fout << arr[r][c] << " ";
			}fout << endl;
		}
		fout.close();
	}
}