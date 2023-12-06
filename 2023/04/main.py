#!/usr/bin/env python3

import typing

class Card:
    def __init__(self,cardNumber:int, winningNumbers:typing.List[int], playingNumbers:typing.List[int]):
        self.cardNumber:int = cardNumber
        self.winningNumbers:typing.List[int] = [ int(w) for w in winningNumbers ]
        self.playingNumbers:typing.List[int] = [ int(p) for p in playingNumbers ]
        self.numWins = 0
        self.numCopies = 0

    def print(self):
        print(f"Card Number {self.cardNumber:3d} : {self.winningNumbers} | {self.playingNumbers} | {self.numWins} | {self.numCopies}")


def getData(filename:str) -> typing.List[Card]:
    cards:typing.List[Card] = list()
    with open(filename,'r') as f:
        for l in f:
            line = l.strip()
            cardNumber = int(line.split(':')[0].split(' ')[-1])
            numbers = line.split(':')[1]
            winningNumbers = numbers.split('|')[0].strip().split()
            playingNumbers = numbers.split('|')[1].strip().split()
            cards.append(Card(cardNumber,winningNumbers, playingNumbers))
    return cards

def part1(cards:typing.List[Card]) -> int:
    score = 0
    for card in cards:
        numWins = 0
        for w in card.winningNumbers:
            if w in card.playingNumbers:
                numWins += 1
        points = int(2**(numWins-1))
        score += points
    return score

def part2(cards:typing.List[Card]) -> int:
    for card in cards:
        numWins = 0
        for w in card.winningNumbers:
            if w in card.playingNumbers:
                numWins += 1
        card.numWins = numWins
    numCards = len(cards)

    score = numCards
    for k in range(numCards):
        if cards[k].numWins == 0:
            continue
        for j in range(cards[k].numWins):
            k1 = min(cards[k].cardNumber + j, numCards)
            cards[k1].numCopies += (1+cards[k].numCopies)
            score += (1+cards[k].numCopies)

    for card in cards:
        card.print()
    return score


def main():
    # data = getData('example.dat')
    data = getData('input.dat')
    # answer = part1(data)
    answer = part2(data)
    print(answer)

if __name__ == "__main__":
    main()
