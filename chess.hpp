/**
 * @file chess.hpp
 * @author Ashot Petrosyan (ashotpetrossian91@gmail.com)
 * @brief 
 *  Main class controls the game.
 *  Class uses independent classes chessPiece and chessBoard.
 *  chess creats 32 chessPieces and one chessBoard.
 *  Every function is briefly commented, some confusing parts are descibed in details.
 *  Those functions which name describes what it does clearly, have no comments.
 *  If a function for white is commented, for black is skipped.
 *  All moves are saved in moveDB.
 *  Rule of 5 is supported for every class(chessBoard, chessPiece, chess).
 *  chess class suports all chess game rules, including checkMate, enPassant capturing,
 *  automate pawn->queen promotion, stalemate check, 3 last moves repetition.
 * 
 * @version 0.1
 * @date 2022-11-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CHESS_H_
#define CHESS_H_

#include "chessBoard.hpp"
#include "chessPiece.hpp"

namespace CHESS {

class Chess {
public: 
    Chess();
    Chess(const Chess&) = delete;
    Chess& operator=(const Chess&) = delete;
    Chess(Chess&&) = delete;
    Chess& operator=(Chess&&) = delete;
    ~Chess();

    void showBoard() const;
    void setWhitePieces();
    void setBlackPieces();

    chessPiece* getPieceFromPosition(const std::string&) const;
    bool isWhiteKingUnderAttack() const;
    bool isBlackKingUnderAttack() const;
    bool isSquareUnderAttackByWhitePieces(const std::string&) const;
    bool isSquareUnderAttackByBlackPieces(const std::string&) const;
    bool canCastle(chessPiece*, const std::string&, const std::string&);

    bool isValidMove(const std::string&, const std::string&);
    std::vector<chessPiece*> getWhiteKingAttackers();
    std::vector<chessPiece*> getBlackKingAttackers();

    bool whiteKingCheckCanBeEliminated();
    bool blackKingCheckCanBeEliminated();

    bool isWhiteCheckMated();
    bool isBlackCheckMated();
    bool isWhiteStalemate();
    bool isBlackStalemate();
    bool isRepetition() const;
    bool isWhiteMoved(const std::string&);
    bool isBlackMoved(const std::string&);

    void move(const std::string&, const std::string&);
    void performCastle(const std::string&, const std::string&);
    void performPawnCapture(const std::string&, const std::string&);
    void performPromotion(chessPiece*&);

    std::vector<std::pair<std::string, std::string>>& getMoveDB() {
        return m_moveDB;
    }

    std::pair<std::string, std::string> getLastMove() const {
        return m_moveDB[m_moveDB.size() - 1];
    }

    void resetFlags() {
        m_activateCastling = false;
        m_activatePawnCapturing = false;
        m_enPassant = false;
        m_activatePromotion = false;
    }

public:
    chessBoard* m_chessBoard = nullptr;
    std::vector<chessPiece*> whitePieces;
    std::vector<chessPiece*> blackPieces;
    std::vector<std::pair<std::string, std::string>> m_moveDB;

    bool m_activateCastling = false;
    bool m_activatePawnCapturing = false;
    bool m_enPassant = false;
    bool m_activatePromotion = false;
};

Chess::Chess() {
    m_chessBoard = new chessBoard();
    setWhitePieces();
    setBlackPieces();  
}

Chess::~Chess() {
    for (auto& piece : whitePieces) {
        delete piece;
    }
    
    for (auto& piece : blackPieces) {
        delete piece;
    }

    delete m_chessBoard;
}

void Chess::setWhitePieces() {
    chessPiece* wKing = new King(chessPiece::COLOR::WHITE, "e1", m_chessBoard);
    whitePieces.push_back(wKing);
    chessPiece* wQueen = new Queen(chessPiece::COLOR::WHITE, "d1", m_chessBoard);
    whitePieces.push_back(wQueen);
    chessPiece* wBishop1 = new Bishop(chessPiece::COLOR::WHITE, "f1", m_chessBoard);
    whitePieces.push_back(wBishop1);
    chessPiece* wBishop2 = new Bishop(chessPiece::COLOR::WHITE, "c1", m_chessBoard);
    whitePieces.push_back(wBishop2);
    chessPiece* wRook1 = new Rook(chessPiece::COLOR::WHITE, "h1", m_chessBoard);
    whitePieces.push_back(wRook1);
    chessPiece* wRook2 = new Rook(chessPiece::COLOR::WHITE, "a1", m_chessBoard);
    whitePieces.push_back(wRook2);
    chessPiece* wKnight1 = new Knight(chessPiece::COLOR::WHITE, "g1", m_chessBoard);
    whitePieces.push_back(wKnight1);
    chessPiece* wKnight2 = new Knight(chessPiece::COLOR::WHITE, "b1", m_chessBoard);
    whitePieces.push_back(wKnight2);
    chessPiece* wPawn1 = new Pawn(chessPiece::COLOR::WHITE, "a2", m_chessBoard);
    whitePieces.push_back(wPawn1);
    chessPiece* wPawn2 = new Pawn(chessPiece::COLOR::WHITE, "b2", m_chessBoard);
    whitePieces.push_back(wPawn2);
    chessPiece* wPawn3 = new Pawn(chessPiece::COLOR::WHITE, "c2", m_chessBoard);
    whitePieces.push_back(wPawn3);
    chessPiece* wPawn4 = new Pawn(chessPiece::COLOR::WHITE, "d2", m_chessBoard);
    whitePieces.push_back(wPawn4);
    chessPiece* wPawn5 = new Pawn(chessPiece::COLOR::WHITE, "e2", m_chessBoard);
    whitePieces.push_back(wPawn5);
    chessPiece* wPawn6 = new Pawn(chessPiece::COLOR::WHITE, "f2", m_chessBoard);
    whitePieces.push_back(wPawn6);
    chessPiece* wPawn7 = new Pawn(chessPiece::COLOR::WHITE, "g2", m_chessBoard);
    whitePieces.push_back(wPawn7);
    chessPiece* wPawn8 = new Pawn(chessPiece::COLOR::WHITE, "h2", m_chessBoard);
    whitePieces.push_back(wPawn8);
}

void Chess::setBlackPieces() {
    chessPiece* bKing = new King(chessPiece::COLOR::BLACK, "e8", m_chessBoard);
    blackPieces.push_back(bKing);
    chessPiece* bQueen = new Queen(chessPiece::COLOR::BLACK, "d8", m_chessBoard);
    blackPieces.push_back(bQueen);
    chessPiece* bBishop1 = new Bishop(chessPiece::COLOR::BLACK, "f8", m_chessBoard);
    blackPieces.push_back(bBishop1);
    chessPiece* bBishop2 = new Bishop(chessPiece::COLOR::BLACK, "c8", m_chessBoard);
    blackPieces.push_back(bBishop2);
    chessPiece* bRook1 = new Rook(chessPiece::COLOR::BLACK, "h8", m_chessBoard);
    blackPieces.push_back(bRook1);
    chessPiece* bRook2 = new Rook(chessPiece::COLOR::BLACK, "a8", m_chessBoard);
    blackPieces.push_back(bRook2);
    chessPiece* bKnight1 = new Knight(chessPiece::COLOR::BLACK, "b8", m_chessBoard);
    blackPieces.push_back(bKnight1);
    chessPiece* bKnight2 = new Knight(chessPiece::COLOR::BLACK, "g8", m_chessBoard);
    blackPieces.push_back(bKnight2);
    chessPiece* bPawn1 = new Pawn(chessPiece::COLOR::BLACK, "a7", m_chessBoard);
    blackPieces.push_back(bPawn1);
    chessPiece* bPawn2 = new Pawn(chessPiece::COLOR::BLACK, "b7", m_chessBoard);
    blackPieces.push_back(bPawn2);
    chessPiece* bPawn3 = new Pawn(chessPiece::COLOR::BLACK, "c7", m_chessBoard);
    blackPieces.push_back(bPawn3);
    chessPiece* bPawn4 = new Pawn(chessPiece::COLOR::BLACK, "d7", m_chessBoard);
    blackPieces.push_back(bPawn4);
    chessPiece* bPawn5 = new Pawn(chessPiece::COLOR::BLACK, "e7", m_chessBoard);
    blackPieces.push_back(bPawn5);
    chessPiece* bPawn6 = new Pawn(chessPiece::COLOR::BLACK, "f7", m_chessBoard);
    blackPieces.push_back(bPawn6);
    chessPiece* bPawn7 = new Pawn(chessPiece::COLOR::BLACK, "g7", m_chessBoard);
    blackPieces.push_back(bPawn7);
    chessPiece* bPawn8 = new Pawn(chessPiece::COLOR::BLACK, "h7", m_chessBoard);
    blackPieces.push_back(bPawn8);
}

void Chess::showBoard() const {
    m_chessBoard->show();
}

chessPiece* Chess::getPieceFromPosition(const std::string& position) const {
    for (chessPiece* p_chessPiece : whitePieces) {
        if (p_chessPiece->getPosition() == position) {
            return p_chessPiece;
        }
    }
    for (chessPiece* p_chessPiece : blackPieces) {
        if (p_chessPiece->getPosition() == position) {
            return p_chessPiece;
        }
    }
    return nullptr;
}

bool Chess::isWhiteKingUnderAttack() const {
    std::string wKingPos = whitePieces[0]->getPosition(); // index call is safe
    auto iter = blackPieces.begin(); ++iter; // skipping king, as it can't attack another king
    for (; iter != blackPieces.end(); ++iter) {
        for (std::string pos : (*iter)->getAttackingSquares()) {
            if (pos == wKingPos) {
                return true;
            }
        }
    }
    return false;
}

bool Chess::isBlackKingUnderAttack() const {
    std::string bKingPos = blackPieces[0]->getPosition();
    auto iter = whitePieces.begin(); ++iter;
    for (; iter != whitePieces.end(); ++iter) {
        for (std::string pos : (*iter)->getAttackingSquares()) {
            if (pos == bKingPos) {
                return true;
            }
        }
    }
    return false;
}

bool Chess::isSquareUnderAttackByWhitePieces(const std::string& position) const {
    auto iter = whitePieces.begin();
    for (; iter != whitePieces.end(); ++iter) {
        for (std::string pos : (*iter)->getAttackingSquares()) {
            if (pos == position) {
                return true;
            }
        }
    }
    return false;
}
bool Chess::isSquareUnderAttackByBlackPieces(const std::string& position) const {
    auto iter = blackPieces.begin();
    for (; iter != blackPieces.end(); ++iter) {
        for (std::string pos : (*iter)->getAttackingSquares()) {
            if (pos == position) {
                return true;
            }
        }
    }
    return false;
}

// can castle if: 1: no check at the moment, 2: king is on it's first move,
//                3: rook is on the first move, 4: no squares between king and the rook are occupied or under attack
bool Chess::canCastle(chessPiece* p_chessPiece, const std::string& source, const std::string& destination) {
    // dynamic cast is safe as piece type is already checked
    King* p_king = dynamic_cast<King*>(p_chessPiece);
    if (!p_king) return false;
    if (p_king->getColor() == chessPiece::COLOR::WHITE) {
        if (isWhiteKingUnderAttack() || !p_king->isFirstMove()) {
            return false;
        }
        if (destination == "g1") {
            if (m_chessBoard->isSquareOccupied("f1") || m_chessBoard->isSquareOccupied("g1") ||
                isSquareUnderAttackByBlackPieces("f1") || isSquareUnderAttackByBlackPieces("g1") ) {
                return false;
            }
            chessPiece* p_destPiece = getPieceFromPosition("h1");
            if (p_destPiece && p_destPiece->getPiece() == chessPiece::PIECE::ROOK && p_chessPiece->isFirstMove()) {
                return true;
            }
        }

        if (destination == "c1") {
            if (m_chessBoard->isSquareOccupied("d1") || m_chessBoard->isSquareOccupied("c1") || 
                m_chessBoard->isSquareOccupied("b1") || isSquareUnderAttackByBlackPieces("d1") || 
                isSquareUnderAttackByBlackPieces("c1")) {
                    return false;
            }
            chessPiece* p_destPiece = getPieceFromPosition("a1");
            if (p_destPiece && p_destPiece->getPiece() == chessPiece::PIECE::ROOK && p_chessPiece->isFirstMove()) {
                return true;
            }
        }
    }
    
    if (p_chessPiece->getColor() == chessPiece::COLOR::BLACK) {
        if (isBlackKingUnderAttack() || !p_king->isFirstMove()) {
            return false;
        }
        if (destination == "g8") {
            if (m_chessBoard->isSquareOccupied("f8") || m_chessBoard->isSquareOccupied("g8") ||
                isSquareUnderAttackByWhitePieces("f8") || isSquareUnderAttackByWhitePieces("g8")) {
                return false;
            }
            chessPiece* p_destPiece = getPieceFromPosition("h8");
            if (p_destPiece && p_destPiece->getPiece() == chessPiece::PIECE::ROOK && p_chessPiece->isFirstMove()) {
                return true;
            }
        }

        if (destination == "c8") {
            if (m_chessBoard->isSquareOccupied("d8") || m_chessBoard->isSquareOccupied("c8") || 
                m_chessBoard->isSquareOccupied("b8") || isSquareUnderAttackByWhitePieces("d8") || 
                isSquareUnderAttackByWhitePieces("c8")) {
                    return false;
            }
            chessPiece* p_destPiece = getPieceFromPosition("a8");
            if (p_destPiece && p_destPiece->getPiece() == chessPiece::PIECE::ROOK && p_chessPiece->isFirstMove()) {
                return true;
            }
        }
    }

    return false;
}

// move validation, more comments in each line
bool Chess::isValidMove(const std::string& source, const std::string& destination) {
    chessPiece* p_chessPiece = getPieceFromPosition(source);
    if (!p_chessPiece) return false;
    if (!p_chessPiece->isValidMove(source, destination)) { // move validation used from chessPiece for game rule check
        // if the move is not valid for king, check for castling
        if (p_chessPiece->getPiece() == chessPiece::PIECE::KING) {
            m_activateCastling = canCastle(p_chessPiece, source, destination);
            return m_activateCastling;
        }
        // if the move is not valid for a pawn, we check for capturing and enPassant moves.
        if (p_chessPiece->getPiece() == chessPiece::PIECE::PAWN) {
            // if the destination can be found in attackingSquares
            std::vector<std::string> pawnAttackingSquares = p_chessPiece->getAttackingSquares();
            if (std::find(pawnAttackingSquares.begin(), pawnAttackingSquares.end(), destination) == pawnAttackingSquares.end()) return false;
            if (p_chessPiece->getColor() == chessPiece::COLOR::WHITE) {
                for (chessPiece* p_piece : blackPieces) {
                    if (p_piece->getPosition() == destination) {
                        m_activatePawnCapturing = true;
                    }
                }
            } else if (p_chessPiece->getColor() == chessPiece::COLOR::BLACK) {
                for (chessPiece* p_piece : whitePieces) {
                    if (p_piece->getPosition() == destination) {
                        m_activatePawnCapturing = true;
                    }
                }
            }
            // if the pawn can neither move nor capture, check en passant
            if (!m_activatePawnCapturing) {
                std::pair<std::string, std::string> lastMove = getLastMove(); // we must have an exact last move for enPassant
                chessPiece* lastMover = getPieceFromPosition(lastMove.second);
                Pawn* p_pawn = dynamic_cast<Pawn*>(lastMover);
                // if the the last move performer is not a pawn or is not a 2 move forward,
                // or not near the pawn diagonale => there is no en passant
                if (!p_pawn || std::abs(lastMove.first[1] - lastMove.second[1]) != 2 || 
                    std::abs(p_chessPiece->getPosition()[0] - lastMove.second[0]) != 1 ||
                    (p_chessPiece->getPosition()[1] != lastMove.second[1])) return false; // in enPassant case the row is the same for 2 pawns
                m_enPassant = true;
            }
        }
        if (!m_activatePawnCapturing && !m_enPassant) return false;
    }
    // if the move is valid for the pawn but the square is occupied return false
    if (p_chessPiece->getPiece() == chessPiece::PIECE::PAWN && p_chessPiece->isValidMove(source, destination) && m_chessBoard->isSquareOccupied(destination)) {
        return false;
    }
    // if the piece is the king then the destination should not be under attack.
    if (p_chessPiece->getPiece() == chessPiece::PIECE::KING) {
        if (p_chessPiece->getColor() == chessPiece::COLOR::WHITE) {
            if (isSquareUnderAttackByBlackPieces(destination)) {
                return false;
            }
            auto whiteKingAttackers = getWhiteKingAttackers();
            // there can be at most 2 attackers on the king, and if they do attack at that moment, 
            // that means that the next position for the king could be under attack too. (i.e. if the rook from h1 attacks e1 king, then king cannot go to d1)
            // the reason for the additional check with getAttackingPath() function is that
            // getAttackingSquares can't see the squares after the king, which is NOT INcorrect
            for (chessPiece* p_blackAttacker : whiteKingAttackers) {
                for (std::string possibleAttackedSquare : p_blackAttacker->getAttackingPath(destination)) {
                    if (possibleAttackedSquare == destination) {
                        return false;
                    }
                }
            }
        } else {
            if (isSquareUnderAttackByWhitePieces(destination)) {
                return false;
            }
            auto blackKingAttackers = getBlackKingAttackers();
            for (chessPiece* p_whiteAttacker : blackKingAttackers) {
                for (std::string possibleAttackedSquare : p_whiteAttacker->getAttackingPath(destination)) {
                    if (possibleAttackedSquare == destination) {
                        return false;
                    }
                }
            }
        }
    }
    // check if the destination piece(if exists) is with the same color
    chessPiece::COLOR pieceColor = p_chessPiece->getColor();
    chessPiece* p_pieceFromDestination = getPieceFromPosition(destination);
    if (p_pieceFromDestination) {
        chessPiece::COLOR destPieceColor = p_pieceFromDestination->getColor();
        if (pieceColor == destPieceColor) {
            return false;
        }
    }

    // Check all black pieces which can attack the white king after white's move.
    // We skip the black piece from destination, as it can be taken, and there is no need to check it's attacking performance.
    // We consider queen, rook, and bishop, as moving a white piece can open a check for these 3 guys only.
    // Iterating over attacking path(to the king) of each mentioned piece,
    // we check if the entire path is not occupied, and therefore the check can be opened after white's move
    // Also we add a check for the case when moving a white piece can close the check, so if 
    // the destination is on the path, it's ok to move => so the occupation check added for the destination
    // the same is done for the black piece movement.
    if (p_chessPiece->getColor() == chessPiece::COLOR::WHITE) {
        std::string wKingPos = whitePieces[0]->getPosition();
        // if the moving piece is the king, then there is no need to check it's source position
        // for a possible check opening. Instead we should remove the wKingPos check 
        // and reassign it to the destination, as it is the square where the king will be placed.
        if (wKingPos == source) wKingPos = destination;
        for (chessPiece* blackPiece : blackPieces) {
            chessPiece::PIECE blackPieceType = blackPiece->getPiece();
            if (blackPiece != p_pieceFromDestination && (blackPieceType == chessPiece::PIECE::QUEEN ||
                                                         blackPieceType == chessPiece::PIECE::ROOK ||
                                                         blackPieceType == chessPiece::PIECE::BISHOP)) {
                for (std::string squareOnPath : blackPiece->getAttackingPath(wKingPos)) {
                    if (squareOnPath == blackPiece->getPosition() || // skip own square
                        (wKingPos != destination && source == squareOnPath)) continue; // if the moved piece is not the king and the source position is not the square on path, as the piece is not under that position any more
                    if ((m_chessBoard->isSquareOccupied(squareOnPath) || squareOnPath == destination) && squareOnPath != wKingPos) { // if the path can be closed or is already closed for the check and that square is not the king's square
                        break;
                    }
                    if (squareOnPath == wKingPos) {
                        return false; // if any black piece after white's piece move can attack white's king => the move is not valid
                    }
                }
            } else if (blackPiece != p_pieceFromDestination) { // case for knights and pawns
                for (std::string attackedSquare : blackPiece->getAttackingSquares()) {
                    if (attackedSquare == blackPiece->getPosition()) continue;
                    if (attackedSquare == wKingPos) return false;
                }
            }
        }
    } else if (p_chessPiece->getColor() == chessPiece::COLOR::BLACK) {
        std::string bKingPos = blackPieces[0]->getPosition();
        if (bKingPos == source) bKingPos = destination;
        for (chessPiece* whitePiece : whitePieces) {
            chessPiece::PIECE whitePieceType = whitePiece->getPiece();
            if (whitePiece != p_pieceFromDestination && (whitePieceType == chessPiece::PIECE::QUEEN ||
                                                         whitePieceType == chessPiece::PIECE::ROOK) ||
                                                         whitePieceType == chessPiece::PIECE::BISHOP) {
                for (std::string squareOnPath : whitePiece->getAttackingPath(bKingPos)) {
                    if (squareOnPath == whitePiece->getPosition() || 
                        (bKingPos != destination && source == squareOnPath)) continue;
                    if ((m_chessBoard->isSquareOccupied(squareOnPath) || squareOnPath == destination) && squareOnPath != bKingPos) {
                        break;
                    }
                    if (squareOnPath == bKingPos) {
                        return false;
                    }
                }
            } else if (whitePiece != p_pieceFromDestination) {
                for (std::string attackedSquare : whitePiece->getAttackingSquares()) {
                    if (attackedSquare == whitePiece->getPosition()) continue;
                    if (attackedSquare == bKingPos) return false;
                }
            }
        }
    }

    return true;
}

std::vector<chessPiece*> Chess::getWhiteKingAttackers() {
    std::vector<chessPiece*> whiteKingAttackers;
    chessPiece* wKing = whitePieces[0];
    std::string wKingPos = wKing->getPosition();
    auto iter = blackPieces.begin(); ++iter; // skip the king, as king cannot attack the king
    for (; iter != blackPieces.end(); ++iter) { 
        for (std::string s : (*iter)->getAttackingSquares()) {
            if (s == wKingPos) { 
                whiteKingAttackers.push_back(*(iter));
                break; // if we found an attacker then there is no need to look at another attacking squares of the same piece
            }
        }
    }
    return whiteKingAttackers;
}

std::vector<chessPiece*> Chess::getBlackKingAttackers() {
    std::vector<chessPiece*> blackKingAttackers;
    chessPiece* bKing = blackPieces[0];
    std::string bKingPos = bKing->getPosition();
    auto iter = whitePieces.begin(); ++iter;
    for (; iter != whitePieces.end(); ++iter) {
        for (std::string s : (*iter)->getAttackingSquares()) {
            if (s == bKingPos) { 
                blackKingAttackers.push_back(*(iter));
                break;
            }
        }
    }
    return blackKingAttackers;
}

// if the king is under attack, check if the king check can be terminated
// this function call is useless if the king is not under attack
bool Chess::whiteKingCheckCanBeEliminated() {
    chessPiece* wKing = whitePieces[0];
    std::string wkingPos = wKing->getPosition();
    // check if the king can run away
    for (std::string pos : wKing->getAttackingSquares()) {
        if (isValidMove(wkingPos, pos)) {
            return true;
        }
    }

    const auto& whiteKingAttackers = getWhiteKingAttackers();
    if (whiteKingAttackers.empty()) throw std::logic_error("Invalid function use"); // there were no attackers.
    if (whiteKingAttackers.size() > 1) { // if there is a double check => no way to eliminate the attack. And as the king's moves are already checked return false
        return false;
    }

    chessPiece* attacker = whiteKingAttackers[0];
    std::string attackerPosition = attacker->getPosition();
    // getting attacking path of the attacker, as the check can be eliminated by covering the check path, which can be performed only for bishop, rook and queen
    // or be captured if the king has no way to move
    auto attackingPath = attacker->getAttackingPath(wkingPos);
    attackingPath.pop_back(); // we remove the king's square for the upcoming check

    auto iter = whitePieces.begin(); ++iter;
    for (; iter != whitePieces.end(); ++iter) {
        auto attackingSquares = (*iter)->getAttackingSquares();
        if ((*iter)->getPiece() == chessPiece::PIECE::PAWN) {
            Pawn* p_pawn = dynamic_cast<Pawn*>((*iter));
            // only pawn should be check for additional valid moves,
            // as the pawn can not only eat the attacker, but also make a move and block the attacking path
            // for all other pieces the valid moves are attacking squares, which is not true for the pawn
            for (std::string s : p_pawn->getValidMovesWithoutAttack()) {
                attackingSquares.push_back(s);
            }
        }
        for (std::string s : attackingSquares) {
            if (s == attackerPosition && isValidMove((*iter)->getPosition(), s)) { // attacker can be captured
                return true;
            }
            if (!attackingPath.empty() && std::find(attackingPath.begin(), attackingPath.end(), s) != attackingPath.end() && isValidMove((*iter)->getPosition(), s)) { // attacking path can be closed
                return true;
            }
        }
    }

    return false;
}

bool Chess::blackKingCheckCanBeEliminated() {
    chessPiece* bKing = blackPieces[0];
    std::string bkingPos = bKing->getPosition();
    for (std::string pos : bKing->getAttackingSquares()) {
        if (isValidMove(bkingPos, pos)) {
            return true;
        }
    }

    const auto& blackKingAttackers = getBlackKingAttackers();
    if (blackKingAttackers.empty()) throw std::logic_error("Invalid function use"); 
    if (blackKingAttackers.size() > 1) {
        return false;
    }

    chessPiece* attacker = blackKingAttackers[0];
    std::string attackerPosition = attacker->getPosition();
    auto attackingPath = attacker->getAttackingPath(bkingPos);
    attackingPath.pop_back();

    auto iter = blackPieces.begin(); ++iter;
    for (; iter != blackPieces.end(); ++iter) {
        auto attackingSquares = (*iter)->getAttackingSquares();
        if ((*iter)->getPiece() == chessPiece::PIECE::PAWN) {
            Pawn* p_pawn = dynamic_cast<Pawn*>((*iter));
            for (std::string s : p_pawn->getValidMovesWithoutAttack()) {
                attackingSquares.push_back(s);
            }
        }
        for (std::string s : attackingSquares) {
            if (s == attackerPosition && isValidMove((*iter)->getPosition(), s)) {
                return true;
            }
            if (!attackingPath.empty() && std::find(attackingPath.begin(), attackingPath.end(), s) != attackingPath.end() && isValidMove((*iter)->getPosition(), s)) {
                return true;
            }
        }
    }

    return false;
}

bool Chess::isWhiteCheckMated() {
    return (isWhiteKingUnderAttack() && !whiteKingCheckCanBeEliminated());
}

bool Chess::isBlackCheckMated() {
    return (isBlackKingUnderAttack() && !blackKingCheckCanBeEliminated());
}

void Chess::performCastle(const std::string& source, const std::string& destination) {
    chessPiece* p_chessPiece = getPieceFromPosition(source); // guarantee that this function will be called after Piece type check
    if (p_chessPiece->getColor() == chessPiece::COLOR::WHITE) {
        if (destination == "g1") {            
            chessPiece* p_destPiece = getPieceFromPosition("h1");
            p_chessPiece->move("g1");
            p_destPiece->move("f1");
        }

        if (destination == "c1") {
            chessPiece* p_destPiece = getPieceFromPosition("a1");
            p_chessPiece->move("c1");
            p_destPiece->move("d1");
        }
    }
    
    if (p_chessPiece->getColor() == chessPiece::COLOR::BLACK) {
        if (destination == "g8") {
            chessPiece* p_destPiece = getPieceFromPosition("h8");
            p_chessPiece->move("g8");
            p_destPiece->move("f8");
        }

        if (destination == "c8") {
            chessPiece* p_destPiece = getPieceFromPosition("a8");
            p_chessPiece->move("c8");
            p_destPiece->move("d8");
        }
    }

    m_activateCastling = false;
}

void Chess::performPawnCapture(const std::string& source, const std::string& destination) {
    chessPiece* p_chessPiece = getPieceFromPosition(source);
    if (m_enPassant) {
        std::pair<std::string, std::string> lastMove = getLastMove();
        chessPiece* lastMover = getPieceFromPosition(lastMove.second);
        std::string destSquare; 
        destSquare.push_back(lastMove.second[0]);
        destSquare.push_back( (lastMove.second[1] + lastMove.first[1]) / 2);
        p_chessPiece->move(destSquare);
        auto iter1 = std::find(whitePieces.begin(), whitePieces.end(), lastMover);
        auto iter2 = std::find(blackPieces.begin(), blackPieces.end(), lastMover);
        if (iter1 != whitePieces.end()) {
            delete (*iter1);
            whitePieces.erase(iter1);
            *m_chessBoard->getBoardMap()[lastMove.second] = '_'; // as the destination is not the position of the taken piece, we reset the taken pawn position to _
        } else if (iter2 != blackPieces.end()) {
            delete (*iter2);
            blackPieces.erase(iter2);
            *m_chessBoard->getBoardMap()[lastMove.second] = '_';
        } else {
            throw std::logic_error("En passant failure\n");
        }
        m_enPassant = false;
        return;
    }
    if (m_activatePawnCapturing) {
        chessPiece* p_pieceFromDestination = getPieceFromPosition(destination);
        p_chessPiece->move(destination);
        auto iter1 = std::find(whitePieces.begin(), whitePieces.end(), p_pieceFromDestination);
        auto iter2 = std::find(blackPieces.begin(), blackPieces.end(), p_pieceFromDestination);
        if (iter1 != whitePieces.end()) {
            delete (*iter1);
            whitePieces.erase(iter1);
        } else if (iter2 != blackPieces.end()) {
            delete (*iter2);
            blackPieces.erase(iter2);
        } else {
            throw std::logic_error("Pawn capturing failure\n");
        }
        m_activatePawnCapturing = false;
        return;
    }
}

void Chess::performPromotion(chessPiece*& p_chessPiece) {
    std::string pos = p_chessPiece->getPosition();
    if (p_chessPiece->getColor() == chessPiece::COLOR::WHITE && pos[1] == '8') {
        auto iter = std::find(whitePieces.begin(), whitePieces.end(), p_chessPiece);
        if (iter != whitePieces.end()) {
            delete (*iter);
            whitePieces.erase(iter);
            Queen* newQueen = new Queen(chessPiece::COLOR::WHITE, pos, m_chessBoard);
            whitePieces.push_back(newQueen);
        } else {
            throw std::logic_error("Couldn't find the pawn to promote!\n");
        }
    } else if (p_chessPiece->getColor() == chessPiece::COLOR::BLACK && pos[1] == '1') {
        auto iter = std::find(blackPieces.begin(), blackPieces.end(), p_chessPiece);
        if (iter != blackPieces.end()) {
            delete (*iter);
            blackPieces.erase(iter);
            Queen* newQueen = new Queen(chessPiece::COLOR::BLACK, pos, m_chessBoard);
            blackPieces.push_back(newQueen);
        } else {
            throw std::logic_error("Couldn't find the pawn to promote!\n");
        }
    }
}

// this function DOES NOT check for validation, responsibility is on the Game object
void Chess::move(const std::string& source, const std::string& destination) {
    chessPiece* p_chessPiece = getPieceFromPosition(source);
    if (p_chessPiece->getPiece() == chessPiece::PIECE::KING) {
        if (m_activateCastling) {
            performCastle(source, destination);
            return;
        }
    }
    if (p_chessPiece->getPiece() == chessPiece::PIECE::PAWN) {
        if (destination[1] == '8' || destination[1] == '1') {
            m_activatePromotion = true;
        }
        if (m_activatePawnCapturing || m_enPassant) {
            performPawnCapture(source, destination);
            if (m_activatePromotion) performPromotion(p_chessPiece);
            return;
        }
    }
    chessPiece* p_pieceFromDestination = getPieceFromPosition(destination);
    p_chessPiece->move(destination);
    if (p_pieceFromDestination) {
        auto iter1 = std::find(whitePieces.begin(), whitePieces.end(), p_pieceFromDestination);
        auto iter2 = std::find(blackPieces.begin(), blackPieces.end(), p_pieceFromDestination);
        if (iter1 != whitePieces.end()) {
            delete (*iter1);
            whitePieces.erase(iter1);
        } else if (iter2 != blackPieces.end()) {
            delete (*iter2);
            blackPieces.erase(iter2);
        } else {
            throw std::logic_error("Piece capturing failure\n");
        }
    }
    if (m_activatePromotion) performPromotion(p_chessPiece);
    m_moveDB.push_back({source, destination});
}

bool Chess::isWhiteMoved(const std::string& source) {
    return (getPieceFromPosition(source)->getColor() == chessPiece::COLOR::WHITE);
}

bool Chess::isBlackMoved(const std::string& source) {
    return (getPieceFromPosition(source)->getColor() == chessPiece::COLOR::BLACK);
}

bool Chess::isWhiteStalemate() {
    bool flag = true;
    if (isWhiteKingUnderAttack()) return false;
    for (chessPiece* p_piece : whitePieces) {
        std::string sourcePos = p_piece->getPosition();
        std::vector<std::string> attackingSquares = p_piece->getAttackingSquares();
        if (p_piece->getPiece() == chessPiece::PIECE::PAWN) {
            Pawn* p_pawn = dynamic_cast<Pawn*>(p_piece);
            if (p_pawn) {
                for (std::string s : p_pawn->getValidMovesWithoutAttack()) {
                    attackingSquares.push_back(s);
                }
            }
        }
        for (std::string dest : attackingSquares) {
            if (isValidMove(sourcePos, dest)) {
                flag = false;
            }
            if (!flag) return false;
        }
    }
    return flag;
}

bool Chess::isBlackStalemate() {
    bool flag = true;
    if (isBlackKingUnderAttack()) return false;
    for (chessPiece* p_piece : blackPieces) {
        std::string sourcePos = p_piece->getPosition();
        std::vector<std::string> attackingSquares = p_piece->getAttackingSquares();
        if (p_piece->getPiece() == chessPiece::PIECE::PAWN) {
            Pawn* p_pawn = dynamic_cast<Pawn*>(p_piece);
            if (p_pawn) {
                for (std::string s : p_pawn->getValidMovesWithoutAttack()) {
                    attackingSquares.push_back(s);
                }
            }
        }
        for (std::string dest : attackingSquares) {
            if (isValidMove(sourcePos, dest)) {
                flag = false;
            }
            if (!flag) return false;
        }
    }
    return flag;
}


bool Chess::isRepetition() const {
    std::vector<std::pair<std::string, std::string>> lastThreeMoves;
    int count = 12;
    for (int i = m_moveDB.size() - 1; i >= 0 && count; --i) {
        lastThreeMoves.push_back(m_moveDB[i]);
        --count;
    }
    if (count) return false;
    if (lastThreeMoves[0] == lastThreeMoves[4] && lastThreeMoves[4] == lastThreeMoves[8] &&
        lastThreeMoves[2] == lastThreeMoves[6] && lastThreeMoves[6] == lastThreeMoves[10] &&
        lastThreeMoves[1] == lastThreeMoves[5] && lastThreeMoves[5] == lastThreeMoves[9] &&
        lastThreeMoves[3] == lastThreeMoves[7] && lastThreeMoves[7] == lastThreeMoves[11]) {
            return true;
    }
    return false;
}

} // CHESS

#endif