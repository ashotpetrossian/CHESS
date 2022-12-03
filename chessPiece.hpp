/**
 * @file chessPiece.hpp
 * @author Ashot Petrosyan (ashotpetrossian91@gmail.com)
 * @brief 
 *  chessPiece class is an abstract class for all chessPieces in chess.
 *  Implemented using dynamic polymorphism.
 *  Liskov substitution principle is actively used in chess.hpp,
 *  Rarely needed for dynamic cast(pawn and king cases).
 * 
 *  Functions to be explained: getAttackingSquares and getAttackingPath:
 *  For each piece there are attacking squares which the getAttackingSquares function returns, but
 *  if the piece is (queen, rook or bishop) they don't see the squares behind the piece they attack.
 *  Attacking path is writted for mentioned 3 pieces which has "path" idea.
 *  Giving the destination they will return the path to the particular square, skipping occupied squares.
 * 
 *  isValidMove is checking only if the move is valid due to the game rules, which is only a part of isValidMove of chess class.
 *  
 * @version 0.1
 * @date 2022-11-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CHESSPIECE_H_
#define CHESSPIECE_H_


#include "chessBoard.hpp"
#include <string>
#include <vector>
#include <algorithm>

namespace CHESS {

class chessPiece {
public:
    enum class COLOR { WHITE, BLACK };
    enum class PIECE { KING, QUEEN, KNIGHT, BISHOP, ROOK, PAWN, NONE };
    virtual bool isValidMove(const std::string& source, const std::string& destination) = 0;
    virtual void move(const std::string& destination) = 0;
    virtual COLOR getColor() const = 0;
    virtual void setPosition(const std::string&) = 0;
    virtual std::string getPosition() const = 0;
    virtual PIECE getPiece() const = 0;
    virtual std::vector<std::string> getAttackingSquares() = 0;
    virtual bool isFirstMove() const;
    virtual std::vector<std::string> getAttackingPath(const std::string&);

    virtual ~chessPiece() = default;
};

bool chessPiece::isFirstMove() const {
    return false;
}

std::vector<std::string> chessPiece::getAttackingPath(const std::string&) {
    return {};
}

class King : public chessPiece {
public:
    King(COLOR color, const std::string& position, chessBoard* chessBoard) : 
            m_color(color), m_position(position), m_chessBoard(chessBoard) {
        setPosition(position);
    }

    King(const King&) = default;
    King& operator=(const King&) = default;
    King(King&&) = default;
    King& operator=(King&&) = default;
    virtual ~King() = default;

    bool isValidMove(const std::string& source, const std::string& destination) override {
        auto& boardMap = m_chessBoard->getBoardMap();
        if (boardMap.find(source) == boardMap.end() || boardMap.find(destination) == boardMap.end() || source == destination) {
            return false;
        }
        for (std::string pos : getAttackingSquares()) {
            if (pos == destination) {
                return true;
            }
        }
        return false;
    }

    void move(const std::string& destination) override {
        auto& tmpBoardMap = m_chessBoard->getBoardMap();
        std::string source = m_position;
        setPosition(destination);
        *tmpBoardMap[source] = '_';
        if (m_firstMove) {
            m_firstMove = false;
        }
    }

    bool isFirstMove() const override {
        return m_firstMove;
    }

    COLOR getColor() const override {
        return m_color;
    }

    void setPosition(const std::string& position) override {
        auto& tmpBoardMap = m_chessBoard->getBoardMap();
        if (m_color == COLOR::WHITE) {
            *tmpBoardMap[position] = L'\u265A';
        } else {
            *tmpBoardMap[position] = L'\u2654';
        }
        m_position = position;
    }    

    std::string getPosition() const override {
        return m_position;
    }

    PIECE getPiece() const override {
        return m_piece;
    }

    std::vector<std::string> getAttackingSquares() override {
        std::vector<std::string> vec;
        std::vector<std::string> res;
        std::string pos = m_position;
        std::string tmp1 = pos; ++tmp1[0]; vec.push_back(tmp1);
        std::string tmp2 = pos; ++tmp2[0]; --tmp2[1]; vec.push_back(tmp2);
        std::string tmp3 = pos; ++tmp3[0]; ++tmp3[1]; vec.push_back(tmp3);
        std::string tmp4 = pos; ++tmp4[1]; vec.push_back(tmp4);
        std::string tmp5 = pos; --tmp5[1]; vec.push_back(tmp5);
        std::string tmp6 = pos; --tmp6[0]; vec.push_back(tmp6);
        std::string tmp7 = pos; --tmp7[0]; ++tmp7[1]; vec.push_back(tmp7);
        std::string tmp8 = pos; --tmp8[0]; --tmp8[1]; vec.push_back(tmp8);

        auto& boardMap = m_chessBoard->getBoardMap();
        for (auto it = vec.begin(); it != vec.end(); ++it) {
            if (boardMap.find(*it) != boardMap.end()) {
                res.push_back(*it);
            }
        }
        return res;
    }

private:
    chessBoard* m_chessBoard;
    COLOR m_color;
    std::string m_position;
    PIECE m_piece = PIECE::KING;
    bool m_firstMove = true;
};

class Queen : public chessPiece {
public:
    Queen(COLOR color, const std::string& position, chessBoard* chessBoard) : 
            m_color(color), m_position(position), m_chessBoard(chessBoard) {
        setPosition(position);
    }

    Queen(const Queen&) = default;
    Queen& operator=(const Queen&) = default;
    Queen(Queen&&) = default;
    Queen& operator=(Queen&&) = default;
    virtual ~Queen() = default;

    bool isValidMove(const std::string& source, const std::string& destination) override {
        auto& boardMap = m_chessBoard->getBoardMap();
        if (boardMap.find(source) == boardMap.end() || boardMap.find(destination) == boardMap.end() || source == destination) {
            return false;
        }
        for (std::string pos : getAttackingSquares()) {
            if (pos == destination) {
                return true;
            }
        }
        return false;
    }
    void move(const std::string& destination) override {
        auto& tmpBoardMap = m_chessBoard->getBoardMap();
        std::string source = m_position;
        setPosition(destination);
        *tmpBoardMap[source] = '_';
    }

    COLOR getColor() const override {
        return m_color;
    }

    void setPosition(const std::string& position) override {
        auto& tmpBoardMap = m_chessBoard->getBoardMap();
        if (m_color == COLOR::WHITE) {
            *tmpBoardMap[position] = L'\u265B';
        } else {
            *tmpBoardMap[position] = L'\u2655';
        }
        m_position = position;
    }    

    std::string getPosition() const override {
        return m_position;
    }

    PIECE getPiece() const override {
        return m_piece;
    }

    std::vector<std::string> getAttackingSquares() override {
        std::vector<std::string> vec;
        std::vector<std::string> res;
        std::string pos = m_position;
        char letter = pos[0];
        char digit = pos[1];
        ++letter;
        while (letter <= 'h') {
            vec.push_back({letter, digit});
            if (m_chessBoard->isSquareOccupied({letter, digit})) { // the square with the attacked piece is also included
                break;
            }
            ++letter;
        }
        letter = pos[0]; --letter;
        while (letter >= 'a') {
            vec.push_back({letter, digit});
            if (m_chessBoard->isSquareOccupied({letter, digit})) {
                break;
            }
            --letter;
        }
        letter = pos[0]; ++digit;
        while (digit <= '8') {
            vec.push_back({letter, digit});
            if (m_chessBoard->isSquareOccupied({letter, digit})) {
                break;
            }
            ++digit;
        }
        digit = pos[1]; --digit;
        while (digit >= '1') {
            vec.push_back({letter, digit});
            if (m_chessBoard->isSquareOccupied({letter, digit})) {
                break;
            }
            --digit;
        }
        digit = pos[1];
        ++letter; ++digit;
        while (letter <= 'h' && digit <= '8') {
            vec.push_back({letter, digit});
            if (m_chessBoard->isSquareOccupied({letter, digit})) {
                break;
            }
            ++letter; ++digit;
        }
        letter = pos[0]; digit = pos[1];
        ++letter; --digit;
        while (letter <= 'h' && digit >= '1') {
            vec.push_back({letter, digit});
            if (m_chessBoard->isSquareOccupied({letter, digit})) {
                break;
            }
            ++letter; --digit;
        }
        letter = pos[0]; digit = pos[1];
        --letter; ++digit;
        while (letter >= 'a' && digit <= '8') {
            vec.push_back({letter, digit});
            if (m_chessBoard->isSquareOccupied({letter, digit})) {
                break;
            }
            --letter; ++digit;
        }
        letter = pos[0]; digit = pos[1];
        --letter; --digit;
        while (letter >= 'a' && digit >= '1') {
            vec.push_back({letter, digit});
            if (m_chessBoard->isSquareOccupied({letter, digit})) {
                break;
            }
            --letter; --digit;
        }

        auto& boardMap = m_chessBoard->getBoardMap();
        for (auto it = vec.begin(); it != vec.end(); ++it) {
            if (boardMap.find(*it) != boardMap.end()) {
                res.push_back(*it);
            }
        }
        return res;
    }

    std::vector<std::string> getAttackingPath(const std::string& destination) {
        std::vector<std::string> attackingPathVec;
        std::string pos = m_position;
        if (pos[0] == destination[0] && pos[1] < destination[1]) {
            while (pos[1] <= destination[1]) {
                attackingPathVec.push_back(pos);
                ++pos[1];
            }
            return attackingPathVec;
        } 
        pos = m_position;
        if (pos[0] == destination[0] && pos[1] > destination[1]) {
            while (pos[1] >= destination[1]) {
                attackingPathVec.push_back(pos);
                --pos[1];
            }
            return attackingPathVec;
        }
        pos = m_position;
        if (pos[0] < destination[0] && pos[1] == destination[1]) {
            while (pos[0] <= destination[0]) {
                attackingPathVec.push_back(pos);
                ++pos[0];
            }
            return attackingPathVec;
        }
        pos = m_position;
        if (pos[0] > destination[0] && pos[1] == destination[1]) {
            while (pos[0] >= destination[0]) {
                attackingPathVec.push_back(pos);
                --pos[0];
            }
            return attackingPathVec;
        }
        
        pos = m_position;
        if (pos[0] < destination[0] && pos[1] < destination[1]) {  // left down
            while (pos[0] <= destination[0] && pos[1] <= destination[1]) {
                attackingPathVec.push_back(pos);
                ++pos[0]; ++pos[1];
            }
            return attackingPathVec;
        }

        if (pos[0] > destination[0] && pos[1] < destination[1]) { // right down
            while (pos[0] >= destination[0] && pos[1] <= destination[1]) {
                attackingPathVec.push_back(pos);
                --pos[0]; ++pos[1];
            }
            return attackingPathVec;
        }

        if (pos[0] < destination[0] && pos[1] > destination[1]) { // left up
            while (pos[0] <= destination[0] && pos[1] >= destination[1]) {
                attackingPathVec.push_back(pos);
                ++pos[0]; --pos[1];
            }
            return attackingPathVec;
        }

        if (pos[0] > destination[0] && pos[1] > destination[1]) { // right up
            while (pos[0] >= destination[0] && pos[1] >= destination[1]) {
                attackingPathVec.push_back(pos);
                --pos[0]; --pos[1];
            }
            return attackingPathVec;
        }

        return {};
    }

private:
    chessBoard* m_chessBoard;
    COLOR m_color;
    std::string m_position;
    PIECE m_piece = PIECE::QUEEN;
};

class Bishop : public chessPiece {
public:
    Bishop(COLOR color, const std::string& position, chessBoard* chessBoard) : 
            m_color(color), m_position(position), m_chessBoard(chessBoard) {
        setPosition(position);
    }

    Bishop(const Bishop&) = default;
    Bishop& operator=(const Bishop&) = default;
    Bishop(Bishop&&) = default;
    Bishop& operator=(Bishop&&) = default;
    virtual ~Bishop() = default;

    bool isValidMove(const std::string& source, const std::string& destination) override {
        auto& boardMap = m_chessBoard->getBoardMap();
        if (boardMap.find(source) == boardMap.end() || boardMap.find(destination) == boardMap.end() || source == destination) {
            return false;
        }
        for (std::string pos : getAttackingSquares()) {
            if (pos == destination) {
                return true;
            }
        }
        return false;
    }
    void move(const std::string& destination) override {
        auto& tmpBoardMap = m_chessBoard->getBoardMap();
        std::string source = m_position;
        setPosition(destination);
        *tmpBoardMap[source] = '_';
    }

    COLOR getColor() const override {
        return m_color;
    }

    void setPosition(const std::string& position) override {
        auto& tmpBoardMap = m_chessBoard->getBoardMap();
        if (m_color == COLOR::WHITE) {
            *tmpBoardMap[position] = L'\u265D';
        } else {
            *tmpBoardMap[position] = L'\u2657';
        }
        m_position = position;
    }    

    std::string getPosition() const override {
        return m_position;
    }

    PIECE getPiece() const override {
        return m_piece;
    }

    std::vector<std::string> getAttackingSquares() override {
        std::vector<std::string> vec;
        std::vector<std::string> res;
        std::string pos = m_position;
        char letter = pos[0];
        char digit = pos[1];
        ++letter; ++digit;
        while (letter <= 'h' && digit <= '8') {
            vec.push_back({letter, digit});
            if (m_chessBoard->isSquareOccupied({letter, digit})) {
                break;
            }
            ++letter; ++digit;
        }
        letter = pos[0]; digit = pos[1];
        ++letter; --digit;
        while (letter <= 'h' && digit >= '1') {
            vec.push_back({letter, digit});
            if (m_chessBoard->isSquareOccupied({letter, digit})) {
                break;
            }
            ++letter; --digit;
        }
        letter = pos[0]; digit = pos[1];
        --letter; ++digit;
        while (letter >= 'a' && digit <= '8') {
            vec.push_back({letter, digit});
            if (m_chessBoard->isSquareOccupied({letter, digit})) {
                break;
            }
            --letter; ++digit;
        }
        letter = pos[0]; digit = pos[1];
        --letter; --digit;
        while (letter >= 'a' && digit >= '1') {
            vec.push_back({letter, digit});
            if (m_chessBoard->isSquareOccupied({letter, digit})) {
                break;
            }
            --letter; --digit;
        }

        auto& boardMap = m_chessBoard->getBoardMap();
        for (auto it = vec.begin(); it != vec.end(); ++it) {
            if (boardMap.find(*it) != boardMap.end()) {
                res.push_back(*it);
            }
        }

        return res;
    }

    std::vector<std::string> getAttackingPath(const std::string& destination) {
        std::vector<std::string> attackingPathVec;        
        std::string pos = m_position;
        if (pos[0] < destination[0] && pos[1] < destination[1]) {  // left down
            while (pos[0] <= destination[0] && pos[1] <= destination[1]) {
                attackingPathVec.push_back(pos);
                ++pos[0]; ++pos[1];
            }
            return attackingPathVec;
        }

        if (pos[0] > destination[0] && pos[1] < destination[1]) { // right down
            while (pos[0] >= destination[0] && pos[1] <= destination[1]) {
                attackingPathVec.push_back(pos);
                --pos[0]; ++pos[1];
            }
            return attackingPathVec;
        }

        if (pos[0] < destination[0] && pos[1] > destination[1]) { // left up
            while (pos[0] <= destination[0] && pos[1] >= destination[1]) {
                attackingPathVec.push_back(pos);
                ++pos[0]; --pos[1];
            }
            return attackingPathVec;
        }

        if (pos[0] > destination[0] && pos[1] > destination[1]) { // right up
            while (pos[0] >= destination[0] && pos[1] >= destination[1]) {
                attackingPathVec.push_back(pos);
                --pos[0]; --pos[1];
            }
            return attackingPathVec;
        }

        return {};
    }

private:
    chessBoard* m_chessBoard;
    COLOR m_color;
    std::string m_position;
    PIECE m_piece = PIECE::BISHOP;
};

class Rook : public chessPiece {
public:
    Rook(COLOR color, const std::string& position, chessBoard* chessBoard) : 
            m_color(color), m_position(position), m_chessBoard(chessBoard) {
        setPosition(position);
    }

    Rook(const Rook&) = default;
    Rook& operator=(const Rook&) = default;
    Rook(Rook&&) = default;
    Rook& operator=(Rook&&) = default;
    virtual ~Rook() = default;

    bool isValidMove(const std::string& source, const std::string& destination) override {
        auto& boardMap = m_chessBoard->getBoardMap();
        if (boardMap.find(source) == boardMap.end() || boardMap.find(destination) == boardMap.end() || source == destination) {
            return false;
        }
        for (std::string pos : getAttackingSquares()) {
            if (pos == destination) {
                return true;
            }
        }
        return false;
    }

    void move(const std::string& destination) override {
        auto& tmpBoardMap = m_chessBoard->getBoardMap();
        std::string source = m_position;
        setPosition(destination);
        *tmpBoardMap[source] = '_';
        if (m_firstMove) {
            m_firstMove = false;
        }
    }

    bool isFirstMove() const override {
        return m_firstMove;
    }

    COLOR getColor() const override {
        return m_color;
    }

    void setPosition(const std::string& position) override {
        auto& tmpBoardMap = m_chessBoard->getBoardMap();
        if (m_color == COLOR::WHITE) {
            *tmpBoardMap[position] = L'\u265C';
        } else {
            *tmpBoardMap[position] = L'\u2656';
        }
        m_position = position;
    }    

    std::string getPosition() const override {
        return m_position;
    }

    PIECE getPiece() const override {
        return m_piece;
    }

    std::vector<std::string> getAttackingSquares() override {
        std::vector<std::string> vec;
        std::vector<std::string> res;
        std::string pos = m_position;
        char letter = pos[0];
        char digit = pos[1];
        ++letter;
        while (letter <= 'h') {
            vec.push_back({letter, digit});
            if (m_chessBoard->isSquareOccupied({letter, digit})) {
                break;
            }
            ++letter;
        }
        letter = pos[0]; --letter;
        while (letter >= 'a') {
            vec.push_back({letter, digit});
            if (m_chessBoard->isSquareOccupied({letter, digit})) {
                break;
            }
            --letter;
        }
        letter = pos[0]; ++digit;
        while (digit <= '8') {
            vec.push_back({letter, digit});
            if (m_chessBoard->isSquareOccupied({letter, digit})) {
                break;
            }
            ++digit;
        }
        digit = pos[1]; --digit;
        while (digit >= '1') {
            vec.push_back({letter, digit});
            if (m_chessBoard->isSquareOccupied({letter, digit})) {
                break;
            }
            --digit;
        }

        auto& boardMap = m_chessBoard->getBoardMap();
        for (auto it = vec.begin(); it != vec.end(); ++it) {
            if (boardMap.find(*it) != boardMap.end()) {
                res.push_back(*it);
            }
        }

        return res;
    }

    std::vector<std::string> getAttackingPath(const std::string& destination) {
        std::vector<std::string> attackingPathVec;
        std::string pos = m_position;
        if (pos[0] == destination[0] && pos[1] < destination[1]) {
            while (pos[1] <= destination[1]) {
                attackingPathVec.push_back(pos);
                ++pos[1];
            }
            return attackingPathVec;
        } 
        pos = m_position;
        if (pos[0] == destination[0] && pos[1] > destination[1]) {
            while (pos[1] >= destination[1]) {
                attackingPathVec.push_back(pos);
                --pos[1];
            }
            return attackingPathVec;
        }
        pos = m_position;
        if (pos[0] < destination[0] && pos[1] == destination[1]) {
            while (pos[0] <= destination[0]) {
                attackingPathVec.push_back(pos);
                ++pos[0];
            }
            return attackingPathVec;
        }
        pos = m_position;
        if (pos[0] > destination[0] && pos[1] == destination[1]) {
            while (pos[0] >= destination[0]) {
                attackingPathVec.push_back(pos);
                --pos[0];
            }
            return attackingPathVec;
        }

        return {};
    }

private:
    chessBoard* m_chessBoard;
    COLOR m_color;
    std::string m_position;
    PIECE m_piece = PIECE::ROOK;
    bool m_firstMove = true;
};

class Knight : public chessPiece {
public:
    Knight(COLOR color, const std::string& position, chessBoard* chessBoard) : 
            m_color(color), m_position(position), m_chessBoard(chessBoard) {
        setPosition(position);
    }

    Knight(const Knight&) = default;
    Knight& operator=(const Knight&) = default;
    Knight(Knight&&) = default;
    Knight& operator=(Knight&&) = default;
    virtual ~Knight() = default;

    bool isValidMove(const std::string& source, const std::string& destination) override {
        auto& boardMap = m_chessBoard->getBoardMap();
        if (boardMap.find(source) == boardMap.end() || boardMap.find(destination) == boardMap.end() || source == destination) {
            return false;
        }
        for (std::string pos : getAttackingSquares()) {
            if (pos == destination) {
                return true;
            }
        }
        return false;
    }
    
    void move(const std::string& destination) override {
        auto& tmpBoardMap = m_chessBoard->getBoardMap();
        std::string source = m_position;
        setPosition(destination);
        *tmpBoardMap[source] = '_';
    }

    COLOR getColor() const override {
        return m_color;
    }

    void setPosition(const std::string& position) override {
        auto& tmpBoardMap = m_chessBoard->getBoardMap();
        if (m_color == COLOR::WHITE) {
            *tmpBoardMap[position] = L'\u265E';
        } else {
            *tmpBoardMap[position] = L'\u2658';
        }
        m_position = position;
    }    

    std::string getPosition() const override {
        return m_position;
    }

    PIECE getPiece() const override {
        return m_piece;
    }

    std::vector<std::string> getAttackingSquares() override {
        std::vector<std::string> vec;
        std::vector<std::string> res;
        std::string pos = m_position;
        std::string tmp1 = pos; tmp1[0] += 2; ++tmp1[1]; vec.push_back(tmp1);
        std::string tmp2 = pos; tmp2[0] += 2; --tmp2[1]; vec.push_back(tmp2);
        std::string tmp3 = pos; ++tmp3[0]; tmp3[1] += 2; vec.push_back(tmp3);
        std::string tmp4 = pos; ++tmp4[0]; tmp4[1] -= 2; vec.push_back(tmp4);
        std::string tmp5 = pos; tmp5[0] -= 2; ++tmp5[1]; vec.push_back(tmp5);
        std::string tmp6 = pos; tmp6[0] -= 2; --tmp6[1]; vec.push_back(tmp6);
        std::string tmp7 = pos; --tmp7[0]; tmp7[1] += 2; vec.push_back(tmp7);
        std::string tmp8 = pos; --tmp8[0]; tmp8[1] -= 2; vec.push_back(tmp8);

        auto& boardMap = m_chessBoard->getBoardMap();
        for (auto it = vec.begin(); it != vec.end(); ++it) {
            if (boardMap.find(*it) != boardMap.end()) {
                res.push_back(*it);
            }
        }
        return res;
    }

private:
    chessBoard* m_chessBoard;
    COLOR m_color;
    std::string m_position;
    PIECE m_piece = PIECE::KNIGHT;
};

class Pawn : public chessPiece {
public:
    Pawn(COLOR color, const std::string& position, chessBoard* chessBoard) : 
            m_color(color), m_position(position), m_chessBoard(chessBoard) {
        setPosition(position);
    }

    Pawn(const Pawn&) = default;
    Pawn& operator=(const Pawn&) = default;
    Pawn(Pawn&&) = default;
    Pawn& operator=(Pawn&&) = default;
    virtual ~Pawn() = default;

    bool isValidMove(const std::string& source, const std::string& destination) override {
        auto& boardMap = m_chessBoard->getBoardMap();
        if (boardMap.find(source) == boardMap.end() || boardMap.find(destination) == boardMap.end() || source == destination) {
            return false;
        }
        if (m_chessBoard->isSquareOccupied(destination)) {
            auto vec = getAttackingSquares();
            if (std::find(vec.begin(), vec.end(), destination) == vec.end()) {
                return false;
            }
        }

        if (m_color == chessPiece::COLOR::WHITE && destination[1] <= source[1] || 
            m_color == chessPiece::COLOR::BLACK && destination[1] >= source[1]) {
                return false;
        }
        return ( 
                 (source[0] == destination[0] && (std::abs(destination[1] - source[1]) == 2) && m_firstMove) || 
                 (source[0] == destination[0] && (std::abs(destination[1] - source[1]) == 1))
               );
    }
    void move(const std::string& destination) override {
        auto& tmpBoardMap = m_chessBoard->getBoardMap();
        std::string source = m_position;
        setPosition(destination);
        *tmpBoardMap[source] = '_';
        if (m_firstMove) {
            m_firstMove = false;
        }
    }

    bool isFirstMove()  const override {
        return m_firstMove;
    }

    COLOR getColor() const override {
        return m_color;
    }

    void setPosition(const std::string& position) override {
        auto& tmpBoardMap = m_chessBoard->getBoardMap();
        if (m_color == COLOR::WHITE) {
            *tmpBoardMap[position] = L'\u265F';
        } else {
            *tmpBoardMap[position] = L'\u2659';
        }
        m_position = position;
    }    

    std::string getPosition() const override {
        return m_position;
    }

    PIECE getPiece() const override {
        return m_piece;
    }

    std::vector<std::string> getAttackingSquares() override {
        std::vector<std::string> vec;
        std::vector<std::string> res;
        std::string pos = m_position;
        if (m_color == COLOR::WHITE) {
            std::string tmp1 = pos; ++tmp1[0]; ++tmp1[1]; vec.push_back(tmp1);
            std::string tmp2 = pos; --tmp2[0]; ++tmp2[1]; vec.push_back(tmp2);
        } else {
            std::string tmp1 = pos; ++tmp1[0]; --tmp1[1]; vec.push_back(tmp1);
            std::string tmp2 = pos; --tmp2[0]; --tmp2[1]; vec.push_back(tmp2);
        }

        auto& boardMap = m_chessBoard->getBoardMap();
        for (auto it = vec.begin(); it != vec.end(); ++it) {
            if (boardMap.find(*it) != boardMap.end()) {
                res.push_back(*it);
            }
        }
        return res;
    }

    // for elimination check, as getting attacking squares in not enough
    // see the explanation in chess.hpp
    std::vector<std::string> getValidMovesWithoutAttack() {
        std::vector<std::string> validMoves;
        if (m_color == chessPiece::COLOR::WHITE) {
            std::string pos = m_position;
            std::string tmp1 = pos; ++tmp1[1]; validMoves.push_back(tmp1);
            if (m_firstMove) {
                std::string tmp2 = pos; tmp2[1] += 2; validMoves.push_back(tmp2);
            }
        } else {
            std::string pos = m_position;
            std::string tmp1 = pos; --tmp1[1]; validMoves.push_back(tmp1);
            if (m_firstMove) {
                std::string tmp2 = pos; tmp2[1] -= 2; validMoves.push_back(tmp2);
            }
        }
        return validMoves;
    }

private:
    chessBoard* m_chessBoard;
    COLOR m_color;
    std::string m_position;
    PIECE m_piece = PIECE::PAWN;
    bool m_firstMove = true;
};

} // CHESS

#endif