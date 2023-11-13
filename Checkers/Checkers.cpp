// Checkers.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <vector>
#include <string>
#include <map>

// Definicje stałych
const int SIZE = 8; // Rozmiar planszy
const char EMPTY = '.'; // Symbol pustego pola
const char PLAYER1 = 'x'; // Symbol pionków gracza 1
const char PLAYER2 = 'o'; // Symbol pionków gracza 2

// Deklaracja funkcji
void initializeBoard(std::vector<std::vector<char>>& board);
void printBoard(const std::vector<std::vector<char>>& board);
bool makeMove(std::vector<std::vector<char>>& board, const std::string& from, const std::string& to, char player);
bool isMoveValid(std::vector<std::vector<char>>& board, const std::string& from, const std::string& to, char player);
std::pair<int, int> parsePosition(const std::string& position);


int main() {
    std::vector<std::vector<char>> board(SIZE, std::vector<char>(SIZE));
    initializeBoard(board);

    std::string from, to;
    bool player1Turn = true;

    while (true) {
        printBoard(board);

        // Wejście gracza
        std::cout << "Gracz " << (player1Turn ? "1 [x]" : "2 [o]") << " - podaj ruch (np. a3 b4): ";
        std::cin >> from >> to;
        if (makeMove(board, from, to, player1Turn ? PLAYER1 : PLAYER2)) {
            player1Turn = !player1Turn; // Zmiana gracza tylko, jeśli ruch był poprawny
        }
        else {
            std::cout << "Nieprawidłowy ruch! Spróbuj ponownie." << std::endl;
        }

        // Zmiana gracza
        player1Turn = !player1Turn;
    }

    return 0;
}

// Inicjalizacja szachwonicy
void initializeBoard(std::vector<std::vector<char>>& board) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if ((i + j) % 2 != 0) {
                if (i < 3) board[i][j] = PLAYER2;
                else if (i > 4) board[i][j] = PLAYER1;
                else board[i][j] = EMPTY;
            }
            else {
                board[i][j] = EMPTY;
            }
        }
    }
}

// Wyświetlanie szachownicy
void printBoard(const std::vector<std::vector<char>>& board) {
    std::cout << "  ";
    for (char c = 'a'; c < 'a' + SIZE; ++c) std::cout << c << ' ';
    std::cout << std::endl;

    for (int i = 0; i < SIZE; ++i) {
        std::cout << SIZE - i << ' ';
        for (int j = 0; j < SIZE; ++j) {
            std::cout << board[i][j] << ' ';
        }
        std::cout << SIZE - i;
        std::cout << std::endl;
    }

    std::cout << "  ";
    for (char c = 'a'; c < 'a' + SIZE; ++c) std::cout << c << ' ';
    std::cout << std::endl;
}


// Funkcja sprawdzająca poprawność ruchu w aktualnej sytuacji
bool isMoveValid(const std::vector<std::vector<char>>& board, const std::string& from, const std::string& to, char player) {
    auto fromPos = parsePosition(from);
    auto toPos = parsePosition(to);

    int fromRow = fromPos.first;
    int fromCol = fromPos.second;
    int toRow = toPos.first;
    int toCol = toPos.second;

    // Sprawdzenie, czy ruch jest na planszy
    if (fromRow < 0 || fromRow >= SIZE || fromCol < 0 || fromCol >= SIZE ||
        toRow < 0 || toRow >= SIZE || toCol < 0 || toCol >= SIZE) {
        return false;
    }

    // Sprawdzenie, czy ruch jest wykonany przez właściwego gracza
    if (board[fromRow][fromCol] != player) {
        return false;
    }

    // Sprawdzenie, czy pole docelowe jest puste
    if (board[toRow][toCol] != EMPTY) {
        return false;
    }

    int rowDiff = toRow - fromRow;
    int colDiff = toCol - fromCol;

    // Sprawdzenie, czy ruch jest po skosie
    if (abs(rowDiff) != abs(colDiff)) {
        return false;
    }

    // Sprawdzenie, czy ruch jest o maksymalnie jedno pole (dla zwykłego ruchu) lub o dwa (dla zbicia)
    if (abs(rowDiff) > 2 || abs(colDiff) > 2) {
        return false;
    }

    // Sprawdzenie możliwości zbicia
    if (abs(rowDiff) == 2) {
        int middleRow = (fromRow + toRow) / 2;
        int middleCol = (fromCol + toCol) / 2;
        char opponent = (player == PLAYER1) ? PLAYER2 : PLAYER1;

        if (board[middleRow][middleCol] != opponent) {
            return false;
        }
    }

    return true;
}

bool makeMove(std::vector<std::vector<char>>& board, const std::string& from, const std::string& to, char player) {
    if (!isMoveValid(board, from, to, player)) {
        return false; // Ruch nie jest dozwolony
    }

    auto fromPos = parsePosition(from);
    auto toPos = parsePosition(to);

    int fromRow = fromPos.first;
    int fromCol = fromPos.second;
    int toRow = toPos.first;
    int toCol = toPos.second;

    // Sprawdzenie zbicia
    int rowDiff = toRow - fromRow;
    int colDiff = toCol - fromCol;

    if (abs(rowDiff) == 2 && abs(colDiff) == 2) { // Zbicie
        int middleRow = (fromRow + toRow) / 2;
        int middleCol = (fromCol + toCol) / 2;
        board[middleRow][middleCol] = EMPTY; // Usunięcie zbitego pionka
    }

    // Przesunięcie pionka
    board[toRow][toCol] = player;
    board[fromRow][fromCol] = EMPTY;

    return true;
}
std::pair<int, int> parsePosition(const std::string& position) {
    if (position.length() != 2) return { -1, -1 };

    int col = tolower(position[0]) - 'a';
    int row = SIZE - (position[1] - '0');

    return { row, col };
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
