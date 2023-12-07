#!/usr/bin/env python3

from __future__ import annotations
from functools import cmp_to_key
import typing
import tqdm

# Five of a kind, where all five cards have the same label: AAAAA -> 7
# Four of a kind, where four cards have the same label and one card has a different label: AA8AA -> 6
# Full house, where three cards have the same label, and the remaining two cards share a different label: 23332 -> 5
# Three of a kind, where three cards have the same label, and the remaining two cards are each different from any other card in the hand: TTT98 -> 4
# Two pair, where two cards share one label, two other cards share a second label, and the remaining card has a third label: 23432 -> 3
# One pair, where two cards share one label, and the other three cards have a different label from the pair and each other: A23A4 -> 2
# High card, where all cards' labels are distinct: 23456 -> 1

FIVE_OF_A_KIND=7
FOUR_OF_A_KIND=6
FULL_HOUSE=5
THREE_OF_A_KIND=4
TWO_PAIR=3
ONE_PAIR=2
HIGH_CARD=1

Card2Num = {
    'A':14,
    'K':13,
    'Q':12,
    'J':11,
    'T':10,
    '9':9,
    '8':8,
    '7':7,
    '6':6,
    '5':5,
    '4':4,
    '3':3,
    '2':2,
}

Card2Num2 = {
    'A':14,
    'K':13,
    'Q':12,
    'J':1,
    'T':10,
    '9':9,
    '8':8,
    '7':7,
    '6':6,
    '5':5,
    '4':4,
    '3':3,
    '2':2,
}

class CamelCard:
    def __init__(self, hand:str, bid:int):
        self.hand:str = hand
        self.bid:int = bid
        self.rank:int = -1
        self.handType:int = -1
        self.highNumber:int = 0
        # self.getHandType()
        self.getHandTypeWithJokers()
        # self.getHighNumber()
        self.getHighNumberWithJokers()

    def getHighNumber(self):
        if self.handType < 0:
            print("ERROR: Hand Type was not found...")
            print(self.hand)
            exit()
        N = len(self.hand)
        self.highNumber = self.handType * 16**(N)
        for k in range(N):
            self.highNumber += Card2Num[self.hand[k]]*16**(N-k-1)

    def getHighNumberWithJokers(self):
        if self.handType < 0:
            print("ERROR: Hand Type was not found...")
            print(self.hand)
            exit()
        N = len(self.hand)
        self.highNumber = self.handType * 16**(N)
        for k in range(N):
            self.highNumber += Card2Num2[self.hand[k]]*16**(N-k-1)

    def getHandTypeWithJokers(self):
        if 'J' not in self.hand:
            self.getHandType()
            return

        allOptions = ["A","K","Q","T","9","8","7","6","5","4","3","2"]
        bestType = 0
        oldHand = self.hand
        ranges = []
        for h in self.hand:
            if h == 'J':
                ranges.append(allOptions)
            else:
                ranges.append([h])

        self.hand = list(self.hand)
        for k1 in ranges[0]:
            if oldHand[0] == 'J':
                self.hand[0]=k1
            for k2 in ranges[1]:
                if oldHand[1] == 'J':
                    self.hand[1]=k2
                for k3 in ranges[2]:
                    if oldHand[2] == 'J':
                        self.hand[2]=k3
                    for k4 in ranges[3]:
                        if oldHand[3] == 'J':
                            self.hand[3]=k4
                        for k5 in ranges[4]:
                            if oldHand[4] == 'J':
                                self.hand[4]=k5
                            self.hand = ''.join([k1,k2,k3,k4,k5])
                            self.getHandType()
                            if self.handType > bestType:
                                bestType = self.handType
                            self.hand = list(oldHand)
        self.handType = bestType
        self.hand = oldHand

    def getHandType(self):
        numCards = {'A':0,'K':0,'Q':0,'J':0,'T':0,'9':0,'8':0,'7':0,'6':0,'5':0,'4':0,'3':0,'2':0}
        for card in self.hand:
            numCards[card] += 1

        # Check hands types
        have5=False
        have4=False
        have3=False
        have2=False
        numPairs = 0
        for k in numCards:
            if numCards[k]==2:
                have2 = True
                numPairs+=1
            elif numCards[k]==3:
                have3 = True
            elif numCards[k]==4:
                have4=True
            elif numCards[k]==5:
                have5=True

        if have5:
            self.handType = FIVE_OF_A_KIND
        elif have4:
            self.handType = FOUR_OF_A_KIND
        elif have2 and have3:
            self.handType = FULL_HOUSE
        elif have3:
            self.handType = THREE_OF_A_KIND
        elif have2 and numPairs==2:
            self.handType = TWO_PAIR
        elif have2:
            self.handType = ONE_PAIR
        else:
            self.handType = HIGH_CARD

    @staticmethod
    def sortKey(self:CamelCard):
        return self.highNumber

    @staticmethod
    def compare(self:CamelCard, other:CamelCard):
        if self.handType != other.handType:
            if self.handType < other.handType:
                return -1
            elif self.handType > other.handType:
                return 1
            else:
                return 0

        if self.highNumber < other.highNumber:
            return -1
        elif self.highNumber > other.highNumber:
            return 1
        else:
            return 0

def getData(filename:str) -> typing.List[CamelCard]:
    cards:typing.List[CamelCard] = list()
    with open(filename, 'r') as f:
        numLines = len(f.readlines())
    with open(filename, 'r') as f:
        for l in tqdm.tqdm(f, "Getting Data", numLines):
            line = l.strip()
            handBid = line.split()
            cards.append(
                CamelCard(handBid[0], int(handBid[1]))
            )
    return cards

def doPart_1(data:typing.List[CamelCard]) -> int :
    answer = 0
    # for d in data:
    #     print(d.hand)
    print('---------')
    # data.sort(key=cmp_to_key(CamelCard.compare))
    # data.sort(key=CamelCard.sortKey)
    data = sorted(data,key=CamelCard.sortKey)
    # for d in data:
    #     print(d.hand, d.highNumber)
    for k in range(len(data)):
        answer += data[k].bid*(k+1)
    return answer

def doPart_2(data):
    return 0

def main():
    # filename = 'example.dat'
    filename = 'input.dat'
    data = getData(filename)
    answer = doPart_1(data)
    print(answer)
    answer = doPart_2(data)
    print(answer)

if __name__ == "__main__":
    main()
