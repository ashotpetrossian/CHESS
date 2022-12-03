/**
 * @file chessBoard.hpp
 * @author Ashot Petrosyan (ashotpetrossian91@gmail.com)
 * @brief 
 *  The class owns the matrix of the chess board,
 *  chess squares to matrix points' map
 *  
 * @version 0.1
 * @date 2022-11-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CHESSBOARD_H_
#define CHESSBOARD_H_

#include <vector>
#include <string>
#include <unordered_map>
#include <locale>
#include <iostream>

namespace CHESS {

class chessBoard {
public:
    chessBoard();
    ~chessBoard() = default;
    chessBoard(const chessBoard&) = default;
    chessBoard& operator=(const chessBoard&) = default;
    chessBoard(chessBoard&&) = default;
    chessBoard& operator=(chessBoard&&) = default;

    void show() const;
    std::unordered_map<std::string, wchar_t*>& getBoardMap() {
        return m_map;
    }
    bool isSquareOccupied(const std::string& position) {
        if (m_map.find(position) != m_map.end()) {
            return (*m_map[position]) != '_';
        }
        return false;
    }

private:
    std::vector<std::vector<wchar_t>> m_board;
    std::unordered_map<std::string, wchar_t*> m_map;
};

chessBoard::chessBoard() {
    m_board.push_back( {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_',} );
    m_board.push_back( {'8', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|',} );
    m_board.push_back( {'7', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|',} );
    m_board.push_back( {'6', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|',} );
    m_board.push_back( {'5', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|',} );
    m_board.push_back( {'4', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|',} );
    m_board.push_back( {'3', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|',} );
    m_board.push_back( {'2', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|',} );
    m_board.push_back( {'1', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|', '_', '|',} );
    m_board.push_back( {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_',} );
    m_board.push_back( {' ', ' ', 'a', ' ', 'b', ' ', 'c', ' ', 'd', ' ', 'e', ' ', 'f', ' ', 'g', ' ', 'h', ' ',} );

    m_map["a1"] = &m_board[8][2];
    m_map["a2"] = &m_board[7][2];
    m_map["a3"] = &m_board[6][2];
    m_map["a4"] = &m_board[5][2];
    m_map["a5"] = &m_board[4][2];
    m_map["a6"] = &m_board[3][2];
    m_map["a7"] = &m_board[2][2];
    m_map["a8"] = &m_board[1][2];

    m_map["b1"] = &m_board[8][4];
    m_map["b2"] = &m_board[7][4];
    m_map["b3"] = &m_board[6][4];
    m_map["b4"] = &m_board[5][4];
    m_map["b5"] = &m_board[4][4];
    m_map["b6"] = &m_board[3][4];
    m_map["b7"] = &m_board[2][4];
    m_map["b8"] = &m_board[1][4];

    m_map["c1"] = &m_board[8][6];
    m_map["c2"] = &m_board[7][6];
    m_map["c3"] = &m_board[6][6];
    m_map["c4"] = &m_board[5][6];
    m_map["c5"] = &m_board[4][6];
    m_map["c6"] = &m_board[3][6];
    m_map["c7"] = &m_board[2][6];
    m_map["c8"] = &m_board[1][6];

    m_map["d1"] = &m_board[8][8];
    m_map["d2"] = &m_board[7][8];
    m_map["d3"] = &m_board[6][8];
    m_map["d4"] = &m_board[5][8];
    m_map["d5"] = &m_board[4][8];
    m_map["d6"] = &m_board[3][8];
    m_map["d7"] = &m_board[2][8];
    m_map["d8"] = &m_board[1][8];

    m_map["e1"] = &m_board[8][10];
    m_map["e2"] = &m_board[7][10];
    m_map["e3"] = &m_board[6][10];
    m_map["e4"] = &m_board[5][10];
    m_map["e5"] = &m_board[4][10];
    m_map["e6"] = &m_board[3][10];
    m_map["e7"] = &m_board[2][10];
    m_map["e8"] = &m_board[1][10];

    m_map["f1"] = &m_board[8][12];
    m_map["f2"] = &m_board[7][12];
    m_map["f3"] = &m_board[6][12];
    m_map["f4"] = &m_board[5][12];
    m_map["f5"] = &m_board[4][12];
    m_map["f6"] = &m_board[3][12];
    m_map["f7"] = &m_board[2][12];
    m_map["f8"] = &m_board[1][12];

    m_map["g1"] = &m_board[8][14];
    m_map["g2"] = &m_board[7][14];
    m_map["g3"] = &m_board[6][14];
    m_map["g4"] = &m_board[5][14];
    m_map["g5"] = &m_board[4][14];
    m_map["g6"] = &m_board[3][14];
    m_map["g7"] = &m_board[2][14];
    m_map["g8"] = &m_board[1][14];

    m_map["h1"] = &m_board[8][16];
    m_map["h2"] = &m_board[7][16];
    m_map["h3"] = &m_board[6][16];
    m_map["h4"] = &m_board[5][16];
    m_map["h5"] = &m_board[4][16];
    m_map["h6"] = &m_board[3][16];
    m_map["h7"] = &m_board[2][16];
    m_map["h8"] = &m_board[1][16];
}

void chessBoard::show() const {
    setlocale(LC_CTYPE,"");
    for (const auto& v : m_board) {
        for (const wchar_t c : v) {
            std::wcout << c;
        }
        std::wcout << std::endl;
    }
}

} // CHESS

#endif