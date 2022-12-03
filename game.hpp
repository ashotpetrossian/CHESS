/**
 * @file game.hpp
 * @author Ashot Petrosyan (ashotpetrossian91@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-04
 * 
 * game class controls the game process including validations.
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "chess.hpp"
#include <sstream>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


void handler(int sig) {
  void *array[50];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 50);

  // print out all the frames to stderr
  std::wcout << "Error: signal " << sig << std::endl;
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}


namespace CHESS {

class Game {
public:
    Game();
    ~Game();
    void play();
    void welcome() const;
    void display() const;
    void printMoves(bool falag = false) const;
    std::pair<std::string, std::string> getMoves(const std::string&) const; 
    bool isValidInput(const std::string& source, const std::string& destination);
public:
    Chess* m_chess = nullptr;
};

Game::Game() {
    m_chess = new Chess();
}

Game::~Game() {
    delete m_chess;
}

void Game::welcome() const {
    setlocale(LC_CTYPE, "");
    std::wcout << "**********************WELCOME TO CHESS**********************" << std::endl;
}

void Game::display() const {
    m_chess->showBoard();
}

std::pair<std::string, std::string> Game::getMoves(const std::string& move)  const{
    std::string source; std::string destination;
    for (int i = 0; i < move.size() - 1; ++i) {
        if (move[i] == ' ') continue;
        if (source.empty()) {
            source.push_back(move[i]);
            source.push_back(move[i + 1]);
            ++i;
        } else {
            destination.push_back(move[i]);
            destination.push_back(move[i + 1]);
            break;
        }
    }
    return {source, destination};
}

bool Game::isValidInput(const std::string& source, const std::string& destination) {
    if (source.size() != 2 || destination.size() != 2 || source == destination) {
        return false;
    }
    if (source[0] < 'a' || source[0] > 'h' || 
        destination[0] < 'a' || destination[0] > 'h' ||
        source[1] < '1' || source[1] > '8' ||
        destination[1] < '1' || destination[1] > '8'){
        return false;
    }
    if (!m_chess->getPieceFromPosition(source)) return false;
    return true;
}

void Game::play() {
    welcome();
    setlocale(LC_CTYPE,"");
    signal(SIGSEGV, handler);
    bool whiteMove = true;
    bool blackMove = true;
    while (true) {
        while (whiteMove) {
            std::cin.clear();
            printMoves(true);
            std::wcout << std::endl;
            display();
            std::wcout << "white's turn: ";
            std::string move;
            std::getline(std::cin, move);
            std::string source; std::string destination;
            source = getMoves(move).first; destination = getMoves(move).second;
            if (!isValidInput(source, destination) || !m_chess->isWhiteMoved(source) || !m_chess->isValidMove(source, destination)) {
                whiteMove = true;
                m_chess->resetFlags();
                continue;
            }
            whiteMove = true;
            m_chess->move(source, destination);
            m_chess->resetFlags();
            whiteMove = false;
        }

        if (m_chess->isBlackCheckMated()) {
            std::wcout << "White WON!" << std::endl;
            break;
        }
        if (m_chess->isBlackStalemate()) {
            std::wcout << "Black under stalemate, DRAW!" << std::endl;
            break;
        }
        if (m_chess->isRepetition()) {
            std::wcout << "REPETITION: DRAW!" << std::endl;
            break;
        }

        while (blackMove) {
            std::cin.clear();
            printMoves();
            std::wcout << std::endl;
            display();
            std::wcout << "black's turn: ";
            std::string move;
            std::getline(std::cin, move);
            std::string source; std::string destination;
            source = getMoves(move).first; destination = getMoves(move).second;
            if (!isValidInput(source, destination) || !m_chess->isBlackMoved(source) || !m_chess->isValidMove(source, destination)) {
                blackMove = true;
                m_chess->resetFlags();
                continue;
            }
            m_chess->move(source, destination);
            m_chess->resetFlags();
            blackMove = false;
        }

        if (m_chess->isWhiteCheckMated()) {
            std::wcout << "Black WON" << std::endl;
            break;
        }
        if (m_chess->isWhiteStalemate()) {
            std::wcout << "White under stalemate, DRAW!" << std::endl;
            break;
        }
        if (m_chess->isRepetition()) {
            std::wcout << "REPETITION: DRAW!" << std::endl;
            break;
        }
        if (m_chess->getMoveDB().size() == 12) {
            for (auto p : m_chess->getMoveDB()) {
                std::wcout << p.first.c_str() << " " << p.second.c_str() << std::endl;
            }
        }

        whiteMove = true;
        blackMove = true;
    }
    display();
}

} // CHESS